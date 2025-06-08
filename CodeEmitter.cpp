// CodeEmitter.h (Revised for PA3 specifics)
#include "CodeEmitter.h"

// Forward declare SymbolTable stuff if needed, or include its header

CodeEmitter::CodeEmitter() : labelCounter(0), out_stream(&cout), current_class_name_("example"), isMain(false) {} // Default class name

void CodeEmitter::openClass(const std::string &cls) {
    current_class_name_ = cls;
    emitLine("class " + cls + "\n{");
}

void CodeEmitter::closeClass() {
    emitLine("}");
}

void CodeEmitter::setOutputStream(ostream& os) {
    out_stream = &os;
}

// ... (setOutputFile, emitLine, emitComment, emitLabel, newLabel as before) ...
void CodeEmitter::emitLine(const string& line) { (*out_stream) << line << endl; }
void CodeEmitter::emit(const string& ele) { (*out_stream) << ele; }
void CodeEmitter::emitComment(const string& comment) { (*out_stream) << "; " << comment << endl; }

string CodeEmitter::emitLabel(const string& label) { return label + ":\n"; }

string CodeEmitter::newLabel() { return to_string(labelCounter++); }
string CodeEmitter::getLebelCounter() { return to_string(labelCounter); }


void CodeEmitter::declareField(const ExtendedType* type, const string& id, const string val) {
    (*out_stream) << "field static " << getJasminUserType(type) << " " << id << (val != "None" ? " = " + val : "") << endl;
}


void CodeEmitter::beginMethod(const ExtendedType* ret_type, const string& id, const vector<string>& params, bool isMain = false) {
    string sig;
    sig += '(';
    if (id == "main") {
        sig += "java.lang.String[]";
    } else { 
        for (size_t i = 0; i < params.size(); ++i) {
            if (i) sig += ", ";
            sig += params[i];
        }
    }
    sig += ')';

    emitLine("method public static " + getJasminUserType(ret_type) + " " + id + sig);
    emitLine("max_stack 100");
    emitLine("max_locals 100");
    emitLine("{");
    this->isMain = isMain;
}

void CodeEmitter::endMethod() {
    if (isMain) emitLine("return");
    emitLine("}");
    this->isMain = false;
}

// --- JVM Type Helpers (PA3 Specific) ---

string CodeEmitter::getLiteralOf(const Literal lit) {
    switch (lit.tag) {
        case Literal::INT: return to_string(lit.ival);
        case Literal::BOOL: return to_string(lit.bval);
        case Literal::STR: return lit.sval;
        default: return "None";
    }
}


// For user-friendly types in field/method declarations in Jasmin
// Produces "int", "void", "java.lang.String"
string CodeEmitter::getJasminUserType(const ExtendedType* type) {
    if (!type) return "void";
        switch (type->t) {
        case Type::INT:    return "int"; // As per 'putstatic int example.a'
        case Type::BOOL:   return "boolean"; // Booleans treated as int for fields/locals
        case Type::VOID:   return "void";
        case Type::STRING: return "java.lang.String"; // For print method signature
        default:
            // cerr << "Warning: getJasminUserType called with unexpected sD type." << endl;
            return "unknown_sD_type"; // Or throw error
    }
}

// For sD source-like types in Jasmin method signatures (e.g., "method ... add(int, int)")
string CodeEmitter::getSdTypeForJasminSignature(const ExtendedType* type) {
    if (!type) return "void"; // Should not happen for params
        switch (type->t) {
        case Type::INT:    return "int";
        case Type::BOOL:   return "int"; // sD bool params are int in Jasmin
        // case Type::STRING: return "java.lang.String"; // sD functions don't take string params in PA3
        case Type::VOID:   return "void"; // For return type
        default:
            return "unknown_sD_type_sig";
    }
}


// --- Specific Instructions (PA3 Focused) ---
string CodeEmitter::emitLoadInt(int index) { return "iload " + to_string(index) + "\n"; }
string CodeEmitter::emitStoreInt(int index) { return "istore " + to_string(index) + "\n"; }
// NO aload/astore as sD has no string variables in PA3

string CodeEmitter::emitGetStaticInt(const string& fieldName) { // type is always 'int' for sD globals
    return "getstatic int " + current_class_name_ + "." + fieldName + "\n";
}

string CodeEmitter::emitPutStatic(const ExtendedType exprType, const string& fieldName) { // type is always 'int' for sD globals
    string param_descriptor;
    switch(exprType.t) {
        case Type::INT:
        case Type::BOOL: // Booleans printed as integers 0 or 1
            param_descriptor = "int ";
            break;
        case Type::STRING:
            param_descriptor = "java.lang.String ";
            break;
        default:
            emitComment("ERROR: Unsupported type for print: ");
            return "";
    }
    return "putstatic " + param_descriptor + current_class_name_ + "." + fieldName + "\n";
}

