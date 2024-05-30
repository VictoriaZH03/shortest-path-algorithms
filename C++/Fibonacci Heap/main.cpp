#include<bits/stdc++.h>

using namespace std;

#include "fib.h"

const int SIZE = 10;

int main()
{
	// TESTING IMPLEMENTED FUNCTIONS/STRUCTURES
	FibonacciHeap<int> fheap;
	
	// insert random values into the Fibonacci heap
	for (int i = 0; i < SIZE; i++)
	{
		fheap.insert(rand() % 90 + 10); // generate random numbers in the range [10, 99]
	}
	
	// print the Fibonacci heap with size, empty?, min key, root list
	fheap.print();
	cout << endl;
	
	// decrease the key of a given node with a given key
	FHeapNode<int>* node = fheap.extractMin();
	node = fheap.getMin()->next;
	cout << "Node key: " << node->getKey() << endl;
	int key = node->getKey() - 10;
	cout << "New key: " << key << endl;
	fheap.decreaseKey(node, key);
	fheap.print();
	cout << endl;
	
	// delete a node
	node = fheap.getMin()->next;
	cout << "Will delete node key: " << node->getKey() << endl;
	fheap.deleteNode(node);
	fheap.print();
	cout << endl;
	
	// test union operation
	FibonacciHeap<int> fheap2;
	for (int i = 0; i < SIZE; i++)
	{
		fheap2.insert(rand() % 90 + 10);
	}
	
	cout << "Second heap before union:" << endl;
	fheap2.print();
	cout << endl;
	
	FibonacciHeap<int> fheap_union = fheap.unionWith(fheap2);
	
	cout << "After union:" << endl;
	fheap_union.print();

	return 0;
}//main
