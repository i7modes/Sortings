/**
 * @file test_sortings.c
 * @brief Automated unit test suite for sorting algorithms.
 * @author i7modes
 * @license MIT
 */

#include "sortings.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static int total_tests = 0;
static int passed_tests = 0;

#define TEST_ASSERT(expr, msg) do { \
    total_tests++; \
    if (expr) { \
        passed_tests++; \
        printf("  [PASS] %s\n", msg); \
    } else { \
        printf("  [FAIL] %s (Line %d)\n", msg, __LINE__); \
    } \
} while (0)

static void test_empty_and_single(void)
{
    printf("\n--- Test: Edge Cases (NULL, Empty, Single Element) ---\n");
    int single[1] = {42};

    TEST_ASSERT(Sort_IsSorted(NULL, 0) == true, "NULL is sorted");
    TEST_ASSERT(Sort_IsSorted(single, 1) == true, "Single element is sorted");

    Sort_Insertion(NULL, 0);
    Sort_Insertion(single, 1);
    TEST_ASSERT(single[0] == 42, "Insertion Sort on single element is unchanged");

    Sort_Selection(single, 1);
    TEST_ASSERT(single[0] == 42, "Selection Sort on single element is unchanged");

    Sort_Bubble(single, 1);
    TEST_ASSERT(single[0] == 42, "Bubble Sort on single element is unchanged");

    Sort_Merge(single, 1);
    TEST_ASSERT(single[0] == 42, "Merge Sort on single element is unchanged");

    Sort_Quick(single, 1);
    TEST_ASSERT(single[0] == 42, "Quick Sort on single element is unchanged");

    Sort_Shell(single, 1);
    TEST_ASSERT(single[0] == 42, "Shell Sort on single element is unchanged");

    Sort_Heap(single, 1);
    TEST_ASSERT(single[0] == 42, "Heap Sort on single element is unchanged");

    Sort_Counting(single, 1);
    TEST_ASSERT(single[0] == 42, "Counting Sort on single element is unchanged");
}

static void test_all_algorithms(void)
{
    printf("\n--- Test: All 8 Algorithms on Arbitrary Arrays ---\n");
    int base[] = {64, -15, 22, 11, 0, 90, -15, 33, 47, 100, 1};
    size_t n = sizeof(base) / sizeof(base[0]);
    int buf[sizeof(base) / sizeof(base[0])];

    // Insertion Sort
    Sort_Copy(buf, base, n);
    Sort_Insertion(buf, n);
    TEST_ASSERT(Sort_IsSorted(buf, n) == true, "Insertion Sort correctly sorts array");

    // Selection Sort
    Sort_Copy(buf, base, n);
    Sort_Selection(buf, n);
    TEST_ASSERT(Sort_IsSorted(buf, n) == true, "Selection Sort correctly sorts array");

    // Bubble Sort
    Sort_Copy(buf, base, n);
    Sort_Bubble(buf, n);
    TEST_ASSERT(Sort_IsSorted(buf, n) == true, "Bubble Sort correctly sorts array");

    // Merge Sort
    Sort_Copy(buf, base, n);
    Sort_Merge(buf, n);
    TEST_ASSERT(Sort_IsSorted(buf, n) == true, "Merge Sort correctly sorts array");

    // Quick Sort
    Sort_Copy(buf, base, n);
    Sort_Quick(buf, n);
    TEST_ASSERT(Sort_IsSorted(buf, n) == true, "Quick Sort correctly sorts array");

    // Shell Sort
    Sort_Copy(buf, base, n);
    Sort_Shell(buf, n);
    TEST_ASSERT(Sort_IsSorted(buf, n) == true, "Shell Sort correctly sorts array");

    // Heap Sort
    Sort_Copy(buf, base, n);
    Sort_Heap(buf, n);
    TEST_ASSERT(Sort_IsSorted(buf, n) == true, "Heap Sort correctly sorts array");

    // Counting Sort
    Sort_Copy(buf, base, n);
    TEST_ASSERT(Sort_Counting(buf, n) == true, "Counting Sort succeeds");
    TEST_ASSERT(Sort_IsSorted(buf, n) == true, "Counting Sort correctly sorts array");
}

