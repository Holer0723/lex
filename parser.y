%{
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <vector>
#include "symbolTable.h"

#define TRACE(t) printf(t)


using namespace std;
extern FILE* yyin;

#define YYSTYPE_IS_DECLARED 1
typedef union {
    int          ival;
    float        fval;
    char*        sval;
    ExtendedType tval;    
} YYSTYPE;

SymbolTable symtab;
extern int linenum;                    
void yyerror(const string& msg);
const static ExtendedType T_STRING = ExtendedType{Type::T_STRING, {}};
const static ExtendedType T_BOOL   = ExtendedType{Type::T_BOOL, {}};
const static ExtendedType T_INT    = ExtendedType{Type::T_INT, {}};
const static ExtendedType T_FLOAT  = ExtendedType{Type::T_FLOAT, {}};
const static ExtendedType T_VOID   = ExtendedType{Type::T_VOID, {}};
const static ExtendedType T_ERROR  = ExtendedType{Type::T_ERROR, {}};

static void semantic_error(const string& msg, const string& id){
    cerr << "SEMANTIC(" << linenum << "): " << msg << ' ' << id << '\n';
    exit(-1);
}

static bool type_compatible(ExtendedType dst, ExtendedType src) {
    if (dst == src)                                  return true;
    if (dst == T_STRING || src == T_STRING)  return false;
    if (dst == T_FLOAT && src == T_INT)      return true;
    if (dst == T_INT && src == T_FLOAT)      return true;
    if ((dst == T_INT || dst == T_FLOAT) && src == T_BOOL) return true;
    return false;
}

static ExtendedType promote(ExtendedType ta, ExtendedType tb) {
    if (ta == T_ERROR || tb == T_ERROR)   return T_ERROR;
    if (ta == T_STRING || tb == T_STRING) return T_ERROR;
    if (ta == T_FLOAT || tb == T_FLOAT)   return T_FLOAT;
    return T_INT;
}

static bool invalid_main_function(Type t, string func_id) {
    return func_id == "main" && t != Type::T_VOID;
}

static ExtendedType current_func_type = T_ERROR;
static bool has_main_func = false;

struct Pending_var {
    string       id;
    ExtendedType type;
};

vector<Pending_var> decl_vars;
vector<ExtendedType> func_params_type;
int yylex(void);
%}

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


/* ───────── 優先權 ───────── */
%left   OR
%left   AND
%right  '!'
%nonassoc EQ NE '<' '>' LE GE
%left   '+' '-'
%left   '*' '/' '%'
%nonassoc UMINUS
%right  INC DEC


/* 指定各符號使用 union 何欄位 */
%type <tval>  type_spec
%type <tval>  const_expr
%type <tval>  boolean_expr
%type <tval>  expr
%type <tval>  array_block
%type <sval>  identifier


/* ───────── 開始符號 ───────── */
%start program

%%                      

program
    : decl_list               { TRACE("program OK\n"); }
    ;

/* ── 2. “零到多個宣告 or 函式” ── */
decl_list
    : /* empty */
    | decl_list declaration
    ;

declaration
    : const_decl
    | var_decl
    | func_def
    ;

/* ───────── 常量宣告 ───────── */
const_decl
    : CONST type_spec identifier '=' const_expr ';' {
        if (!symtab.insert($3, Kind::K_CONST, $2, {}))
            semantic_error("redeclared const",$3);
        if ($2 != $5)
            semantic_error("const type mismatch",$3);
      }
    ;


/* ───────── 變量宣告 ───────── */
var_decl
    : type_spec ident_init_list ';' { 
        for (auto& var : decl_vars) {
            string name = var.id;
            ExtendedType type = var.type;
            if (!symtab.insert(name, Kind::K_VAR, ExtendedType{$1.t, type.dims}, {}))
                semantic_error("redeclared var", name);
            if (type.t != Type::T_ERROR && !type_compatible(type, $1))
                semantic_error("type mismatch in init", "");
        }
        decl_vars.clear();
      }
    ;

ident_init_list
    : ident_init
    | ident_init ',' ident_init_list 
    ;

