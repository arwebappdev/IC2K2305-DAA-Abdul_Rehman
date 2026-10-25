
#include <iostream>
using namespace std;

// Recursive function to calculate Fibonacci number
long long fibonacci(int n) {
    // Base cases
    if (n == 0) {
        return 0;
    }

    if (n == 1) {
        return 1;
    }

    // Recursive calls
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    int n;

    cout << "Enter the number of terms: ";
    cin >> n;

    if (n < 1 || n > 45) {
        cout << "Please enter a number between 1 and 45."
             << endl;
        return 0;
    }

    cout << "\nFibonacci Series:\n";

    for (int i = 0; i < n; i++) {
        cout << fibonacci(i) << " ";
    }

    cout << endl;

    return 0;
}
