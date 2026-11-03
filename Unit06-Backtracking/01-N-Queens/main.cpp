
#include <iostream>
#include <vector>
using namespace std;

int solutionCount = 0;
const int MAX_DISPLAY = 20;

// Check whether a queen can be placed safely
bool isSafe(const vector<int>& board, int row, int col) {

    // Check previously placed queens
    for (int i = 0; i < row; i++) {

        // Same column
        if (board[i] == col) {
            return false;
        }

        // Same diagonal
        if (abs(board[i] - col) == abs(i - row)) {
            return false;
        }
    }

    return true;
}

// Display one valid board arrangement
void displayBoard(const vector<int>& board, int n) {

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {

            if (board[i] == j) {
                cout << "Q ";
            } else {
                cout << ". ";
            }
        }

        cout << endl;
    }

    cout << endl;
}

// Solve N-Queens using Backtracking
void solveNQueens(vector<int>& board, int row, int n) {

    // All queens have been placed
    if (row == n) {

        solutionCount++;

        // Display only the first 20 solutions
        if (solutionCount <= MAX_DISPLAY) {

            cout << "Solution " << solutionCount << ":\n";
            displayBoard(board, n);
        }

        return;
    }

    // Try every column in the current row
    for (int col = 0; col < n; col++) {

        if (isSafe(board, row, col)) {

            // Place queen
            board[row] = col;

            // Move to the next row
            solveNQueens(board, row + 1, n);

            // Backtrack: remove the queen
            board[row] = -1;
        }
    }
}

int main() {

    int n;

    cout << "Enter the value of N: ";
    cin >> n;

    if (n <= 0 || n > 12) {
        cout << "Please enter N between 1 and 12." << endl;
        return 1;
    }

    vector<int> board(n, -1);

    solveNQueens(board, 0, n);

    cout << "Total number of solutions: "
         << solutionCount << endl;

    if (solutionCount > MAX_DISPLAY) {
        cout << "Only the first " << MAX_DISPLAY
             << " solutions were displayed." << endl;
    }

    if (solutionCount == 0) {
        cout << "No valid solution exists." << endl;
    }

    return 0;
}