ident_init
    : identifier array_block {
        decl_vars.push_back({$1, $2});
      }
    | identifier '=' const_expr { 
        decl_vars.push_back({$1, $3});
      }
    ;

array_block
    : /* empty */ {
        $$ = ExtendedType{Type::T_ERROR, {}};
    }
    | '[' ICONST ']' array_block {
        vector<int> dims;
        dims.push_back($2);
        for (auto& d : $4.dims)
            dims.push_back(d);
        $$ = ExtendedType{Type::T_ERROR, dims};
    }

/* ───────── 函式定義 ───────── */
func_def
    : type_spec identifier {
          if (!symtab.insert($2, Kind::K_FUNC, $1, {})) 
              semantic_error("redeclared func", $2);
          if (string($2) == "main") 
              has_main_func = true;
          if (invalid_main_function($1.t, $2)) 
              semantic_error("invalid main function type:", SymbolTable::type2Str($1.t));
          current_func_type = $1;
          symtab.pushScope();
      } '(' param_list_opt ')' block {
          symtab.popScope();
          const Symbol *sym = symtab.lookup($2);
          sym->params = std::move(func_params_type);
          func_params_type.clear();
          current_func_type = T_ERROR;
      }
    ;

param_list_opt : /* empty */ | param_list ;

param_list
    : param
    | param_list ',' param
    ;

param
    : type_spec identifier array_block { 
          if (!symtab.insert($2, Kind::K_VAR, ExtendedType{$1.t, $3.dims}, {}))
              semantic_error("redeclared param", $2);
          func_params_type.emplace_back($1.t, $3.dims);
      }
    ;

/* ───────── Block & Statement ───────── */
block
    : '{' block_item_list '}' 
    ;

block_item_list
    : /* empty */
    | block_item_list block_item
    ;

block_item
    : declaration
    | statement
    ;

/* ------------ Statement ------------ */
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
        // cout << $1 << "<here>";
        const Symbol* sym = symtab.lookup($1);
        if (!sym) semantic_error("undeclared id",$1);
          else if (!type_compatible(sym->type, $3)) {
              // cout << SymbolTable::type2Str(sym->type) << ' ' << SymbolTable::type2Str($3) << '\n';
              semantic_error("type mismatch in assignment", $1);
          }
      }
    | identifier INC 
    | identifier DEC 
    | PRINT   expr 
    | PRINTLN expr 
    | READ    identifier 
    | /* empty */
    ;

