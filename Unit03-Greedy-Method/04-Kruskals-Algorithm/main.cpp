
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int source;
    int destination;
    int weight;
};

// Disjoint Set Union (Union-Find)
class DisjointSet {
private:
    vector<int> parent;
    vector<int> rankValue;

public:
    DisjointSet(int n) {
        parent.resize(n + 1);
        rankValue.resize(n + 1, 0);

        for (int i = 1; i <= n; i++) {
            parent[i] = i;
        }
    }

    // Find the representative of a set
    int find(int vertex) {
        if (parent[vertex] != vertex) {
            parent[vertex] = find(parent[vertex]);
        }

        return parent[vertex];
    }

    // Merge two sets
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

// Sort edges by increasing weight
bool compareEdges(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

void kruskalsAlgorithm(vector<Edge>& edges, int vertices) {
    sort(edges.begin(), edges.end(), compareEdges);

    DisjointSet ds(vertices);

    int totalCost = 0;
    int edgesSelected = 0;

    cout << "\nMinimum Spanning Tree:\n";
    cout << "Edge\tWeight\n";

    for (const Edge& edge : edges) {
        // Add edge only if it does not form a cycle
        if (ds.unite(edge.source, edge.destination)) {
            cout << edge.source << " - "
                 << edge.destination << "\t"
                 << edge.weight << endl;

            totalCost += edge.weight;
            edgesSelected++;

            if (edgesSelected == vertices - 1) {
                break;
            }
        }
    }

    if (edgesSelected != vertices - 1) {
        cout << "\nThe graph is disconnected."
             << " Minimum Spanning Tree cannot be formed."
             << endl;
        return;
    }

    cout << "\nMinimum Cost of Spanning Tree: "
         << totalCost << endl;
}

int main() {
    int vertices, edgeCount;

    cout << "Enter number of vertices: ";
    cin >> vertices;

    if (vertices <= 0 || vertices > 100) {
        cout << "Please enter between 1 and 100 vertices."
             << endl;
        return 0;
    }

    cout << "Enter number of edges: ";
    cin >> edgeCount;

    if (edgeCount < 0 || edgeCount > 10000) {
        cout << "Invalid number of edges." << endl;
        return 0;
    }

    vector<Edge> edges(edgeCount);

    cout << "\nEnter source, destination and weight of each edge:\n";

    for (int i = 0; i < edgeCount; i++) {
        cin >> edges[i].source
            >> edges[i].destination
            >> edges[i].weight;

        if (edges[i].source < 1 ||
            edges[i].source > vertices ||
            edges[i].destination < 1 ||
            edges[i].destination > vertices) {

            cout << "Invalid vertex number." << endl;
            return 0;
        }
    }

    kruskalsAlgorithm(edges, vertices);

    return 0;
}

