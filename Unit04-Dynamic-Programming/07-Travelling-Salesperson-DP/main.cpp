
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

const long long INF = numeric_limits<long long>::max() / 4;

int main() {

    int n;

    cout << "Enter number of cities: ";
    cin >> n;

    if (n <= 0 || n > 18) {
        cout << "Number of cities must be between 1 and 18."
             << endl;
        return 1;
    }

    vector<vector<long long>> cost(
        n, vector<long long>(n)
    );

    cout << "\nEnter the cost matrix:\n";
    cout << "Enter 99999 if there is no direct route.\n\n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            long long value;
            cin >> value;

            if (value == 99999) {
                cost[i][j] = INF;
            } else {
                cost[i][j] = value;
            }
        }
    }

    // A city has no travelling cost to itself
    for (int i = 0; i < n; i++) {
        if (cost[i][i] != 0) {
            cout << "\nDiagonal elements must be zero."
                 << endl;
            return 1;
        }
    }

    int totalMasks = 1 << n;
    int allVisited = totalMasks - 1;

    // dp[mask][u] = minimum cost to visit mask and end at u
    vector<vector<long long>> dp(
        totalMasks, vector<long long>(n, INF)
    );

    // Store the previous city for route reconstruction
    vector<vector<int>> parent(
        totalMasks, vector<int>(n, -1)
    );

    // Start from city 1 (index 0)
    dp[1][0] = 0;

    // Consider every possible visited-city mask
    for (int mask = 1; mask < totalMasks; mask++) {

        // Consider the current ending city
        for (int u = 0; u < n; u++) {

            if (!(mask & (1 << u)) || dp[mask][u] == INF) {
                continue;
            }

            // Try visiting every unvisited city
            for (int v = 0; v < n; v++) {

                if (mask & (1 << v)) {
                    continue;
                }

                if (cost[u][v] == INF) {
                    continue;
                }

                int newMask = mask | (1 << v);

                long long newCost = dp[mask][u] + cost[u][v];

                if (newCost < dp[newMask][v]) {

                    dp[newMask][v] = newCost;
                    parent[newMask][v] = u;
                }
            }
        }
    }

    // Find the minimum cost of returning to the starting city
    long long minimumCost = INF;
    int lastCity = -1;

    for (int u = 0; u < n; u++) {

        if (dp[allVisited][u] == INF || cost[u][0] == INF) {
            continue;
        }

        long long totalCost = dp[allVisited][u] + cost[u][0];

        if (totalCost < minimumCost) {
            minimumCost = totalCost;
            lastCity = u;
        }
    }

    if (lastCity == -1) {
        cout << "\nNo complete tour is possible." << endl;
        return 0;
    }

    // Reconstruct the optimal route
    vector<int> route;

    int mask = allVisited;
    int current = lastCity;

    while (current != -1) {

        route.push_back(current);

        int previous = parent[mask][current];

        mask ^= (1 << current);
        current = previous;
    }

    reverse(route.begin(), route.end());

    // Return to the starting city
    route.push_back(0);

    cout << "\nMinimum travelling cost: "
         << minimumCost << endl;

    cout << "\nOptimal route: ";

    for (int i = 0; i < static_cast<int>(route.size()); i++) {

        cout << route[i] + 1;

        if (i != static_cast<int>(route.size()) - 1) {
            cout << " -> ";
        }
    }

    cout << endl;

    return 0;
}
