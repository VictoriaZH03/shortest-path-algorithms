#ifndef FIB_H
#define FIB_H

#include <bits/stdc++.h>


// DECLARATION OF TEMPLATE CLASS FHEAPNODE AND ITS MEMBERS

// Fibonacci heap node

template<typename T>
class FHeapNode
{
	public:
	// key that is stores in the node
	T key;
	// whether the node has lost child since it was made a child
	bool mark;
	// degree of the node is the number of children nodes
	int degr;
	// pointers to parent and child node, previous sibling, next sibling
	FHeapNode<T>* prnt;
	FHeapNode<T>* chld;
	FHeapNode<T>* prev;
	FHeapNode<T>* next;
	
	// constructor
	FHeapNode(T k) : key(k), mark(false), degr(0), prnt(nullptr), chld(nullptr), prev(this), next(this) {}
	
	T getKey() const
	{
		return key;
	}
};

// DECLARATION OF FIBONACCIHEAP TEMPLATE CLASS AND ITS MEMBERS

template<typename T>
class FibonacciHeap
{
	public:
	// constructor without parameters
	FibonacciHeap() : min(nullptr), numb(0) {}
	
	int size() const;
	bool isEmpty() const;
	T minimum() const;
	int maxDegree() const;
	void insert(T key);
	FHeapNode<T>* extractMin();
	FibonacciHeap<T> unionWith(FibonacciHeap<T>& other);
	void decreaseKey(FHeapNode<T>* node, T key);
	void deleteNode(FHeapNode<T>* node);
	void print() const;

	FHeapNode<T>* getMin() const
	{
		return min;
	}
	private:
	// pointer to the root of the tree containing the minimum
	FHeapNode<T>* min;
	// number of elements currently stored in the Fibonacci heap
	int numb;
	
	int degree(FHeapNode<T>* node) const;
	bool isEmptyChild(FHeapNode<T>* node) const;
	FHeapNode<T>* attach(FHeapNode<T>*& head, FHeapNode<T>* node);
	FHeapNode<T>* detach(FHeapNode<T>*& head, FHeapNode<T>* node);
	void addChild(FHeapNode<T>* parent, FHeapNode<T>* child);
	FHeapNode<T>* removeChild(FHeapNode<T>* parent);
	void lstPrint(FHeapNode<T>* head) const;
	void printNode(const FHeapNode<T>* node) const;
	vector<FHeapNode<T>*> getArray(FHeapNode<T>* head) const;
	FHeapNode<T>* connect(FHeapNode<T>* firstHead, FHeapNode<T>* secondHead);
	void attachToRoot(FHeapNode<T>* node);
	void link(FHeapNode<T>* y, FHeapNode<T>* x);
	void consolidate();
	void cut(FHeapNode<T>* node, FHeapNode<T>* parent);
	void cascadingCut(FHeapNode<T>* node);
	
};

// IMPLEMENTATION OF FIBONACCIHEAP PRIVATE FUNCTIONS

// number of children of a node
template<typename T>
int FibonacciHeap<T>::degree(FHeapNode<T>* node) const
{
	return node ? node->degr : 0;
}

// whether the child list is empty
template<typename T>
bool FibonacciHeap<T>::isEmptyChild(FHeapNode<T>* node) const
{
	return node ? node->chld == nullptr : true;
}

// attach node to a circular doubly-linked list defined by a node
template<typename T>
FHeapNode<T>* FibonacciHeap<T>::attach(FHeapNode<T>*& head, FHeapNode<T>* node)
{
	if (!head)
	{
		// this is the first node in the list
		head = node;
		head->next = head; // keep list circular
		head->prev = head;
	}
	else if (head->next == head)
	{
		// the list node is the only node in the list
		head->next = node; // attach the new node as second
		head->prev = node; // keep the list circular
		node->prev = head; // attach the previous link of the new node
		node->next = head; // keep the list circular
	}
	else
	{
		// there is more than one node in the list
		FHeapNode<T>* after = head->next; // the node after the head node
		head->next = node; // attach the new node after the list node
		node->prev = head; // the previous of the new node becomes the head
		node->next = after; // connect new node to next
		after->prev = node; // connect the node after to the new node
	}
	return head;
}

