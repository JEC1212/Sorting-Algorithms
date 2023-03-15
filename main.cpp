//  Justin Coyle
//  main.cpp
//  program1
//
//  Created by Justin Coyle.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        int min = i;
        for (int j = i+1; j < n; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        // Swap the minimum element with the first element
        int temp = arr[min];
        arr[min] = arr[i];
        arr[i] = temp;
    }
}
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                // Swap elements if they are in the wrong order
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int comp = arr[i];
        int j = i-1;
        
        while (j >= 0 && arr[j] > comp) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = comp;
    }
}





// Function to find the middle element index of an array
int findMiddleIndex(int arr[], int start, int end) {
    int mid = start + (end - start) / 2;
    if ((arr[start] <= arr[mid] && arr[mid] <= arr[end]) || (arr[end] <= arr[mid] && arr[mid] <= arr[start]))
        return mid;
    else if ((arr[mid] <= arr[start] && arr[start] <= arr[end]) || (arr[end] <= arr[start] && arr[start] <= arr[mid]))
        return start;
    else
        return end;
}

// Function to partition the array and return the pivot index
int partition(int arr[], int low, int high) {
    int mid = findMiddleIndex(arr, low, high);
    int pivot = arr[mid];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[mid]);
    return i + 1;
}

// Quick sort function
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivot = partition(arr, low, high);

        quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, high);
    }
}


// Function to merge two subarrays into a single sorted array
void merge(int arr[], int left[], int lsize, int right[], int rsize) {
    int i = 0, j = 0, k = 0;
    while (i < lsize && j < rsize) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    while (i < lsize) {
        arr[k] = left[i];
        i++;
        k++;
    }
    while (j < rsize) {
        arr[k] = right[j];
        j++;
        k++;
    }
}

// Function to perform Merge Sort
void mergeSort(int arr[], int low, int high) {
    if (low < high) {
        int n = high - low + 1;
        if (n < 10) {
            quickSort(arr, low, high);
        } else {
            int mid = low + (high - low) / 2;
            int left_size = mid - low + 1;
            int right_size = high - mid;
            int left[left_size], right[right_size];
            for (int i = 0; i < left_size; i++) {
                left[i] = arr[low + i];
            }
            for (int i = 0; i < right_size; i++) {
                right[i] = arr[mid + 1 + i];
            }
            mergeSort(left, 0, left_size - 1);
            mergeSort(right, 0, right_size - 1);
            merge(arr, left, left_size, right, right_size);
        }
    }
}

void count(int arr[], int n, int exp) {
    int output[n], count[10] = {0};
    
    
    for (int i = 0; i < n; i++) {
        count[(arr[i] / exp) % 10]++;
    }

   
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

   
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

void radixSort(int arr[], int n) {
    
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    for (int exp = 1; max / exp > 0; exp *= 10) {
        count(arr, n, exp);
    }
}



int main() {
    const int n = 16384;
    int arr[n];
    srand(time(NULL));

    // Fill the array with random numbers
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000;
    }

    clock_t start, end;

    // Time the selection sort algorithm
    start = clock();
    selectionSort(arr, n);
    end = clock();
    cout << "Selection sort time: " << (double)(end - start) << endl;

    // Time the bubble sort algorithm
    start = clock();
    bubbleSort(arr, n);
    end = clock();
    cout << "Bubble sort time: " << (double)(end - start) << endl;

    // Time the insertion sort algorithm
    start = clock();
    insertionSort(arr, n);
    end = clock();
    cout << "Insertion sort time: " << (double)(end - start) << endl;

    // Time the quick sort algorithm
    start = clock();
    quickSort(arr, 0, n-1);
    end = clock();
    cout << "Quick sort time: " << (double)(end - start) << endl;

    // Time the merge sort algorithm
    start = clock();
    mergeSort(arr, 0, n-1);
    end = clock();
    cout << "Merge sort time: " << (double)(end - start)  << endl;
    
    // Time the merge sort algorithm
    start = clock();
    radixSort(arr, n-1);
    end = clock();
    cout << "Radix sort time: " << (double)(end - start) << endl;

    return 0;
}