// Handles iconst_n and sipush based on value for integers/booleans
string CodeEmitter::emitLoadConstantInt(int val) {
    if (val >= 0 && val <= 1) {
        return "iconst_" + to_string(val) + "\n";
    } else if (val >= -32768 && val <= 32767) { // sipush range, covering bipush too
        return "sipush " + to_string(val) + "\n";
    } else {
        // ldc int is also possible but sipush covers a wide range for sD integers
        return "ldc " + to_string(val) + "\n"; // Fallback, Jasmin assembler might optimize
    }
}

string CodeEmitter::emitLoadConstantString(const string& str_val) {
    // Jasmin expects strings to be quoted if they contain spaces or special chars.
    // The input SCONST from lexer already handles internal quotes ("").
    // Ensure quotes are properly escaped for the ldc instruction itself if needed by your assembler.
    // For standard Jasmin, "ldc \"hello world\"" is fine.
    string escaped_str = str_val; // Basic placeholder for now.
                                        // Real escaping might be needed if str_val can contain '"' or '\'
                                        // that aren't part of the sD literal representation.
                                        // However, sD "" means a single quote, so lexer should handle this.
    return "ldc \"" + escaped_str + "\"\n";
}

string CodeEmitter::emitInvokeStatic(const ExtendedType exprType, const string& methodName, int paramsize) {
    string param_descriptor;

    switch(exprType.t) {
        case Type::INT:
            param_descriptor = " int ";
            break;
        case Type::BOOL:
            param_descriptor = " boolean ";
            break;
        case Type::VOID:
            param_descriptor = " void ";
            break;
        case Type::STRING:
        default:
            // Should be caught by semantic analysis before codegen
            emitComment("ERROR: Unsupported type for print: ");
            return "";
    }

    string p;
    for (int i = 0; i < paramsize; ++i) {
        p += "int";
        if (i + 1 < paramsize) p += ", ";
    }
    return "invokestatic" + param_descriptor + current_class_name_ + "." + methodName + "(" + p +")\n";

}

// For print/println
string CodeEmitter::emitInvokeVirtualPrint(const ExtendedType* exprType, bool isPrintln) {
    string method_name = isPrintln ? "println" : "print";
    string param_descriptor;

    switch(exprType->t) {
        case Type::INT:
            param_descriptor = "(int)";
            break;
        case Type::BOOL: // Booleans printed as integers 0 or 1
            param_descriptor = "(boolean)";
            break;
        case Type::STRING:
            param_descriptor = "(java.lang.String)";
            break;
        default:
            // Should be caught by semantic analysis before codegen
            emitComment("ERROR: Unsupported type for print: " + getJasminUserType(exprType));
            return "";
    }
    // Assumes the PrintStream object is already on the stack (via getstatic System/out)
    return "invokevirtual void java.io.PrintStream." + method_name + param_descriptor + "\n";
}

// Standard arithmetic/logical (directly from PA3 table)
string CodeEmitter::emitIADD() { return "iadd\n"; }
string CodeEmitter::emitISUB() { return "isub\n"; }
string CodeEmitter::emitIMUL() { return "imul\n"; }
string CodeEmitter::emitIDIV() { return "idiv\n"; }
string CodeEmitter::emitIREM() { return "irem\n"; }
string CodeEmitter::emitINEG() { return "ineg\n"; }
string CodeEmitter::emitIAND() { return "iand\n"; } // For &&
string CodeEmitter::emitIOR()  { return "ior\n";  } // For ||
string CodeEmitter::emitIXOR() { return "ixor\n"; } // For ! (boolean not: 1 ^ operand -> if operand 0, result 1; if 1, result 0)

// Control Flow (as per PA3 examples)
string CodeEmitter::emitIFEQ(const string& label) { return "ifeq " + label + "\n"; }
string CodeEmitter::emitIFNE(const string& label) { return "ifne " + label + "\n"; }
string CodeEmitter::emitIFLT(const string& label) { return "iflt " + label + "\n"; }
string CodeEmitter::emitIFGT(const string& label) { return "ifgt " + label + "\n"; }
// PA3 uses ifle as <= and ifge as >= in the table, but if_acmpeq etc. for objects
// For integer comparisons as shown (a < b -> isub, iflt), these direct int comparisons are fine.
string CodeEmitter::emitIFLE(const string& label) { return "ifle " + label + "\n"; } // if less than or equal to 0
string CodeEmitter::emitIFGE(const string& label) { return "ifge " + label + "\n"; } // if greater than or equal to 0
string CodeEmitter::emitGOTO(const string& label) { return "goto " + label + "\n"; }

// Return instructions
string CodeEmitter::emitIRETURN() { return "ireturn\n"; } // For int/bool returning functions
string CodeEmitter::emitRETURN()  { return "return\n";  } // For void functions

