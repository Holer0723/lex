%{
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <vector>
#include <fstream>
#include "SymbolTable.h"
#include "CodeEmitter.h"

using namespace std;


namespace dbg {

    /* ------ 內部遞迴展開 ------ */
    inline void print_one() {}                // 終止遞迴 (零參)

    template<typename First, typename... Rest>
    void print_one(const First& v, const Rest&... rest)
    {
        std::cout << v;
        if (sizeof...(rest)) std::cout << ' ';  // 只有還有參數時才印空格
        print_one(rest...);
    }

    /* ------ 對外介面 ------ */
    template<typename... Args>
    void debug(const Args&... args)
    {
        std::cout << "╔════════ DEBUG BEGIN ════════\n";
        std::cout.setf(std::ios::boolalpha);   // 讓 bool 印 true / false
        print_one(args...);
        std::cout << "\n╚════════ DEBUG  END  ════════\n";
        std::cout.flush();
    }
} 

/* ---------------------------------------------------------------
 *  Structures shared between semantic actions
 * ---------------------------------------------------------------*/
struct Pending_var {
    string        id;     // variable name waiting for insertion
    ExtendedType* type;   // fully qualified type (might include dims)
};

extern FILE* yyin;          // input stream set by main()
SymbolTable symtab;         // global symbol table (manages scope stack)
extern int linenum;         // current line number (set by lexer)               

void yyerror(const string& msg);
int yylex(void);

/* ------------------------------------------------------------------
 *  Temporary containers used while reducing grammar productions
 * ------------------------------------------------------------------*/
vector<Pending_var>   decl_vars;       // vars collected inside a decl list
vector<Pending_var>   delay_symbols;   // params & call args, resolved later
vector<ExtendedType*> type_pool;       // heap objects to free on exit

/* ------------------------------------------------------------------
 *  Helper functions for semantic analysis
 * ------------------------------------------------------------------*/
static void semantic_error(const string& msg, const string& id) {
    cerr << "SEMANTIC(" << linenum << "): " << msg << ' ' << id << '\n';
    for (auto& ptr : type_pool) delete ptr;
    exit(-1);
}

/*  Test whether a value of type src can be stored in dst. */
static bool type_compatible(const ExtendedType* dst, const ExtendedType* src) {
    if (dst->t == src->t)                                                    return true;
    if (dst->t == Type::STRING || src->t == Type::STRING)                      return false;
    if (dst->t == Type::FLOAT  && src->t == Type::INT)                         return true;
    if (dst->t == Type::INT    && src->t == Type::FLOAT)                       return true;
    if ((dst->t == Type::INT || dst->t == Type::FLOAT) && src->t == Type::BOOL) return true;
    return false;
}

/*  Usual arithmetic promotions (INT+FLOAT → FLOAT, etc.). */
static ExtendedType* promote(const ExtendedType* a, const ExtendedType* b) {
    if (a->t == Type::ERROR || b->t == Type::ERROR)   return new ExtendedType{Type::ERROR, {}};
    if (a->t == Type::STRING || b->t == Type::STRING) return new ExtendedType{Type::ERROR, {}};
    if (a->t == Type::FLOAT  || b->t == Type::FLOAT)  return new ExtendedType{Type::FLOAT, {}};
    return new ExtendedType{Type::INT, {}};
}

/*  main() must be declared as "void main()" in this language. */
static bool invalid_main_function(Type t, string func_id) {
    return func_id == "main" && t != Type::VOID;
}

/*  Track the return type of the function currently being parsed. */
static ExtendedType* current_func_type = new ExtendedType{Type::ERROR, {}};
static bool has_main_func = false;
CodeEmitter emitter;
int symbolIndex = 0;
%}

/* ------------------------------------------------------------------
 *  Bison declarations (tokens, types, precedences)
 * ------------------------------------------------------------------*/
%union {
    int            ival;
    float          fval;
    char*          sval;
    Kind           kval;
    ExtendedType*  tval;
}

%token  DO WHILE FOR FOREACH CONTINUE BREAK RETURN
%token  CONST IF ELSE SWITCH CASE DEFAULT 
%token  PRINT PRINTLN READ
%token  TVOID EXTERN
%token  FCONST TDOUBLE TCHAR
%token  EQ NE LE GE AND OR

%token <sval> ID
%token <fval> TFLOAT
%token <ival> TBOOL
%token <ival> TINT
%token <ival> ICONST
%token <sval> TSTRING
%token <sval> SCONST
%token <ival> BCONST


/*  Operator precedence and associativity table. */
%left   OR
%left   AND
%right  '!'
%nonassoc EQ NE '<' '>' LE GE
%left   '+' '-'
%left   '*' '/' '%'
%nonassoc UMINUS INC DEC

/*  Non‑terminal semantic types. */
%type <tval>  simple_or_block_stmt simple_stmt if_stmt while_stmt for_stmt return_stmt foreach_stmt
%type <tval>  data_type expr block
%type <tval>  var_decl const_decl
%type <tval>  block_item_list block_item block_decl statement
%type <tval>  array array_block expr_array_block
%type <tval>  arg_list_opt arg_list
%type <sval>  identifier


/* ───────── start symbol ───────── */
%start program

%%                      

program
    : decl_list 
    ;

