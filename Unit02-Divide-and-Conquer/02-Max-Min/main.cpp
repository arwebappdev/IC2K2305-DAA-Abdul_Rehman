
#include <iostream>
using namespace std;

// Structure to store minimum and maximum values
struct MinMax {
    int minimum;
    int maximum;
};

// Find minimum and maximum using Divide and Conquer
MinMax findMinMax(int arr[], int low, int high) {

    MinMax result;

    // Base Case 1: Only one element
    if (low == high) {
        result.minimum = arr[low];
        result.maximum = arr[low];

        return result;
    }

    // Base Case 2: Only two elements
    if (high == low + 1) {

        if (arr[low] < arr[high]) {
            result.minimum = arr[low];
            result.maximum = arr[high];
        }
        else {
            result.minimum = arr[high];
            result.maximum = arr[low];
        }

        return result;
    }

    // Divide the array into two halves
    int mid = low + (high - low) / 2;

    // Find minimum and maximum in the left half
    MinMax leftResult = findMinMax(arr, low, mid);

    // Find minimum and maximum in the right half
    MinMax rightResult = findMinMax(arr, mid + 1, high);

    // Combine the results
    result.minimum = min(leftResult.minimum, rightResult.minimum);
    result.maximum = max(leftResult.maximum, rightResult.maximum);

    return result;
}

int main() {

    int arr[100];
    int size;

    cout << "===== MAXIMUM AND MINIMUM USING DIVIDE AND CONQUER =====\n";

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

    // Find minimum and maximum
    MinMax result = findMinMax(arr, 0, size - 1);

    cout << "\n========== RESULT ==========\n";

    cout << "Minimum Element: " << result.minimum << endl;
    cout << "Maximum Element: " << result.maximum << endl;

    return 0;
}
