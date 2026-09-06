/**
 * @file sortings.c
 * @brief Implementation of classical and modern sorting algorithms in C.
 * @author i7modes
 * @license MIT
 */

#include "sortings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* -------------------------------------------------------------------------- */
/*                         Verification & Utilities                           */
/* -------------------------------------------------------------------------- */

void Sort_Swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

bool Sort_IsSorted(const int *arr, size_t n)
{
    if (arr == NULL || n <= 1)
    {
        return true;
    }

    for (size_t i = 0; i < n - 1; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            return false;
        }
    }
    return true;
}

bool Sort_IsSortedDescending(const int *arr, size_t n)
{
    if (arr == NULL || n <= 1)
    {
        return true;
    }

    for (size_t i = 0; i < n - 1; i++)
    {
        if (arr[i] < arr[i + 1])
        {
            return false;
        }
    }
    return true;
}

void Sort_Copy(int *dest, const int *src, size_t n)
{
    if (dest != NULL && src != NULL && n > 0)
    {
        memcpy(dest, src, n * sizeof(int));
    }
}

void Sort_Print(const int *arr, size_t n, FILE *stream)
{
    if (arr == NULL || stream == NULL)
    {
        return;
    }

    fprintf(stream, "[ ");
    for (size_t i = 0; i < n; i++)
    {
        fprintf(stream, "%d ", arr[i]);
    }
    fprintf(stream, "]\n");
}

/* -------------------------------------------------------------------------- */
/*                         Insertion Sort & Selection Sort                    */
/* -------------------------------------------------------------------------- */

void Sort_Insertion(int *arr, size_t n)
{
    if (arr == NULL || n <= 1)
    {
        return;
    }

    for (size_t i = 1; i < n; i++)
    {
        int key = arr[i];
        size_t j = i;

        while (j > 0 && arr[j - 1] > key)
        {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = key;
    }
}

void Sort_Selection(int *arr, size_t n)
{
    if (arr == NULL || n <= 1)
    {
        return;
    }

    for (size_t i = 0; i < n - 1; i++)
    {
        size_t min_idx = i;
        for (size_t j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_idx])
            {
                min_idx = j;
            }
        }

        if (min_idx != i)
        {
            Sort_Swap(&arr[i], &arr[min_idx]);
        }
    }
}

/* -------------------------------------------------------------------------- */
/*                                Bubble Sort                                 */
/* -------------------------------------------------------------------------- */

