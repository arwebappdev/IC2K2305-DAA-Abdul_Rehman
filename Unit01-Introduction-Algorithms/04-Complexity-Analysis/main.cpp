
#include <iostream>
using namespace std;

// Linear Search with comparison counting
int linearSearch(int arr[], int size, int target, int &comparisons) {
    comparisons = 0;

    for (int i = 0; i < size; i++) {
        comparisons++;

        if (arr[i] == target) {
            return i;
        }
    }

    return -1;
}

int main() {
    int arr[100];
    int size;
    int comparisons;
    int result;

    cout << "===== COMPLEXITY ANALYSIS =====\n";

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

    // Best Case: Target at the first position
    cout << "\n--- BEST CASE ---\n";

    result = linearSearch(arr, size, arr[0], comparisons);

    cout << "Target Element: " << arr[0] << endl;
    cout << "Comparisons: " << comparisons << endl;
    cout << "Time Complexity: O(1)\n";

    // Average Case: Target at the middle position
    cout << "\n--- AVERAGE CASE ---\n";

    int middleElement = arr[size / 2];

    result = linearSearch(arr, size, middleElement, comparisons);

    cout << "Target Element: " << middleElement << endl;
    cout << "Comparisons: " << comparisons << endl;
    cout << "Time Complexity: O(n)\n";

    // Worst Case: Search for an element not present
    cout << "\n--- WORST CASE ---\n";

    int worstTarget = arr[size - 1];

    if (worstTarget < 1000000) {
        worstTarget++;
    } else {
        worstTarget--;
    }

    result = linearSearch(arr, size, worstTarget, comparisons);

    cout << "Target Element: " << worstTarget << endl;
    cout << "Comparisons: " << comparisons << endl;
    cout << "Time Complexity: O(n)\n";

    return 0;
}
