// HEADER FILE CONTAINING:
// IMPLEMENTATION OF DIJKSTRA'S ALGORITHM BASED ON ADJACENCY_LIST
// IMPLEMENTATION OF YEN'S ALGORITHM USING DIJKSTRA'S ALGORITHM


#ifndef YEN_H
#define YEN_H

#include <bits/stdc++.h>
using namespace std;

// INF = 1B to avoid overflow
#define INF 1000000000

typedef pair<int, int> pii; // (vertex, weight)
typedef vector<int> vi; // path
typedef vector<pii> vii; // list of neighbors with weights
typedef vector<vii> vvii; // adjacency list representation

// Dijkstra's algorithm implementation to find shortest distances from a given source vertex
vector<int> dijkstra(vvii& graph, int src)
{
	int n = graph.size();
	// initialize all distances with infinity
	vector<int> dist(n, INF);
	// min-heap priority queue
	priority_queue<pii, vector<pii>, greater<pii>> pq;
	// distance from source to itself is 0
	dist[src] = 0;
	// push the source vertex into the priority queue with distance 0
	pq.push({0, src});

	// Dijkstra's algorithm main loop
	while (!pq.empty())
	{
		// extract the vertex with minimum distance
		int u = pq.top().second;
		// extract the distance
		int d = pq.top().first;
		// remove the vertex from the priority queue
		pq.pop();
		
		// if the extracted distance is greater than the current known distance, skip it
		if (d > dist[u])
		{
			continue;
		}

		for (pii& neighbor : graph[u])
		{
			// neighbor vertex
			int v = neighbor.first;
			// weight of the edge between u and v
			int w = neighbor.second;
			// if the path through u to v is shorter than the currently known distance to v
			if (dist[u] + w < dist[v])
			{
				// update the distance to v
  				dist[v] = dist[u] + w;
  				// push v into the priority queue with updated distance
				pq.push({dist[v], v});
			}
		}
	}
	// return the array of shortest distances from the source vertex
	return dist;
}

// structure to represent a path along with its total weight
struct PathWithWeight
{
	// vector to store the path
	vi path;
	// total weight of the path
	int total_weight;
	// parameter constructor to initialize path and total weight
	PathWithWeight(vi _path, int _total_weight) : path(_path), total_weight(_total_weight) {}
	// custom comparison operator for priority queue
	// needed for displaying paths in ascending order based on their total weight
	bool operator<(const PathWithWeight& other) const
	{
		return total_weight > other.total_weight;
	}
};

// helper function to find all possible paths between src and dst using DFS
void findAllPaths(vector<vector<int>>& kShortestPaths, const vvii& graph, vi& currentPath,
						int u, int dst, unordered_set<int>& visited)
{
	// if the current vertex is the destination, add the current path to the result
	if (u == dst)
   {
		kShortestPaths.push_back(currentPath);
		return;
	}

	// iterate through the neighbors of the current vertex
	for (const pii& neighbor : graph[u]) 
	{
		// neighbor vertex
		int v = neighbor.first;
		// if the neighbor vertex has not been visited yet
		if (visited.find(v) == visited.end())
		{
			currentPath.push_back(v); // add the neighbor vertex to the current path
			visited.insert(v); // mark the neighbor vertex as visited
			// recursively find paths from the neighbor vertex
			findAllPaths(kShortestPaths, graph, currentPath, v, dst, visited);
			visited.erase(v); // mark the neighbor vertex as unvisited for other paths
			currentPath.pop_back(); // remove the neighbor vertex from the current path
		}
	}
}


// Yen's algorithm to find K shortest path between a source and a destination vertex
vector<vector<int>> yenAlgorithm(vvii& graph, int src, int dst, int k)
{
	// vector to store the K-shortest paths
	vector<vector<int>> kShortestPaths;
	// min-heap priority queue of paths with their total weights
	priority_queue<PathWithWeight> pq;
	// declaring a separate vector variable ensures that we have an lvalue expression that can be passed to the function without encountering the error related to binding non-const lvalue references to rvalue expressions
	vi currentPath = {src};

	// find all possible paths between src and dst
	unordered_set<int> visited;
	// mark src as visited
	visited.insert(src);
	// start DFS to find all paths
	findAllPaths(kShortestPaths, graph, currentPath, src, dst, visited);

	// calculate total weights for each path and push them into the priority queue
	for (vi& path : kShortestPaths)
	{
		// initialize total weight for path
		int totalWeight = 0;
		// iterate through the vertices in the path to calculate the total weight
		for (int i = 0; i < path.size() - 1; i++)
		{
			// iterate throught the neighbors of the current vertex to find the weight of the edge
			for (pii& neighbor : graph[path[i]])
			{
				// if the neighbor vertex is the next vertex in the path, add the weight of the edge to the total weight
				// break out of inner loop
				if (neighbor.first == path[i + 1])
				{
					totalWeight += neighbor.second;
					break;
				}
			}
		}
		// push the path with its total weight into the priority queue
		pq.push({path, totalWeight});
	}

	// Extract k shortest paths from the priority queue
	vector<vector<int>> result;
	for (int i = 0; i < k && !pq.empty(); i++)
	{
		// extract the path from the top of the priority queue
		vi path = pq.top().path;
		// reverse the path to start from src and end at dst
		reverse(path.begin(), path.end());
		// add the reversed path to the result
		result.push_back(path);
		// remove it from the priority queue
		pq.pop();
	}
	// return the vector of K-shortest paths
	return result;
}

#endif
