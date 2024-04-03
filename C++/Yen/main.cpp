// MAIN.CPP FILE CONTAINING:
// READING INPUT FROM GRAPH.TXT AND CONSTRUCTING GRAPH
// SHOWING YEN'S ALGORITHM ON GRAPH

#include<bits/stdc++.h>

using namespace std;

#include "yen.h"

int main()
{
	// open input file
	ifstream infile("graph.txt");
	// display error message if file can't be opened
	if (!infile)
	{
		cerr << "Error: Input file could not be opened or doesn't exist" << endl;
		return 1;
	}
	// define an adjacency list to represent the graph
	// vvii is a defined type in yen.h
	vvii adjList;
	
	// read the input from the file and contruct the adjacency list
	int node, neighbor, weight;
	while (infile >> node >> neighbor >> weight)
	{
		// resize the adjacency list if necessary
		adjList.resize(max(adjList.size(), (size_t)max(node, neighbor) + 1));	
		// add the neighbor and its weight to the node's list of neighbors
		adjList[node].push_back({neighbor, weight});
	}
	// close the input file
	infile.close();
	
	// define the source, destination, and the number of shortest paths to find
	int src = 0, dst = 4, K = 3;
	// find K-shortest paths between the source and destination using Yen's algorithm
	vector<vi> KShortestPaths = yenAlgorithm(adjList, src, dst, K);
   
   // check if no paths have been found and return
	if (KShortestPaths.size() == 0)
	{
		cout << "No paths from source to target have been found." << endl;
		return 1;
	}
	
	// otherwise, print the K-shortest paths
	cout << "The " << K << " shortest paths between " << src << " and " << dst << ":" << endl;
	for (int i = 0; i < KShortestPaths.size(); i++)
	{
		cout << "Path " << i + 1 << ": ";
		// print each node in the path
		for (int j = KShortestPaths[i].size() - 1; j >= 0; j--)
		{
			cout << KShortestPaths[i][j];
			// print an arrow between the nodes if it's not the first node in the path
			if (j != 0)
			{
				cout << " -> ";
			}
		}
		cout << endl;
	}

	return 0;
}//main
