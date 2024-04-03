#include<bits/stdc++.h>

using namespace std;

#include "astar.h"

int main()
{
	// Read input from graph.txt and construct graph
    ifstream inputFile("graph.txt");
    if (!inputFile) {
        cerr << "Error: Unable to open input file graph.txt\n";
        return 1;
    }

    vector<vector<Edge>> graph;
    int numVertices = 0;

    // Create a map to map vertex IDs to indices in the graph
    map<int, int> vertexIndices;

    int source, neighbor, weight;
    while (inputFile >> source >> neighbor >> weight) {
        // If the source vertex does not exist in the map, add it to the graph and update the map
        if (vertexIndices.find(source) == vertexIndices.end()) {
            vertexIndices[source] = numVertices++;
            graph.push_back(vector<Edge>());
        }
        // If the neighbor vertex does not exist in the map, add it to the graph and update the map
        if (vertexIndices.find(neighbor) == vertexIndices.end()) {
            vertexIndices[neighbor] = numVertices++;
            graph.push_back(vector<Edge>());
        }
        // Add the edge to the graph
        graph[vertexIndices[source]].push_back({neighbor, weight});
    }
    inputFile.close();

	int curr_source = 0;
	int curr_target = 4;

	// Find shortest path using A* algorithm
	vector<int> shortest_path = astar(graph, curr_source, curr_target);

	// Print shortest path
	cout << "Shortest Path from " << curr_source << " to " << curr_target << ": ";
	for (int node : shortest_path)
	{
		cout << node << " ";
	}
	cout << endl;


	return 0;
}
