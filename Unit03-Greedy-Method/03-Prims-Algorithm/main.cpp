
#include <iostream>
#include <vector>
#include <limits>
using namespace std;

const int INF = numeric_limits<int>::max();

// Find the unvisited vertex with the minimum key value
int findMinVertex(const vector<int>& key,
                  const vector<bool>& inMST,
                  int n) {
    int minValue = INF;
    int minIndex = -1;

    for (int i = 0; i < n; i++) {
        if (!inMST[i] && key[i] < minValue) {
            minValue = key[i];
            minIndex = i;
        }
    }

    return minIndex;
}

// Implement Prim's Algorithm
void primsAlgorithm(const vector<vector<int>>& graph, int n) {
    vector<int> parent(n, -1);
    vector<int> key(n, INF);
    vector<bool> inMST(n, false);

    // Start from vertex 1
    key[0] = 0;

    for (int count = 0; count < n; count++) {
        int u = findMinVertex(key, inMST, n);

        // No reachable unvisited vertex means graph is disconnected
        if (u == -1) {
            cout << "\nThe graph is disconnected."
                 << " Minimum Spanning Tree cannot be formed."
                 << endl;
            return;
        }

        inMST[u] = true;

        // Update adjacent vertices
        for (int v = 0; v < n; v++) {
            if (graph[u][v] > 0 &&
                !inMST[v] &&
                graph[u][v] < key[v]) {

                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    int totalCost = 0;

    cout << "\nMinimum Spanning Tree:\n";
    cout << "Edge\tWeight\n";

    for (int i = 1; i < n; i++) {
        cout << parent[i] + 1 << " - " << i + 1
             << "\t" << graph[i][parent[i]] << endl;

        totalCost += graph[i][parent[i]];
    }

    cout << "\nMinimum Cost of Spanning Tree: "
         << totalCost << endl;
}

int main() {
    int n;

    cout << "Enter number of vertices: ";
    cin >> n;

    if (n <= 0 || n > 100) {
        cout << "Please enter between 1 and 100 vertices."
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

    // Validate that the graph is undirected
    for (int i = 0; i < n; i++) {
        if (graph[i][i] != 0) {
            cout << "Diagonal elements must be 0."
                 << endl;
            return 0;
        }

        for (int j = i + 1; j < n; j++) {
            if (graph[i][j] != graph[j][i]) {
                cout << "The adjacency matrix must be symmetric."
                     << endl;
                return 0;
            }
        }
    }

    primsAlgorithm(graph, n);

    return 0;
}
