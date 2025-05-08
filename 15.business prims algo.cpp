#include <iostream>
using namespace std;

class Graph {
    int n;
    int cost[10][10], G[10][10];

public:
    void readGraph();
    int prims();
    void printGraph();
};

void Graph::readGraph() {
    cout << "Enter the number of nodes: ";
    cin >> n;
    cout << "Enter the cost of edges:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "Enter cost between [" << i << "][" << j << "]: ";
            int k;
            cin >> k;
            if (k == 0)
                cost[i][j] = 99; // Use 99 to represent infinity
            else
                cost[i][j] = k;
            G[i][j] = 0;
        }
    }
}

int Graph::prims() {
    int from[10], distance[10], visited[10], min_cost = 0, edge = n - 1;
    visited[0] = 1;
    for (int i = 1; i < n; i++) {
        distance[i] = cost[0][i];
        from[i] = 0;
        visited[i] = 0;
    }

    while (edge > 0) {
        int min = 99, v;
        for (int i = 1; i < n; i++) {
            if (visited[i] == 0 && distance[i] < min) {
                min = distance[i];
                v = i;
            }
        }

        int u = from[v];
        G[u][v] = distance[v];
        G[v][u] = distance[v];
        visited[v] = 1;
        min_cost += cost[u][v];
        edge--;

        for (int i = 1; i < n; i++) {
            if (visited[i] == 0 && cost[i][v] < distance[i]) {
                distance[i] = cost[i][v];
                from[i] = v;
            }
        }
    }
    return min_cost;
}

void Graph::printGraph() {
    cout << "\nSpanning Tree Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << G[i][j] << "\t";
        }
        cout << "\n";
    }
}

int main() {
    Graph g;
    int choice, cost;
    do {
        cout << "\n---- MENU ----\n";
        cout << "1. Enter Adjacency Matrix\n";
        cout << "2. Apply Prim's Algorithm\n";
        cout << "3. Display MST Matrix\n";
        cout << "4. Display Minimum Cost\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                g.readGraph();
                break;
            case 2:
                cost = g.prims();
                cout << "Prim's Algorithm Applied.\n";
                break;
            case 3:
                g.printGraph();
                break;
            case 4:
                cout << "Minimum Cost of Spanning Tree: " << cost << "\n";
                break;
            case 5:
                cout << "Thank You!\n";
                break;
            default:
                cout << "Invalid Choice!\n";
        }
    } while (choice != 5);

    return 0;
}

