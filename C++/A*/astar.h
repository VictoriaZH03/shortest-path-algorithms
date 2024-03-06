#ifndef ASTAR_H
#define ASTAR_H

#include<bits/stdc++.h>

using namespace std;

// Structure to represent a graph edge
struct Edge
{
	int dest;
	int weight;
};

// Function declaration for A* search algorithm
vector<int> astar(const vector<vector<Edge>>& graph, int source, int target);

// Structure to represent a graph node
struct Node
{
	// node ID
	int id;
	// heuristic value for A* algorithm
	int heuristic;
	// cost from start node to current node
	int g_cost;
	// constructor for Node
	Node(int id, int heuristic, int g_cost) : id(id), heuristic(heuristic), g_cost(g_cost) {}
	// Define priority queue based on f(n) = g(n) + h(n)
	bool operator<(const Node& other) const
	{
	return g_cost + heuristic > other.g_cost + other.heuristic;
	}
};

// A* search algorithm implementation
vector<int> astar(const vector<vector<Edge>>& graph, int source, int target)
{
	// get the number of nodes in the graph
	int num_nodes = graph.size();
	// parent vector to store the shortest path
	vector<int> parent(num_nodes, -1);
	// vector to track visited nodes, initialize with false, change to true when node is visited
	vector<bool> visited(num_nodes, false);
	// priority queue to explore nodes based on their priority
	priority_queue<Node> pq;
    
	// heuristic values for each node
	vector<int> heuristic(num_nodes);
	for (int i = 0; i < num_nodes; i++)
	{
		// assuming heuristic values are predefined (as in the example)
		// i represents the index of the current node in the graph
		// i * 2 ensures the nodes with smaller indices have higher heuristic values
		// 10 is the maximum heuristic value being 10
		heuristic[i] = 10 - i * 2;
	}
    
	// initializing source node and adding it to the priority queue
	pq.push(Node(source, heuristic[source], 0));
   
   // A* algorithm main loop
	while (!pq.empty())
	{
		// extract the node with the highest priority first
		Node current = pq.top();
		pq.pop();
		// get the id of the current node
		int current_id = current.id;
      
      // mark the current node as visited (true)  
		visited[current_id] = true;
        
		if (current_id == target)
		{
			break; // exit if target node is reached
		}
        
		// explore neighbors of the current node
		for (const Edge& edge : graph[current_id])
		{
			// get the id of the neighbor node
			int neighbor_id = edge.dest;
			// calculate the new cost from start to neighbor
			int new_g_cost = current.g_cost + edge.weight;
         
         // check if the neighbor node has not been visited or a shorter path is foun
			if (!visited[neighbor_id])
			{
				if (parent[neighbor_id] == -1 || new_g_cost < current.g_cost)
				{
					// update heuristic if needed (same heuristic function)
					heuristic[neighbor_id] = 10 - neighbor_id * 2;
					// update the parent of the neighbor node
					parent[neighbor_id] = current_id;
					// push the neighbor node into the priority queue
					pq.push({neighbor_id, heuristic[neighbor_id], new_g_cost});
				}
			}
		}
	}
    
	// reconstruct the shortest path from source to target
	vector<int> shortest_path;
	int current_node = target;
	while (current_node != -1)
	{
		// add the current node to the shortest path
		shortest_path.push_back(current_node);
		// move to the parent node
		current_node = parent[current_node];
	}
	// reverse the shortest path...
	reverse(shortest_path.begin(), shortest_path.end());
	
	// return the shortest path from source to target
	return shortest_path;
}



#endif
