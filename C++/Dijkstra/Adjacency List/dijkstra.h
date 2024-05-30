// IMPLEMENTATION USING ADJACENCY_LIST


#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <bits/stdc++.h>

using namespace std;

// INF = 1B to avoid overflow
#define INF 100000000

// adjacency list representation of the graph
typedef pair<int, int> ii;
vector<vector<ii>> adjList;


// Dijkstra algorithm
vector<int> dijkstra(int src, const vector<vector<ii>>& adjList)
{
	int n = adjList.size();
	vector<int> shortestDistances(n, INF);
	priority_queue<ii, vector<ii>, greater<ii>> pq;

	shortestDistances[src] = 0;
	pq.push({0, src});

	while (!pq.empty())
	{
		int curr_vertex = pq.top().second;
		int curr_dist = pq.top().first;
		pq.pop();

		if (curr_dist > shortestDistances[curr_vertex])
		{
			continue;
		}

		for (auto edge : adjList[curr_vertex])
		{
			int neighbor = edge.first;
			int weight = edge.second;

			if (shortestDistances[curr_vertex] + weight < shortestDistances[neighbor])
			{
				shortestDistances[neighbor] = shortestDistances[curr_vertex] + weight;
				pq.push({shortestDistances[neighbor], neighbor});
			}
	 	}
	}

	return shortestDistances;
}


#endif