/* --------------------------------------------------
 *  Declarations (global or within a block)
 * --------------------------------------------------*/
decl_list
    : /* empty */
    | decl_list declaration
    ;

declaration
    : const_decl
    | var_decl
    | func_decl
    ;

/* ───────── Constant Declarations ───────── */
const_decl
    : CONST data_type identifier '=' expr ';' {
        // 1) enforce uniqueness
        if (!symtab.insert($3, Kind::K_CONST, *$2, {}))
            semantic_error("redeclared const", $3);
        // 2) type checking
        if (!type_compatible($2, $5))
            semantic_error("const type mismatch", $3);
        // 3) forbid void constants
        if ($2->t == Type::VOID) 
            semantic_error("cannot declare a void type constant", $3);

        Symbol* sym = symtab.lookup($3);
        $$ = new ExtendedType{sym->type.t, {}};
        sym->type.lit = $5->lit;
        $$->code += $5->code;
        bool inGlobal = symtab.depth() == 1;
        if (inGlobal) {
            emitter.declareField($2, $3, CodeEmitter::getLiteralOf($5->lit));
        } else {         
            int idx = symbolIndex++;
            sym->index = idx;
            int val;
            switch(sym->type.lit.tag) {
                case Literal::INT: val = sym->type.lit.ival; break;
                case Literal::BOOL: val = sym->type.lit.bval; break;
                case Literal::STR: semantic_error("Unexpected string", ""); break;
                default: semantic_error("Unexpected error", ""); break;
            }
            $$->code += emitter.emitStoreInt(idx);
        }
    }
    ;


/* ───────── variable declaration ───────── */
var_decl
    : data_type init_id_list ';' { 
        if ($1->t == Type::VOID)
            semantic_error("cannot decalre a void type variable", "");

        bool inGlobal = symtab.depth() == 1;
        
        // Iterate over each variable collected in init_id_list
        for (auto& var : decl_vars) {
            string name = var.id;
            ExtendedType* type = var.type;

            /* Reject if same identifier already exists as function */
            Symbol* sym = symtab.lookup(name);
            if (sym) 
                if (sym->kind == Kind::K_FUNC)
                    semantic_error("variable name conflicts with existing function", name);
            
            /* Insert into symbol table */
            if (!symtab.insert(name, Kind::K_VAR, ExtendedType{$1->t, type->dims}, {}))
                semantic_error("redeclared var", name);
            
            /* Check initializer / array dims consistency */
            if (type->t != Type::ERROR && !type_compatible(type, $1))
                semantic_error("type mismatch in init", "");

            if (inGlobal) {
                emitter.declareField($1, name, CodeEmitter::getLiteralOf(type->lit));
            } else {                                              
                int idx = symbolIndex++;
                Symbol* sym = symtab.lookup(name);
                sym->index = idx;
                if (type->lit.tag != Literal::NONE) {
                    sym->type.lit.tag = type->lit.tag;
                    switch(type->lit.tag) {
                        case Literal::INT: sym->type.lit.ival = type->lit.ival; break;
                        case Literal::BOOL: sym->type.lit.bval = type->lit.bval; break;
                        case Literal::STR: semantic_error("Unexpected string", ""); break;
                        default: semantic_error("Unexpected error", ""); break;
                    }
                    $$->code += type->code;
                    $$->code += emitter.emitStoreInt(idx);
                } else {
                    if (type->code.empty())
                        $$->code += emitter.emitLoadConstantInt(0);
                    else 
                        $$->code += type->code;
                    $$->code += emitter.emitStoreInt(idx);
                }
            }
        }
        decl_vars.clear();
    }
    ;

/*  Build a comma‑separated list of variables with optional
 *  initializers or array dimensions.
 */
init_id_list
    : init_id
    | init_id ',' init_id_list 
    ;

init_id
    : identifier array_block  /* plain declaration, possibly array */
      { decl_vars.push_back({$1, $2}); }
    | identifier '=' expr {   /* declaration with initializer */
        ExtendedType* nt = new ExtendedType{$3->t, {}};
        nt->lit = $3->lit;
        nt->code = $3->code;
        type_pool.push_back(nt);
        decl_vars.push_back({$1, nt}); 
    }
    ;

/*  Convert nested "[ICONST]" chains into an ExtendedType
 *  with the corresponding list<int> dims.
 */
array_block
    : /* empty */ { 
        $$ = new ExtendedType{Type::ERROR, {}};
    }
    | '[' ICONST ']' array_block { /* prepend current dim */
        if ($2 < 1)
            semantic_error("array dimension cannot less than 1", "");
        vector<int> dims;
        dims.push_back($2);
        for (auto& d : $4->dims)
            dims.push_back(d);
        ExtendedType* nt = new ExtendedType{Type::ERROR, dims};
        type_pool.push_back(nt);
        $$ = nt;
    }
    ;

