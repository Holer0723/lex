#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

enum class Type {
    T_INT,
    T_FLOAT,
    T_BOOL,
    T_STRING,
    T_VOID,     
    T_ERROR     
};

enum class Kind {
    K_CONST,
    K_FUNC,
    K_VAR,
};

// struct ArrayDesc {
//     vector<int> dims;
//     bool operator==(const ArrayDesc& o) const { return dims == o.dims; }
// };

// struct ExtendedType {
//     Type      type;
//     ArrayDesc arr;
// };

// struct FuncSig {
//     Type                 ret;
//     vector<ExtendedType> params;
// };

struct Symbol {
    string   name;
    Kind     kind;
    Type     type;
    // FuncSig* func;
};

class SymbolTable {
private:
    vector<unordered_map<string, Symbol>> scopes;
    vector<unordered_map<string, Symbol>> archive;

public:
    static const string kind2Str(Kind k);
    static const string type2Str(Type t);

    SymbolTable();

    void pushScope();

    void popScope();

    bool insert(const string& id, Kind kind, Type type);

    const Symbol* lookup(const string& id) const;

    void dump();
};