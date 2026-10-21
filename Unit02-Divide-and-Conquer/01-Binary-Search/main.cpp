
#include <iostream>
using namespace std;

// Binary Search using Divide and Conquer
int binarySearch(int arr[], int low, int high, int target) {

    // Base condition: Search space is empty
    if (low > high) {
        return -1;
    }

    // Divide: Find the middle element
    int mid = low + (high - low) / 2;

    // Check whether the target is found
    if (arr[mid] == target) {
        return mid;
    }

    // Conquer: Search in the right half
    if (arr[mid] < target) {
        return binarySearch(arr, mid + 1, high, target);
    }

    // Conquer: Search in the left half
    return binarySearch(arr, low, mid - 1, target);
}

int main() {
    int arr[100];
    int size, target;

    cout << "===== BINARY SEARCH USING DIVIDE AND CONQUER =====\n";

    cout << "Enter array size (1-100): ";
    cin >> size;

    if (cin.fail() || size < 1 || size > 100) {
        cout << "Invalid array size.\n";
        return 1;
    }

    cout << "Enter " << size << " elements in ascending order:\n";

    for (int i = 0; i < size; i++) {
        cin >> arr[i];

        if (cin.fail()) {
            cout << "Invalid input.\n";
            return 1;
        }

        if (i > 0 && arr[i] < arr[i - 1]) {
            cout << "Error: Array must be sorted in ascending order.\n";
            return 1;
        }
    }

    cout << "Enter element to search: ";
    cin >> target;

    if (cin.fail()) {
        cout << "Invalid input.\n";
        return 1;
    }

    int result = binarySearch(arr, 0, size - 1, target);

    cout << "\n========== SEARCH RESULT ==========\n";

    if (result != -1) {
        cout << "Element found successfully!\n";
        cout << "Element: " << target << endl;
        cout << "Index: " << result << endl;
        cout << "Position: " << result + 1 << endl;
    }
    else {
        cout << "Element not found in the array.\n";
    }

    return 0;
}
