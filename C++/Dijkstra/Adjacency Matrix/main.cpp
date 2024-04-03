// IMPLEMENTATION USING ADJACENCY_MATRIX

#include <iostream>
#include <fstream>
#include "dijkstra.h"

using namespace std;

int main()
{
    // number of vertices
    const int V = 5;

    // initialize the graph adjacency matrix with INF
    int** graph = new int*[V];
    for (int i = 0; i < V; i++)
    {
        graph[i] = new int[V];
        for (int j = 0; j < V; j++)
        {
            graph[i][j] = INF;
        }
    }

    // read the graph information from the file and populate the adjacency matrix
    ifstream inputFile("graph.txt");
    if (!inputFile)
    {
        cerr << "Error: Unable to open the file." << endl;
        return 1;
    }

    int node, neighbor, weight;
    while (inputFile >> node >> neighbor >> weight)
    {
        // add the edge to the adjacency matrix
        graph[node][neighbor] = weight;
    }
    inputFile.close();

    // source vertex
    int src = 0; 

    // run Dijkstra's algorithm
    int* shortestDistances = dijkstra(graph, V, src);

    // output shortest distances from source vertex
    cout << "Shortest distances from vertex " << src << " to all other vertices:" << endl;
    for (int i = 0; i < V; i++)
    {
        cout << "Vertex " << i << ": " << shortestDistances[i] << endl;
    }

    // deallocate memory for the adjacency matrix
    for (int i = 0; i < V; i++)
    {
        delete[] graph[i];
    }
    delete[] graph;

    // Deallocate memory for the shortest distances array
    delete[] shortestDistances;

    return 0;
}//main
