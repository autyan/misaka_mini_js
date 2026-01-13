# misaka_mini_js

A minimal JavaScript runtime written in C for learning and experimentation.

This repository is an educational JS runtime that focuses on clarity and system design
over performance or ECMAScript completeness.

## Status

This project is in the pre-compiler stage. The current focus is on:

- CLI and application flow
- Runtime entry selection
- Cross-platform filesystem helpers
- Streaming input and encoding detection

## Build

### Requirements

- CMake 3.20+
- C17-capable compiler (GCC/Clang)

### Build from source

```bash
cmake -S . -B build
cmake --build build
```

The output binary is written to `build/minijs`.

## Usage

### Run a JavaScript file

```bash
./build/minijs run path/to/file.js
```

### Run a project directory

```bash
./build/minijs run path/to/project
```

Project entry resolution:

1. `main.js`
2. `index.js`

If no entry is found, the runtime returns an error.

## Encoding Policy

- Default encoding is UTF-8.
- UTF-8 with BOM is accepted.
- UTF-16/UTF-32 are detected but currently rejected until a decoder is implemented.

## Project Layout

```text
include/
  app/         # Application entry API
  cli/         # CLI parsing
  common/      # Errors, console, utilities
  platform/    # Cross-platform filesystem helpers
  runtime/     # Runtime interfaces and stream IO
src/
  app/
  cli/
  common/
  platform/
  runtime/
```

## Design Goals

- Readability over performance
- Clear layering between CLI, runtime, and platform
- Simple, explicit behavior

## Non-Goals

- Full ECMAScript compliance
- JIT compilation
- Production readiness

## License

MIT
