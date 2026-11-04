
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Item {
    int weight;
    int profit;
    int originalIndex;
    double ratio;
};

long long maxProfit = 0;
long long exploredNodes = 0;
long long prunedNodes = 0;

vector<int> currentSelection;
vector<int> bestSelection;

// Calculate the optimistic upper bound using fractional knapsack
double calculateBound(
    const vector<Item>& items,
    int index,
    int currentWeight,
    long long currentProfit,
    int capacity
) {
    if (currentWeight > capacity) {
        return 0;
    }

    double bound = currentProfit;
    int totalWeight = currentWeight;

    // Add complete items while capacity permits
    for (int i = index; i < items.size(); i++) {
        if (totalWeight + items[i].weight <= capacity) {
            totalWeight += items[i].weight;
            bound += items[i].profit;
        }
        else {
            // Add a fraction only for calculating the bound
            int remainingCapacity = capacity - totalWeight;

            bound += remainingCapacity * items[i].ratio;
            break;
        }
    }

    return bound;
}

// Branch and Bound recursive function
void knapsackBranchAndBound(
    const vector<Item>& items,
    int index,
    int currentWeight,
    long long currentProfit,
    int capacity
) {
    exploredNodes++;

    // Update the best solution
    if (currentProfit > maxProfit) {
        maxProfit = currentProfit;
        bestSelection = currentSelection;
    }

    // All items have been considered
    if (index == items.size()) {
        return;
    }

    // Calculate upper bound
    double upperBound = calculateBound(
        items,
        index,
        currentWeight,
        currentProfit,
        capacity
    );

    // Prune if the branch cannot improve the best profit
    if (upperBound <= maxProfit) {
        prunedNodes++;
        return;
    }

    // Choice 1: Include the current item
    if (currentWeight + items[index].weight <= capacity) {
        currentSelection[index] = 1;

        knapsackBranchAndBound(
            items,
            index + 1,
            currentWeight + items[index].weight,
            currentProfit + items[index].profit,
            capacity
        );

        currentSelection[index] = 0;
    }

    // Choice 2: Exclude the current item
    knapsackBranchAndBound(
        items,
        index + 1,
        currentWeight,
        currentProfit,
        capacity
    );
}

int main() {
    int n, capacity;

    cout << "Enter number of items: ";
    cin >> n;

    if (n <= 0) {
        cout << "Number of items must be positive." << endl;
        return 0;
    }

    vector<Item> items(n);

    cout << "\nEnter weight and profit of each item:\n";

    for (int i = 0; i < n; i++) {
        cout << "Item " << i + 1 << ": ";
        cin >> items[i].weight >> items[i].profit;

        if (items[i].weight <= 0 || items[i].profit < 0) {
            cout << "Weight must be positive and profit cannot be negative."
                 << endl;
            return 0;
        }

        items[i].originalIndex = i;
        items[i].ratio =
            static_cast<double>(items[i].profit) / items[i].weight;
    }

    cout << "\nEnter knapsack capacity: ";
    cin >> capacity;

    if (capacity < 0) {
        cout << "Capacity cannot be negative." << endl;
        return 0;
    }

    // Sort items by profit-to-weight ratio in descending order
    sort(items.begin(), items.end(),
        [](const Item& a, const Item& b) {
            return a.ratio > b.ratio;
        }
    );

    currentSelection.resize(n, 0);
    bestSelection.resize(n, 0);

    // Execute Branch and Bound
    knapsackBranchAndBound(
        items,
        0,
        0,
        0,
        capacity
    );

    cout << "\n----- 0/1 Knapsack Branch and Bound -----\n";

    cout << "\nSelected items:\n";

    long long totalWeight = 0;

    bool itemSelected = false;

    // Display items using their original input numbers
    for (int i = 0; i < n; i++) {
        if (bestSelection[i] == 1) {
            cout << "Item " << items[i].originalIndex + 1
                 << " | Weight: " << items[i].weight
                 << " | Profit: " << items[i].profit
                 << endl;

            totalWeight += items[i].weight;
            itemSelected = true;
        }
    }

    if (!itemSelected) {
        cout << "No items selected." << endl;
    }

    cout << "\nTotal Weight: " << totalWeight << endl;
    cout << "Maximum Profit: " << maxProfit << endl;

    cout << "\nExplored Nodes: " << exploredNodes << endl;
    cout << "Pruned Nodes: " << prunedNodes << endl;

    return 0;
}
