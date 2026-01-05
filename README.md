# misake_mini_js

A minimal JavaScript runtime implemented in C, designed for learning and experimentation with JavaScript engine internals.

`misake_mini_js` is a lightweight JavaScript runtime implemented from scratch in **C (C17 standard)**.

The primary goal of this project is to gain a practical, engineering-level understanding of the core components of a JavaScript engine, including:

* Lexical analysis (Lexer)
* Syntax parsing (Parser)
* Abstract Syntax Tree (AST)
* Virtual Machine (VM) execution model

> ⚠️ This project is intended for learning and experimentation purposes. It is **not** a complete implementation of the ECMAScript specification, nor is it designed for performance or production use.

---

## Features

* Implemented in **C (C17 standard)**
* Built and tested with **GCC**
* Hand-written Lexer and Parser
* AST-based execution model
* Simple stack-based virtual machine
* Clear and minimal internal architecture
* Focused on educational value

---

## Platform Support

At the current stage:

* **Operating System**: Linux
* **Distribution**: Fedora 42
* **Compiler**: GCC (Clang is not supported yet)

Multi-platform support (other Linux distributions, Clang, macOS, etc.) will be considered **after the first core milestone**.

---

## Build

### Requirements

* Fedora 42
* GCC (with C17 support)
* GNU Make

### Build from source

```bash
make
```

Build output example:

```bash
./minijs
```

---

## Usage

### Run a JavaScript file

```bash
./minijs examples/hello.js
```

### Example

```js
print(1 + 2);
```

---

## Project Structure

```text
src/
├── lexer.c        # Lexical analysis
├── parser.c       # Syntax parsing
├── ast.c          # Abstract Syntax Tree
├── vm.c           # Virtual machine implementation
├── runtime.c      # Runtime environment
└── main.c         # Program entry
```

---

## Design Goals

* **Readability over performance**
* **Clear separation of compilation stages**
* **Minimal and explicit feature set**
* **Educational value first**

The project prioritizes clarity and correctness of implementation over completeness or optimization.

---

## Non-Goals

* Full ECMAScript compliance
* JIT compilation
* Advanced garbage collection
* Browser or Node.js compatibility

---

## Roadmap

* [ ] Variables and lexical scope
* [ ] Function calls and closures
* [ ] Control flow (`if`, `while`)
* [ ] Basic memory management / GC prototype
* [ ] Execution model refinements

---

## License

This project is licensed under the **MIT License**.

The MIT license template used is the standard **GitHub MIT License** template.
See the [LICENSE](LICENSE) file for details.

---

## Acknowledgements

* ECMAScript® Language Specification
* Crafting Interpreters
* Various open-source language runtime implementations