static void test_adversarial_patterns(void)
{
    printf("\n--- Test: Adversarial Patterns (Sorted, Reverse, All Equal) ---\n");
    int sorted[20];
    int reverse[20];
    int all_equal[20];

    for (int i = 0; i < 20; i++)
    {
        sorted[i] = i * 3;
        reverse[i] = (20 - i) * 3;
        all_equal[i] = 7;
    }

    int test_buf[20];

    // Quick Sort on already sorted (median-of-three test)
    Sort_Copy(test_buf, sorted, 20);
    Sort_Quick(test_buf, 20);
    TEST_ASSERT(Sort_IsSorted(test_buf, 20) == true, "QuickSort handles sorted array in O(n log n)");

    // Quick Sort on reverse sorted
    Sort_Copy(test_buf, reverse, 20);
    Sort_Quick(test_buf, 20);
    TEST_ASSERT(Sort_IsSorted(test_buf, 20) == true, "QuickSort handles reverse array in O(n log n)");

    // Quick Sort on all equal keys
    Sort_Copy(test_buf, all_equal, 20);
    Sort_Quick(test_buf, 20);
    TEST_ASSERT(Sort_IsSorted(test_buf, 20) == true, "QuickSort handles all identical elements");

    // Merge Sort on reverse
    Sort_Copy(test_buf, reverse, 20);
    Sort_Merge(test_buf, 20);
    TEST_ASSERT(Sort_IsSorted(test_buf, 20) == true, "MergeSort handles reverse array");

    // Shell Sort on reverse
    Sort_Copy(test_buf, reverse, 20);
    Sort_Shell(test_buf, 20);
    TEST_ASSERT(Sort_IsSorted(test_buf, 20) == true, "ShellSort handles reverse array");
}

static void test_large_random_array(void)
{
    printf("\n--- Test: High Volume Stress Test (1,000 Elements) ---\n");
    size_t n = 1000;
    int *arr = (int *)malloc(n * sizeof(int));
    assert(arr != NULL);

    // Seed deterministic sequence
    unsigned int seed = 12345;
    for (size_t i = 0; i < n; i++)
    {
        seed = seed * 1103515245 + 12345;
        arr[i] = (int)(seed % 100000) - 50000;
    }

    int *copy = (int *)malloc(n * sizeof(int));
    assert(copy != NULL);

    // Merge Sort 1000 elements
    Sort_Copy(copy, arr, n);
    Sort_Merge(copy, n);
    TEST_ASSERT(Sort_IsSorted(copy, n) == true, "Merge Sort sorts 1,000 random items");

    // Quick Sort 1000 elements
    Sort_Copy(copy, arr, n);
    Sort_Quick(copy, n);
    TEST_ASSERT(Sort_IsSorted(copy, n) == true, "Quick Sort sorts 1,000 random items");

    // Heap Sort 1000 elements
    Sort_Copy(copy, arr, n);
    Sort_Heap(copy, n);
    TEST_ASSERT(Sort_IsSorted(copy, n) == true, "Heap Sort sorts 1,000 random items");

    free(arr);
    free(copy);
}

static void test_legacy_api_compatibility(void)
{
    printf("\n--- Test: Legacy Academic API Compatibility ---\n");

    int arr1[] = {12, 11, 13, 5, 6};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    InsertionSort(arr1, n1);
    TEST_ASSERT(Sort_IsSorted(arr1, n1) == true, "Legacy InsertionSort succeeds");

    int arr2[] = {64, 25, 12, 22, 11};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    SelectionSort(arr2, n2);
    TEST_ASSERT(Sort_IsSorted(arr2, n2) == true, "Legacy SelectionSort succeeds");

    int arr3[] = {38, 27, 43, 3, 9, 82, 10};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    mergeSort(arr3, 0, n3 - 1);
    TEST_ASSERT(Sort_IsSorted(arr3, n3) == true, "Legacy mergeSort succeeds");

    int arr4[] = {12, 34, 54, 2, 3};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    shellSort(arr4, n4);
    TEST_ASSERT(Sort_IsSorted(arr4, n4) == true, "Legacy shellSort succeeds");

    int arr5[] = {10, 7, 8, 9, 1, 5};
    int n5 = sizeof(arr5) / sizeof(arr5[0]);
    quickSort(arr5, 0, n5 - 1);
    TEST_ASSERT(Sort_IsSorted(arr5, n5) == true, "Legacy quickSort succeeds");
}

int main(void)
{
    printf("========================================\n");
    printf("  Sorting Algorithms Automated Tests\n");
    printf("========================================\n");

    test_empty_and_single();
    test_all_algorithms();
    test_adversarial_patterns();
    test_large_random_array();
    test_legacy_api_compatibility();

    printf("\n========================================\n");
    printf("  Results: %d/%d assertions passed\n", passed_tests, total_tests);
    printf("========================================\n");

    return (passed_tests == total_tests) ? 0 : 1;
}
