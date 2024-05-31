#ifndef DI_FIB_H
#define DI_FIB_H

// CLASS DIJKSTRA IMPLEMENTING GRAPH AND DIJKSTRA ALGORITHM
template <typename VertexType, typename DistanceType>
class Dijkstra
{
	public:
	// constructor
	Dijkstra(const vector<vector<pair<VertexType, DistanceType>>>& graph) : graph_(graph) {}

	// Dijkstra's algorithm
	vector<DistanceType> shortestDistances(VertexType start)
	{
		// initialize distances array with infinite distance
		vector<DistanceType> distances(graph_.size(), std::numeric_limits<DistanceType>::max());
		distances[start] = 0; // distance from start vertex to itself is 0

		// priority queue to store vertices based on their distances from the start vertex
		priority_queue<pair<DistanceType, VertexType>, vector<pair<DistanceType, VertexType>>, greater<>> pq;
		
		pq.push({0, start}); // Start vertex with distance 0

		// Dijkstra's algorithm
		while (!pq.empty())
		{
			DistanceType dist = pq.top().first;
			VertexType u = pq.top().second;
			pq.pop();

			// update distances to adjacent vertices
			for (const auto& edge : graph_[u])
			{
				VertexType v = edge.first;
				DistanceType weight = edge.second;
				if (dist + weight < distances[v])
				{
					distances[v] = dist + weight;
					pq.push({distances[v], v});
				}
			}
		}

		return distances;
	}

	private:
	vector<vector<pair<VertexType, DistanceType>>> graph_;
};

#endif