/* ───────── function declaration ───────── */
func_decl
    : data_type identifier {
        if (!symtab.insert($2, Kind::K_FUNC, *$1, {})) 
            semantic_error("redeclared func", $2);
        if (invalid_main_function($1->t, $2)) 
            semantic_error("invalid main function type:", SymbolTable::type2Str($1->t));
        current_func_type = $1;  // remember return type
        symbolIndex = 0;
    } '(' opt_param_list ')' {
        // Post‑process parameters stored in delay_symbols
        if (string($2) == "main" && !delay_symbols.empty())
            semantic_error("main function must not take parameters", "");
        

        Symbol *sym = symtab.lookup($2);
        if (!sym) dbg::debug("dsddd");
        for (auto& p : delay_symbols) 
            sym->params.push_back(*p.type);

        vector<string> param_type;
        for (auto& p : delay_symbols) {
            param_type.push_back(SymbolTable::type2Str((*p.type).t));
        }

        if (string($2) == "main") {
            has_main_func = true;
            emitter.beginMethod($1, $2, param_type, true);
        } else {
            emitter.beginMethod($1, $2, param_type, false);
        }

    } block { /* function body */
        current_func_type = new ExtendedType{Type::ERROR, {}};;
        emitter.emit($<tval>8->code);
        emitter.endMethod();
    }
    ;

opt_param_list 
    : /* empty */ 
    | param_list 
    ;

param_list
    : param
    | param_list ',' param
    ;

/*  Parameter becomes a pending variable – it will be installed
 *  into the function scope at the beginning of the block.
 */
param
    : data_type identifier array_block { 
        if ($1->t == Type::VOID) 
            semantic_error("function parameter cannot be of void type", $2);
        ExtendedType* nt = new ExtendedType{$1->t, $3->dims};
        delay_symbols.push_back({$2, nt});
        type_pool.push_back(nt);
    }
    ;

/* --------------------------------------------------
 *  Blocks & Statements (push / pop new scope)
 * --------------------------------------------------*/
block
    : '{' { 
        $<tval>$ = new ExtendedType{Type::ERROR, {}};
        symtab.pushScope(); 
        // add parameters collected in func_decl
        for (size_t i = 0; i < delay_symbols.size(); ++i) {
            auto& symbol = delay_symbols[i];
            int idx = symbolIndex++;
            if (!symtab.insert(symbol.id, Kind::K_VAR, *symbol.type, {}))
                semantic_error("redeclared param", symbol.id);
            Symbol* sym = symtab.lookup(symbol.id);
            sym->index = idx;
        }
        delay_symbols.clear();
    } block_item_list '}' { 
        $$ = new ExtendedType{Type::ERROR, {}};
        $$->code += $<tval>2->code + $<tval>3->code;
        symtab.popScope(); 
    } 
    ;

block_item_list
    : /* empty */ { 
        $$ = new ExtendedType{Type::ERROR, {}};
        $$->code += ""; 
    }
    | block_item block_item_list { 
        $$ = new ExtendedType{Type::ERROR, {}};
        $$->code += $1->code + $2->code; 
    }
    ;

block_item
    : block_decl { 
        $$ = new ExtendedType{Type::ERROR, {}};
        $$->code += $1->code; 
    }
    | statement { 
        $$ = new ExtendedType{Type::ERROR, {}};
        $$->code += $1->code; 
    }
    ;

block_decl
    : const_decl { 
        $$ = new ExtendedType{Type::ERROR, {}};
        $$->code += $1->code; 
    }
    | var_decl { 
        $$ = new ExtendedType{Type::ERROR, {}};
        $$->code += $1->code; 
    }
    ;

/* ───────── Statement ───────── */
statement
    : simple_stmt ';' {
        $$ = new ExtendedType{Type::ERROR, {}};
        $$->code += $1->code; 
    }
    | if_stmt { 
        $$ = new ExtendedType{Type::ERROR, {}};
        $$->code += $1->code; 
    }
    | while_stmt { 
        $$ = new ExtendedType{Type::ERROR, {}};
        $$->code += $1->code; 
    }
    | for_stmt { 
        $$ = new ExtendedType{Type::ERROR, {}};
        $$->code += $1->code; 
    }
    | foreach_stmt { 
        $$ = new ExtendedType{Type::ERROR, {}};
        $$->code += $1->code;
    }
    | return_stmt  { 
        $$ = new ExtendedType{Type::ERROR, {}};
        $$->code += $1->code; 
    }
    | block { 
        $$ = new ExtendedType{Type::ERROR, {}};
        $$->code += $1->code; 
    }
    ;

/*  Either a single statement or a nested block (for if/while bodies). */
simple_or_block_stmt
    : simple_stmt ';' { 
        $$ = new ExtendedType{Type::ERROR, {}};
        $$->code += $1->code; 
    }
    | block { 
        $$ = new ExtendedType{Type::ERROR, {}};
        $$->code += $1->code; 
    }
    ;

