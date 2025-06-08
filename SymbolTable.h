#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

enum class Type {
    INT,
    FLOAT,
    BOOL,
    STRING,
    VOID,     
    ERROR     
};

enum class Kind {
    K_CONST,
    K_FUNC,
    K_VAR,
};

struct Literal {
    enum Tag { NONE, INT, BOOL, STR } tag = NONE;
    int         ival;
    bool        bval;
    string      sval;
};

struct ExtendedType {
    Type        t;
    vector<int> dims;
    Literal     lit;
    string      code;
    bool operator==(const ExtendedType& o) const { return t == o.t && dims == o.dims; }
    bool operator!=(const ExtendedType& o) const { return !(*this == o); }
    ExtendedType(Type t, vector<int> d) : t(t), dims(d) {};
};


struct Symbol {
    int                  index;
    string               name;
    Kind                 kind;
    ExtendedType         type;
    vector<ExtendedType> params;
};

class SymbolTable {
private:
    vector<unordered_map<string, Symbol>> scopes;

public:
    static const string kind2Str(Kind k);
    static const string type2Str(Type t);

    SymbolTable();

    void pushScope();
    void popScope();
    void dump();
    
    int depth();

    bool insert(const string& id, Kind kind, ExtendedType type, vector<ExtendedType> params);
    Symbol* lookup(const string& id);
};