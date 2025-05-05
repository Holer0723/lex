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

vector<Pending_var> decl_vars;
vector<ExtendedType*> func_params_type;
vector<ExtendedType*> type_pool;

static void semantic_error(const string& msg, const string& id){
    cerr << "SEMANTIC(" << linenum << "): " << msg << ' ' << id << '\n';
    for (auto& ptr : type_pool) delete ptr;
    exit(-1);
}

static bool type_compatible(const ExtendedType* dst, const ExtendedType* src) {
    if (*dst == *src)                                 return true;
    if (dst == T_STRING || src == T_STRING)           return false;
    if (dst == T_FLOAT  && src == T_INT)              return true;
    if (dst == T_INT    && src == T_FLOAT)            return true;
    if ((dst == T_INT || dst == T_FLOAT) && src == T_BOOL) return true;
    return false;
}

static ExtendedType* promote(const ExtendedType* a, const ExtendedType* b) {
    if (a == T_ERROR || b == T_ERROR)   return T_ERROR;
    if (a == T_STRING || b == T_STRING) return T_ERROR;
    if (a == T_FLOAT  || b == T_FLOAT)  return T_FLOAT;
    return T_INT;
}

static bool invalid_main_function(Type t, string func_id) {
    return func_id == "main" && t != Type::VOID;
}

static ExtendedType* current_func_type = T_ERROR;
static bool has_main_func = false;
%}

%union{
    int            ival;
    float          fval;
    char*          sval;
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
        if (!symtab.insert($3, Kind::K_CONST, *$2, {}))
            semantic_error("redeclared const", $3);
        if ($2 != $5)
            semantic_error("const type mismatch", $3);
      }
    ;


/* ───────── 變量宣告 ───────── */
var_decl
    : type_spec ident_init_list ';' { 
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
        $$ = T_ERROR;
    }
    | '[' ICONST ']' array_block {
        vector<int> dims;
        dims.push_back($2);
        for (auto& d : $4->dims)
            dims.push_back(d);
        ExtendedType* nt = new ExtendedType{Type::ERROR, dims};
        type_pool.push_back(nt);
        $$ = nt;
    }

/* ───────── 函式定義 ───────── */
func_def
    : type_spec identifier {
          if (!symtab.insert($2, Kind::K_FUNC, *$1, {})) 
              semantic_error("redeclared func", $2);
          if (string($2) == "main") 
              has_main_func = true;
          if (invalid_main_function($1->t, $2)) 
              semantic_error("invalid main function type:", SymbolTable::type2Str($1->t));
          current_func_type = $1;
          symtab.pushScope();
      } '(' param_list_opt ')' block {
          symtab.popScope();
          Symbol *sym = symtab.lookup($2);
          for (auto* p : func_params_type)
            sym->params.push_back(*p);
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
          if (!symtab.insert($2, Kind::K_VAR, ExtendedType{$1->t, $3->dims}, {}))
              semantic_error("redeclared param", $2);
          func_params_type.push_back(new ExtendedType{ $1->t, $3->dims });
          type_pool.push_back(func_params_type.back());
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
        Symbol* sym = symtab.lookup($1);
        if (!sym) semantic_error("undeclared id",$1);
        else if (!type_compatible(&sym->type, $3)) 
            semantic_error("type mismatch in assignment", $1);
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
    : expr '+' expr { 
          ExtendedType* t = promote($1, $3);
          if (t == T_ERROR) 
              semantic_error("invalid operation", "");
          $$ = t;
      }
    | expr '-' expr { 
          ExtendedType* t = promote($1, $3);
          if (t == T_ERROR) 
              semantic_error("invalid operation", "");
          $$ = t; 
      }
    | expr '*' expr {
          ExtendedType* t = promote($1, $3);
          if (t == T_ERROR) 
              semantic_error("invalid operation", "");
          $$ = t; 
      }
    | expr '/' expr {
          ExtendedType* t = promote($1, $3);
          if (t == T_ERROR) 
              semantic_error("invalid operation", "");
          $$ = t; 
    }
    | expr '%' expr {
          ExtendedType* t = promote($1, $3);
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
        Symbol* sym = symtab.lookup($1);
        if (!sym) semantic_error("undeclared var",$1);
        $$ = sym ? &sym->type : (ExtendedType*)T_ERROR;
      }
    | identifier '(' arg_list_opt ')' {
        Symbol* sym = symtab.lookup($1);
        if (!sym || sym->kind != Kind::K_FUNC)
            semantic_error("call of non-function", $1);
        if (sym->params.size() != func_params_type.size())  
            semantic_error("function parameter count mismatch in call to function: ", $1);
        for (int i = 0; i < (int) sym->params.size(); ++i)
            if (sym->params[i] != *func_params_type[i]) 
                semantic_error("function parameter type mismatch in call to function: ", $1);
        func_params_type.clear();
        $$ = sym ? &sym->type : (ExtendedType*)T_ERROR;
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
    : expr {
        func_params_type.push_back($1);
    }
    | arg_list ',' expr {
        func_params_type.push_back($3);
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

    if (yyparse() == 0) {
        if (!has_main_func) 
            semantic_error("has no main function", "");
        puts("PASS – no errors");
    }
    for (auto& ptr : type_pool) delete ptr;
    return 0;
}
