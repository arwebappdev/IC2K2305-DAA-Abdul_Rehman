
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int knapsack(int capacity, const vector<int>& weights,
             const vector<int>& values, int n) {

    // Create DP table initialized with 0
    vector<vector<int>> dp(n + 1,
                           vector<int>(capacity + 1, 0));

    // Build the DP table
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {

            // If the current item cannot fit
            if (weights[i - 1] > w) {
                dp[i][w] = dp[i - 1][w];
            } else {
                // Maximum of including or excluding the item
                int exclude = dp[i - 1][w];

                int include = values[i - 1]
                            + dp[i - 1][w - weights[i - 1]];

                dp[i][w] = max(include, exclude);
            }
        }
    }

    // Display selected items by tracing the DP table
    cout << "\nSelected Items:\n";

    int remainingCapacity = capacity;

    for (int i = n; i > 0; i--) {
        if (dp[i][remainingCapacity] !=
            dp[i - 1][remainingCapacity]) {

            cout << "Item " << i
                 << " | Weight: " << weights[i - 1]
                 << " | Value: " << values[i - 1] << endl;

            remainingCapacity -= weights[i - 1];
        }
    }

    return dp[n][capacity];
}

int main() {
    int n, capacity;

    cout << "Enter number of items: ";
    cin >> n;

    if (n <= 0 || n > 100) {
        cout << "Please enter between 1 and 100 items."
             << endl;
        return 0;
    }

    vector<int> weights(n);
    vector<int> values(n);

    cout << "\nEnter weight and value of each item:\n";

    for (int i = 0; i < n; i++) {
        cout << "Item " << i + 1 << " (weight value): ";
        cin >> weights[i] >> values[i];

        if (weights[i] <= 0 || values[i] < 0) {
            cout << "Weight must be positive and value "
                 << "cannot be negative." << endl;
            return 0;
        }
    }

    cout << "\nEnter knapsack capacity: ";
    cin >> capacity;

    if (capacity < 0 || capacity > 10000) {
        cout << "Capacity must be between 0 and 10000."
             << endl;
        return 0;
    }

    int maximumValue = knapsack(capacity, weights, values, n);

    cout << "\nMaximum Knapsack Value: "
         << maximumValue << endl;

    return 0;
}
