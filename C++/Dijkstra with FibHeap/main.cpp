#include <bits/stdc++.h>
using namespace std;

#include "fib.h"
#include "di_fib.h"

int main()
{
	// example graph representation (adjacency list)
	vector<vector<pair<int, int>>> graph = {
        {{1, 4}, {2, 1}},
        {{3, 1}},
        {{1, 2}, {3, 5}},
        {}
    };

	// instantiate Dijkstra class with the graph
	Dijkstra<int, int> dijkstra(graph);

	// run Dijkstra's algorithm from vertex 0
	vector<int> distances = dijkstra.shortestDistances(0);

	// Output shortest distances
	for (int i = 0; i < distances.size(); i++)
	{
		cout << "Shortest distance from 0 to " << i << " is " << distances[i] << endl;
	}

	return 0;
}//main
