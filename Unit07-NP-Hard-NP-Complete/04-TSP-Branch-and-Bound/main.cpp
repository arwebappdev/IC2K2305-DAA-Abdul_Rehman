
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

const long long INF = LLONG_MAX / 4;

long long bestCost = INF;
long long exploredNodes = 0;
long long prunedNodes = 0;

vector<int> bestPath;
vector<int> currentPath;
vector<bool> visited;

// Minimum outgoing edge from every city
vector<long long> minOutgoing;

// Calculate lower bound for the current partial route
long long calculateLowerBound(
    const vector<vector<int>>& graph,
    int currentCity,
    long long currentCost,
    int n
) {
    long long bound = currentCost;

    // Minimum edge needed to leave the current city
    long long minEdge = INF;

    for (int j = 0; j < n; j++) {
        if (!visited[j] && graph[currentCity][j] > 0) {
            minEdge = min(minEdge, (long long)graph[currentCity][j]);
        }
    }

    // If all cities are visited, return to the starting city
    if (minEdge == INF) {
        if (graph[currentCity][0] == 0) {
            return INF;
        }

        bound += graph[currentCity][0];
    }
    else {
        bound += minEdge;
    }

    // Add minimum outgoing edges for unvisited cities
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            bound += minOutgoing[i];
        }
    }

    return bound;
}

// Branch and Bound function
void tspBranchAndBound(
    const vector<vector<int>>& graph,
    int currentCity,
    int visitedCount,
    long long currentCost,
    int n
) {
    exploredNodes++;

    // All cities have been visited
    if (visitedCount == n) {

        // Return to the starting city
        if (graph[currentCity][0] == 0) {
            return;
        }

        long long totalCost =
            currentCost + graph[currentCity][0];

        if (totalCost < bestCost) {
            bestCost = totalCost;
            bestPath = currentPath;
            bestPath.push_back(0);
        }

        return;
    }

    // Calculate lower bound
    long long lowerBound = calculateLowerBound(
        graph,
        currentCity,
        currentCost,
        n
    );

    // Prune if this branch cannot improve the best tour
    if (lowerBound >= bestCost) {
        prunedNodes++;
        return;
    }

    // Try every unvisited city
    for (int nextCity = 1; nextCity < n; nextCity++) {

        if (!visited[nextCity] &&
            graph[currentCity][nextCity] > 0) {

            visited[nextCity] = true;
            currentPath.push_back(nextCity);

            tspBranchAndBound(
                graph,
                nextCity,
                visitedCount + 1,
                currentCost + graph[currentCity][nextCity],
                n
            );

            // Backtrack
            currentPath.pop_back();
            visited[nextCity] = false;
        }
    }
}

int main() {
    int n;

    cout << "Enter number of cities: ";
    cin >> n;

    if (n < 2) {
        cout << "At least 2 cities are required." << endl;
        return 0;
    }

    vector<vector<int>> graph(
        n, vector<int>(n)
    );

    cout << "\nEnter the cost adjacency matrix:\n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];

            if (graph[i][j] < 0) {
                cout << "Negative costs are not supported." << endl;
                return 0;
            }

            if (i == j && graph[i][j] != 0) {
                cout << "Diagonal values must be zero." << endl;
                return 0;
            }
        }
    }

    // Calculate minimum outgoing edge for each city
    minOutgoing.resize(n, INF);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && graph[i][j] > 0) {
                minOutgoing[i] = min(
                    minOutgoing[i],
                    (long long)graph[i][j]
                );
            }
        }
    }

    // Every city must have an outgoing edge
    for (int i = 0; i < n; i++) {
        if (minOutgoing[i] == INF) {
            cout << "No complete tour exists." << endl;
            return 0;
        }
    }

    visited.resize(n, false);

    // Start from city 0
    visited[0] = true;
    currentPath.push_back(0);

    tspBranchAndBound(
        graph,
        0,
        1,
        0,
        n
    );

    cout << "\n----- TSP Branch and Bound Result -----\n";

    if (bestCost == INF) {
        cout << "No complete tour exists." << endl;
    }
    else {
        cout << "Optimal Tour: ";

        for (int city : bestPath) {
            cout << city + 1 << " ";
        }

        cout << "\nMinimum Tour Cost: " << bestCost << endl;
    }

    cout << "\nExplored Nodes: " << exploredNodes << endl;
    cout << "Pruned Nodes: " << prunedNodes << endl;

    return 0;
}
