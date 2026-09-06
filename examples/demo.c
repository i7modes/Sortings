/**
 * @file demo.c
 * @brief Demonstration and benchmark suite for sorting algorithms.
 * @author i7modes
 * @license MIT
 */

#include "sortings.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void print_banner(const char *title)
{
    printf("\n========================================\n");
    printf("  %s\n", title);
    printf("========================================\n");
}

static void run_and_print(const char *name, void (*sort_func)(int *, size_t), const int *original, size_t n)
{
    int *buf = (int *)malloc(n * sizeof(int));
    if (buf == NULL)
    {
        return;
    }

    Sort_Copy(buf, original, n);
    sort_func(buf, n);

    printf("%-16s: ", name);
    Sort_Print(buf, n, stdout);
    printf("  Verified Sorted: %s\n", Sort_IsSorted(buf, n) ? "YES" : "NO");

    free(buf);
}

static void benchmark_algorithm(const char *name, void (*sort_func)(int *, size_t), const int *dataset, size_t n)
{
    int *buf = (int *)malloc(n * sizeof(int));
    if (buf == NULL)
    {
        return;
    }

    Sort_Copy(buf, dataset, n);

    clock_t start = clock();
    sort_func(buf, n);
    clock_t end = clock();

    double elapsed_ms = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
    printf("  %-16s: %8.3f ms | Correct? %s\n",
           name, elapsed_ms, Sort_IsSorted(buf, n) ? "YES" : "NO");

    free(buf);
}

int main(void)
{
    print_banner("1. Comparative Demonstration on Sample Dataset");
    int sample[] = {64, 25, 12, 22, 11, 90, 33, 47, -5, 0, 100};
    size_t n = sizeof(sample) / sizeof(sample[0]);

    printf("Original Input Array: ");
    Sort_Print(sample, n, stdout);
    printf("\n");

    run_and_print("Insertion Sort", Sort_Insertion, sample, n);
    run_and_print("Selection Sort", Sort_Selection, sample, n);
    run_and_print("Bubble Sort",    Sort_Bubble,    sample, n);
    run_and_print("Merge Sort",     Sort_Merge,     sample, n);
    run_and_print("Quick Sort",     Sort_Quick,     sample, n);
    run_and_print("Shell Sort",     Sort_Shell,     sample, n);
    run_and_print("Heap Sort",      Sort_Heap,      sample, n);

    print_banner("2. Counting Sort (Linear-Time Non-Comparative)");
    int count_input[] = {12, 5, 8, 12, 3, 1, 9, 8, 5, 12};
    size_t count_n = sizeof(count_input) / sizeof(count_input[0]);
    printf("Before Counting Sort: ");
    Sort_Print(count_input, count_n, stdout);
    Sort_Counting(count_input, count_n);
    printf("After Counting Sort:  ");
    Sort_Print(count_input, count_n, stdout);
    printf("Verified: %s\n", Sort_IsSorted(count_input, count_n) ? "YES" : "NO");

    print_banner("3. High-Volume Performance Benchmark (5,000 Elements)");
    size_t bench_n = 5000;
    int *dataset = (int *)malloc(bench_n * sizeof(int));
    if (dataset != NULL)
    {
        unsigned int seed = 42;
        for (size_t i = 0; i < bench_n; i++)
        {
            seed = seed * 1103515245 + 12345;
            dataset[i] = (int)(seed % 50000);
        }

        benchmark_algorithm("Quick Sort", Sort_Quick, dataset, bench_n);
        benchmark_algorithm("Merge Sort", Sort_Merge, dataset, bench_n);
        benchmark_algorithm("Heap Sort",  Sort_Heap,  dataset, bench_n);
        benchmark_algorithm("Shell Sort", Sort_Shell, dataset, bench_n);

        free(dataset);
    }

    print_banner("4. Legacy Coursework API Demonstration");
    int arr_legacy[] = {38, 27, 43, 3, 9, 82, 10};
    int legacy_len = sizeof(arr_legacy) / sizeof(arr_legacy[0]);

    printf("Legacy mergeSort: ");
    printArray(arr_legacy, legacy_len);
    mergeSort(arr_legacy, 0, legacy_len - 1);
    printf("Sorted array with Merge Sort: ");
    printArray(arr_legacy, legacy_len);

    printf("\nAll sorting algorithm demonstrations completed successfully!\n");
    return 0;
}