simple_stmt
    : identifier '=' expr {
        Symbol* sym = symtab.lookup($1);
        if (!sym) 
            semantic_error("undeclared id",$1);
        if (sym->kind == Kind::K_FUNC)
            semantic_error("cannot assign to a function", $1);
        if ($3->t == Type::VOID)
            semantic_error("cannot assign result of void function", "");
        if (sym->kind == Kind::K_CONST)
            semantic_error("cannot modify constant", $1);
        if (!type_compatible(&sym->type, $3)) 
            semantic_error("type mismatch", $1);
        if (!sym->type.dims.empty())
            semantic_error("cannot assign to an array without specify the dimension", $1);

        $$ = new ExtendedType{Type::ERROR, {}};
        $$->code += $3->code;
        if (sym->index == -1) {
            $$->code += emitter.emitPutStatic(sym->type, $1);
        } else {
            $$->code += emitter.emitStoreInt(sym->index);
        }
    }
    | expr {
        $$ = new ExtendedType{Type::ERROR, {}};
    }
    | array '=' expr {
        if (!type_compatible($1, $3))
            semantic_error("type mismatch", "");
    }
    | identifier INC {
        Symbol* sym = symtab.lookup($1);
        if (!sym) 
            semantic_error("undeclared id",$1);
        if (sym->kind == Kind::K_FUNC)
            semantic_error("invalid ++ on function", $1);
        if (sym->kind == Kind::K_CONST)
            semantic_error("invalid ++ on constant", $1);
        if (sym->type.t != Type::INT && sym->type.t != Type::FLOAT) 
            semantic_error("++ requires numeric operand", $1);
        
        $$ = new ExtendedType{Type::ERROR, {}};
        if (sym->index == -1) {
            $$->code += emitter.emitGetStaticInt($1);
        } else {
            $$->code += emitter.emitLoadInt(sym->index);
        }
        $$->code += emitter.emitLoadConstantInt(1);
        $$->code += emitter.emitIADD();
        if (sym->index == -1) {
            $$->code += emitter.emitPutStatic(sym->type, $1);
        } else {
            $$->code += emitter.emitStoreInt(sym->index);
        }
    }
    | identifier DEC {
        Symbol* sym = symtab.lookup($1);
        if (!sym) 
            semantic_error("undeclared id",$1);
        if (sym->kind == Kind::K_FUNC)
            semantic_error("invalid -- on function", $1);
        if (sym->kind == Kind::K_CONST)
            semantic_error("invalid -- on constant", $1);
        if (sym->type.t != Type::INT && sym->type.t != Type::FLOAT)
            semantic_error("-- requires numeric operand", $1);        
            
        $$ = new ExtendedType{Type::ERROR, {}};
        if (sym->index == -1) {
            $$->code += emitter.emitGetStaticInt($1);
        } else {
            $$->code += emitter.emitLoadInt(sym->index);
        }
        $$->code += emitter.emitLoadConstantInt(1);
        $$->code += emitter.emitIADD();
        if (sym->index == -1) {
            $$->code += emitter.emitPutStatic(sym->type, $1);
        } else {
            $$->code += emitter.emitStoreInt(sym->index);
        }
    }
    | PRINT   expr {
        if ($2->t == Type::VOID) 
            semantic_error("invalid print", "");
        
        $$ = new ExtendedType{Type::ERROR, {}};
        $$->code += "getstatic java.io.PrintStream java.lang.System.out\n";
        $$->code += $2->code;
        $$->code += emitter.emitInvokeVirtualPrint($2, false);
    }
    | PRINTLN expr {
        if ($2->t == Type::VOID) 
            semantic_error("invalid print", "");
        
        $$ = new ExtendedType{Type::ERROR, {}};
        $$->code += "getstatic java.io.PrintStream java.lang.System.out\n";
        $$->code += $2->code;
        $$->code += emitter.emitInvokeVirtualPrint($2, true);
    }
    | READ    identifier {
        Symbol* sym = symtab.lookup($2);
        if (!sym) 
            semantic_error("undeclared id", $2);
        if (sym->kind == Kind::K_FUNC)
            semantic_error("cannot read into function", $2);
        if (sym->kind == Kind::K_CONST)
            semantic_error("cannot read into constant", $2);
        
        $$ = new ExtendedType{Type::ERROR, {}};
    }
    | /* empty */ { 
        $$ = new ExtendedType{Type::ERROR, {}};
        $$->code = "";
    }
    ;

if_stmt
    : IF '(' expr ')' simple_or_block_stmt { 
        if ($3->t != Type::BOOL) semantic_error("if cond not bool","");
        $$ = new ExtendedType{Type::ERROR, {}};

        $$->code += $3->code;
        string curLabel = "Lexit_" + emitter.newLabel();
        $$->code += emitter.emitIFEQ(curLabel);
        $$->code += $5->code;
        $$->code += emitter.emitLabel(curLabel);
    }
    | IF '(' expr ')' simple_or_block_stmt ELSE simple_or_block_stmt { 
        if ($3->t != Type::BOOL) semantic_error("if cond not bool","");
        $$ = new ExtendedType{Type::ERROR, {}};
        $$->code += $3->code;
        string curLabel = "Lfalse_" + emitter.newLabel();
        $$->code += emitter.emitIFEQ(curLabel);
        $$->code += $5->code;
        string exitLabel = "Lexit_" + emitter.newLabel();
        $$->code += emitter.emitGOTO(exitLabel);
        $$->code += emitter.emitLabel(curLabel);
        $$->code += $7->code;
        $$->code += emitter.emitLabel(exitLabel);
    }
    ;

while_stmt
    : WHILE '(' expr ')' simple_or_block_stmt { 
        if ($3->t != Type::BOOL) semantic_error("while condition not boolean",""); 
        $$ = new ExtendedType{Type::ERROR, {}};

        string beginLabel = "Lbegin_" + emitter.newLabel();
        $$->code += emitter.emitLabel(beginLabel);
        $$->code += $3->code;
        string exitLabel = "Lexit_" + emitter.newLabel();
        $$->code += emitter.emitIFEQ(exitLabel);
        $$->code += $5->code;
        $$->code += emitter.emitGOTO(beginLabel);
        $$->code += emitter.emitLabel(exitLabel);
    }
    ;

