%{
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <vector>
#include "symbolTable.h"

using namespace std;

static ExtendedType _T_STRING{Type::STRING,{}};
static ExtendedType _T_BOOL  {Type::BOOL  ,{}};
static ExtendedType _T_INT   {Type::INT   ,{}};
static ExtendedType _T_FLOAT {Type::FLOAT ,{}};
static ExtendedType _T_VOID  {Type::VOID  ,{}};
static ExtendedType _T_ERROR {Type::ERROR ,{}};

#define TRACE(t) printf(t)
#define  T_STRING (&_T_STRING)
#define  T_BOOL   (&_T_BOOL)
#define  T_INT    (&_T_INT)
#define  T_FLOAT  (&_T_FLOAT)
#define  T_VOID   (&_T_VOID)
#define  T_ERROR  (&_T_ERROR)

struct Pending_var {
    string        id;
    ExtendedType* type;
};

extern FILE* yyin;
SymbolTable symtab;
extern int linenum;                    

void yyerror(const string& msg);
int yylex(void);

vector<Pending_var> decl_vars, delay_symbols;
vector<ExtendedType*> type_pool;

static void semantic_error(const string& msg, const string& id) {
    cerr << "SEMANTIC(" << linenum << "): " << msg << ' ' << id << '\n';
    for (auto& ptr : type_pool) delete ptr;
    exit(-1);
}

static bool type_compatible(const ExtendedType* dst, const ExtendedType* src) {
    if (dst->t == src->t)                                            return true;
    if (dst->t == T_STRING->t || src->t == T_STRING->t)                  return false;
    if (dst->t == T_FLOAT->t  && src->t == T_INT->t)                     return true;
    if (dst->t == T_INT->t    && src->t == T_FLOAT->t)                   return true;
    if ((dst->t == T_INT->t || dst->t == T_FLOAT->t) && src->t == T_BOOL->t) return true;
    return false;
}

static ExtendedType* promote(const ExtendedType* a, const ExtendedType* b) {
    if (*a == *T_ERROR || *b == *T_ERROR)   return T_ERROR;
    if (*a == *T_STRING || *b == *T_STRING) return T_ERROR;
    if (*a == *T_FLOAT  || *b == *T_FLOAT)  return T_FLOAT;
    return T_INT;
}

static bool invalid_main_function(Type t, string func_id) {
    return func_id == "main" && t != Type::VOID;
}

static ExtendedType* current_func_type = T_ERROR;
static bool has_main_func = false;
%}

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
%token  FCONST SCONST BCONST TDOUBLE TCHAR
%token  EQ NE LE GE AND OR

%token <sval> ID
%token <fval> TFLOAT
%token <ival> TBOOL
%token <ival> TINT
%token <ival> ICONST
%token <sval> TSTRING


/* ───────── precedence ───────── */
%left   OR
%left   AND
%right  '!'
%nonassoc EQ NE '<' '>' LE GE
%left   '+' '-'
%left   '*' '/' '%'
%nonassoc UMINUS INC DEC


%type <tval>  data_type const_expr boolean_expr expr variable_expr
%type <tval>  array  array_block expr_array_block
%type <sval>  identifier


/* ───────── start symbol ───────── */
%start program

%%                      

program
    : decl_list               { TRACE("program OK\n"); }
    ;

decl_list
    : /* empty */
    | decl_list declaration
    ;

declaration
    : const_decl
    | var_decl
    | func_decl
    ;

/* ───────── constant expression ───────── */
const_decl
    : CONST data_type identifier '=' const_expr ';' {
        if (!symtab.insert($3, Kind::K_CONST, *$2, {}))
            semantic_error("redeclared const", $3);
        if ($2 != $5)
            semantic_error("const type mismatch", $3);
        if ($2 == T_VOID) 
            semantic_error("cannot declare a void type constant", $3);
    }
    ;


/* ───────── variable declaration ───────── */
var_decl
    : data_type init_id_list ';' { 
        if ($1 == T_VOID)
            semantic_error("cannot decalre a void type variable", "");
        for (auto& var : decl_vars) {
            string name = var.id;
            ExtendedType* type = var.type;
            if (!symtab.insert(name, Kind::K_VAR, ExtendedType{$1->t, type->dims}, {}))
                semantic_error("redeclared var", name);
            if (type->t != Type::ERROR && !type_compatible(type, $1))
                semantic_error("type mismatch in init", "");
        }
        decl_vars.clear();
    }
    ;

init_id_list
    : init_id
    | init_id ',' init_id_list 
    ;

