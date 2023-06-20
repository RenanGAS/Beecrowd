## Arquivo base - Grafos

```
#include <ostream>
#include <limits.h>
#include <fstream>
#include <map>
#include <list>
#include <vector>

using namespace std;

int main()
{
    ifstream infile;
    infile.open("06-2023/tripProg.txt");

    int num_v, num_e;

    while (infile >> num_v >> num_e)
    {
    }

    return EXIT_SUCCESS;
}
```

## Merge Sort

```
#include <iostream>
#include <vector>

// Merge two sorted subarrays into one sorted array
void merge(std::vector<int>& arr, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    // Create temporary arrays
    std::vector<int> L(n1), R(n2);

    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[middle + 1 + j];

    // Merge the temporary arrays back into arr[left..right]
    int i = 0;  // Initial index of first subarray
    int j = 0;  // Initial index of second subarray
    int k = left;  // Initial index of merged subarray

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Recursive function to perform merge sort
void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);

        // Merge the sorted halves
        merge(arr, left, middle, right);
    }
}

void printArray(const std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
}

int main() {
    std::vector<int> arr = {98, 22, 11, 0, 100, 2};
    int n = arr.size();

    std::cout << "Original array: ";
    printArray(arr);

    mergeSort(arr, 0, n - 1);

    std::cout << "Sorted array: ";
    printArray(arr);

    return 0;
}
```

## Heap Sort

```
#include <iostream>
#include <vector>

// Heapify a subtree rooted at index i
void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i;       // Initialize largest as root
    int left = 2 * i + 1;  // Left child
    int right = 2 * i + 2; // Right child

    // If left child is larger than root
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // If right child is larger than largest so far
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // If largest is not root
    if (largest != i) {
        std::swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// Heap Sort function
void heapSort(std::vector<int>& arr) {
    int n = arr.size();

    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extract elements from the heap one by one
    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]); // Move current root to end
        heapify(arr, i, 0);        // Heapify the reduced heap
    }
}

// Helper function to print the elements of an array
void printArray(const std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
}

int main() {
    std::vector<int> arr = {12, 11, 13, 5, 6, 7};
    int n = arr.size();

    std::cout << "Original array: ";
    printArray(arr);

    heapSort(arr);

    std::cout << "Sorted array: ";
    printArray(arr);

    return 0;
}
```