for_stmt 
    : FOR '(' simple_stmt ';'  expr ';' simple_stmt ')' simple_or_block_stmt { 
        if ($5->t != Type::BOOL) semantic_error("for condition not boolean",""); 
        $$ = new ExtendedType{Type::ERROR, {}};

        $$->code += $3->code;
        string beginLabel = "Lbegin_" + emitter.newLabel();
        $$->code += emitter.emitLabel(beginLabel);
        $$->code += $5->code;
        string exitLabel = "Lexit_" + emitter.newLabel();
        $$->code += emitter.emitIFEQ(exitLabel);
        $$->code += $9->code;
        $$->code += $7->code;
        $$->code += emitter.emitGOTO(beginLabel);
        $$->code += emitter.emitLabel(exitLabel);
    }
    ;

foreach_stmt
    : FOREACH '(' identifier ':' ICONST '.''.' ICONST ')' simple_or_block_stmt { /* ICONST .. ICONST */
        Symbol* sym = symtab.lookup($3);
        if (!sym) semantic_error("undeclared id", $3);
        if (sym->type.t != Type::INT) semantic_error("foreach loop variable must be of type int:", $3);

        if (sym->kind == Kind::K_FUNC)
            semantic_error("invalid identifier in foreach", $3);
        if (sym->kind == Kind::K_CONST)
            semantic_error("invalid identifier in foreach", $3);
        
        $$ = new ExtendedType{Type::ERROR, {}};
        // ICONST1 5,  ICONST2 8, simple 10
        $$->code += emitter.emitLoadConstantInt($5);
        if (sym->index != -1) {
            $$->code += emitter.emitStoreInt(sym->index);
        } else {
            $$->code += emitter.emitPutStatic(sym->type, $3);
        }

        string beginLabel = "Lbegin_" + emitter.newLabel();
        $$->code += emitter.emitLabel(beginLabel);
        if ($5 > $8) {

            if (sym->index != -1) {
                $$->code += emitter.emitLoadInt(sym->index);
            } else {
                $$->code += emitter.emitGetStaticInt($3);
            }

            $$->code += emitter.emitLoadConstantInt($8);
            $$->code += emitter.emitISUB();
            
            string false_label = "Lfalse_" + emitter.newLabel();
            string exit_label = "Lfalse_" + emitter.newLabel();

            $$->code += emitter.emitIFLT(false_label);
            $$->code += "iconst_1\n";
            $$->code += emitter.emitGOTO(exit_label);

            $$->code += emitter.emitLabel(false_label);
            $$->code += "iconst_0\n";

            $$->code += emitter.emitLabel(exit_label);
        } else {

            if (sym->index != -1) {
                $$->code += emitter.emitLoadInt(sym->index);
            } else {
                $$->code += emitter.emitGetStaticInt($3);
            }
            
            $$->code += emitter.emitLoadConstantInt($8);
            $$->code += emitter.emitISUB();
            
            string false_label = "Lfalse_" + emitter.newLabel();
            string exit_label = "Lfalse_" + emitter.newLabel();

            $$->code += emitter.emitIFGT(false_label);
            $$->code += "iconst_1\n";
            $$->code += emitter.emitGOTO(exit_label);

            $$->code += emitter.emitLabel(false_label);
            $$->code += "iconst_0\n";
            
            $$->code += emitter.emitLabel(exit_label);
        }

        string exitLabel = "Lexit_" + emitter.newLabel();
        $$->code += emitter.emitIFEQ(exitLabel);
        $$->code += $10->code;
        if ($5 > $8) {
            $$->code += emitter.emitLoadInt(sym->index);
            $$->code += emitter.emitLoadConstantInt(1);
            $$->code += emitter.emitISUB();
            $$->code += emitter.emitStoreInt(sym->index);
        } else {
            $$->code += emitter.emitLoadInt(sym->index);
            $$->code += emitter.emitLoadConstantInt(1);
            $$->code += emitter.emitIADD();
            $$->code += emitter.emitStoreInt(sym->index);
        }
        $$->code += emitter.emitGOTO(beginLabel);
        $$->code += emitter.emitLabel(exitLabel);
    }
    ;

/* ───────── Return ───────── */
return_stmt
    : RETURN expr ';' {
        if (current_func_type->t == Type::VOID)
            semantic_error("void function should not return a value", "");
        else if (!type_compatible(current_func_type, $2)) 
            semantic_error("return type mismatch", "");
        
        $$ = new ExtendedType{Type::ERROR, {}};
        $$->code += $2->code;
        $$->code += emitter.emitIRETURN();
    }
    | RETURN ';' { 
        $$ = new ExtendedType{Type::ERROR, {}};
        $$->code = emitter.emitRETURN(); 
    }
    ;

/* --------------------------------------------------
 *  Expressions (arithmetic, logical, function calls)
 * --------------------------------------------------*/
