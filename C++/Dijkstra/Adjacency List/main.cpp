#include <bits/stdc++.h>

using namespace std;

#include "dijkstra.h"

int main()
{
	adjList = {
	{{1, 4}, {2, 1}},	// Node 0: (1,4), (2, 1)
	{{3, 2}},			// Node 1: (3, 2)
	{{1, 5}, {3, 1}},	// Node 2: (1, 5), (3, 1)
	{{4, 3}}};			// Node 3: (4, 3)
	
	// source node for Dijkstra's algorithm
	int src = 3;
	
	// test the algorithm
	vector<int> shortestDistances = dijkstra(src, adjList.size());
	
	//output shortest distances
	for (int i = 0; i < shortestDistances.size(); ++i)
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
