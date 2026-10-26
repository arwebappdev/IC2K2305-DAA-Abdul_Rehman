
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// Recursive DFS
void recursiveDFS(int current,
                  const vector<vector<int>>& adjList,
                  vector<bool>& visited) {

    // Mark current vertex as visited
    visited[current] = true;

    cout << current + 1 << " ";

    // Visit all unvisited neighbours
    for (int neighbour : adjList[current]) {

        if (!visited[neighbour]) {
            recursiveDFS(neighbour, adjList, visited);
        }
    }
}

// Iterative DFS using an explicit stack
void iterativeDFS(int start,
                  const vector<vector<int>>& adjList,
                  int vertices) {

    vector<bool> visited(vertices, false);
    stack<int> st;

    st.push(start);

    cout << "\nIterative DFS Traversal: ";

    while (!st.empty()) {

        int current = st.top();
        st.pop();

        // Skip vertices that have already been visited
        if (visited[current]) {
            continue;
        }

        visited[current] = true;
        cout << current + 1 << " ";

        // Push neighbours in reverse order
        // to match recursive DFS traversal order
        for (int i = static_cast<int>(adjList[current].size()) - 1;
             i >= 0; i--) {

            int neighbour = adjList[current][i];

            if (!visited[neighbour]) {
                st.push(neighbour);
            }
        }
    }

    cout << endl;
}

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

    vector<vector<int>> adjList(vertices);

    cout << "\nEnter edges (source destination):\n";

    for (int i = 0; i < edges; i++) {

        int u, v;
        cin >> u >> v;

        if (u < 1 || u > vertices ||
            v < 1 || v > vertices) {

            cout << "Invalid vertex number." << endl;
            return 1;
        }

        // Convert to 0-based indexing
        u--;
        v--;

        // Create an undirected edge
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    int start;

    cout << "\nEnter starting vertex: ";
    cin >> start;

    if (start < 1 || start > vertices) {
        cout << "Invalid starting vertex." << endl;
        return 1;
    }

    start--;

    // Recursive DFS
    vector<bool> visited(vertices, false);

    cout << "\nRecursive DFS Traversal: ";

    recursiveDFS(start, adjList, visited);

    cout << endl;

    // Iterative DFS
    iterativeDFS(start, adjList, vertices);

    return 0;
}
