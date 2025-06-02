# liblv

**liblv** is a modular and extensible C utility library built to provide core functionality for systems-level programming, offering flexible memory management, dynamic containers, and a modern approach to classic C utilities.

---

## Features

- **Modular Design**: Each functionality is encapsulated in its own module for clarity and reusability.
- **Dynamic Memory Management**: Includes support for tagged allocations, optional garbage collection, and allocator safety tools like deferred cleanup.
- **String and Character Utilities**: Provides flexible string manipulation, safe copies, trimming, joining, and more.
- **Vector & Map Structures**: Includes dynamic arrays and a key-value map abstraction built over typed vectors.
- **Formatted Output**: Lightweight printf implementation with FD-based output support.
- **Numerical Conversions**: Tools for base conversions and integer-string utilities.
- **List Structures**: Classic singly-linked list implementation.
- **Get Next Line**: Streamline file descriptor reading with a reusable GNL implementation.

---

## Modules

| Module      | Description |
|-------------|-------------|
| `alloc`     | Custom allocation and memory tracking (tagged and GC-aware) |
| `chars`     | Character classification functions (`isalpha`, `isdigit`, etc.) |
| `cstr`      | Core string manipulation utilities |
| `gnl`       | `get_next_line` implementation |
| `liblv`     | Main entry header to include the entire library |
| `lst`       | Singly linked list utilities |
| `map`       | Dynamic key-value map based on vectors |
| `mem`       | Low-level memory utilities with architecture-aware optimizations |
| `nums`      | Base conversions and number-string parsing |
| `printf`    | Custom lightweight printf implementation |
| `put`       | Basic printing utilities |
| `structs`   | Definitions for types like `t_vec`, `t_map`, `t_string`, etc. |
| `tstr`      | Temp string structure with dynamic buffer and string operations |
| `vec`       | Type-safe dynamic vector implementation |

---

## Build

This project includes a `Makefile` for compilation. Simply run:

```bash
make
