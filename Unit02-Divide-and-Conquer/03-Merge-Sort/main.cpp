
#include <iostream>
using namespace std;

// Merge two sorted subarrays
void merge(int arr[], int low, int mid, int high) {

    int leftSize = mid - low + 1;
    int rightSize = high - mid;

    int left[leftSize];
    int right[rightSize];

    // Copy elements into temporary arrays
    for (int i = 0; i < leftSize; i++) {
        left[i] = arr[low + i];
    }

    for (int j = 0; j < rightSize; j++) {
        right[j] = arr[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = low;

    // Merge both sorted subarrays
    while (i < leftSize && j < rightSize) {

        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        }
        else {
            arr[k] = right[j];
            j++;
        }

        k++;
    }

    // Copy remaining elements from left array
    while (i < leftSize) {
        arr[k] = left[i];
        i++;
        k++;
    }

    // Copy remaining elements from right array
    while (j < rightSize) {
        arr[k] = right[j];
        j++;
        k++;
    }
}

// Merge Sort using Divide and Conquer
void mergeSort(int arr[], int low, int high) {

    if (low < high) {

        // Divide the array into two halves
        int mid = low + (high - low) / 2;

        // Sort the left half
        mergeSort(arr, low, mid);

        // Sort the right half
        mergeSort(arr, mid + 1, high);

        // Merge the sorted halves
        merge(arr, low, mid, high);
    }
}

// Display array elements
void displayArray(int arr[], int size) {

    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }

    cout << endl;
}

int main() {

    int arr[100];
    int size;

    cout << "===== MERGE SORT =====\n";

    cout << "Enter array size (1-100): ";
    cin >> size;

    if (cin.fail() || size < 1 || size > 100) {
        cout << "Invalid array size.\n";
        return 1;
    }

    cout << "Enter " << size << " array elements:\n";

    for (int i = 0; i < size; i++) {
        cin >> arr[i];

        if (cin.fail()) {
            cout << "Invalid input.\n";
            return 1;
        }
    }

    cout << "\nOriginal Array: ";
    displayArray(arr, size);

    // Perform Merge Sort
    mergeSort(arr, 0, size - 1);

    cout << "Sorted Array:   ";
    displayArray(arr, size);

    cout << "\nArray sorted successfully!\n";

    return 0;
}
