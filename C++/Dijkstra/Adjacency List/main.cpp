// IMPLEMENTATION USING ADJACENCY_LIST

#include <bits/stdc++.h>

#include "dijkstra.h"

using namespace std;

int main()
{
	// Read input from graph.txt and construct adjacency list
	ifstream inputFile("graph.txt");
	if (!inputFile)
	{
		cerr << "Error: Unable to open input file.\n";
		return 1;
	}

	vector<vector<ii>> adjList;
	int numVertices = 0;

	// Create a map to map vertex IDs to indices in the adjacency list
	map<int, int> vertexIndices;

	int source, neighbor, weight;
	while (inputFile >> source >> neighbor >> weight)
	{
		// If the source vertex does not exist in the map, add it to the adjacency list and update the map
		if (vertexIndices.find(source) == vertexIndices.end())
		{
			vertexIndices[source] = numVertices++;
			adjList.push_back(vector<ii>());
		}
		// If the neighbor vertex does not exist in the map, add it to the adjacency list and update the map
		if (vertexIndices.find(neighbor) == vertexIndices.end())
		{
			vertexIndices[neighbor] = numVertices++;
			adjList.push_back(vector<ii>());
		}
		// Add the edge to the adjacency list with its weight
		adjList[vertexIndices[source]].push_back({vertexIndices[neighbor], weight});
	}
	inputFile.close();

	// Source node for Dijkstra's algorithm
	int src = 0;

	// Test the algorithm
	vector<int> shortestDistances = dijkstra(src, adjList);

	// Output shortest distances
	for (int i = 0; i < shortestDistances.size(); i++)
	{
		cout << "Shortest distance from node " << src << " to node " << i << " is: ";
		if (shortestDistances[i] == INF)
		{
			cout << "INF" << endl;
		}
		else
		{
			cout << shortestDistances[i] << endl;
		}
	}

	return 0;
}//main