expr
    : expr '+' expr {
        if ($1->t == Type::STRING || $3->t == Type::STRING) {
            if (*$1 != *$3) 
                semantic_error("mixed string / non‑string operands", "");
            else
                $$ = new ExtendedType{Type::STRING, {}};; 
        } else {
            ExtendedType* t = promote($1, $3);
            if (t->t == Type::ERROR) 
                semantic_error("invalid '+' operands", "");
            $$ = t;
        }

        $$->code += $1->code + $3->code;
        $$->code += emitter.emitIADD();
    }
    | expr '-' expr {
        ExtendedType* t = promote($1, $3);
        if (t->t == Type::ERROR) 
            semantic_error("invalid '-' operands", "");
        $$ = t; 

        $$->code += $1->code + $3->code;
        $$->code += emitter.emitISUB();
    }
    | expr '*' expr {
        ExtendedType* t = promote($1, $3);
        if (t->t == Type::ERROR) 
            semantic_error("invalid '*' operands", "");
        $$ = t; 

        $$->code += $1->code + $3->code;
        $$->code += emitter.emitIMUL();
    }
    | expr '/' expr {
        ExtendedType* t = promote($1, $3);
        if (t->t == Type::ERROR) 
            semantic_error("invalid '/' operands", "");
        $$ = t; 

        $$->code += $1->code + $3->code;
        $$->code += emitter.emitIDIV();
    }
    | expr '%' expr {
        if ($1->t != Type::INT || $3->t != Type::INT)
            semantic_error("'%' requires integer operands", "");
        $$ = new ExtendedType{Type::INT, {}}; 

        $$->code += $1->code + $3->code;
        $$->code += emitter.emitIREM();
    }
    | '-' expr %prec UMINUS  { 
        $$ = $2; 
        $$->code += emitter.emitINEG();
    }
    | '(' expr ')'           { $$ = $2; }
    | identifier {
        Symbol* sym = symtab.lookup($1);
        if (!sym) semantic_error("undeclared var", $1);
        if (sym->kind == Kind::K_FUNC)
            semantic_error("function used as variable", $1);
        $$ = &sym->type;
        
        if (sym->kind == Kind::K_CONST) {
            switch(sym->type.lit.tag) {
                case Literal::INT:  $$->code = emitter.emitLoadConstantInt(sym->type.lit.ival); break;
                case Literal::BOOL: $$->code = emitter.emitLoadConstantInt(sym->type.lit.bval); break;
                case Literal::STR:  $$->code = emitter.emitLoadConstantString(sym->type.lit.sval); break;
                default: semantic_error("Unexpected error", ""); break;
            }
        } else {
            if (sym->index != -1) $$->code = emitter.emitLoadInt(sym->index);
            else $$->code = emitter.emitGetStaticInt($1);
        }
    } 
    | array {
        $$ = $1;
    }
    | identifier '(' arg_list_opt ')' {
        /*  Function call  */
        Symbol* sym = symtab.lookup($1);
        if (!sym || sym->kind != Kind::K_FUNC)
            semantic_error("call of non-function", $1);
        if (sym->params.size() != delay_symbols.size())  
            semantic_error("function parameter count mismatch in call to function: ", $1);
        
        /*  Per‑parameter checks (dims + base type) */
        for (size_t i = 0; i < sym->params.size(); ++i) {
            /* dimension consistency */
            if (!delay_symbols[i].type->dims.empty() && !sym->params[i].dims.empty() &&
                 delay_symbols[i].type->dims.size() != sym->params[i].dims.size())
                semantic_error("array rank mismatch in arg", $1);
            
            if (!delay_symbols[i].type->dims.empty() && !sym->params[i].dims.empty() && 
                 !delay_symbols[i].type->dims.empty()) {
                for (size_t j = 0; j < delay_symbols[i].type->dims.size(); ++j)
                    if (delay_symbols[i].type->dims[j] != sym->params[i].dims[j])
                        semantic_error("array dim mismatch in arg", $1);
            }
            /* base type */
            if (!type_compatible(delay_symbols[i].type, &sym->params[i])) 
                semantic_error("type mismatch in arg", $1);
        }
        delay_symbols.clear();


        $$ = &sym->type;
        $$->code += $3->code;
        $$->code += emitter.emitInvokeStatic(sym->type, $1, sym->params.size());
    }
    | FCONST { 
        $$ = new ExtendedType{Type::FLOAT, {}}; 
    }
    | BCONST { 
        $$ = new ExtendedType{Type::BOOL, {}}; 
        $$->lit.tag = Literal::BOOL;
        $$->lit.bval = $1;
        $$->code = emitter.emitLoadConstantInt($1);
    }
    | SCONST { 
        dbg::debug($1);
        $$ = new ExtendedType{Type::STRING, {}}; 
        $$->lit.tag = Literal::STR;
        $$->lit.sval = $1;
        $$->code = emitter.emitLoadConstantString($1);
    }
    | ICONST { 
        $$ = new ExtendedType{Type::INT, {}}; 
        $$->lit.tag = Literal::INT;
        $$->lit.ival = $1;
        $$->code = emitter.emitLoadConstantInt($1);
    }
    | expr EQ expr {
        bool same   = (*$1 == *$3);                                     
        bool numMix = (($1->t == Type::INT || $1->t == Type::FLOAT || $1->t == Type::BOOL) 
                    && ($3->t == Type::INT || $3->t == Type::FLOAT || $3->t == Type::BOOL));
        if (!(same || numMix))
            semantic_error("comparison type mismatch", "");
        $$ = new ExtendedType{Type::BOOL, {}};;

        $$->code += $1->code + $3->code;
        $$->code += emitter.emitISUB();

        string true_label = "Ltrue_" + emitter.newLabel();
        string exit_label = "Lfalse_" + emitter.newLabel();

        $$->code += emitter.emitIFEQ(true_label);
        $$->code += "iconst_0\n";
        $$->code += emitter.emitGOTO(exit_label);

        $$->code += emitter.emitLabel(true_label);
        $$->code += "iconst_1\n";

        $$->code += emitter.emitLabel(exit_label);
        
    }
    | expr NE expr {
        bool same   = (*$1 == *$3);                                     
        bool numMix = (($1->t == Type::INT || $1->t == Type::FLOAT || $1->t == Type::BOOL) 
                    && ($3->t == Type::INT || $3->t == Type::FLOAT || $3->t == Type::BOOL));
        if (!(same || numMix))
           semantic_error("comparison type mismatch", "");
        $$ = new ExtendedType{Type::BOOL, {}};;

        $$->code += $1->code + $3->code;
        $$->code += emitter.emitISUB();

        string true_label = "Ltrue_" + emitter.newLabel();
        string exit_label = "Lfalse_" + emitter.newLabel();

        $$->code += emitter.emitIFNE(true_label);
        $$->code += "iconst_0\n";
        $$->code += emitter.emitGOTO(exit_label);

        $$->code += emitter.emitLabel(true_label);
        $$->code += "iconst_1\n";

        $$->code += emitter.emitLabel(exit_label);
    }
    | expr '>' expr {
        bool ok = (*$1 == *$3 && $1->t != Type::STRING) ||                 
                 (($1->t == Type::INT  || $1->t == Type::FLOAT || $1->t == Type::BOOL) &&
                  ($3->t == Type::INT  || $3->t == Type::FLOAT || $3->t == Type::BOOL));
        if (!ok)
            semantic_error("comparison type mismatch", "");
        $$ = new ExtendedType{Type::BOOL, {}};;

        $$->code += $1->code + $3->code;
        $$->code += emitter.emitISUB();
        
        string true_label = "Ltrue_" + emitter.newLabel();
        string exit_label = "Lfalse_" + emitter.newLabel();

        $$->code += emitter.emitIFGT(true_label);
        $$->code += "iconst_0\n";
        $$->code += emitter.emitGOTO(exit_label);

        $$->code += emitter.emitLabel(true_label);
        $$->code += "iconst_1\n";

        $$->code += emitter.emitLabel(exit_label);


    }
    | expr '<' expr { 
        bool ok = (*$1 == *$3 && $1->t != Type::STRING) ||                 
                 (($1->t == Type::INT  || $1->t == Type::FLOAT || $1->t == Type::BOOL) &&
                  ($3->t == Type::INT  || $3->t == Type::FLOAT || $3->t == Type::BOOL));
        if (!ok)
            semantic_error("comparison type mismatch", "");
        $$ = new ExtendedType{Type::BOOL, {}};;

        $$->code += $1->code + $3->code;
        $$->code += emitter.emitISUB();
        
        string true_label = "Ltrue_" + emitter.newLabel();
        string exit_label = "Lfalse_" + emitter.newLabel();

        $$->code += emitter.emitIFLT(true_label);
        $$->code += "iconst_0\n";
        $$->code += emitter.emitGOTO(exit_label);

        $$->code += emitter.emitLabel(true_label);
        $$->code += "iconst_1\n";

        $$->code += emitter.emitLabel(exit_label);
    }
    | expr LE expr {
        bool ok = (*$1 == *$3 && $1->t != Type::STRING) ||                 
                 (($1->t == Type::INT  || $1->t == Type::FLOAT || $1->t == Type::BOOL) &&
                  ($3->t == Type::INT  || $3->t == Type::FLOAT || $3->t == Type::BOOL));
        if (!ok)
            semantic_error("comparison type mismatch", "");
        $$ = new ExtendedType{Type::BOOL, {}};;

        $$->code += $1->code + $3->code;
        $$->code += emitter.emitISUB();
        
        string false_label = "Lfalse_" + emitter.newLabel();
        string exit_label = "Lfalse_" + emitter.newLabel();

        $$->code += emitter.emitIFGT(false_label);
        $$->code += "iconst_1\n";
        $$->code += emitter.emitGOTO(exit_label);

        $$->code += emitter.emitLabel(false_label);
        $$->code += "iconst_0\n";
        
        $$->code += emitter.emitLabel(exit_label);
    }
    | expr GE expr {
        bool ok = (*$1 == *$3 && $1->t != Type::STRING) ||                 
                 (($1->t == Type::INT  || $1->t == Type::FLOAT || $1->t == Type::BOOL) &&
                  ($3->t == Type::INT  || $3->t == Type::FLOAT || $3->t == Type::BOOL));
        if (!ok)
            semantic_error("comparison type mismatch", "");
        $$ = new ExtendedType{Type::BOOL, {}};;

        $$->code += $1->code + $3->code;
        $$->code += emitter.emitISUB();
        
        string false_label = "Lfalse_" + emitter.newLabel();
        string exit_label = "Lfalse_" + emitter.newLabel();

        $$->code += emitter.emitIFLT(false_label);
        $$->code += "iconst_1\n";
        $$->code += emitter.emitGOTO(exit_label);

        $$->code += emitter.emitLabel(false_label);
        $$->code += "iconst_0\n";

        $$->code += emitter.emitLabel(exit_label);
    }
    | '!' expr {
        if ($2->t != Type::BOOL)
            semantic_error("! operand not bool", "");
        $$ = new ExtendedType{Type::BOOL, {}};;

        $$->code += $2->code;
        $$->code += "iconst_1\n";
        $$->code += emitter.emitIXOR();
    }
    | expr AND expr {
        if ($1->t != Type::BOOL || $3->t != Type::BOOL)
            semantic_error("&& on non‑bool", "");
        $$ = new ExtendedType{Type::BOOL, {}};;

        $$->code += $1->code + $3->code;
        $$->code += emitter.emitIAND();
    }
    | expr OR expr {
        if ($1->t != Type::BOOL || $3->t != Type::BOOL)
            semantic_error("|| on non‑bool", "");
        $$ = new ExtendedType{Type::BOOL, {}};;

        $$->code += $1->code + $3->code;
        $$->code += emitter.emitIOR();
    }
    ;

