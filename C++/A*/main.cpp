#include<bits/stdc++.h>

using namespace std;

#include "astar.h"

int main()
{
	// Example graph initialization
	vector<vector<Edge>> graph =
	{
		{{1, 4}, {2, 1}},	// Node 0
		{{3, 2}},			// Node 1
		{{1, 5}, {3, 1}},	// Node 2
		{{4, 3}},			// Node 3
		{},					// Node 4 (target)
    };

	int source = 2;
	int target = 4;

	// Find shortest path using A* algorithm
	vector<int> shortest_path = astar(graph, source, target);

	// Print shortest path
	cout << "Shortest Path from " << source << " to " << target << ": ";
	for (int node : shortest_path)
	{
		cout << node << " ";
	}
	cout << endl;


	return 0;
}
