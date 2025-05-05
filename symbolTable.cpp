#include "symbolTable.h"


SymbolTable::SymbolTable() {
    scopes.emplace_back();
}

void SymbolTable::pushScope() {
    scopes.emplace_back();
}

void SymbolTable::popScope() {
    if (scopes.size() == 1) {
        cerr << "attempt to pop global scope\n";
        return;
    }
    archive.push_back(move(scopes.back()));
    scopes.pop_back();
}


bool SymbolTable::insert(const string& id, Kind kind, ExtendedType type, vector<ExtendedType> params) {
    Symbol sym = Symbol{id, kind, type, params};
    return scopes.back().emplace(id, sym).second;
}

Symbol* SymbolTable::lookup(const string& id) {
    for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
        auto f = it->find(id);
        if (f != it->end()) return &f->second;
    }
    return nullptr;
}

void SymbolTable::dump() {

    auto printTable = [&](const unordered_map<string, Symbol>& table) -> void {
        for (auto it : table) {
            cout << it.second.name << ' ' << kind2Str(it.second.kind) << ' ' << type2Str(it.second.type.t);
        }
    };

    for (auto it = archive.begin(); it != archive.end(); ++it) {
        printTable(*it);
    }

    for (auto it = scopes.begin(); it != scopes.end(); ++it) {
        printTable(*it);
    }
        
}

const string SymbolTable::kind2Str(Kind k) {
    switch (k) {
        case Kind::K_CONST: return "CONST";
        case Kind::K_FUNC: return "FUNC";
        case Kind::K_VAR: return "VAR";
        default: return "ERROR KIND";
    }
}

const string SymbolTable::type2Str(Type t) {
    switch (t) {
        case Type::INT:    return "INT";
        case Type::FLOAT:  return "FLOAT";
        case Type::BOOL:   return "BOOL";
        case Type::STRING: return "STRING";
        case Type::VOID:   return "VOID";
        default:           return "ERROR";
    }
}