/*  array = identifier '['expr']'...  (rank is checked vs declaration) */
array
    : identifier expr_array_block {
        Symbol* sym = symtab.lookup($1);
        if (!sym) semantic_error("undeclared var",$1);
        if (sym->type.dims.size() != $2->dims.size()) {
            semantic_error("array dimension mismatch", $1);
        }
        $$ = &sym->type;
    }
    ;

/*  Build an anonymous ExtendedType that stores the rank of the
 *  subscripting expression.  (Actual bounds are ignored at compile‑time.)
 */
expr_array_block
    : '[' expr ']' { 
        if ($2->t != Type::INT && $2->t != Type::BOOL)
            semantic_error("array dimension not integer", "");
        vector<int> dims(1);
        ExtendedType* nt = new ExtendedType{Type::ERROR, dims};
        type_pool.push_back(nt);
        $$ = nt;
    }
    | '[' expr ']' expr_array_block {
        if ($2->t != Type::INT && $2->t != Type::BOOL)
            semantic_error("array dimension not integer", "");
        vector<int> dims(1);
        for (auto& _ : $4->dims)
            dims.push_back(1);
        ExtendedType* nt = new ExtendedType{Type::ERROR, dims};
        type_pool.push_back(nt);
        $$ = nt;
    }
    ;

