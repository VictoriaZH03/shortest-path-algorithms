
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


// Dijkstra's algorithm implementation
vector<int> dijkstra(int src, int n)
{
	// create a vector to store the shortest distances from the source vertex to all other vertices, initialize all distances with infinity
	vector<int> shortestDistances(n, INF);
	// create a priority queue to store vertices and their distances from the source, here a min-heap is used so the pair with the smallest distance will be at the top
	priority_queue<ii, vector<ii>, greater<ii>> pq;
	
	// set the distance of the source vertex to itself to 0
	shortestDistances[src] = 0;
	// push the source vertex and its distance (0) into priority queue
	pq.push({0, src});
	
	// main loop of Dijkstra's algorithm
	while (!pq.empty())
	{
		// extract the vertex with the smallest distance
		int curr_vertex = pq.top().second;	// get the vertex
		int curr_dist = pq.top().first;	// get the distance
		pq.pop();									// remove the vertex from pq
		
		
		// if the extracted distance is greater than the distance already calculated for this vertex, it means we've found a shorter path in the past, so we skip this vertex
		if (curr_dist > shortestDistances[curr_vertex]) continue;
		
		// iterato through all the adjacent vertices of curr_vertex
		for (auto edge : adjList[curr_vertex])
		{
			int neighbor = edge.first;	// adjacent vertex
			int weight = edge.second;	// weight of the edge from curr_vertex to neighbor
			
			// if the distance from source to curr_vertex plus the weight of the edge from curr_vertex to neighbor is less than the current distance from source to neighbor, update the distance
			if (shortestDistances[curr_vertex] + weight < shortestDistances[neighbor])
			{
				// udpate the distance to neighbor
				shortestDistances[neighbor] = shortestDistances[curr_vertex] + weight;
				// push the updated distance and neighbor into pq
				pq.push({shortestDistances[neighbor], neighbor});
			}
		}
	}
	// return the vector containing the shortest distance from source vertex
	return shortestDistances;
}

#endif
