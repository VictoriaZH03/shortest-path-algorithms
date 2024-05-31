#ifndef FIB_H
#define FIB_H

#include<bits/stdc++.h>
using namespace std;

// forward declaration of FibonacciHeap and Dijkstra
template <typename VertexType, typename DistanceType>
class FibonacciHeap;

template <typename VertexType, typename DistanceType>
class Dijkstra;

template <typename VertexType, typename DistanceType>
class Node
{
	public:
	// constructor
	Node(VertexType v, DistanceType d)
	: vertex(v), dist(d), parent(nullptr), child(nullptr), left(this), right(this), degree(0), mark(false) {}
	// getter functions for vertex and distance
	VertexType getVertex() const
	{
		return vertex;
	}

	DistanceType getDistance() const
	{
		return dist;
	}

	private:
	VertexType vertex; // vertex of the node
	DistanceType dist; // distance of the node
	Node* parent; // parent node
	Node* child; // child node
	Node* left; // left sibling
	Node* right; // right sibling
	int degree; // degree of the node
	bool mark; // mark for cascading cut


	// declare FibonacciHeap and Dijkstra as friends to allow access to private members
	friend class FibonacciHeap<VertexType, DistanceType>;
	friend class Dijkstra<VertexType, DistanceType>;
};


// FIBONACCIHEAP CLASS IMPLEMENTING THE FIBONACCI HEAP

template <typename VertexType, typename DistanceType>
class FibonacciHeap
{
	public:
	FibonacciHeap() : min(nullptr), n(0) {}
	
	// insert a new node into the heap
	Node<VertexType, DistanceType>* insert(VertexType vertex, DistanceType dist)
	{
		Node<VertexType, DistanceType>* node = new Node<VertexType, DistanceType>(vertex, dist);
		if (min == nullptr)
		{
			min = node;
		}
		else
		{
			node->right = min;
			node->left = min->left;
			min->left->right = node;
			min->left = node;
         if (node->dist < min->dist)
         {
				min = node;
			}
		}
		n++;
		return node;
	}
	
	// extract the minimum node from the heap
	Node<VertexType, DistanceType>* extractMin()
	{
		Node<VertexType, DistanceType>* z = min;
		if (z != nullptr)
		{
			if (z->child != nullptr)
			{
				vector<Node<VertexType, DistanceType>*> children;
				Node<VertexType, DistanceType>* x = z->child;
				do
				{
					children.push_back(x);
					x = x->right;
				} while (x != z->child);
				
				for (Node<VertexType, DistanceType>* x : children)
				{
					x->left->right = x->right;
					x->right->left = x->left;
					x->left = min->left;
					x->right = min;
					min->left->right = x;
					min->left = x;
					x->parent = nullptr;
				}
			}
			
			z->left->right = z->right;
			z->right->left = z->left;
			if (z == z->right)
			{
				min = nullptr;
			}
			else
			{
				min = z->right;
				consolidate();
			}
			n--;
		}
		
		return z;
	}
	
	// decrease the key of a node in the heap
	void decreaseKey(Node<VertexType, DistanceType>* x, DistanceType k)
	{
		if (k > x->dist)
		{
			cerr << "New key is greater than current key" << endl;
			return;
		}
		
		x->dist = k;
		Node<VertexType, DistanceType>* y = x->parent;
		if (y != nullptr && x->dist < y->dist)
		{
			cut(x, y);
			cascadingCut(y);
		}
		if (x->dist < min->dist)
		{
			min = x;
		}
	}
	
	// cut a node from its parent in the heap
	void cut(Node<VertexType, DistanceType>* x, Node<VertexType, DistanceType>* y)
	{
		if (x->right == x)
		{
 			y->child = nullptr;
		}
		else
		{
			x->right->left = x->left;
			x->left->right = x->right;
			if (y->child == x)
			{
				y->child = x->right;
			}
		}
		
		y->degree--;
		x->left = x->right = x;
		x->parent = nullptr;
		x->mark = false;
		x->right = min;
		x->left = min->left;
		min->left->right = x;
		min->left = x;
	}

	// perform cascading cut on a node in the heap
	void cascadingCut(Node<VertexType, DistanceType>* y)
	{
		Node<VertexType, DistanceType>* z = y->parent;
		if (z != nullptr)
		{
			if (!y->mark)
			{
				y->mark = true;
			}
			else
			{
				cut(y, z);
				cascadingCut(z);
			}
		}
	}
	
	// check if the heap is empty
	bool empty() const
	{
		return min == nullptr;
	}
		
	private:
	// pointer to the minimum node in the heap
	Node<VertexType, DistanceType>* min;
	// number of nodes in the heap
	int n;

	// link 2 nodes together
	void link(Node<VertexType, DistanceType>* y, Node<VertexType, DistanceType>* x)
	{
		y->left->right = y->right;
		y->right->left = y->left;
		y->parent = x;
		y->left = y->right = y;
		if (x->child == nullptr)
		{
			x->child = y;
		}
		else
		{
			y->right = x->child;
			y->left = x->child->left;
			x->child->left->right = y;
			x->child->left = y;
		}
		x->degree++;
		y->mark = false;
	}

	// consolidate the heap
	void consolidate()
	{
		int maxDegree = static_cast<int>(std::log2(n)) + 1;
		vector<Node<VertexType, DistanceType>*> A(maxDegree, nullptr);

		vector<Node<VertexType, DistanceType>*> rootList;
		Node<VertexType, DistanceType>* x = min;
		if (x != nullptr)
		{
			do
			{
				rootList.push_back(x);
				x = x->right;
			} while (x != min);
		}

		for (Node<VertexType, DistanceType>* w : rootList)
		{
			x = w;
			int d = x->degree;
			while (A[d] != nullptr)
			{
				Node<VertexType, DistanceType>* y = A[d];
				if (x->dist > y->dist)
				{
					swap(x, y);
				}
				link(y, x);
				A[d] = nullptr;
				d++;
			}
			A[d] = x;
		}

		min = nullptr;
		for (Node<VertexType, DistanceType>* y : A)
		{
			if (y != nullptr)
			{
				if (min == nullptr)
				{
					min = y;
					y->left = y->right = y;
				}
				else
				{
					y->right = min;
					y->left = min->left;
					min->left->right = y;
					min->left = y;
					if (y->dist < min->dist)
					{
						min = y;
					}
				}
			}
		}
	}
};
#endif
