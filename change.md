---
title: change.md
tags: [Compiler]

---

### 1. token 改成 return 的形式
將
```
token("WHILE");
```
改成
```
token("WHILE"); return WHILE;
```

### 2. 將 SymbolTable 搬到移到 SymbolTable.h 中

### 3. 將 parser 需要的資料放入 yylval 中
```
yylval.sval = make_string(yytext, yyleng);
yylval.sval = strdup(yytext);
yylval.ival = atoi(yytext);
yylval.fval = atof(yytext);
```
> 其中 make_string 是處理 str""str -> str"str 的 function

### 4. 將原本合在一起的運算子分開
將
```
addition                   (\+\+|\+)
{addition}                 { token(yytext); }
```
改成
```
"+"                    { token("+"); return '+'; }
"++"                   { token("++"); return INC; }
```




