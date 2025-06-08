#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream> 
#include "SymbolTable.h"

using namespace std;


class CodeEmitter {
public:
    CodeEmitter(); // Default class name

    void openClass(const string & cls);
    void closeClass();

    void setOutputStream(ostream& os);

    void emitLine(const string& line);
    void emit(const string& ele);
    void emitComment(const string& comment); 
    
    string emitLabel(const string& label); 
    

    // --- JVM Type Helpers (PA3 Specific) ---

    // For type descriptors in instructions like getstatic, putstatic, invokestatic signatures
    // Produces "I" for int/bool, "Ljava/lang/String;" for String, "V" for void.
    static string getLiteralOf(const Literal lit);
    static string getJvmTypeDescriptor(const ExtendedType* type);
    static string getJasminUserType(const ExtendedType* type);
    static string getSdTypeForJasminSignature(const ExtendedType* type);

    string newLabel(); 
    string getLebelCounter();

    int newSymbol();
    int getSymbolCounter();

    void declareField(const ExtendedType* type, const string& id, const string val);

    void beginMethod(const ExtendedType* ret_type, const string& id, const vector<string>& params, bool isMain);
    void endMethod();

    string emitLoadInt(int index);
    string emitStoreInt(int index);


    string emitGetStaticInt(const string& fieldName);
    string emitPutStatic(const ExtendedType exprType, const string& fieldName);

    string emitLoadConstantInt(int val);
    
    string emitLoadConstantString(const string& str_val);

    string emitInvokeStatic(const ExtendedType exprType, const string& methodName, int paramsize);
    
    // For print/println
    string emitInvokeVirtualPrint(const ExtendedType* exprType, bool isPrintln);

    // Standard arithmetic/logical (directly from PA3 table)
    string emitIADD();
    string emitISUB();
    string emitIMUL();
    string emitIDIV();
    string emitIREM();
    string emitINEG();
    string emitIAND(); 
    string emitIOR(); 
    string emitIXOR(); 

    // Control Flow (as per PA3 examples)
    string emitIFEQ(const string& label);
    string emitIFNE(const string& label);
    string emitIFLT(const string& label);
    string emitIFGT(const string& label);
    // PA3 uses ifle as <= and ifge as >= in the table, but if_acmpeq etc. for objects
    // For integer comparisons as shown (a < b -> isub, iflt), these direct int comparisons are fine.
    string emitIFLE(const string& label); // if less than or equal to 0
    string emitIFGE(const string& label); // if greater than or equal to 0
    string emitGOTO(const string& label);

    // Return instructions
    string emitIRETURN(); // For int/bool returning functions
    string emitRETURN(); // For void functions


private:
    int labelCounter, symbolCounter;
    ostream* out_stream;
    bool isMain;
    string current_class_name_; // Store the class name for getstatic/putstatic etc.
    // ofstream file_stream; // If writing to a file, manage in main or class constructor
};