if_stmt
    : IF '(' boolean_expr ')' simple_or_block_stmt
      { if ($3 != T_BOOL) semantic_error("if cond not bool",""); }
    | IF '(' boolean_expr ')' simple_or_block_stmt ELSE simple_or_block_stmt
      { if ($3 != T_BOOL) semantic_error("if cond not bool",""); }
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
        const Symbol* sym = symtab.lookup($3);
        if (!sym) semantic_error("undeclared id", $3);
        if (sym->type != T_INT) semantic_error("foreach loop variable must be of type int:", $3);

        const Symbol* sym2 = symtab.lookup($5);
        if (!sym2) semantic_error("undeclared id", $5);
        if (sym2->type != T_INT) semantic_error("foreach loop range must be of type int:", $5);
        const Symbol* sym3 = symtab.lookup($8);
        if (!sym3) semantic_error("undeclared id", $8);
        if (sym3->type != T_INT) semantic_error("foreach loop range must be of type int:", $8);

    }
    | FOREACH '(' identifier ':' identifier '.''.' ICONST ')' simple_or_block_stmt {
        const Symbol* sym = symtab.lookup($3);
        if (!sym) semantic_error("undeclared id", $3);
        if (sym->type != T_INT) semantic_error("foreach loop variable must be of type int:", $3);

        const Symbol* sym2 = symtab.lookup($5);
        if (!sym2) semantic_error("undeclared id", $5);
        if (sym2->type != T_INT) semantic_error("foreach loop range must be of type int:", $5);
    }
    | FOREACH '(' identifier ':' ICONST '.''.' identifier ')' simple_or_block_stmt {
        const Symbol* sym = symtab.lookup($3);
        if (!sym) semantic_error("undeclared id", $3);
        if (sym->type != T_INT) semantic_error("foreach loop variable must be of type int:", $3);
        const Symbol* sym3 = symtab.lookup($8);
        if (!sym3) semantic_error("undeclared id", $8);
        if (sym3->type != T_INT) semantic_error("foreach loop range must be of type int:", $8);
    }
    | FOREACH '(' identifier ':' ICONST '.''.' ICONST ')' simple_or_block_stmt {
        const Symbol* sym = symtab.lookup($3);
        if (!sym) semantic_error("undeclared id", $3);
        if (sym->type != T_INT) semantic_error("foreach loop variable must be of type int:", $3);
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
    : expr '+' expr { 
          ExtendedType t = promote($1, $3);
          if (t == T_ERROR) 
              semantic_error("invalid operation", "");
          $$ = t;
      }
    | expr '-' expr { 
          ExtendedType t = promote($1, $3);
          if (t == T_ERROR) 
              semantic_error("invalid operation", "");
          $$ = t; 
      }
    | expr '*' expr {
          ExtendedType t = promote($1, $3);
          if (t == T_ERROR) 
              semantic_error("invalid operation", "");
          $$ = t; 
      }
    | expr '/' expr {
          ExtendedType t = promote($1, $3);
          if (t == T_ERROR) 
              semantic_error("invalid operation", "");
          $$ = t; 
    }
    | expr '%' expr {
          ExtendedType t = promote($1, $3);
          if (t == T_ERROR) 
              semantic_error("invalid operation", "");
          $$ = t; 
    }
    | '-' expr %prec UMINUS  { $$ = $2; }
    | '(' expr ')'           { $$ = $2; }
    | ICONST                 { $$ = T_INT;   }
    | FCONST                 { $$ = T_FLOAT; }
    | SCONST                 { $$ = T_STRING;}
    | BCONST                 { $$ = T_BOOL;  }
    | identifier {
        const Symbol* sym = symtab.lookup($1);
        if (!sym) semantic_error("undeclared var",$1);
        $$ = sym ? sym->type : T_ERROR;
      }
    | identifier '(' arg_list_opt ')' {
        const Symbol* sym = symtab.lookup($1);
        if (!sym || sym->kind != Kind::K_FUNC)
            semantic_error("call of non-function", $1);
        $$ = sym ? sym->type : T_ERROR;
      }
    | boolean_expr
    ;

boolean_expr
    : expr EQ expr { 
        if (!type_compatible($1, $3)) semantic_error("expression type mismatch", ""); 
        $$ = T_BOOL;
      }
    | expr NE expr { 
        if (!type_compatible($1, $3)) semantic_error("expression type mismatch", ""); 
        $$ = T_BOOL;
      }
    | expr '>' expr { 
        if (!type_compatible($1, $3)) semantic_error("expression type mismatch", ""); 
        $$ = T_BOOL;
      }
    | expr '<' expr { 
        if (!type_compatible($1, $3)) semantic_error("expression type mismatch", ""); 
        $$ = T_BOOL;
      }
    | expr LE expr  { 
        if (!type_compatible($1, $3)) semantic_error("expression type mismatch", ""); 
        $$ = T_BOOL;
      }
    | expr GE expr  { 
        if (!type_compatible($1, $3)) semantic_error("expression type mismatch", ""); 
        $$ = T_BOOL;
      }
    | '!' expr {
        $$ = T_BOOL;
      }
    | expr AND expr {
        $$ = T_BOOL;
    }
    | expr OR expr {
        $$ = T_BOOL;
    }
    ;

const_expr  
    : ICONST { $$ = T_INT; }
    | FCONST { $$ = T_FLOAT; }
    | BCONST { $$ = T_BOOL; }
    | SCONST { $$ = T_STRING; }
    ;

type_spec
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
    | arg_list ',' expr
    ;

%%           

void yyerror(const string& msg) {
    cerr << "SYNTAX(" << linenum << "): " << msg << '\n';
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
    return 0;
}
