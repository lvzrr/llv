# llv

`liblv` is a C utility library that provides fundamental building blocks for low-level programming. It contains custom implementations for various common programming tasks, designed for use in C projects where precise control over memory, data structures, and fundamental operations is beneficial.

This library offers a set of functionalities that often serve as alternatives or extensions to standard C library components. Its development emphasizes modularity, allowing for selective integration based on project requirements and specific performance considerations, such as memory alignment and optimized memory access patterns.

---

## Memory Management

`liblv` includes its own suite of memory allocation and deallocation functions. This module facilitates **aligned memory allocation**, which can be critical for performance in certain computing contexts. Deallocation routines are designed to enhance programming safety by automatically nullifying pointers after memory is freed. The library also provides optimized low-level operations for direct memory manipulation, such as setting, copying, moving, comparing, and searching within memory blocks, often with performance considerations in mind. Mechanisms for automatic resource cleanup via compiler attributes are also integrated.

---

## Dynamic Data Structures

This section of `liblv` provides implementations of common dynamic containers. It features a generic **vector (`t_vec`)**, capable of storing elements of arbitrary types and dynamically resizing as needed. A **singly linked list (`t_list`)** offers a flexible structure for chained data organization. Additionally, a custom **dynamic string type (`t_string`)** is included, which manages its own capacity and length, simplifying string manipulation tasks. These structures include their own functions for creation, modification, and destruction.

---

## Core Utilities

`liblv` offers a collection of general-purpose utilities. This includes comprehensive functions for **C-style string manipulation**, covering operations like duplication, searching, concatenation, comparison, and tokenization. Basic **character classification** and case conversion routines are also provided. For numerical operations, the library contains functions for converting between string and integer representations, including specialized routines for different number bases. Input and output capabilities are present, with a custom formatted printing interface and a utility for reading lines from file descriptors.

---

## Design and Integration

The library is designed for **modularity**, allowing individual components to be integrated into projects based on specific needs without requiring the entire library. Its implementations often leverage **compiler attributes** for features such as enforcing specific memory alignment for data types and facilitating automatic resource management. This approach aims to provide a consistent and controlled environment for C development, focusing on efficiency and explicit control.

---

## Documentation

Each function and significant structure within `liblv` is documented using a **comment-style format** directly within the source code. These comments provide details on function purpose, parameters, return values, and any specific notes or behaviors.

---

## Compatibility

`liblv` is written in C and primarily utilizes features from the C99 standard, with some components potentially leveraging C11 or later features. The use of compiler-specific extensions, such as `__attribute__` for alignment and cleanup, indicates primary compatibility with **GCC and Clang** compilers. While efforts are made to ensure portability, specific compiler environments may require adjustments.

---

## License

`liblv` is free software: you can redistribute it and/or modify it under the terms of the **GNU General Public License** as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
