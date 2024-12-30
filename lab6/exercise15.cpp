//Nguyen Huu Dinh-22520251-lab6

#include <iostream>
#include <climits> // For INT_MAX
#include <cstring> // For memset

using namespace std;

const int MAX_NODES = 100;

// Function to find the minimum weight edge in the MST
int findMinKey(int key[], bool included[], int N) {
    int minKey = INT_MAX, minIndex = -1;

    for (int i = 0; i < N; ++i) {
        if (!included[i] && key[i] < minKey) {
            minKey = key[i];
            minIndex = i;
        }
    }

    return minIndex;
}

// Prim's algorithm to find the Minimum Spanning Tree (MST)
void primMST(int graph[MAX_NODES][MAX_NODES], int N) {
    int parent[MAX_NODES];  // To store the MST
    int key[MAX_NODES];     // Minimum weights for each node
    bool included[MAX_NODES]; // To track included nodes

    // Initialize arrays
    for (int i = 0; i < N; ++i) {
        key[i] = INT_MAX;
        included[i] = false;
    }

    key[0] = 0; // Start with the first node
    parent[0] = -1; // First node has no parent

    // Build the MST
    for (int count = 0; count < N - 1; ++count) {
        int u = findMinKey(key, included, N);
        included[u] = true;

        for (int v = 0; v < N; ++v) {
            if (graph[u][v] && !included[v] && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    // Print the MST
    cout << "Minimum Spanning Tree (MST):\n";
    int totalWeight = 0;
    for (int i = 1; i < N; ++i) {
        cout << parent[i] << " - " << i << " (Weight: " << graph[parent[i]][i] << ")\n";
        totalWeight += graph[parent[i]][i];
    }
    cout << "Total weight of MST: " << totalWeight << endl;
}

// DFS to find bridges in the network
void dfsBridges(int u, int parent, int adj[MAX_NODES][MAX_NODES], int N, int discovery[], int low[], bool visited[], int& time) {
    discovery[u] = low[u] = ++time;
    visited[u] = true;

    for (int v = 0; v < N; ++v) {
        if (adj[u][v] == 0) continue; // No direct connection

        if (!visited[v]) {
            dfsBridges(v, u, adj, N, discovery, low, visited, time);
            low[u] = min(low[u], low[v]);

            if (low[v] > discovery[u]) {
                cout << u << " - " << v << " is a critical connection (bridge)\n";
            }
        } else if (v != parent) {
            low[u] = min(low[u], discovery[v]);
        }
    }
}

// Find all critical connections (bridges) in the network
void findBridges(int graph[MAX_NODES][MAX_NODES], int N) {
    int discovery[MAX_NODES], low[MAX_NODES];
    bool visited[MAX_NODES];
    memset(discovery, -1, sizeof(discovery));
    memset(low, -1, sizeof(low));
    memset(visited, false, sizeof(visited));

    int time = 0;

    cout << "\nCritical Connections (Bridges):\n";
    for (int i = 0; i < N; ++i) {
        if (!visited[i]) {
            dfsBridges(i, -1, graph, N, discovery, low, visited, time);
        }
    }
}

int main() {
    int N = 6; // Number of devices (nodes)
    int graph[MAX_NODES][MAX_NODES] = {0};

    // Define the graph as an adjacency matrix
    graph[0][1] = 4; graph[1][0] = 4;
    graph[0][2] = 3; graph[2][0] = 3;
    graph[1][2] = 1; graph[2][1] = 1;
    graph[1][3] = 2; graph[3][1] = 2;
    graph[3][4] = 2; graph[4][3] = 2;
    graph[4][5] = 6; graph[5][4] = 6;
    graph[3][5] = 4; graph[5][3] = 4;

    // Optimize the network topology
    primMST(graph, N);
    findBridges(graph, N);

    return 0;
}
