---
title: README.md
tags: [Compiler]

---

# Programming Assignment 3: Code Generation for sD

> *NTUST / Compiler 2025 Spring* – **C++ 11**, GNU Flex & Bison  
> Author : 何喬熒   Student ID : B11115036

---

## 1 | Directory Layout

| Path                  | Purpose                                                                       |
| :-------------------- | :---------------------------------------------------------------------------- |
| `parser.y`            | Bison grammar definitions (+ semantic actions + **code generation actions**)  |
| `scanner.l`           | Flex lexer (keywords, literals, comments, etc.)                               |
| `SymbolTable.{h,cpp}` | Multi-scope symbol table & function signatures (possibly updated for codegen) |
| `CodeEmitter.{h,cpp}` | **(New)** Helper class for generating Java assembly code (Jasmin format)     |
| `makefile`            | One-command build (`make`, `make clean`, `make run-test`) |
| `test/`               | Sample `.sd` source files                                                     |
| `javaa`               | **(Provided)** Java Assembler (converts `.j` files to `.class` files)       |
| *generated*           | `y.tab.c/h`, `lex.yy.c`, `*.o`, `mycompiler` (executable), `*.j` (Jasmin file), `*.class` (Java bytecode) |

---

## 2 | Language Features

* **Primitive types** `int` `bool` `void`
* **Functions** – full signature/type check
* **Statements**  
  `if / else`, `while`, `for`, `foreach (i : lo .. hi)`, `return`, block `{ … }`
* Built‑ins `print`, `println`
* **Semantic diagnostics**  duplicate/undeclared id, mismatched types, missing `main`, etc.

---

## 3 | Build

```bash
sudo apt install g++ flex bison        # once, on Debian/Ubuntu
make                                   # build ./mycompiler


make clean                             # remove all generated file
```

## 4 | Run
```bash
# run bundled test case
make run-test

# run your own test case
./mycompiler path/to/source.sd
./javaa source.j
java source
```
* **Compiler Success Message**: On successful compilation, mycompiler should print a message like `PASS – no errors` and generate the `.j` file.

* Syntax / semantic errors are reported as
```bash
SYNTAX(23): unexpected token ...
SEMANTIC(41): type mismatch in assignment a
```
> line numbers come from the lexer’s global `linenum`.

### Example Workflow and Output:
Let's assume `test/example.sd` contains the following sD code:
```c++
// test/example.sd
void main() {
  int x = 10;
  int y = 20;
  println x + y;
  print "Hello, sD!";
}
```
After running the three steps above (`./mycompiler test/example.sd`, `./javaa example.j`, `java example`), the expected output on the console would be:
```
30
Hello, sD!
```

## 5 | Type‑Checking Rules

| Context                    | Accepted operands                                             | Notes                                   |
| -------------------------- | ------------------------------------------------------------- | --------------------------------------- |
| `!x`, `x && y`, `x \|\| y` | **bool only**                                                 | non‑bool → `logical operand not bool`   |
| `==`, `!=`                 | same type (string allowed)<br>or *(int ∣ float ∣ bool) mixed* | string can be compared only to string   |
| `< > <= >=`                | same type (string not allowed)<br>or *(int ∣ float ∣ bool) mixed* |                                         |
| assignment                 | destination / source must satisfy `type_compatible()`         | `bool→int` allowed |
| return                     | expression must be compatible with function return type       | void fn must not return value           |

    