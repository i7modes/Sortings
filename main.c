#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void printArray(int[], int);
void InsertionSort(int[], int);
void SelectionSort(int[], int);
void mergeSort(int[], int, int);
void shellSort(int[], int);

int main()
{

    int arr1[] = {12, 11, 13, 5, 6};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("Original array for Insertion Sort: ");
    printArray(arr1, n1);
    InsertionSort(arr1, n1);
    printf("Sorted array with Insertion Sort: ");
    printArray(arr1, n1);
    printf("\n");

    int arr2[] = {64, 25, 12, 22, 11};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("Original array for Selection Sort: ");
    printArray(arr2, n2);
    SelectionSort(arr2, n2);
    printf("Sorted array with Selection Sort: ");
    printArray(arr2, n2);
    printf("\n");

    int arr3[] = {38, 27, 43, 3, 9, 82, 10};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("Original array for Merge Sort: ");
    printArray(arr3, n3);
    mergeSort(arr3, 0, n3 - 1);
    printf("Sorted array with Merge Sort: ");
    printArray(arr3, n3);
    printf("\n");

    int arr4[] = {12, 34, 54, 2, 3};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    printf("Original array for Shell Sort: ");
    printArray(arr4, n4);
    shellSort(arr4, n4);
    printf("Sorted array with Shell Sort: ");
    printArray(arr4, n4);
    printf("\n");

    return 0;
}

// Helper function to print an array
void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// INSERTION SORT
// Worst and avarge case = O(n^2)
// Best case = O(n)

void InsertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// SELECTION SORT = O(n^2)

void SelectionSort(int arr[], int n)
{
    int i, j, temp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[i])
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
    }
}

// MERGE SORT = O(n log n)

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temp arrays
    int L[n1], R[n2];

    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temp arrays back into arr[l..r
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[],
    // if there are any
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[],
    // if there are any
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// l is for left index and r is right index of the
// sub-array of arr to be sorted
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

// SHELL SORT
// Worst case = O(n^2)
// Best and avarge case = O(n log n)

void shellSort(int arr[], int n)
{
    int inc, j, k, temp;
    for (inc = n / 2; inc > 0; inc /= 2)
    {
        for (j = inc; j < n; j++)
        {
            for (k = j - inc; k >= 0; k -= inc)
            {
                if (arr[k + inc] >= arr[k])
                    break;
                else
                {
                    temp = arr[k];
                    arr[k] = arr[k + inc];
                    arr[k + inc] = temp;
                }
            }
        }
    }
}
