# CSCI 2021: Machine Architecture and Organization

My coursework for CSCI 2021 in Spring 2022 at the University of Minnesota. The course covers C programming fundamentals and how they relate to machine architecture. Key concepts include binary data representation, x86-64 assembly, memory hierarchy, cache performance, and heap allocation. Everything here is written in C or x86-64 assembly and is intended to be run on Linux.

The course website of a later offering (so some assignment details may differ): <https://kauffman77.github.io/2021/>


## Repository layout

| Folder | Contents |
|---|---|
| [`p1-code(v1)/`](p1-code%28v1%29/) | P1: stock price analysis and a hash map in C |
| [`p2-code/`](p2-code/) | P2: thermometer display driver with bit operations, and a GDB puzzle |
| [`p3-code/`](p3-code/) | P3: the thermometer display driver rewritten in x86-64 assembly |
| [`p4-code/`](p4-code/) | P4: performance optimization and search benchmarks |
| [`p5-code/`](p5-code/) | P5: explicit-list heap allocator |
| [`bomb424/`](bomb424/), [`bomb425/`](bomb425/), [`bomb430/`](bomb430/) | Binary bomb labs: reverse engineering x86-64 executables with GDB |
| `lab*-code/`, [`hw01-code/`](hw01-code/) | Weekly labs and homework; see [Labs](#labs) |


## Projects

### P1: Stock analysis and hash map

[`p1-code(v1)/`](p1-code%28v1%29/) has two unrelated C programs. The first reads stock prices from a text file. It finds the low and high values, identifies the best buy/sell interval in one O(N) pass, and produces an ASCII chart that marks the low, high, and holding period. The second program is a string-to-string hash map with separate chaining. It supports rehashing into a larger prime-sized table.

> **Note:** This folder currently contains an early version of `stock_funcs.c` and does not include the hash map source files. As is, it does not build with `make`. I plan to add the final version.

- **Files I wrote:** `stock_funcs.c`, `hashmap_funcs.c`, `hashmap_main.c`
- **Topics:** `malloc`/`free`, pointers and structs, file I/O, hash tables

### P2: Thermometer display, bit manipulation, and GDB

[`p2-code/`](p2-code/) simulates a digital thermometer's display firmware. It reads a temperature sensor port and a status port, converts the fixed point reading, rounds it, and constructs the 32-bit value for a four-digit seven-segment LCD. The display handles negative values, Celsius/Fahrenheit mode, errors, and leading-zero suppression. The second portion is `puzzlebox`, a multistage input puzzle solved with GDB.

- **Files I wrote:** `thermo_update.c`, `input.txt`
- **Topics:** masks and shifts, fixed point arithmetic, memory-mapped I/O, structs passed by value and pointer, GDB
- **Run:** `./thermo_main <sensor_value> C|F`


### P3: Thermometer in x86-64 assembly

[`p3-code/`](p3-code/) reimplements the three P2 display functions, `set_temp_from_ports`, `set_display_from_temp`, and `thermo_update`, in x86-64 assembly using AT&T syntax. The hybrid build lets the C and assembly implementations be combined so individual functions can be tested separately. This directory also includes `bomb425/`.

- **File I wrote:** `thermo_update_asm.s` (~240 lines)
- **Topics:** System V calling convention, pointer-based struct access, structs passed in registers, RIP-relative globals, lookup tables and scaled-index addressing, signed division with `idiv`
- **Run:** `make test-hybrid` for the mixed C/assembly tests

### P4: Performance optimization

[`p4-code/`](p4-code/) covers optimization and empirical performance testing.

For the matrix portion, I optimized a computation of A<sup>T</sup>A. My version, `matata_OPTM`, skips building the transpose, iterates through memory in row-major order (to match the C convention), removes accessor calls from the inner loop by working on plain arrays, and takes advantage of symmetry to reduce the number of operations. The largest test case ran about 10.8 times faster than the baseline on the course server. The second portion compares four search implementations as input size grows. The search algorithms are linear search over an array, linear search over a linked list, binary search over a sorted array, and a binary search tree.

Results from [`P4-WRITEUP.txt`](p4-code/P4-WRITEUP.txt), measured on the course lab server:

| Matrix size | Baseline (s) | Optimized (s) | Speedup |
|---:|---:|---:|---:|
| 171 | 0.0322 | 0.0105 | 3.06x |
| 196 | 0.0476 | 0.0155 | 3.06x |
| 256 | 0.1375 | 0.0350 | 3.93x |
| 320 | 0.2515 | 0.0657 | 3.83x |
| 801 | 4.692 | 1.011 | 4.64x |
| 1024 | 23.99 | 2.226 | 10.78x |

- **Files I wrote:** `matata_optm.c`, `search_benchmark.c`, `P4-WRITEUP.txt`
- **Topics:** cache locality, loop ordering, row-major memory layout, symmetry, benchmarking with `clock()`, contiguous versus pointer-heavy data structures
- **Run:** `./matata_benchmark` and `./search_benchmark 9 14 10`  
  The three numbers are the minimum power of two, maximum power of two, and repetitions. Add `la`, `ll`, `bl`, or `bt` to choose specific searches.

### P5: Explicit-list heap allocator

[`p5-code/`](p5-code/) implements a small replacement for `malloc` and `free`. It creates and manages its own heap with `mmap()` at a fixed address.

Every block stores a header containing its size, status, and list links, and a footer containing its size. That layout makes it possible to find adjacent blocks in constant time. Free and allocated blocks are maintained in separate explicit doubly linked lists with sentinel nodes. Allocation uses first fit and splits blocks when appropriate. Freeing merges neighboring free blocks. The heap can grow by mapping additional pages at its end.

- **Files I wrote:** required functions in `el_malloc.c`, including `el_malloc`, `el_free`, `el_split_block`, `el_merge_block_with_above`, `el_append_pages_to_heap`, `el_find_first_avail`, and the block/list helpers
- **Topics:** heap layout, boundary tags, pointer arithmetic, doubly linked lists, `mmap()`, fragmentation
- **Run:** `./el_demo`

## Labs

| Folder | Topic |
|---|---|
| [`hw01-code/`](hw01-code/) | C basics and separate compilation |
| [`lab01-code-1/`](lab01-code-1/) | Unix environment setup |
| [`lab02-code/`](lab02-code/) | Linked lists |
| [`lab03-code/`](lab03-code/) | File I/O and structs |
| [`lab05-code/`](lab05-code/) | Bit masking |
| [`lab06-code/`](lab06-code/) | GDB |
| [`lab07-code/`](lab07-code/), [`lab07-bonus-code/`](lab07-bonus-code/) | Assembly with structs |
| [`lab08-code/`](lab08-code/) | Assembly: stack frames and function calls |
| [`lab10-code/`](lab10-code/) | Superscalar execution |
| [`lab11-code/`](lab11-code/) | Cache behavior and memory stride |
| [`lab12-code/`](lab12-code/) | Preprocessor macros |
| [`lab14-code/`](lab14-code/) | Binary files and `mmap()` |

## Building and running

The projects require x86-64 Linux, `gcc`, and `make`. Many tests use `valgrind`, and the debugging exercises use `gdb`. Every project can be built and tested the same way:

```bash
cd p5-code
make                        # build
make test                   # run all tests
make test-prob1 testnum=3   # run one test
```

The P4 benchmark has warnings when it is not running on the course's `csel-atlas` server.

## Acknowledgments

- Chris Kauffman wrote the assignments, starter code, and the GPLv3 `testy` runner.
- Mark Snyder and Chris Kauffman created `puzzlebox`.
- Randal Bryant and David O'Hallaron created the binary bomb lab.
