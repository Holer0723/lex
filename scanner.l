%{
#include <iostream>
#include <string>
#include "symbolTable.h"
#include "y.tab.h"

using namespace std;

int linenum = 1;
string buffer;

void multicomment(const char* text, int length) {
    string comment(text, text + length), output;
    for (auto& c : comment) {
        if (c != '\n') {
            output += c;
        } else {
            cout << linenum++ << ": " << output << '\n';
            output.clear();
        }
    }
}

char* make_string(const char* str, int length) {
    string res;
    for (int i = 1; i < length - 1; ++i) {
        if (str[i] == '\"') {
            if (i + 1 < length - 1 && str[i + 1] == '\"') {
                res += '\"';
                i++;
            }
        } else {
            res += str[i];
        }
    }
    return strdup(res.c_str());
}

#define LIST buffer += yytext;
#define token(tok) { LIST cout << "<" << tok << ">\n"; }
#define tokenString(tok, s) { LIST cout << '<' << tok << ":" << s << ">\n"; }
#define tokenInteger(tok, s) { LIST cout << '<' << tok << ":" << s << ">\n"; }
%}

print           print

id              [a-zA-Z][a-zA-Z0-9]*
integer         [+-]?[0-9]+
string          \"([^"]|\"\")*\"
relational      (<|<=|>=|>|==|!=)
mulcomment      "/*"([^*]|\*+[^*/])*\*+"/\n"
real            [+-]?([0-9]+\.[0-9]*|\.[0-9]+)([Ee][+-]?[0-9]+)?

%%

"//".*\n                { cout << linenum++ << ": " << yytext; }

{mulcomment}           { multicomment(yytext, yyleng); }

"."                    { token("'.'"); return '.'; }
","                    { token("','"); return ','; }
":"                    { token("':'"); return ':'; }
";"                    { token("';'"); return ';'; }
"("                    { token("'('"); return '('; }
")"                    { token("')'"); return ')'; }
"{"                    { token("'{'"); return '{'; }
"}"                    { token("'}'"); return '}'; }
"]"                    { token("']'"); return ']'; }
"["                    { token("'['"); return '['; }

"=="                   { token("=="); return EQ; }
"!="                   { token("!="); return NE; }
"<="                   { token("<="); return LE; }
">="                   { token(">="); return GE; }
"&&"                   { token("&&"); return AND; }
"||"                   { token("||"); return OR; }
"<"                    { token("<"); return '<'; }
">"                    { token(">"); return '>'; }

"++"                   { token("++"); return INC; }
"--"                   { token("--"); return DEC; }

"+"                    { token("+"); return '+'; }
"-"                    { token("-"); return '-'; }
"*"                    { token("*"); return '*'; }
"/"                    { token("/"); return '/'; }
"%"                    { token("%"); return '%'; }
"="                    { token("="); return '='; }
"!"                    { token("!"); return '!'; }

"bool"                 { token("BOOL"); return TBOOL; }
"break"                { token("BREAK"); return BREAK; }
"case"                 { token("CASE"); return CASE; }
"char"                 { token("CHAR"); return TCHAR; }
"const"                { token("CONST"); return CONST; }
"continue"             { token("CONTINUE"); return CONTINUE; }
"default"              { token("DEFAULT"); return DEFAULT; }
"do"                   { token("DO"); return DO; }
"double"               { token("DOUBLE"); return TDOUBLE; }
"else"                 { token("ELSE"); return ELSE; }
"extern"               { token("EXTERN"); return EXTERN; }
"false"                { token("FALSE"); yylval.ival = 0; return BCONST; }
"float"                { token("FLOAT"); return TFLOAT; }
"for"                  { token("FOR"); return FOR; }
"foreach"              { token("FOREACH"); return FOREACH; }
"if"                   { token("IF"); return IF; }
"int"                  { token("INT"); return TINT; }
"print"                { token("PRINT"); return PRINT; }
"println"              { token("PRINTLN"); return PRINTLN; }
"read"                 { token("READ"); return READ; }
"return"               { token("RETURN"); return RETURN; }
"string"               { token("STRING"); return TSTRING; }
"switch"               { token("SWITCH"); return SWITCH; }
"true"                 { token("TRUE"); yylval.ival = 1; return BCONST; }
"void"                 { token("VOID"); return TVOID; }
"while"                { token("WHILE"); return WHILE; }

{string}               {
                          tokenString("string", string(yytext + 1, yyleng - 2));
                          yylval.sval = make_string(yytext, yyleng);
                          return SCONST;
                       }

{id}                   {
                          tokenString("ID", yytext);
                          yylval.sval = strdup(yytext);
                          return ID;
                       }

{integer}              {
                          tokenInteger("INTEGER", yytext);
                          yylval.ival = atoi(yytext);
                          return ICONST;
                      }

{real}                 {
                          tokenString("REAL", yytext);
                          yylval.fval = atof(yytext);
                          return FCONST;
                      }

[ \t]+                 { LIST }

\n                     { LIST cout << linenum++ << ": " << buffer; buffer.clear(); }

.                      {
                         cerr << "LEX(" << linenum << "): bad char '" << yytext << "'\n";
                         exit(1);
                      }

<<EOF>>                {
                          LIST cout << linenum++ << ": " << buffer << '\n';
                          buffer.clear();
                          return 0;
                      }
%%