---
title: README.md
tags: [Compiler]

---

# Programming Assignment 2 Syntactic and Semantic Definitions

> *NTUST / Compiler 2025 Spring* – **C++ 11**, GNU Flex & Bison  
> Author : 何喬熒   Student ID : B11115036

---

## 1 | Directory Layout

| Path | Purpose |
|------|---------|
| `parser.y` | Bison grammar (+ semantic actions) |
| `scanner.l` | Flex lexer (keywords, literals, comments …) |
| `SymbolTable.{h,cpp}` | Multi‑scope symbol table & function signatures |
| `makefile` | One‑command build (`make` / `make clean` / `make run-test`) |
| `test/` | Sample `.sd` source files |
| *generated* | `y.tab.c/h`, `lex.yy.c`, `*.o`, executable |

---

## 2 | Language Features

* **Primitive types** `int float bool string void`
* **Arrays** – arbitrary dimension (`int a[3][4];`)
* **Functions** – full signature/type check (arrays included)
* **Statements**  
  `if / else`, `while`, `for`, `foreach (i : lo .. hi)`, `break`, `continue`, `return`, block `{ … }`
* Built‑ins `print`, `println`, `read`
* **Semantic diagnostics**  duplicate/undeclared id, mismatched types, missing `main`, etc.

---

## 3 | Build

```bash
sudo apt install g++ flex bison        # once, on Debian/Ubuntu
make                                   # build ./mycompiler
make clean                             # remove intermediates
```

## 4 | Run
```bash
# run bundled test case
make run-test

# run your own test case
./mycompiler path/to/source.sd
```
* On success prints `PASS – no errors`
* Syntax / semantic errors are reported as
```bash
SYNTAX(23): unexpected token ...
SEMANTIC(41): type mismatch in assignment a
```
line numbers come from the lexer’s global `linenum`.

## 5 | Type‑Checking Rules

| Context                    | Accepted operands                                             | Notes                                   |
| -------------------------- | ------------------------------------------------------------- | --------------------------------------- |
| `!x`, `x && y`, `x \|\| y` | **bool only**                                                 | non‑bool → `logical operand not bool`   |
| `==`, `!=`                 | same type (string allowed)<br>or *(int ∣ float ∣ bool) mixed* | string can be compared only to string   |
| `< > <= >=`                | same type (string not allowed)<br>or *(int ∣ float ∣ bool) mixed* |                                         |
| assignment                 | destination / source must satisfy `type_compatible()`         | `int ⇄ float`, `bool→int/float` allowed |
| return                     | expression must be compatible with function return type       | void fn must not return value           |

## 6 | Extra Features Implemented

1. **`return ;` (empty return)**    
   A naked `return;` is accepted inside functions whose declared return type is `void`.
   ``` c
    void func() {
        return ;
    }
    ```

2. **Mixed declarator list can include arrays**    
    ```c
   int a, arr[2][3];
    ```
    Multiple variables—scalars and multi‑dimensional arrays—can be declared in the same statement.

3. Initializer can be any expression or function call 
    ```c
    int a = b + c,  x = add(b, c);
    ```
4. Implicit numeric promotion in arithmetic expressions

    When an int and a float appear in the same arithmetic expression,the int is implicitly promoted to float and the result type becomes float.
    ``` c
    3 + 4.5 // result type: float
    ```
    