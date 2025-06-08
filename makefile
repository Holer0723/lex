# Makefile for Project2 (separate-compile style)

# 工具
YACC      = yacc -y -d
LEX       = lex
CXX       = g++
CXXFLAGS  = -std=c++11 -g -Wall

# 執行檔名稱
TARGET    = mycompiler

# 中間檔
Y_TAB_C   = y.tab.c
Y_TAB_H   = y.tab.h
LEX_C     = lex.yy.c

# 物件檔
OBJS      = y.tab.o lex.yy.o SymbolTable.o CodeEmitter.o

# 主要規則
all: $(TARGET)

# 產生 parser
$(Y_TAB_C) $(Y_TAB_H): parser.y
	$(YACC) parser.y

# 編譯 parser 產出 y.tab.o
y.tab.o: $(Y_TAB_C)
	$(CXX) $(CXXFLAGS) -c $(Y_TAB_C) -o y.tab.o

# 產生 scanner
$(LEX_C): scanner.l $(Y_TAB_H)
	$(LEX) -o $(LEX_C) scanner.l

# 編譯 scanner 產出 lex.yy.o
lex.yy.o: $(LEX_C)
	$(CXX) $(CXXFLAGS) -c $(LEX_C) -o lex.yy.o

# 編譯 SymbolTable
SymbolTable.o: SymbolTable.cpp SymbolTable.h
	$(CXX) $(CXXFLAGS) -c SymbolTable.cpp -o SymbolTable.o

CodeEmitter.o: CodeEmitter.cpp CodeEmitter.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 連結所有物件檔
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) -ll

# 清理
clean:
	rm -f $(TARGET) $(Y_TAB_C) $(Y_TAB_H) $(LEX_C) output.j mycase.class *.OBJ

run-test: $(TARGET)
	./$(TARGET) test/mycase.sd
	./javaa output.j
	java mycase
	

.PHONY: all clean
