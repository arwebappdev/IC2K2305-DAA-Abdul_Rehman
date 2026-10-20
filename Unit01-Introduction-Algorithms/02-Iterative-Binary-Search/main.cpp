
#include <iostream>
using namespace std;

// Iterative Binary Search
int binarySearch(int arr[], int size, int target) {
    int low = 0;
    int high = size - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            return mid;
        }
        else if (arr[mid] < target) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }

    return -1;
}

int main() {
    int arr[100];
    int size, target;

    cout << "===== ITERATIVE BINARY SEARCH =====\n";

    cout << "Enter array size (1-100): ";
    cin >> size;

    if (cin.fail() || size < 1 || size > 100) {
        cout << "Invalid array size.\n";
        return 1;
    }

    cout << "Enter " << size << " elements in sorted order:\n";

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

    int result = binarySearch(arr, size, target);

    if (result != -1) {
        cout << "\nElement found successfully!\n";
        cout << "Element: " << target << endl;
        cout << "Index: " << result << endl;
        cout << "Position: " << result + 1 << endl;
    }
    else {
        cout << "\nElement not found in the array.\n";
    }

    return 0;
}
