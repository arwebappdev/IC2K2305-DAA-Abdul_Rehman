
#include <iostream>
#include <algorithm>
using namespace std;

// Partition the array around the pivot
int partition(int arr[], int low, int high) {

    // Select the last element as pivot
    int pivot = arr[high];

    int i = low - 1;

    for (int j = low; j < high; j++) {

        // Place smaller elements before the pivot
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    // Place pivot at its correct position
    swap(arr[i + 1], arr[high]);

    return i + 1;
}

// Quick Sort using Divide and Conquer
void quickSort(int arr[], int low, int high) {

    if (low < high) {

        // Find the correct position of pivot
        int pivotIndex = partition(arr, low, high);

        // Sort the left subarray
        quickSort(arr, low, pivotIndex - 1);

        // Sort the right subarray
        quickSort(arr, pivotIndex + 1, high);
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

    cout << "===== QUICK SORT =====\n";

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

    // Perform Quick Sort
    quickSort(arr, 0, size - 1);

    cout << "Sorted Array:   ";
    displayArray(arr, size);

    cout << "\nArray sorted successfully!\n";

    return 0;
}