void Sort_Bubble(int *arr, size_t n)
{
    if (arr == NULL || n <= 1)
    {
        return;
    }

    for (size_t i = 0; i < n - 1; i++)
    {
        bool swapped = false;
        for (size_t j = 0; j < n - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                Sort_Swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
        {
            break; /* Early termination for already sorted segments */
        }
    }
}

/* -------------------------------------------------------------------------- */
/*                                 Merge Sort                                 */
/* -------------------------------------------------------------------------- */

static void merge_internal(int *arr, int *temp, size_t left, size_t mid, size_t right)
{
    size_t i = left;
    size_t j = mid + 1;
    size_t k = left;

    while (i <= mid && j <= right)
    {
        if (arr[i] <= arr[j])
        {
            temp[k++] = arr[i++];
        }
        else
        {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid)
    {
        temp[k++] = arr[i++];
    }

    while (j <= right)
    {
        temp[k++] = arr[j++];
    }

    for (size_t idx = left; idx <= right; idx++)
    {
        arr[idx] = temp[idx];
    }
}

static void merge_sort_recursive(int *arr, int *temp, size_t left, size_t right)
{
    if (left < right)
    {
        size_t mid = left + (right - left) / 2;
        merge_sort_recursive(arr, temp, left, mid);
        merge_sort_recursive(arr, temp, mid + 1, right);
        merge_internal(arr, temp, left, mid, right);
    }
}

void Sort_Merge(int *arr, size_t n)
{
    if (arr == NULL || n <= 1)
    {
        return;
    }

    int *temp = (int *)malloc(n * sizeof(int));
    if (temp == NULL)
    {
        /* Fallback to insertion sort if memory fails */
        Sort_Insertion(arr, n);
        return;
    }

    merge_sort_recursive(arr, temp, 0, n - 1);
    free(temp);
}

/* -------------------------------------------------------------------------- */
/*                                 Quick Sort                                 */
/* -------------------------------------------------------------------------- */

static size_t quick_partition(int *arr, size_t low, size_t high)
{
    /* Median-of-three pivot selection */
    size_t mid = low + (high - low) / 2;
    if (arr[mid] < arr[low])
    {
        Sort_Swap(&arr[mid], &arr[low]);
    }
    if (arr[high] < arr[low])
    {
        Sort_Swap(&arr[high], &arr[low]);
    }
    if (arr[high] < arr[mid])
    {
        Sort_Swap(&arr[high], &arr[mid]);
    }

    Sort_Swap(&arr[mid], &arr[high]);
    int pivot = arr[high];

    size_t i = low;
    for (size_t j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            Sort_Swap(&arr[i], &arr[j]);
            i++;
        }
    }

    Sort_Swap(&arr[i], &arr[high]);
    return i;
}

static void quick_sort_recursive(int *arr, size_t low, size_t high)
{
    while (low < high)
    {
        size_t p = quick_partition(arr, low, high);

        /* Tail-call optimization on smaller partition */
        if (p > 0 && p - 1 - low < high - (p + 1))
        {
            if (p > 0)
            {
                quick_sort_recursive(arr, low, p - 1);
            }
            low = p + 1;
        }
        else
        {
            quick_sort_recursive(arr, p + 1, high);
            if (p == 0)
            {
                break;
            }
            high = p - 1;
        }
    }
}

void Sort_Quick(int *arr, size_t n)
{
    if (arr == NULL || n <= 1)
    {
        return;
    }

    quick_sort_recursive(arr, 0, n - 1);
}

/* -------------------------------------------------------------------------- */
/*                                 Shell Sort                                 */
/* -------------------------------------------------------------------------- */

void Sort_Shell(int *arr, size_t n)
{
    if (arr == NULL || n <= 1)
    {
        return;
    }

    /* Knuth's gap sequence: 1, 4, 13, 40, 121, ... */
    size_t gap = 1;
    while (gap < n / 3)
    {
        gap = 3 * gap + 1;
    }

    while (gap >= 1)
    {
        for (size_t i = gap; i < n; i++)
        {
            int temp = arr[i];
            size_t j = i;

            while (j >= gap && arr[j - gap] > temp)
            {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
        gap = (gap - 1) / 3;
    }
}

/* -------------------------------------------------------------------------- */
/*                                  Heap Sort                                 */
/* -------------------------------------------------------------------------- */

static void heapify_down(int *arr, size_t n, size_t i)
{
    size_t largest = i;
    size_t left = 2 * i + 1;
    size_t right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
    {
        largest = left;
    }
    if (right < n && arr[right] > arr[largest])
    {
        largest = right;
    }

    if (largest != i)
    {
        Sort_Swap(&arr[i], &arr[largest]);
        heapify_down(arr, n, largest);
    }
}

void Sort_Heap(int *arr, size_t n)
{
    if (arr == NULL || n <= 1)
    {
        return;
    }

    /* Build max heap */
    for (size_t k = n / 2; k > 0; k--)
    {
        heapify_down(arr, n, k - 1);
    }

    /* Extract elements */
    for (size_t end = n - 1; end > 0; end--)
    {
        Sort_Swap(&arr[0], &arr[end]);
        heapify_down(arr, end, 0);
    }
}

/* -------------------------------------------------------------------------- */
/*                                Counting Sort                               */
/* -------------------------------------------------------------------------- */

bool Sort_Counting(int *arr, size_t n)
{
    if (arr == NULL || n <= 1)
    {
        return true;
    }

    int min_val = arr[0];
    int max_val = arr[0];

    for (size_t i = 1; i < n; i++)
    {
        if (arr[i] < min_val)
        {
            min_val = arr[i];
        }
        if (arr[i] > max_val)
        {
            max_val = arr[i];
        }
    }

    long long range = (long long)max_val - (long long)min_val + 1;
    if (range > 10000000)
    {
        /* Range too large for counting sort */
        return false;
    }

    size_t count_size = (size_t)range;
    size_t *count = (size_t *)calloc(count_size, sizeof(size_t));
    if (count == NULL)
    {
        return false;
    }

    for (size_t i = 0; i < n; i++)
    {
        count[arr[i] - min_val]++;
    }

    size_t idx = 0;
    for (size_t c = 0; c < count_size; c++)
    {
        while (count[c] > 0)
        {
            arr[idx++] = (int)c + min_val;
            count[c]--;
        }
    }

    free(count);
    return true;
}

/* -------------------------------------------------------------------------- */
/*                       Legacy API Compatibility Layer                       */
/* -------------------------------------------------------------------------- */

void printArray(int arr[], int size)
{
    if (arr == NULL)
    {
        return;
    }
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void swap(int *a, int *b)
{
    Sort_Swap(a, b);
}

void InsertionSort(int arr[], int n)
{
    if (n > 0)
    {
        Sort_Insertion(arr, (size_t)n);
    }
}

void SelectionSort(int arr[], int n)
{
    if (n > 0)
    {
        Sort_Selection(arr, (size_t)n);
    }
}

void merge(int arr[], int l, int m, int r)
{
    if (arr == NULL || l > m || m > r)
    {
        return;
    }

    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));
    if (L == NULL || R == NULL)
    {
        free(L);
        free(R);
        return;
    }

    for (int i = 0; i < n1; i++)
    {
        L[i] = arr[l + i];
    }
    for (int j = 0; j < n2; j++)
    {
        R[j] = arr[m + 1 + j];
    }

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k++] = L[i++];
        }
        else
        {
            arr[k++] = R[j++];
        }
    }

    while (i < n1)
    {
        arr[k++] = L[i++];
    }
    while (j < n2)
    {
        arr[k++] = R[j++];
    }

    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void shellSort(int arr[], int n)
{
    if (n > 0)
    {
        Sort_Shell(arr, (size_t)n);
    }
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        if (pi > 0)
        {
            quickSort(arr, low, pi - 1);
        }
        quickSort(arr, pi + 1, high);
    }
}
