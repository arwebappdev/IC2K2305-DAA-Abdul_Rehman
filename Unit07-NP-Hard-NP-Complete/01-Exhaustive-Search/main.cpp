
#include <iostream>
#include <vector>
using namespace std;

long long maxProfit = 0;
long long totalSubsets = 0;

vector<int> bestSelection;
vector<int> currentSelection;

void exhaustiveSearch(
    const vector<int>& weights,
    const vector<int>& profits,
    int index,
    long long currentWeight,
    long long currentProfit,
    int capacity
) {
    // All items have been considered
    if (index == weights.size()) {
        totalSubsets++;

        // Check whether this is the best valid solution
        if (currentWeight <= capacity &&
            currentProfit > maxProfit) {

            maxProfit = currentProfit;
            bestSelection = currentSelection;
        }

        return;
    }

    // Choice 1: Exclude the current item
    currentSelection[index] = 0;

    exhaustiveSearch(
        weights,
        profits,
        index + 1,
        currentWeight,
        currentProfit,
        capacity
    );

    // Choice 2: Include the current item
    currentSelection[index] = 1;

    exhaustiveSearch(
        weights,
        profits,
        index + 1,
        currentWeight + weights[index],
        currentProfit + profits[index],
        capacity
    );

    // Restore the current selection
    currentSelection[index] = 0;
}

int main() {
    int n, capacity;

    cout << "Enter number of items: ";
    cin >> n;

    if (n <= 0) {
        cout << "Number of items must be positive." << endl;
        return 0;
    }

    vector<int> weights(n);
    vector<int> profits(n);

    cout << "\nEnter weights of items:\n";

    for (int i = 0; i < n; i++) {
        cin >> weights[i];

        if (weights[i] <= 0) {
            cout << "Weights must be positive." << endl;
            return 0;
        }
    }

    cout << "\nEnter profits of items:\n";

    for (int i = 0; i < n; i++) {
        cin >> profits[i];

        if (profits[i] < 0) {
            cout << "Profits cannot be negative." << endl;
            return 0;
        }
    }

    cout << "\nEnter knapsack capacity: ";
    cin >> capacity;

    if (capacity < 0) {
        cout << "Capacity cannot be negative." << endl;
        return 0;
    }

    currentSelection.resize(n, 0);
    bestSelection.resize(n, 0);

    exhaustiveSearch(
        weights,
        profits,
        0,
        0,
        0,
        capacity
    );

    cout << "\n----- Exhaustive Search Result -----\n";

    cout << "Total subsets examined: "
         << totalSubsets << endl;

    cout << "\nSelected items:\n";

    bool itemSelected = false;
    long long totalWeight = 0;

    for (int i = 0; i < n; i++) {
        if (bestSelection[i] == 1) {
            cout << "Item " << i + 1
                 << " | Weight: " << weights[i]
                 << " | Profit: " << profits[i]
                 << endl;

            totalWeight += weights[i];
            itemSelected = true;
        }
    }

    if (!itemSelected) {
        cout << "No items selected." << endl;
    }

    cout << "\nTotal Weight: " << totalWeight << endl;
    cout << "Maximum Profit: " << maxProfit << endl;

    return 0;
}
