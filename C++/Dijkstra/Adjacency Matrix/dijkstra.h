#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <bits/stdc++.h>

using namespace std;


#define INF  1000000

using namespace std;

// Function to deallocate memory for the adjacency matrix
void deallocateMatrix(int** matrix, int V) {
    for (int i = 0; i < V; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

// Dijkstra's algorithm implementation for adjacency matrix
int* dijkstra(int** graph, int V, int src) {
    // Create an array to store the shortest distances from the source vertex to all other vertices, initialized with infinity
    int* shortestDistances = new int[V];
    // Create an array to keep track of visited vertices
    bool* visited = new bool[V];

    // Set the distance of all vertices from source to infinity and mark them as not visited
    for (int i = 0; i < V; ++i) {
        shortestDistances[i] = INF;
        visited[i] = false;
    }

    // Set the distance of the source vertex to itself to 0
    shortestDistances[src] = 0;

    // Main loop of Dijkstra's algorithm
    for (int count = 0; count < V - 1; ++count) {
        // Find the vertex with the minimum distance that is not yet visited
        int u = -1;
        for (int v = 0; v < V; ++v) {
            if (!visited[v] && (u == -1 || shortestDistances[v] < shortestDistances[u]))
                u = v;
        }

        // Mark the selected vertex as visited
        visited[u] = true;

        // Update the distance of adjacent vertices
        for (int v = 0; v < V; ++v) {
            if (!visited[v] && graph[u][v] && shortestDistances[u] != INF &&
                shortestDistances[u] + graph[u][v] < shortestDistances[v]) {
                shortestDistances[v] = shortestDistances[u] + graph[u][v];
            }
        }
    }

    // Cleanup: deallocate memory
    delete[] visited;

    // Return the array containing the shortest distances from the source vertex
    return shortestDistances;
}


#endif
