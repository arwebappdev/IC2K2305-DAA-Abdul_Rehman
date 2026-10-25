
#include <iostream>
#include <vector>
#include <limits>
using namespace std;

const long long INF = numeric_limits<long long>::max();

// Find minimum cost path in a multistage graph
void multistageGraph(const vector<vector<int>>& graph, int n) {
    vector<long long> cost(n, INF);
    vector<int> nextVertex(n, -1);

    // Destination has zero cost to reach itself
    cost[n - 1] = 0;

    // Process vertices backwards
    for (int u = n - 2; u >= 0; u--) {
        for (int v = u + 1; v < n; v++) {

            // Check whether an edge exists
            if (graph[u][v] > 0 && cost[v] != INF) {

                long long currentCost =
                    graph[u][v] + cost[v];

                if (currentCost < cost[u]) {
                    cost[u] = currentCost;
                    nextVertex[u] = v;
                }
            }
        }
    }

    // Check whether destination is reachable
    if (cost[0] == INF) {
        cout << "\nNo path exists from source to destination."
             << endl;
        return;
    }

    // Display minimum cost
    cout << "\nMinimum Cost: " << cost[0] << endl;

    // Reconstruct the minimum-cost path
    cout << "Minimum Cost Path: ";

    int current = 0;
    cout << current + 1;

    while (current != n - 1) {
        current = nextVertex[current];

        if (current == -1) {
            cout << "\nPath reconstruction failed." << endl;
            return;
        }

        cout << " -> " << current + 1;
    }

    cout << endl;
}

int main() {
    int n;

    cout << "Enter number of vertices: ";
    cin >> n;

    if (n < 2 || n > 100) {
        cout << "Please enter between 2 and 100 vertices."
             << endl;
        return 0;
    }

    vector<vector<int>> graph(n, vector<int>(n));

    cout << "\nEnter the adjacency matrix:\n";
    cout << "(Enter 0 if there is no edge)\n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];

            if (graph[i][j] < 0) {
                cout << "Negative edge weights are not supported."
                     << endl;
                return 0;
            }
        }
    }

    // Validate the topological vertex ordering
    for (int i = 0; i < n; i++) {
        if (graph[i][i] != 0) {
            cout << "Diagonal elements must be 0."
                 << endl;
            return 0;
        }

        for (int j = 0; j < i; j++) {
            if (graph[i][j] != 0) {
                cout << "Invalid edge direction. "
                     << "Edges must go from lower to higher "
                     << "vertex numbers." << endl;
                return 0;
            }
        }
    }

    multistageGraph(graph, n);

    return 0;
}
