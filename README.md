# shortest-path-algorithms
This repository contains implementations of various shortest path algorithms using C++. The primary goal of this project is to understand these algorithms' workings and their practical applications while exploring different data structures for graph representation.

# Graph Theory Overview
Graph theory is a fundamental area of mathematics and computer science that focuses on the study of graphs, which model relationships between pairs of objects. A graph G=(V,E) consists of a set of vertices VV and a set of edges EE connecting pairs of vertices. Graphs are applied in network routing, data organization, social network analysis, and more.
This project addresses the shortest path problem: finding the path between two vertices uu and vv with the minimum total weight of its edges.

# Implemented Algorithms
The following shortest path algorithms are implemented in C++ using various graph representations:

| Algorithm              | Description | Graph Representation |
| :---------------- | :------------: | :----: |
| Dijkstra's Algorithm        | Single-source shortest path for graphs with non-negative edge weights   | Adjacency Matrix, Adjacency List |
| A* Search Algorithm           | Shortest path search using heuristics to guide traversal, suitable for pathfinding applications   | Adjacency List |
| Yen's K-Shortest Paths Algorithm    | Finds multiple shortest paths between two nodes in a graph, useful for routing optimization   | Adjacency Matrix |


* Adjacency Matrix: Useful for dense graphs where memory efficiency is less of a concern.
* Adjacency List: Preferred for sparse graphs due to lower memory usage.

# Conversion Utility
This project also includes a utility for converting between adjacency matrix and adjacency list representations. This utility makes it easier to switch between representations based on the requirements of different algorithms.
