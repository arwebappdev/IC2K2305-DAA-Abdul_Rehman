
#include <iostream>
#include <vector>
#include <limits>
using namespace std;

const long long INF = numeric_limits<long long>::max() / 4;

struct Edge {
    int source;
    int destination;
    long long weight;
};

void bellmanFord(int vertices, const vector<Edge>& edges, int source) {

    vector<long long> distance(vertices, INF);

    // Distance from source to itself is zero
    distance[source] = 0;

    // Relax all edges V-1 times
    for (int i = 0; i < vertices - 1; i++) {

        bool updated = false;

        for (const Edge& edge : edges) {

            int u = edge.source;
            int v = edge.destination;
            long long w = edge.weight;

            // Relax only if the source vertex is reachable
            if (distance[u] != INF &&
                distance[u] + w < distance[v]) {

                distance[v] = distance[u] + w;
                updated = true;
            }
        }

        // Stop early if no distance was updated
        if (!updated) {
            break;
        }
    }

    // Check for a reachable negative-weight cycle
    for (const Edge& edge : edges) {

        int u = edge.source;
        int v = edge.destination;
        long long w = edge.weight;

        if (distance[u] != INF &&
            distance[u] + w < distance[v]) {

            cout << "\nNegative-weight cycle detected."
                 << endl;
            return;
        }
    }

    // Display shortest distances
    cout << "\nShortest distances from vertex "
         << source + 1 << ":\n\n";

    cout << "Vertex\tDistance\n";

    for (int i = 0; i < vertices; i++) {

        cout << i + 1 << "\t";

        if (distance[i] == INF) {
            cout << "INF";
        } else {
            cout << distance[i];
        }

        cout << endl;
    }
}

int main() {

    int vertices, edgeCount;

    cout << "Enter number of vertices: ";
    cin >> vertices;

    cout << "Enter number of edges: ";
    cin >> edgeCount;

    if (vertices <= 0 || edgeCount < 0) {
        cout << "Invalid graph dimensions." << endl;
        return 1;
    }

    vector<Edge> edges;

    cout << "\nEnter edges (source destination weight):\n";

    for (int i = 0; i < edgeCount; i++) {

        int u, v;
        long long w;

        cin >> u >> v >> w;

        // Convert 1-based vertices to 0-based indices
        if (u < 1 || u > vertices ||
            v < 1 || v > vertices) {

            cout << "Invalid vertex number." << endl;
            return 1;
        }

        edges.push_back({u - 1, v - 1, w});
    }

    int source;

    cout << "\nEnter source vertex: ";
    cin >> source;

    if (source < 1 || source > vertices) {
        cout << "Invalid source vertex." << endl;
        return 1;
    }

    bellmanFord(vertices, edges, source - 1);

    return 0;
}
