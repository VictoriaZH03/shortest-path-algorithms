// IMPLEMENTATION USING ADJACENCY_MATRIX

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#define INF 1000000

// function to deallocate memory for the adjacency matrix
void deallocateMatrix(int** matrix, int V)
{
    for (int i = 0; i < V; ++i)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}

// Dijkstra's algorithm implementation for adjacency matrix
int* dijkstra(int** graph, int V, int src)
{
    // create an array to store the shortest distances from the source vertex to all other vertices
    int* shortestDistances = new int[V];
    
    // create an array to keep track of visited vertices
    bool* visited = new bool[V];

    // initialize distances and visited array
    for (int i = 0; i < V; i++)
    {
        shortestDistances[i] = INF;
        visited[i] = false;
    }

    // distance of source vertex from itself is always 0
    shortestDistances[src] = 0;

    // main loop of Dijkstra's algorithm
    for (int count = 0; count < V - 1; count++)
    {
        // Find the vertex with the minimum distance that is not yet visited
        int u = -1;
        for (int v = 0; v < V; v++)
        {
            if (!visited[v] && (u == -1 || shortestDistances[v] < shortestDistances[u]))
            {
                u = v;
            }
        }

        // mark the selected vertex as visited
        visited[u] = true;

        // Update the distance of adjacent vertices
        for (int v = 0; v < V; v++)
        {
            if (!visited[v] && graph[u][v] && shortestDistances[u] != INF && shortestDistances[u] + graph[u][v] < shortestDistances[v])
            {
            shortestDistances[v] = shortestDistances[u] + graph[u][v];
            }
        }
    }

    //deallocate memory
    delete[] visited;

    // Return the array containing the shortest distances from the source vertex
    return shortestDistances;
    
}

#endif