init_id
    : identifier array_block 
      { decl_vars.push_back({$1, $2}); }
    | identifier '=' const_expr 
      { decl_vars.push_back({$1, $3}); }
    ;

array_block
    : /* empty */ { $$ = T_ERROR; }
    | '[' ICONST ']' array_block {
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
        current_func_type = $1;
    } '(' opt_param_list ')' {
        if (string($2) == "main") {
            if (!delay_symbols.empty())
                semantic_error("main function has param", "");
            has_main_func = true;
        }
        Symbol *sym = symtab.lookup($2);
        for (auto& p : delay_symbols) {
            sym->params.push_back(*p.type);
        }
    } block {
        current_func_type = T_ERROR;
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

param
    : data_type identifier array_block { 
        if ($1 == T_VOID) 
            semantic_error("function parameter cannot be of void type", $2);
        ExtendedType* nt = new ExtendedType{$1->t, $3->dims};
        delay_symbols.push_back({$2, nt});
        type_pool.push_back(nt);
    }
    ;

/* ───────── Block & Statement ───────── */
block
    : '{' { 
        symtab.pushScope(); 
        for (auto& symbol : delay_symbols)
            if (!symtab.insert(symbol.id, Kind::K_VAR, *symbol.type, {}))
                semantic_error("redeclared param", symbol.id);
        delay_symbols.clear();
    } block_item_list '}' { symtab.popScope(); } 
    ;

block_item_list
    : /* empty */
    | block_item_list block_item
    ;

block_item
    : block_decl 
    | statement
    ;

block_decl
    : const_decl
    | var_decl
    ;

/* ───────── Statement ───────── */
statement
    : simple_stmt ';'
    | if_stmt
    | while_stmt
    | for_stmt
    | foreach_stmt
    | return_stmt
    | block
    ;

simple_or_block_stmt
    : simple_stmt ';'
    | block
    ;

simple_stmt
    : identifier '=' expr {
        Symbol* sym = symtab.lookup($1);
        if (!sym) 
            semantic_error("undeclared id",$1);
        if (sym->kind == Kind::K_FUNC)
            semantic_error("try to assign to a function: ", $1);
        if ($3 == T_VOID)
            semantic_error("cannot assign result of void function", "");
        if (sym->kind == Kind::K_CONST)
            semantic_error("try to assign to a constant: ", $1);
        if (!type_compatible(&sym->type, $3)) 
            semantic_error("type mismatch in assignment", $1);
        if (!sym->type.dims.empty())
            semantic_error("try to assign value to an array", $1);
    }
    | identifier INC {
        Symbol* sym = symtab.lookup($1);
        if (!sym) 
            semantic_error("undeclared id",$1);
        if (sym->kind == Kind::K_FUNC)
            semantic_error("try to increase a function:", $1);
        if (sym->kind == Kind::K_CONST)
            semantic_error("try to increase a constant:", $1);
        if (sym->type != *T_INT && sym->type != *T_FLOAT) 
            semantic_error("invalid operation on", $1);
    }
    | identifier DEC {
        Symbol* sym = symtab.lookup($1);
        if (!sym) 
            semantic_error("undeclared id",$1);
        if (sym->kind == Kind::K_FUNC)
            semantic_error("try to decrease a function: ", $1);
        if (sym->kind == Kind::K_CONST)
            semantic_error("try to decrease a constant: ", $1);
        if (sym->type != *T_INT && sym->type != *T_FLOAT)
            semantic_error("invalid operation on", $1);                                                                                                                                                                                      
    }
    | PRINT   expr {
        // void
    }
    | PRINTLN expr {
        // void
    }
    | READ    identifier {
        Symbol* sym = symtab.lookup($2);
        if (!sym) 
            semantic_error("undeclared id", $2);
        if (sym->kind == Kind::K_FUNC)
            semantic_error("try to assign value to a function: ", $2);
        if (sym->kind == Kind::K_CONST)
            semantic_error("try to assign value to a constant: ", $2);
    }
    | /* empty */
    ;

if_stmt
    : IF '(' boolean_expr ')' simple_or_block_stmt
    | IF '(' boolean_expr ')' simple_or_block_stmt ELSE simple_or_block_stmt
    ;

while_stmt
    : WHILE '(' boolean_expr ')' simple_or_block_stmt
      { if ($3 != T_BOOL) semantic_error("if cond not bool",""); }
    ;

for_stmt 
    : FOR '(' simple_stmt ';'  boolean_expr ';' simple_stmt ')' simple_or_block_stmt 
       { if ($5 != T_BOOL) semantic_error("if cond not bool",""); }
    ;

foreach_stmt
    : FOREACH '(' identifier ':' identifier '.''.' identifier ')' simple_or_block_stmt {
        Symbol* sym = symtab.lookup($3);
        if (!sym) semantic_error("undeclared id", $3);
        if (sym->type != *T_INT) semantic_error("foreach loop variable must be of type int:", $3);

        Symbol* sym2 = symtab.lookup($5);
        if (!sym2) semantic_error("undeclared id", $5);
        if (sym2->type != *T_INT) semantic_error("foreach loop range must be of type int:", $5);
        Symbol* sym3 = symtab.lookup($8);
        if (!sym3) semantic_error("undeclared id", $8);
        if (sym3->type != *T_INT) semantic_error("foreach loop range must be of type int:", $8);

    }
    | FOREACH '(' identifier ':' identifier '.''.' ICONST ')' simple_or_block_stmt {
        Symbol* sym = symtab.lookup($3);
        if (!sym) semantic_error("undeclared id", $3);
        if (sym->type != *T_INT) semantic_error("foreach loop variable must be of type int:", $3);

        Symbol* sym2 = symtab.lookup($5);
        if (!sym2) semantic_error("undeclared id", $5);
        if (sym2->type != *T_INT) semantic_error("foreach loop range must be of type int:", $5);
    }
    | FOREACH '(' identifier ':' ICONST '.''.' identifier ')' simple_or_block_stmt {
        Symbol* sym = symtab.lookup($3);
        if (!sym) semantic_error("undeclared id", $3);
        if (sym->type != *T_INT) semantic_error("foreach loop variable must be of type int:", $3);
        Symbol* sym3 = symtab.lookup($8);
        if (!sym3) semantic_error("undeclared id", $8);
        if (sym3->type != *T_INT) semantic_error("foreach loop range must be of type int:", $8);
    }
    | FOREACH '(' identifier ':' ICONST '.''.' ICONST ')' simple_or_block_stmt {
        Symbol* sym = symtab.lookup($3);
        if (!sym) semantic_error("undeclared id", $3);
        if (sym->type != *T_INT) semantic_error("foreach loop variable must be of type int:", $3);
    }
    ;

return_stmt
    : RETURN expr ';' {
        if (current_func_type == T_VOID)
            semantic_error("void function should not return value", "");
        else if (!type_compatible(current_func_type, $2)) 
            semantic_error("return type mismatch", "");
      }
    ;

/* ───────── Expression ───────── */
expr
    : variable_expr '+' const_expr {
        if (*$1 == *T_STRING || *$3 == *T_STRING) {
            if (*$1 != *$3) 
                semantic_error("invalid operation", "");
            else
                $$ = T_STRING; 
        } else {
            ExtendedType* t = promote($1, $3);
            if (t == T_ERROR) 
                semantic_error("invalid operation", "");
            $$ = t;
        }
    }
    | const_expr '+' variable_expr {
        if (*$1 == *T_STRING || *$3 == *T_STRING) {
            if (*$1 != *$3) 
                semantic_error("invalid operation", "");
            else
                $$ = T_STRING; 
        } else {
            ExtendedType* t = promote($1, $3);
            if (t == T_ERROR) 
                semantic_error("invalid operation", "");
            $$ = t;
        }
    }
    | variable_expr '-' const_expr {
        ExtendedType* t = promote($1, $3);
        if (t == T_ERROR) 
            semantic_error("invalid operation", "");
        $$ = t; 
    }
    | const_expr '-' variable_expr {
        ExtendedType* t = promote($1, $3);
        if (t == T_ERROR) 
            semantic_error("invalid operation", "");
        $$ = t; 
    }
    | variable_expr '*' const_expr {
        ExtendedType* t = promote($1, $3);
        if (t == T_ERROR) 
            semantic_error("invalid operation", "");
        $$ = t; 
    }
    | const_expr '*' variable_expr {
        ExtendedType* t = promote($1, $3);
        if (t == T_ERROR) 
            semantic_error("invalid operation", "");
        $$ = t; 
    }
    | variable_expr '/' const_expr {
        ExtendedType* t = promote($1, $3);
        if (t == T_ERROR) 
            semantic_error("invalid operation", "");
        $$ = t; 
    }
    | const_expr '/' variable_expr {
        ExtendedType* t = promote($1, $3);
        if (t == T_ERROR) 
            semantic_error("invalid operation", "");
        $$ = t; 
    }
    | variable_expr '%' const_expr {
        if (*$1 != *T_INT || *$3 != *T_INT)
            semantic_error("modulo operator requires integer operands", "");
        $$ = T_INT; 
    }
    | const_expr '%' variable_expr {
        if (*$1 != *T_INT || *$3 != *T_INT)
            semantic_error("modulo operator requires integer operands", "");
        $$ = T_INT; 
    }
    | variable_expr
    | const_expr
    | boolean_expr
    ;

variable_expr
    : variable_expr '+' variable_expr { 
        if (*$1 == *T_STRING || *$3 == *T_STRING) {
            if (*$1 != *$3) 
                semantic_error("invalid operation", "");
            else
                $$ = T_STRING; 
        } else {
            ExtendedType* t = promote($1, $3);
            if (t == T_ERROR) 
                semantic_error("invalid operation", "");
            $$ = t;
        }
    }
    | variable_expr '-' variable_expr { 
        ExtendedType* t = promote($1, $3);
        if (t == T_ERROR) 
            semantic_error("invalid operation", "");
        $$ = t; 
    }
    | variable_expr '*' variable_expr {
        ExtendedType* t = promote($1, $3);
        if (t == T_ERROR) 
            semantic_error("invalid operation", "");
        $$ = t; 
    }
    | variable_expr '/' variable_expr {
        ExtendedType* t = promote($1, $3);
        if (t == T_ERROR) 
            semantic_error("invalid operation", "");
        $$ = t; 
    }
    | variable_expr '%' variable_expr {
        if (*$1 != *T_INT || *$3 != *T_INT)
            semantic_error("modulo operator requires integer operands", "");
        $$ = T_INT; 
    }
    | '-' variable_expr %prec UMINUS  { $$ = $2; }
    | '(' variable_expr ')'           { $$ = $2; }
    | identifier {
        Symbol* sym = symtab.lookup($1);
        if (!sym) semantic_error("undeclared var",$1);
        if (sym->kind == Kind::K_FUNC)
            semantic_error("invalid operation", "");
        $$ = sym ? &sym->type : (ExtendedType*)T_ERROR;
    } 
    | array {
        $$ = $1;
    }
    | identifier '(' arg_list_opt ')' {
        Symbol* sym = symtab.lookup($1);
        if (!sym || sym->kind != Kind::K_FUNC)
            semantic_error("call of non-function", $1);
        if (sym->params.size() != delay_symbols.size())  
            semantic_error("function parameter count mismatch in call to function: ", $1);
        for (int i = 0; i < (int) sym->params.size(); ++i)
            if (sym->params[i] != *delay_symbols[i].type) 
                semantic_error("function parameter type mismatch in call to function: ", $1);
        delay_symbols.clear();
        $$ = sym ? &sym->type : (ExtendedType*)T_ERROR;
    }
    ;

boolean_expr
    : expr EQ expr {
        bool same   = (*$1 == *$3);                                     
        bool numMix = ((*$1 == *T_INT || *$1 == *T_FLOAT || *$1 == *T_BOOL) 
                    && (*$3 == *T_INT || *$3 == *T_FLOAT || *$3 == *T_BOOL));
        if (!(same || numMix))
            semantic_error("comparison type mismatch", "");
        $$ = T_BOOL;
    }
    | expr NE expr {
        bool same   = (*$1 == *$3);                                     
        bool numMix = ((*$1 == *T_INT || *$1 == *T_FLOAT || *$1 == *T_BOOL) 
                    && (*$3 == *T_INT || *$3 == *T_FLOAT || *$3 == *T_BOOL));
        if (!(same || numMix))
           semantic_error("comparison type mismatch", "");
        $$ = T_BOOL;
    }
    | expr '>' expr {
        bool ok = (*$1 == *$3 && *$1 != *T_STRING) ||                 
                 ((*$1 == *T_INT  || *$1 == *T_FLOAT || *$1 == *T_BOOL) &&
                  (*$3 == *T_INT  || *$3 == *T_FLOAT || *$3 == *T_BOOL));
        if (!ok)
            semantic_error("comparison type mismatch", "");
        $$ = T_BOOL;
    }
    | expr '<' expr { 
        bool ok = (*$1 == *$3 && *$1 != *T_STRING) ||                 
                 ((*$1 == *T_INT  || *$1 == *T_FLOAT || *$1 == *T_BOOL) &&
                  (*$3 == *T_INT  || *$3 == *T_FLOAT || *$3 == *T_BOOL));
        if (!ok)
            semantic_error("comparison type mismatch", "");
        $$ = T_BOOL;
    }
    | expr LE expr {
        bool ok = (*$1 == *$3 && *$1 != *T_STRING) ||                 
                 ((*$1 == *T_INT  || *$1 == *T_FLOAT || *$1 == *T_BOOL) &&
                  (*$3 == *T_INT  || *$3 == *T_FLOAT || *$3 == *T_BOOL));
        if (!ok)
            semantic_error("comparison type mismatch", "");
        $$ = T_BOOL;
    }
    | expr GE expr {
        bool ok = (*$1 == *$3 && *$1 != *T_STRING) ||                 
                 ((*$1 == *T_INT  || *$1 == *T_FLOAT || *$1 == *T_BOOL) &&
                  (*$3 == *T_INT  || *$3 == *T_FLOAT || *$3 == *T_BOOL));
        if (!ok)
            semantic_error("comparison type mismatch", "");
        $$ = T_BOOL;
    }
    | '!' expr {
        if (*$2 != *T_BOOL)
            semantic_error("logical operand not bool", "");
        $$ = T_BOOL;
    }
    | expr AND expr {
        if (*$1 != *T_BOOL || *$3 != *T_BOOL)
            semantic_error("logical operand not bool", "");
        $$ = T_BOOL;
    }
    | expr OR expr {
        if (*$1 != *T_BOOL || *$3 != *T_BOOL)
            semantic_error("logical operand not bool", "");
        $$ = T_BOOL;
    }
    ;


const_expr  
    : const_expr '+' const_expr { 
        if (*$1 == *T_STRING || *$3 == *T_STRING) {
            if (*$1 != *$3) 
                semantic_error("invalid operation", "");
            else
                $$ = T_STRING; 
        } else {
            ExtendedType* t = promote($1, $3);
            if (t == T_ERROR) 
                semantic_error("invalid operation", "");
            $$ = t;
        }
    }
    | const_expr '-' const_expr { 
        ExtendedType* t = promote($1, $3);
        if (t == T_ERROR) 
            semantic_error("invalid operation", "");
        $$ = t; 
    }
    | const_expr '*' const_expr {
        ExtendedType* t = promote($1, $3);
        if (t == T_ERROR) 
            semantic_error("invalid operation", "");
        $$ = t; 
    }
    | const_expr '/' const_expr {
        ExtendedType* t = promote($1, $3);
        if (t == T_ERROR) 
            semantic_error("invalid operation", "");
        $$ = t; 
    }
    | '-' const_expr %prec UMINUS  { $$ = $2; }
    | '(' const_expr ')'           { $$ = $2; }
    | FCONST { $$ = T_FLOAT; }
    | BCONST { $$ = T_BOOL; }
    | SCONST { $$ = T_STRING; }
    | ICONST { $$ = T_INT; }
    ;

array
    : identifier expr_array_block {
        Symbol* sym = symtab.lookup($1);
        if (!sym) semantic_error("undeclared var",$1);
        if (sym->type.dims.size() != $2->dims.size()) {
            semantic_error("array dimension mismatch", $1);
        }
        $$ = sym ? &sym->type : (ExtendedType*)T_ERROR;
    }
    ;

expr_array_block
    : '[' const_expr ']' { 
        if ($2 != T_INT)
            semantic_error("array dimension not integer", "");
        vector<int> dims(1);
        ExtendedType* nt = new ExtendedType{Type::ERROR, dims};
        type_pool.push_back(nt);
        $$ = nt;
    }
    | '[' const_expr ']' expr_array_block {
        if ($2 != T_INT)
            semantic_error("array dimension not integer", "");
        vector<int> dims(1);
        for (auto& _ : $4->dims)
            dims.push_back(1);
        ExtendedType* nt = new ExtendedType{Type::ERROR, dims};
        type_pool.push_back(nt);
        $$ = nt;
    }
    ;

data_type
    : TINT    { $$ = T_INT; }
    | TFLOAT  { $$ = T_FLOAT; }
    | TBOOL   { $$ = T_BOOL; }
    | TSTRING { $$ = T_STRING; }
    | TVOID   { $$ = T_VOID; }
    ;

identifier
    : ID { $$ = strdup($1); } 
    ;

arg_list_opt 
    : /* empty */ 
    | arg_list 
    ;


arg_list
    : expr 
      { delay_symbols.push_back({"", $1}); }
    | arg_list ',' expr 
      { delay_symbols.push_back({"", $3}); }
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

    if (yyparse() == 0) {
        if (!has_main_func) 
            semantic_error("has no main function", "");
        puts("PASS – no errors");
    }
    for (auto& ptr : type_pool) delete ptr;
    return 0;
}
