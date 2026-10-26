
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void BFS(int start, const vector<vector<int>>& adjList,
         int vertices) {

    vector<bool> visited(vertices, false);
    queue<int> q;

    // Mark the starting vertex as visited
    visited[start] = true;

    // Insert the starting vertex into the queue
    q.push(start);

    cout << "\nBFS Traversal: ";

    while (!q.empty()) {

        // Remove the front vertex
        int current = q.front();
        q.pop();

        cout << current + 1 << " ";

        // Visit all unvisited neighbours
        for (int neighbour : adjList[current]) {

            if (!visited[neighbour]) {

                visited[neighbour] = true;
                q.push(neighbour);
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

    BFS(start - 1, adjList, vertices);

    return 0;
}
