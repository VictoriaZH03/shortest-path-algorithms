#include <bits/stdc++.h>

using namespace std;

#include "dijkstra.h"

int main()
{
	// example adjacency matrix representing a graph
	int V = 5;	// number of vertices
	int** graph = new int*[V];
	
	for (int i = 0; i < V; ++i)
	{
		graph[i] = new int[V];
		for (int j = 0; j < V; ++j)
		{
			// initialize with INF except for the diagonal
			graph[i][j] = (i == j) ? 0 : INF;
		}
	}
	
	// example edges of graph
	graph[0][1] = 4;
	graph[0][2] = 1;
	graph[1][3] = 2;
	graph[2][1] = 5;
	graph[2][3] = 1;
	graph[3][4] = 3;
	
	// source vertex
	int src = 0;
	
	int* shortestDistances = dijkstra(graph, V, src);
	
	// output shortest distances
	cout << "Shortest distances from vertex " << src << " to all other vertices:" << endl;
	for (int i = 0; i < V; ++i)
	{
		cout << "Vertex " << i << ": " << shortestDistances[i] << endl;
	}
	
	// deallocate memory
	deallocateMatrix(graph, V);
	delete[] shortestDistances;
	
	
	return 0;
}//main
