/**
 * @file sortings.h
 * @brief Comprehensive suite of classical and modern sorting algorithms in C.
 * @author i7modes
 * @license MIT
 */

#ifndef SORTINGS_H
#define SORTINGS_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* -------------------------------------------------------------------------- */
/*                         Comparative Sorting Algorithms                     */
/* -------------------------------------------------------------------------- */

/**
 * @brief Insertion Sort: In-place, stable, O(n^2) worst/average, O(n) best.
 * Optimal for tiny arrays (n <= 16) or nearly sorted data.
 * @param arr Array of integers to sort in-place.
 * @param n Number of elements.
 */
void Sort_Insertion(int *arr, size_t n);

/**
 * @brief Selection Sort: In-place, O(n^2) time, minimizes the total number of swaps (O(n)).
 * @param arr Array of integers to sort in-place.
 * @param n Number of elements.
 */
void Sort_Selection(int *arr, size_t n);

/**
 * @brief Bubble Sort with early-exit flag: In-place, stable, O(n^2) worst, O(n) best.
 * @param arr Array of integers to sort in-place.
 * @param n Number of elements.
 */
void Sort_Bubble(int *arr, size_t n);

/**
 * @brief Merge Sort: Stable, guaranteed O(n log n) time across all inputs.
 * Uses heap-allocated temporary buffers to prevent stack overflow on large inputs.
 * @param arr Array of integers to sort in-place.
 * @param n Number of elements.
 */
void Sort_Merge(int *arr, size_t n);

/**
 * @brief Quick Sort: In-place, average O(n log n) time, cache-friendly partition.
 * @param arr Array of integers to sort in-place.
 * @param n Number of elements.
 */
void Sort_Quick(int *arr, size_t n);

/**
 * @brief Shell Sort: In-place, sub-quadratic generalization of insertion sort.
 * Uses Knuth's gap sequence (h = 3h + 1).
 * @param arr Array of integers to sort in-place.
 * @param n Number of elements.
 */
void Sort_Shell(int *arr, size_t n);

/**
 * @brief Heap Sort: In-place, guaranteed O(n log n) worst-case time with O(1) auxiliary space.
 * @param arr Array of integers to sort in-place.
 * @param n Number of elements.
 */
void Sort_Heap(int *arr, size_t n);

/**
 * @brief Counting Sort: Non-comparative, O(n + k) linear-time sort for integer data.
 * @param arr Array of integers to sort in-place.
 * @param n Number of elements.
 */
bool Sort_Counting(int *arr, size_t n);

/* -------------------------------------------------------------------------- */
/*                         Verification & Utilities                           */
/* -------------------------------------------------------------------------- */

/**
 * @brief Validates whether an array is sorted in non-decreasing order (arr[i] <= arr[i+1]).
 * @return true if sorted, false otherwise.
 */
bool Sort_IsSorted(const int *arr, size_t n);

/**
 * @brief Validates whether an array is sorted in non-increasing order (arr[i] >= arr[i+1]).
 * @return true if sorted descending, false otherwise.
 */
bool Sort_IsSortedDescending(const int *arr, size_t n);

/**
 * @brief Swaps the integer values pointed to by a and b.
 */
void Sort_Swap(int *a, int *b);

/**
 * @brief Copies an array of n integers from src to dest.
 */
void Sort_Copy(int *dest, const int *src, size_t n);

/**
 * @brief Prints an array of integers: [ 1 2 3 4 5 ]
 */
void Sort_Print(const int *arr, size_t n, FILE *stream);

/* -------------------------------------------------------------------------- */
/*                       Legacy API Compatibility Layer                       */
/* -------------------------------------------------------------------------- */

void printArray(int arr[], int size);
void InsertionSort(int arr[], int n);
void SelectionSort(int arr[], int n);
void merge(int arr[], int l, int m, int r);
void mergeSort(int arr[], int l, int r);
void shellSort(int arr[], int n);
int  partition(int arr[], int low, int high);
void quickSort(int arr[], int low, int high);
void swap(int *a, int *b);

#ifdef __cplusplus
}
#endif

#endif /* SORTINGS_H */
