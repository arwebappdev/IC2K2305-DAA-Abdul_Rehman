
#include <iostream>
#include <vector>
using namespace std;

int main() {

    int vertices, edges;

    cout << "Enter number of vertices: ";
    cin >> vertices;

    cout << "Enter number of edges: ";
    cin >> edges;

    if (vertices <= 0 || edges < 0) {
        cout << "Invalid graph dimensions." << endl;
        return 1;
    }

    // Adjacency Matrix
    vector<vector<int>> matrix(
        vertices, vector<int>(vertices, 0)
    );

    // Adjacency List
    vector<vector<int>> adjList(vertices);

    cout << "\nEnter edges (source destination):\n";

    for (int i = 0; i < edges; i++) {

        int u, v;
        cin >> u >> v;

        // Validate vertex numbers
        if (u < 1 || u > vertices ||
            v < 1 || v > vertices) {

            cout << "Invalid vertex number." << endl;
            return 1;
        }

        // Convert 1-based vertices to 0-based indices
        u--;
        v--;

        // Update adjacency matrix
        matrix[u][v] = 1;
        matrix[v][u] = 1;

        // Update adjacency list
        adjList[u].push_back(v + 1);
        adjList[v].push_back(u + 1);
    }

    // Display Adjacency Matrix
    cout << "\nAdjacency Matrix:\n\n";

    cout << "   ";

    for (int i = 0; i < vertices; i++) {
        cout << i + 1 << " ";
    }

    cout << endl;

    for (int i = 0; i < vertices; i++) {

        cout << i + 1 << "  ";

        for (int j = 0; j < vertices; j++) {
            cout << matrix[i][j] << " ";
        }

        cout << endl;
    }

    // Display Adjacency List
    cout << "\nAdjacency List:\n\n";

    for (int i = 0; i < vertices; i++) {

        cout << i + 1 << " -> ";

        for (int neighbour : adjList[i]) {
            cout << neighbour << " ";
        }

        cout << endl;
    }

    return 0;
}
