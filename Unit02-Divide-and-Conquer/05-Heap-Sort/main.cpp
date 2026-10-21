
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Maintains the max-heap property
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

// Heap Sort implementation
void heapSort(vector<int>& arr) {
    int n = arr.size();

    // Build a max heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // Extract elements from the heap one by one
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int main() {
    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    if (n <= 0 || n > 100) {
        cout << "Please enter a size between 1 and 100." << endl;
        return 0;
    }

    vector<int> arr(n);

    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << "\nOriginal Array: ";
    for (int value : arr) {
        cout << value << " ";
    }

    heapSort(arr);

    cout << "\nSorted Array: ";
    for (int value : arr) {
        cout << value << " ";
    }

    cout << endl;

    return 0;
}
