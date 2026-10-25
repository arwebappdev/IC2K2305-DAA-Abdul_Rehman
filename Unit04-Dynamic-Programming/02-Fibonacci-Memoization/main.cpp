
#include <iostream>
#include <vector>
using namespace std;

// Recursive Fibonacci function with memoization
long long fibonacci(int n, vector<long long>& memo) {

    // Base case
    if (n == 0) {
        return 0;
    }

    if (n == 1) {
        return 1;
    }

    // Return stored result if already calculated
    if (memo[n] != -1) {
        return memo[n];
    }

    // Calculate and store the result
    memo[n] = fibonacci(n - 1, memo)
            + fibonacci(n - 2, memo);

    return memo[n];
}

int main() {
    int n;

    cout << "Enter the number of terms: ";
    cin >> n;

    if (n < 1 || n > 91) {
        cout << "Please enter a number between 1 and 91."
             << endl;
        return 0;
    }

    // Initialize memoization array with -1
    vector<long long> memo(n, -1);

    cout << "\nFibonacci Series:\n";

    for (int i = 0; i < n; i++) {
        cout << fibonacci(i, memo) << " ";
    }

    cout << endl;

    return 0;
}