// detach a node to a circular doubly-linked list but preserve the links of the removed node
template<typename T>
FHeapNode<T>* FibonacciHeap<T>::detach(FHeapNode<T>*& head, FHeapNode<T>* node)
{
	if (!head)
	{
		throw invalid_argument("Remove a node from an empty linked list.");
	}
	if (head->next == head)
	{
		if (node != head)
		{
			throw domain_error("Detach the last node, but it is not equal to the head.");
		}
		// detach the last node from the list
		head = nullptr;
	}
	else
	{
		if (node == head)
		{
			// the node to remove is the node that holds the list
			head = head->next;
		}
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	return head;
}

// add a node to the child list of a node
template<typename T>
void FibonacciHeap<T>::addChild(FHeapNode<T>* prnt, FHeapNode<T>* chld)
{
	chld->prnt = prnt; // set the parent of the child node
	chld->mark = false; // reset the mark field of the child node
	// attach child node to the child list of the parent node
	prnt->chld = attach(prnt->chld, chld);
	// increment degree of the parent node
	prnt->degr += 1;
}

// remove a node from the child list and return it as a result
template<typename T>
FHeapNode<T>* FibonacciHeap<T>::removeChild(FHeapNode<T>* prnt)
{
	FHeapNode<T>* result = prnt->chld;
	prnt->chld = detach(prnt->chld, result);
	result->prnt = nullptr; // reset the link of the parent node
	prnt->degr -= 1; // update degree of the parent node
	
	return result;
}

// print the constants of a circular doubly-linked list
template<typename T>
void FibonacciHeap<T>::lstPrint(FHeapNode<T>* head) const
{
	FHeapNode<T>* curr = head;
	bool more = true;
	while (more)
	{
		cout << curr->key << " ";
		curr = curr->next;
		if (curr == head)
		{
			more = false;
		}
	}
	cout << endl;
}

// print a node data structure
template<typename T>
void FibonacciHeap<T>::printNode(const FHeapNode<T>* node) const
{
	cout << "[Key: " << node->key << "]" << endl;
	cout << "Mark: " << boolalpha << node->mark << endl;
	cout << "Degree: " << degree(node) << endl;
	
	cout << "Child list: ";
	if (node->chld)
	{
		cout << "[ ";
		lstprint(node->chld);
		cout << "]" << endl;
	}
	else
	{
		cout << "empty" << endl;
	}
}

// get an array of nodes from a list given its head
template<typename T>
vector<FHeapNode<T>*> FibonacciHeap<T>::getArray(FHeapNode<T>* head) const
{
	vector<FHeapNode<T>*> result;
	bool more = true;
	FHeapNode<T>* curr = head;
	while (more)
	{
		result.push_back(curr);
		curr = curr->next;
		if (curr == head)
		{
			more = false;
		}
	}
	return result;
}

// connect 2 circular doubly-linked lists, where each list is given using a single node reference
template<typename T>
FHeapNode<T>* FibonacciHeap<T>::connect(FHeapNode<T>* fhead, FHeapNode<T>* shead)
{
	if (!fhead || !shead)
	{
		throw invalid_argument("Connect an empty list.");
	}
	// both lists are not empty
	FHeapNode<T>* ftail = fhead->next; // the node after the head becomes tail in first list
	FHeapNode<T>* stail = shead->next; // the node after the head becomes tail in second list
	fhead->next = stail;
	stail->prev = fhead;
	shead->next = ftail;
	ftail->prev = shead;
	
	return fhead;
}

// attach a node to the root list
template<typename T>
void FibonacciHeap<T>::attachToRoot(FHeapNode<T>* node)
{
	min = attach(min, node);
}

// remove a node from the root list and add it as a child of another node
template<typename T>
void FibonacciHeap<T>::link(FHeapNode<T>* y, FHeapNode<T>* x)
{
	// remove y from the root list
	min = detach(min, y);
	// add y as a child of x
	addChild(x, y);
	y->mark = false;
}
	
// consolidate the Fibonacci heap
template<typename T>
void FibonacciHeap<T>::consolidate()
{
	// upper bound on the max degree plus one since indexing starts from 1
	int max_degree = maxDegree();
	// look-up table of pointers to the roots according to their degree
	vector<FHeapNode<T>*> tbl(max_degree + 1, nullptr);
	
	// for each node in the root list of the Fibonacci heap
	vector<FHeapNode<T>*> rootlist = getArray(min);
	for (FHeapNode<T>* w : rootlist)
	{
		FHeapNode<T>* x = w;
		int d = degree(x);
		while (tbl[d] != nullptr)
		{
			FHeapNode<T>* y = tbl[d];
			if (x->key > y->key)
			{
				swap(x, y);
			}
			link(y, x);
			tbl[d] = nullptr;
			d++;
		}
		tbl[d] = x;
	}
	min = nullptr;
	for (FHeapNode<T>* x : tbl)
	{
		if (x != nullptr)
		{
			if (min == nullptr)
			{
				min = x;
			}
			else
			{
				attachToRoot(x);
				if (x->key < min->key)
				{
					min = x;
				}
			}
		} 
	}
}

// cut the link between the parent and the child node, making the child a root
template<typename T>
void FibonacciHeap<T>::cut(FHeapNode<T>* node, FHeapNode<T>* prnt)
{
	prnt->chld = detach(prnt->chld, node); 
	prnt->degr -= 1; // update degree of the parent node 
	node->prnt = nullptr; // reset the link to the parent node
	node->mark = false; // unamrk the detached child node
	attachToRoot(node); // attach the detached child node to the root list
}

// cascading cut operation
template<typename T>
void FibonacciHeap<T>::cascadingCut(FHeapNode<T>* node)
{
	FHeapNode<T>* prnt = node->prnt;
	if (prnt != nullptr)
	{
		if (node->mark == false)
		{
			node->mark = true;
		}
		else
		{
			cut(node, prnt);
			cascadingCut(prnt);
		}
	}
}


// IMPLEMENTATION OF FIBONACCIHEAP PUBLIC FUNCTIONS

// get the size of the Fibonacci heap
template<typename T>
int FibonacciHeap<T>::size() const
{
	return numb;
}

// check whether the Fibonacci heap is empty
template<typename T>
bool FibonacciHeap<T>::isEmpty() const
{	
	return min == nullptr;
	// return numb == 0;
}

// get the key of the minimum node in the Fibonacci heap
template<typename T>
T FibonacciHeap<T>::minimum() const
{
	return !isEmpty() ? min->key : T();
}

// calculate upped bound on the maximum degree
template<typename T>
int FibonacciHeap<T>::maxDegree() const
{
	return static_cast<int>(floor(log(numb) / log((1 + sqrt(5)) / 2)));
}
	
// insert a new key into the Fibonacci heap
template<typename T>	
void FibonacciHeap<T>::insert(T key)
{
	FHeapNode<T>* node = new FHeapNode<T>(key); // create a new node
	attachToRoot(node); // attach the new node to the root list
	if (min == nullptr || node->key < min->key) 
	{
		min = node; // update the pointer to the minimum if needed
	}
	numb += 1; // update number of elements in the heap
}
	

// extract the minimum node and consolidate the Fibonacci heap
template<typename T>
FHeapNode<T>* FibonacciHeap<T>::extractMin()
{
	FHeapNode<T>* z = min;
	if (z != nullptr)
	{
		// add children nodes of the minimum to the root list
		while (!isEmptyChild(min))
		{
			FHeapNode<T>* chld = removeChild(min); // extract child node
			attachToRoot(chld); // attach the child node to the root list
		}
		// remove minimum from the root list
		min = detach(min, min);
		if (min->next != min)
		{
			// min is not the last node in the heap
			consolidate(); // consolidate the Fibonacci heap
		}
		numb--;
	}
	return min;
}



template <typename T>
FibonacciHeap<T> FibonacciHeap<T>::unionWith(FibonacciHeap<T>& other) {
    FibonacciHeap<T> H;
    H.min = connect(min, other.min);
    H.min = (min->key < other.min->key) ? min : other.min;
    H.numb = numb + other.numb;
    return H;
}


// decrease the key of a given node
template<typename T>
void FibonacciHeap<T>::decreaseKey(FHeapNode<T>* node, T key)
{
	if (key > node->key)
	{
		throw invalid_argument("The new key is greater than the current key.");
	}
	node->key = key;
	FHeapNode<T>* y = node->prnt;
	if (y != nullptr && node->key < y->key)
	{
		cut(node, y); // Cut operation
		cascadingCut(y); // Cascading cut operation
	}
	if (node->key < min->key)
	{
		min = node;
	}
}

// delete a node
template<typename T>
void FibonacciHeap<T>::deleteNode(FHeapNode<T>* node)
{
	T min = minimum(); // find the current minimum
	min--; // decrease the current minimum
	decreaseKey(node, min); // set the key of the node to delete the minimum
	extractMin(); // extract the minimum from the Fibonacci heap
}

// print a Fibonacci data structure
template<typename T>
void FibonacciHeap<T>::print() const
{
	cout << "Size of the heap: " << numb << endl;
	cout << "The heap is empty: " << (isEmpty() ? "true" : "false") << endl;
	if (!isEmpty())
	{
		cout << "Minimum: " << min->key << endl;
		cout << "Root list: ";
		lstPrint(min);
	}
}

#endif
