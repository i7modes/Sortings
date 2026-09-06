# Classical & Modern Sorting Algorithms in C

[![CI](https://github.com/i7modes/Sortings/actions/workflows/ci.yml/badge.svg)](https://github.com/i7modes/Sortings/actions/workflows/ci.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![Standard](https://img.shields.io/badge/C-C99-00599C.svg?logo=c)](https://en.wikipedia.org/wiki/C99)
[![Memory Safety](https://img.shields.io/badge/Valgrind-0%20Leaks-brightgreen.svg)]()

A comprehensive, production-grade **Sorting Algorithms Library** implemented in standard ISO C99. Featuring 8 distinct sorting algorithms spanning divide-and-conquer, incremental insertion, priority heaps, and non-comparative distribution, complete with automated performance benchmarking and legacy compatibility.

---

## Features

- **8 Core Sorting Algorithms**:
  - **Divide & Conquer**: Merge Sort, Quick Sort (Median-of-three with tail-call optimization).
  - **Heap & Priority**: Heap Sort (guaranteed $\mathcal{O}(n \log n)$ worst case, $\mathcal{O}(1)$ space).
  - **Incremental Insertion**: Insertion Sort (adaptive $\mathcal{O}(n)$ best case), Shell Sort (Knuth gap sequence).
  - **Exchange & Selection**: Selection Sort, Bubble Sort (with early-exit flag).
  - **Non-Comparative**: Counting Sort ($\mathcal{O}(n + k)$ linear time).
- **VLA-Free Memory Safety**: Replaced unsafe Variable Length Arrays (VLAs) with safe heap-managed temporary buffers to prevent stack overflow on large inputs.
- **Micro-Benchmark Suite**: Built-in timing and throughput verification (`make demo`).
- **Array Utilities**: Directional validators (`Sort_IsSorted`, `Sort_IsSortedDescending`), fast memory copying, and formatters.
- **Zero Memory Leaks**: Clean Valgrind and AddressSanitizer (ASan) verification on every commit.
- **Legacy Compatibility Layer**: 100% drop-in compatibility for academic coursework function signatures (`InsertionSort`, `SelectionSort`, `mergeSort`, `shellSort`, `quickSort`, etc.).

---

## Algorithm Comparison & Asymptotic Complexity

| Algorithm | Best Case | Average Case | Worst Case | Auxiliary Space | Stable? | In-Place? |
| :--- | :---: | :---: | :---: | :---: | :---: | :---: |
| **Insertion Sort** | $\mathcal{O}(n)$ | $\mathcal{O}(n^2)$ | $\mathcal{O}(n^2)$ | $\mathcal{O}(1)$ | **Yes** | **Yes** |
| **Selection Sort** | $\mathcal{O}(n^2)$ | $\mathcal{O}(n^2)$ | $\mathcal{O}(n^2)$ | $\mathcal{O}(1)$ | No | **Yes** |
| **Bubble Sort** | $\mathcal{O}(n)$ | $\mathcal{O}(n^2)$ | $\mathcal{O}(n^2)$ | $\mathcal{O}(1)$ | **Yes** | **Yes** |
| **Merge Sort** | $\mathcal{O}(n \log n)$ | $\mathcal{O}(n \log n)$ | $\mathcal{O}(n \log n)$ | $\mathcal{O}(n)$ | **Yes** | No |
| **Quick Sort** | $\mathcal{O}(n \log n)$ | $\mathcal{O}(n \log n)$ | $\mathcal{O}(n^2)$ | $\mathcal{O}(\log n)$ | No | **Yes** |
| **Shell Sort** | $\mathcal{O}(n \log n)$ | $\mathcal{O}(n^{4/3})$ | $\mathcal{O}(n^{3/2})$ | $\mathcal{O}(1)$ | No | **Yes** |
| **Heap Sort** | $\mathcal{O}(n \log n)$ | $\mathcal{O}(n \log n)$ | $\mathcal{O}(n \log n)$ | $\mathcal{O}(1)$ | No | **Yes** |
| **Counting Sort** | $\mathcal{O}(n + k)$ | $\mathcal{O}(n + k)$ | $\mathcal{O}(n + k)$ | $\mathcal{O}(k)$ | **Yes** | No |

---

## Architecture & Taxonomy

```
                              Sorting Algorithms
                                      |
         +----------------------------+----------------------------+
         |                                                         |
  Comparative Sorting                                    Non-Comparative
         |                                                         |
         +------------------+------------------+             Counting Sort
         |                  |                  |             (Linear Time)
   Divide & Conquer     Insertion & Gaps    Selection & Exchange
         |                  |                  |
    Merge Sort         Insertion Sort      Selection Sort
    Quick Sort         Shell Sort          Bubble Sort
    Heap Sort
```

---

## Project Structure

```
Sortings/
├── .github/
│   └── workflows/
│       └── ci.yml              # Multi-platform CI (Valgrind, ASan, MinGW)
├── examples/
│   └── demo.c                 # Benchmark suite and algorithm demonstrations
├── include/
│   └── sortings.h             # Public API & legacy compatibility wrappers
├── src/
│   └── sortings.c             # Algorithm implementations
├── tests/
│   └── test_sortings.c        # Unit test suite covering all invariants
├── .gitignore
├── compile_flags.txt
├── LICENSE                    # MIT License
├── Makefile                   # Cross-platform build system
└── README.md
```

---

## Getting Started

### Prerequisites

- GCC or Clang with C99 support
- GNU Make (or `mingw32-make` on Windows)
- Valgrind (optional, for Linux memory checks)

### Building and Running

```bash
# Build test runner and demo benchmark binaries
make all

# Run the automated unit test suite
make check

# Run the interactive demo and performance benchmarks
make demo

# Clean build artifacts
make clean
```

---

## API Reference

### Comparative Sorting
```c
void Sort_Insertion(int *arr, size_t n);
void Sort_Selection(int *arr, size_t n);
void Sort_Bubble(int *arr, size_t n);
void Sort_Merge(int *arr, size_t n);
void Sort_Quick(int *arr, size_t n);
void Sort_Shell(int *arr, size_t n);
void Sort_Heap(int *arr, size_t n);
```

### Non-Comparative Sorting
```c
bool Sort_Counting(int *arr, size_t n);
```

### Verification & Utilities
```c
bool Sort_IsSorted(const int *arr, size_t n);
bool Sort_IsSortedDescending(const int *arr, size_t n);
void Sort_Swap(int *a, int *b);
void Sort_Copy(int *dest, const int *src, size_t n);
void Sort_Print(const int *arr, size_t n, FILE *stream);
```

### Legacy Compatibility Layer
```c
void printArray(int arr[], int size);
void InsertionSort(int arr[], int n);
void SelectionSort(int arr[], int n);
void merge(int arr[], int l, int m, int r);
void mergeSort(int arr[], int l, int r);
void shellSort(int arr[], int n);
int  partition(int arr[], int low, int high);
void quickSort(int arr[], int low, int high);
void swap(int *a, int *b);
```

---

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