/* ───────── Primitive Types ───────── */
data_type
    : TINT    { $$ = new ExtendedType{Type::INT, {}}; }
    | TFLOAT  { $$ = new ExtendedType{Type::FLOAT, {}}; }
    | TBOOL   { $$ = new ExtendedType{Type::BOOL, {}}; }
    | TSTRING { $$ = new ExtendedType{Type::STRING, {}}; }
    | TVOID   { $$ = new ExtendedType{Type::VOID, {}}; }
    ;

/*  strdup the identifier (%sval is char*) so that the string is
 *  independently owned (lexer buffer will be reused).
 */
identifier
    : ID { $$ = strdup($1); } 
    ;

/*  Optional argument list in a call.  Each expr is queued in
 *  delay_symbols with an empty id.
 */
arg_list_opt 
    : /* empty */ 
        { $$ = new ExtendedType{Type::ERROR, {}}; }
    | arg_list { 
        $$ = new ExtendedType{Type::ERROR, {}};
        $$->code += $1->code; 
    }
    ;


arg_list
    : expr { 
        delay_symbols.push_back({"", $1}); 
        $$ = new ExtendedType{Type::ERROR, {}};
        $$->code += $1->code;
    }
    | expr ',' arg_list { 
        delay_symbols.push_back({"", $1}); 
        $$ = new ExtendedType{Type::ERROR, {}};
        $$->code += $1->code + $3->code;
    }
    ;

%%           

void yyerror(const string& msg) {
    cerr << "SYNTAX(" << linenum << "): " << msg << '\n';
    for (auto& ptr : type_pool) delete ptr;
    exit(-1);
}

int main(int argc,char* argv[]){
    if (argc!=2) { 
        fprintf(stderr,"usage: %s file.sd\n",argv[0]); 
        return 1;
    }
    yyin=fopen(argv[1],"r");
    if (!yyin) { 
        perror(argv[1]); 
        return 1; 
    }

    auto fileStem = [](const string& path) {
        size_t slash = path.find_last_of("/\\");
        std::string fname = (slash == std::string::npos) ? path : path.substr(slash + 1);
        
        size_t dot = fname.find_last_of('.');
        if (dot != std::string::npos) fname.erase(dot);
        return fname;
    };

    ofstream ofs("output.j");
    emitter.setOutputStream(ofs);
    string className = fileStem(argv[1]);
    emitter.openClass(className);

    if (yyparse() == 0) {
        if (!has_main_func) 
            semantic_error("has no main function", "");
        puts("PASS – no errors");
    }

    emitter.closeClass();
    
    for (auto& ptr : type_pool) delete ptr;
    return 0;
}
