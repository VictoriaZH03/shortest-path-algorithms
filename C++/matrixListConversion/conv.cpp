#include <bits/stdc++.h>

using namespace std;

void printMatrix(const vector<vector<int>>& matrix)
{
	cout << "Adjacency Matrix: " << endl;
	for (const auto& row : matrix)
	{
		for (int weight : row)
		{
			cout << weight << " ";
		}
	cout << endl;
    }
}

void printList(const vector<vector<pair<int, int>>>& adjList)
{
	cout << "Adjacency List: " << endl;
	for (int i = 0; i < adjList.size(); i++)
	{
		cout << "Node " << i << ": ";
		for (const auto& pair : adjList[i])
		{
			cout << "(" << pair.first << ", " << pair.second << ") ";
		}
		cout << endl;
	}
}

vector<vector<pair<int, int>>> matrixToList(const vector<vector<int>>& matrix)
{
	int nodes = matrix.size();
	vector<vector<pair<int, int>>> adjList(nodes);

	for (int i = 0; i < nodes; ++i)
	{
		for (int j = 0; j < nodes; ++j)
		{
			if (matrix[i][j] != 0)
			{
				adjList[i].push_back(make_pair(j, matrix[i][j]));
			}
		}
	}

	return adjList;
}

vector<vector<int>> listToMatrix(const vector<vector<pair<int, int>>>& adjList) {
	int nodes = adjList.size();
	vector<vector<int>> newMatrix(nodes, vector<int>(nodes, 0));

	for (int i = 0; i < nodes; i++)
	{
		for (const auto& edge : adjList[i])
		{
			newMatrix[i][edge.first] = edge.second;
		}
	}

	return newMatrix;
}

int main()
{
	// Read input from graph.txt and construct adjacency matrix and list
	ifstream inputFile("graph.txt");
	if (!inputFile)
	{
		cerr << "Error: Unable to open input file graph.txt\n";
		return 1;
	}

	vector<vector<int>> matrix;
	vector<vector<pair<int, int>>> adjList;
	int numVertices = 0;

	// Create a map to map vertex IDs to indices in the adjacency list
	map<int, int> vertexIndices;

	int source, neighbor, weight;
	while (inputFile >> source >> neighbor >> weight)
	{
		// Update the number of vertices if necessary
		numVertices = max(numVertices, max(source, neighbor) + 1);

		// Resize matrix and adjacency list if necessary
		if (numVertices > matrix.size())
		{
			matrix.resize(numVertices, vector<int>(numVertices, 0));
			adjList.resize(numVertices);
		}

		// Update matrix and adjacency list
		matrix[source][neighbor] = weight;
		adjList[source].push_back({neighbor, weight});
	}
	inputFile.close();

	// Print original matrix and list
	printMatrix(matrix);
	printList(adjList);

	// Transform adjacency list to matrix
	vector<vector<int>> resultMatrix = listToMatrix(adjList);
	cout << "\nTransformed to Matrix:" << endl;
	printMatrix(resultMatrix);

	// Transform matrix to adjacency list
	vector<vector<pair<int, int>>> newAdjList = matrixToList(matrix);
	cout << "\nTransformed to List:" << endl;
	printList(newAdjList);

	return 0;
}
