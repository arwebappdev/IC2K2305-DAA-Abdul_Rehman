
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

const long long INF = 99999;

void floydWarshall(vector<vector<long long>>& dist, int n) {

    // Consider every vertex as an intermediate vertex
    for (int k = 0; k < n; k++) {

        for (int i = 0; i < n; i++) {

            for (int j = 0; j < n; j++) {

                // Avoid adding infinity values
                if (dist[i][k] != INF && dist[k][j] != INF) {

                    long long newDistance =
                        dist[i][k] + dist[k][j];

                    if (newDistance < dist[i][j]) {
                        dist[i][j] = newDistance;
                    }
                }
            }
        }
    }
}

int main() {

    int n;

    cout << "Enter number of vertices: ";
    cin >> n;

    if (n <= 0) {
        cout << "Invalid number of vertices." << endl;
        return 1;
    }

    vector<vector<long long>> dist(
        n, vector<long long>(n)
    );

    cout << "\nEnter the adjacency matrix:\n";
    cout << "Enter 99999 if there is no direct edge.\n\n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> dist[i][j];
        }
    }

    // Check whether diagonal elements are zero
    for (int i = 0; i < n; i++) {
        if (dist[i][i] != 0) {
            cout << "\nInvalid input: Diagonal elements "
                 << "must be zero." << endl;
            return 1;
        }
    }

    floydWarshall(dist, n);

    // Check for negative weight cycles
    for (int i = 0; i < n; i++) {
        if (dist[i][i] < 0) {
            cout << "\nNegative weight cycle detected."
                 << endl;
            return 0;
        }
    }

    cout << "\nAll-Pairs Shortest Distance Matrix:\n\n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {

            if (dist[i][j] == INF) {
                cout << setw(10) << "INF";
            } else {
                cout << setw(10) << dist[i][j];
            }
        }
        cout << endl;
    }

    return 0;
}
