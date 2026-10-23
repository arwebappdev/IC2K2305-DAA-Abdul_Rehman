
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <limits>
using namespace std;
using namespace chrono;

const int INF = numeric_limits<int>::max();

struct Edge {
    int source;
    int destination;
    int weight;
};

struct MSTResult {
    vector<Edge> selectedEdges;
    int totalCost = 0;
    bool connected = false;
};

// ---------------- PRIM'S ALGORITHM ----------------

MSTResult primsAlgorithm(const vector<vector<int>>& graph, int n) {
    MSTResult result;

    vector<int> key(n, INF);
    vector<int> parent(n, -1);
    vector<bool> visited(n, false);

    key[0] = 0;

    for (int count = 0; count < n; count++) {
        int u = -1;
        int minimum = INF;

        for (int i = 0; i < n; i++) {
            if (!visited[i] && key[i] < minimum) {
                minimum = key[i];
                u = i;
            }
        }

        if (u == -1) {
            return result;
        }

        visited[u] = true;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] > 0 &&
                !visited[v] &&
                graph[u][v] < key[v]) {

                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    result.connected = true;

    for (int i = 1; i < n; i++) {
        result.selectedEdges.push_back({
            parent[i], i, graph[i][parent[i]]
        });

        result.totalCost += graph[i][parent[i]];
    }

    return result;
}

// ---------------- DISJOINT SET UNION ----------------

class DisjointSet {
    vector<int> parent;
    vector<int> rankValue;

public:
    DisjointSet(int n) {
        parent.resize(n);
        rankValue.resize(n, 0);

        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }

        return parent[x];
    }

    bool unite(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);

        if (rootU == rootV) {
            return false;
        }

        if (rankValue[rootU] < rankValue[rootV]) {
            parent[rootU] = rootV;
        } else if (rankValue[rootU] > rankValue[rootV]) {
            parent[rootV] = rootU;
        } else {
            parent[rootV] = rootU;
            rankValue[rootU]++;
        }

        return true;
    }
};

// ---------------- KRUSKAL'S ALGORITHM ----------------

MSTResult kruskalsAlgorithm(vector<Edge> edges, int n) {
    MSTResult result;

    sort(edges.begin(), edges.end(),
         [](const Edge& a, const Edge& b) {
             return a.weight < b.weight;
         });

    DisjointSet ds(n);

    for (const Edge& edge : edges) {
        if (ds.unite(edge.source, edge.destination)) {
            result.selectedEdges.push_back(edge);
            result.totalCost += edge.weight;

            if (result.selectedEdges.size() == n - 1) {
                result.connected = true;
                break;
            }
        }
    }

    return result;
}

// ---------------- DISPLAY RESULTS ----------------

void displayResult(const string& algorithmName,
                   const MSTResult& result) {
    cout << "\n" << algorithmName << ":\n";

    if (!result.connected) {
        cout << "MST cannot be formed. Graph is disconnected.\n";
        return;
    }

    cout << "Selected Edges:\n";

    for (const Edge& edge : result.selectedEdges) {
        cout << edge.source + 1 << " - "
             << edge.destination + 1
             << " : " << edge.weight << endl;
    }

    cout << "Total MST Cost: " << result.totalCost << endl;
}

// ---------------- MAIN FUNCTION ----------------

int main() {
    int n;

    cout << "Enter number of vertices: ";
    cin >> n;

    if (n <= 0 || n > 100) {
        cout << "Please enter between 1 and 100 vertices.\n";
        return 0;
    }

    vector<vector<int>> graph(n, vector<int>(n));
    vector<Edge> edges;

    cout << "\nEnter adjacency matrix:\n";
    cout << "(Enter 0 if there is no edge)\n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];

            if (graph[i][j] < 0) {
                cout << "Negative weights are not supported.\n";
                return 0;
            }
        }
    }

    // Validate undirected graph
    for (int i = 0; i < n; i++) {
        if (graph[i][i] != 0) {
            cout << "Diagonal elements must be 0.\n";
            return 0;
        }

        for (int j = i + 1; j < n; j++) {
            if (graph[i][j] != graph[j][i]) {
                cout << "Matrix must be symmetric.\n";
                return 0;
            }

            if (graph[i][j] > 0) {
                edges.push_back({i, j, graph[i][j]});
            }
        }
    }

    // Measure Prim's execution time
    auto primStart = high_resolution_clock::now();
    MSTResult primResult = primsAlgorithm(graph, n);
    auto primEnd = high_resolution_clock::now();

    auto primTime =
        duration_cast<microseconds>(primEnd - primStart).count();

    // Measure Kruskal's execution time
    auto kruskalStart = high_resolution_clock::now();
    MSTResult kruskalResult = kruskalsAlgorithm(edges, n);
    auto kruskalEnd = high_resolution_clock::now();

    auto kruskalTime =
        duration_cast<microseconds>(kruskalEnd - kruskalStart).count();

    // Display both results
    displayResult("Prim's Algorithm", primResult);
    displayResult("Kruskal's Algorithm", kruskalResult);

    cout << "\n========== PERFORMANCE COMPARISON ==========\n";

    cout << left << setw(25) << "Algorithm"
         << "Execution Time (microseconds)\n";

    cout << left << setw(25) << "Prim's Algorithm"
         << primTime << endl;

    cout << left << setw(25) << "Kruskal's Algorithm"
         << kruskalTime << endl;

    if (primResult.connected && kruskalResult.connected) {
        cout << "\nBoth algorithms produced "
             << "the same MST cost: ";

        if (primResult.totalCost == kruskalResult.totalCost) {
            cout << primResult.totalCost << endl;
        } else {
            cout << "Results do not match.\n";
        }
    }

    return 0;
}
