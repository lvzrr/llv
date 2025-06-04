# llv, A Low-Level C Utility Library

**llv** is a lightweight, fast, low-level utility library for C. It’s made for devs who want full control over memory and data without relying on the standard library. No runtime magic, no bloated abstractions. Just you, the stack, and some disciplined bytes.

## 📦 Modules at a Glance

```
+-----------------------+
|     llv Modules       |
+-----------------------+
| Memory    - alloc, mem|
| Strings   - cstr, tstr|
| Vectors   - vec       |
| Lists     - lst       |
| Numbers   - num       |
| IO/Utils  - in, out   |
| Parsing   - is        |
+-----------------------+
```

## 🧬 Memory

* Custom allocator with 128-byte alignment
* Manual cleanup + `__attribute__((cleanup))` support
* Nulls pointers after free (safety first)
* Optimized `memcpy`, `memmove`, `memset`, `memcmp`, `memswap`, `memffb`
* Arena allocator for bursty short-lived allocations

## 📚 Data Structures

* `t_vec`: dynamic vector (generic, resizes on growth)
* `t_list`: singly linked list
* `t_string`: dynamic string with length and capacity tracking

## 🔤 Strings and Utilities

* Full custom C-string lib:

* `strdup`, `strlen`, `strcmp`, `strchr`, `strjoin`, `strtrim`, etc.
* Number parsing/printing with base support
* Minimal I/O (line reader, tiny printf)

## 🔧 Design

* Modular: only compile what you use
* Heavy use of compiler attributes (alignment, cleanup, inline)
* Defensive defaults: NULL checks, sane fallbacks
* Tiny macros (`LV_DEFER`, etc) to ease resource cleanup

## ⚙️ Compatibility

* C99 with hints of C11
* Works best with GCC/Clang
* Focused on Linux/Unix dev environments

## 🧭 Philosophy

* Don’t hide memory, make it obvious
* No surprise allocations
* Functions do one thing
* Built like a mix of:

* Rust (RAII, cleanup, deterministic memory)
* Go (predictability)
* C++ (performance and inlining)

## 📄 License

[GNU GPLv3](https://www.gnu.org/licenses/)
Free to use, modify, or turn into a cursed fork.

## TODO:

- [ ] Improve vector API (iterators, etc ...)
- [ ] Review tstr and test it
- [ ] String formatting macros
