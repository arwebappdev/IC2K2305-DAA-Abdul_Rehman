
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int solutionCount = 0;

void findSubsets(
    const vector<int>& nums,
    int index,
    int currentSum,
    int target,
    vector<int>& subset,
    int remainingSum
) {
    // A valid subset has been found
    if (currentSum == target) {
        solutionCount++;

        cout << "Solution " << solutionCount << ": { ";

        for (int num : subset) {
            cout << num << " ";
        }

        cout << "}" << endl;
        return;
    }

    // Pruning conditions
    if (index == nums.size() ||
        currentSum > target ||
        currentSum + remainingSum < target) {
        return;
    }

    // Choice 1: Include the current element
    subset.push_back(nums[index]);

    findSubsets(
        nums,
        index + 1,
        currentSum + nums[index],
        target,
        subset,
        remainingSum - nums[index]
    );

    // Backtrack: Remove the included element
    subset.pop_back();

    // Choice 2: Exclude the current element
    findSubsets(
        nums,
        index + 1,
        currentSum,
        target,
        subset,
        remainingSum - nums[index]
    );
}

int main() {
    int n, target;

    cout << "Enter number of elements: ";
    cin >> n;

    if (n <= 0) {
        cout << "Number of elements must be positive." << endl;
        return 0;
    }

    vector<int> nums(n);

    cout << "Enter positive distinct elements: ";

    for (int i = 0; i < n; i++) {
        cin >> nums[i];

        if (nums[i] <= 0) {
            cout << "Elements must be positive." << endl;
            return 0;
        }
    }

    sort(nums.begin(), nums.end());

    // Check for duplicate elements
    for (int i = 1; i < n; i++) {
        if (nums[i] == nums[i - 1]) {
            cout << "Please enter distinct elements." << endl;
            return 0;
        }
    }

    cout << "Enter target sum: ";
    cin >> target;

    if (target <= 0) {
        cout << "Target must be positive." << endl;
        return 0;
    }

    vector<int> subset;

    int totalSum = 0;

    for (int num : nums) {
        totalSum += num;
    }

    cout << "\nSubsets with sum " << target << ":" << endl;

    findSubsets(
        nums,
        0,
        0,
        target,
        subset,
        totalSum
    );

    if (solutionCount == 0) {
        cout << "No valid subset found." << endl;
    }

    cout << "\nTotal number of solutions: "
         << solutionCount << endl;

    return 0;
}

