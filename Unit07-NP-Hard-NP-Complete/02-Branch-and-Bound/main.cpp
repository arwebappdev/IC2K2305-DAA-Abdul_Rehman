
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int bestSum = 0;
int exploredNodes = 0;
int prunedNodes = 0;

vector<int> bestSelection;
vector<int> currentSelection;

void branchAndBound(
    const vector<int>& nums,
    int index,
    int currentSum,
    int capacity,
    int remainingSum
) {
    exploredNodes++;

    // Update the best solution
    if (currentSum > bestSum) {
        bestSum = currentSum;
        bestSelection = currentSelection;
    }

    // No elements left
    if (index == nums.size()) {
        return;
    }

    // Upper bound: maximum sum possible from this branch
    int upperBound = currentSum + remainingSum;

    // Prune if this branch cannot improve the best solution
    if (upperBound <= bestSum) {
        prunedNodes++;
        return;
    }

    // Choice 1: Include current element
    if (currentSum + nums[index] <= capacity) {
        currentSelection[index] = 1;

        branchAndBound(
            nums,
            index + 1,
            currentSum + nums[index],
            capacity,
            remainingSum - nums[index]
        );
    }

    // Choice 2: Exclude current element
    currentSelection[index] = 0;

    branchAndBound(
        nums,
        index + 1,
        currentSum,
        capacity,
        remainingSum - nums[index]
    );

    currentSelection[index] = 0;
}

int main() {
    int n, capacity;

    cout << "Enter number of elements: ";
    cin >> n;

    if (n <= 0) {
        cout << "Number of elements must be positive." << endl;
        return 0;
    }

    vector<int> nums(n);

    cout << "Enter positive elements: ";

    int totalSum = 0;

    for (int i = 0; i < n; i++) {
        cin >> nums[i];

        if (nums[i] <= 0) {
            cout << "Elements must be positive." << endl;
            return 0;
        }

        totalSum += nums[i];
    }

    cout << "Enter capacity: ";
    cin >> capacity;

    if (capacity < 0) {
        cout << "Capacity cannot be negative." << endl;
        return 0;
    }

    // Sort in descending order to find good solutions early
    sort(nums.begin(), nums.end(), greater<int>());

    currentSelection.resize(n, 0);
    bestSelection.resize(n, 0);

    totalSum = 0;

    for (int num : nums) {
        totalSum += num;
    }

    branchAndBound(
        nums,
        0,
        0,
        capacity,
        totalSum
    );

    cout << "\n----- Branch and Bound Result -----\n";

    cout << "Selected elements: ";

    for (int i = 0; i < n; i++) {
        if (bestSelection[i] == 1) {
            cout << nums[i] << " ";
        }
    }

    cout << "\nMaximum sum: " << bestSum << endl;

    cout << "Explored nodes: " << exploredNodes << endl;
    cout << "Pruned nodes: " << prunedNodes << endl;

    return 0;
}
