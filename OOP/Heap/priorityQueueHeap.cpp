#include "pch.h"
#include <iostream>
#include <string>
#include <list>
#include <queue>

/*
Binary Heap implementation using comparator.

Heap of height h is a complete binary tree that is, leve 0, 1, 2, 3, h - 1 of T have the maximum
number of nodes possible. Level i has 2^i nodes.
*/

template <typename E>
class isLess {	/*comparator class*/
public:
	const bool operator()(const E& p, const E& q);	//compares two values
};

template <typename E>
class isHigher {	/*comparator class*/
public:
	const bool operator()(const E& p, const E& q);	//compares two values
};


template <typename E>
class BinaryHeap {
	std::vector<E> V;	//tree element

public:
	typedef typename std::vector<E>::iterator Position; //position in the tree
protected:
	Position getPosition(int i); //map index on position
	int getIndex(const Position& p); //map position on index
	void buildHeap() {
		for (int i = ((V.size() - 10) / 2); i > 0; --i) {
			percolateDown(i);
		}
	}
public:
	BinaryHeap()
		:V(1) {};
	BinaryHeap(const std::vector<E> vector)
		: V(vector.size() + 10) {
		Position p; 
		for (int i = 0; i < vector.size(); ++i)
			V[i + 1] = vector[i];
		buildHeap(); 
	}
	void percolateDown(int hole) {
		int child; 
		E temp = std::move(V[hole]); 

		for (hole; hole * 2 <= V.size(); hole = child) {
			child = hole * 2; 
			if (child != V.size() && V[child] > V[child + 1])
				++child; 
			if (V[child] < temp)
				V[hole] = std::move(V[child]);
			else
				break; 
		}
		V[hole] = std::move(temp); 
	}

	int size() const;	//size of three
	Position left(const Position& ofMine);	//return position on left child
	Position right(const Position& ofMine);		//return position on right child
	Position parent(const Position& ofMine);	//return position on parent node
	bool hasLeft(const Position& position);		// return true if node has lef child
	bool hasRight(const Position& position);	// return true if node has right child
	bool isRoot(const Position& position);		// return true if node is root node
	Position root();	//return root position
	Position last();	//return last node position
	void addLast(const E& value);	//add's element
	void removeLast();	//remove element
	void swap(const Position& p, const Position& q);	//swap node content
};


/*priority queue implementation using heap*/
template <typename E, typename K>
class PriorityQueue {
public:
	int size() const;	//invoke V.size()
	bool isEmpty() const;	//compare size to 0
	const E& minimum();		//invoke V.root() 
	void insert(const E& value);
	void removeMin();

private:
	BinaryHeap<E> V;	//Heap's elements inside BinaryHeap class
	K compare;
	typedef typename BinaryHeap<E>::Position Position; //iterator on vector 
};

template <typename E, typename K>
class Adapter : public PriorityQueue<E, K> {
public:
	const E& maximum();
	void removeMax();
private:
	BinaryHeap<E> L;
	K comparator;
	typedef typename BinaryHeap<E>::Position Position; //iterator on vector 
};

/*
Heap sort in place
0. phase:
		  Reversed comparator is used that checks if one value is higher
		  then other.
1. phase:
		  insert elements from list into heap using insert() method
		  that inserts elements with reversed heap order property (reversed comparator).
		  Highest is at the top.
2. phase:
		  return elements into list starting at end() of the list until begin().
		  Interesting method is push_front(). Effect is the same.
*/
template <typename E, typename K>
void heapSort(PriorityQueue<E, K>& heap, std::list<E>& field);

template <typename E, typename K>
void heapSortRegular(PriorityQueue<E, K>& heap, std::list<E>& field);

int main()
{

	std::vector<int> V = { 1, 2, 3, 4, 5 }; 
	BinaryHeap<int> B(V); 
	BinaryHeap<int>::Position p; 
	p = B.root(); 
	std::cout << *(++p); 

	









	return 0;
}
/*
1 param: integer
return i-th position
*/
template <typename E>
typename BinaryHeap<E>::Position BinaryHeap<E>::getPosition(int i) {
	return (i + V.begin());
}
/*
1 param: const referance to Position object
return int as indice
*/
template <typename E>
int BinaryHeap<E>::getIndex(const Position& p) {
	return (p - V.begin());
}
/*
no params
return size of vector - 1
return int
*/
template <typename E>
int BinaryHeap<E>::size() const {
	return (V.size() - 1);
}
/*
1 param: const referance to position object
return position on left child
*/
template <typename E>
typename BinaryHeap<E>::Position BinaryHeap<E>::left(const Position& ofMine) {
	return getPosition(2 * getIndex(ofMine));
}
/*
1 param: const referance to position object
return position on right child
*/
template <typename E>
typename BinaryHeap<E>::Position BinaryHeap<E>::right(const Position& ofMine) {
	return getPosition(2 * getIndex(ofMine) + 1);
}
/*
1 param: const referance to position object
return position on parent node
*/
template <typename E>
typename BinaryHeap<E>::Position BinaryHeap<E>::parent(const Position& ofMine) {
	return getPosition(getIndex(ofMine) / 2);
}
/*
1 param: const referance to position object
return true if node has left child
*/
template <typename E>
bool BinaryHeap<E>::hasLeft(const Position& position) {
	return ((2 * getIndex(position)) <= size());
}
/*
1 param: const referance to position object
return true if node has right child
*/
template <typename E>
bool BinaryHeap<E>::hasRight(const Position& position) {
	return ((2 * getIndex(position) + 1) <= size());
}
/*
1 param: const referance to position object
return true if node on position is root
*/
template <typename E>
bool BinaryHeap<E>::isRoot(const Position& position) {
	return (getIndex(position) == 1);
}
/*
no params
construct root position
return position
*/
template <typename E>
typename BinaryHeap<E>::Position BinaryHeap<E>::root() {
	return getPosition(1);
}
/*
no params
construct last node position
return position
*/
template <typename E>
typename BinaryHeap<E>::Position BinaryHeap<E>::last() {
	return getPosition(size());
}
/*
1 param: const referance to templated value
insert node on back of vector
no return value
*/
template <typename E>
void BinaryHeap<E>::addLast(const E& value) {
	V.push_back(value);
}
/*
no params
remove node from back of vector
no return value
*/
template <typename E>
void BinaryHeap<E>::removeLast() {
	V.pop_back();
}
/*
2 params: const reference to Position A and const reference to Position B
swap their values
no return value
*/
template <typename E>
void BinaryHeap<E>::swap(const Position& p, const Position& q) {
	E temp = *p;
	*p = *q;
	*q = temp;
}
/*
2 params: const references to templated type
return true if first is lower value then second
return bool
*/
template <typename E>
const bool isLess<E>::operator()(const E& p, const E& q) {
	return (p < q);
}
/*
2 params: const references to templated type
return true if first is higher value then second
return bool
*/
template <typename E>
const bool isHigher<E>::operator()(const E& p, const E& q) {
	return (p > q);
}
/*
no param
return size of Heap
return int
*/
template <typename E, typename K>
int PriorityQueue<E, K>::size() const {
	return V.size();
}
/*
no params
compare size with 0
return bool
*/
template <typename E, typename K>
bool PriorityQueue<E, K>::isEmpty() const {
	return (size() == 0);
}
/*
no param
construct root position
return const referance to value
return templated E
*/
template <typename E, typename K>
const E& PriorityQueue<E, K>::minimum() {
	return *(V.root());
}
/*
no params
change first's vlaue to last
heap down bubble to perfect spot
no return value
*/
template <typename E, typename K>
void PriorityQueue<E, K>::removeMin() {
	if (V.size() > 1) {

		Position hole = V.root();
		V.swap(hole, V.last());
		V.removeLast();

		while (V.hasLeft(hole)) {
			Position child = V.left(hole);

			if (V.hasRight(hole) && compare(*(V.right(hole)), *child))
				child = V.right(hole);
			if (!compare(*child, *hole))
				break;
			V.swap(child, hole);
			hole = child;
		}
		return;
	}
	V.removeLast();
}
/*
1 param: const referance to templated value
insert element to last position
Up heap bubbling if its necessary
no return value
*/
template <typename E, typename K>
void PriorityQueue<E, K>::insert(const E& value) {
	V.addLast(value);
	Position newOne = V.last();
	/*up heap bubling*/
	while (!V.isRoot(newOne)) {
		Position parent = V.parent(newOne);
		if (!compare(*newOne, *parent))
			break;
		V.swap(newOne, parent);
		newOne = parent;
	}
}
/*
2 params: referance to heap and referance to list
sort field using heap
no return value
*/
template <typename E, typename K>
void heapSort(PriorityQueue<E, K>& heap, std::list<E>& field) {

	typename std::list<E>::iterator p;	//create iterator
	//insert elements into heap with reverse heap order property
	for (p = field.begin(); p != field.end(); ++p) {
		heap.insert(*p);
	}
	field.clear();	//clear list
	//return element into field fromright to left
	while (!heap.isEmpty()) {
		field.push_front(heap.minimum());
		heap.removeMin();
	}
}
template <typename E, typename K>
void heapSortRegular(PriorityQueue<E, K>& heap, std::list<E>& field) {
	while (!field.empty()) {
		heap.insert(field.front());
		field.pop_front();
	}
	while (!heap.isEmpty()) {
		field.push_front(heap.minimum());
		heap.removeMin();
	}
}
/*
return root value
*/
template <typename E, typename K>
const E& Adapter<E, K>::maximum() {
	return *(L.root());
}
/*
no params
remove root node
designed for Adapter class purpose
no return value
*/
template <typename E, typename K>
void Adapter<E, K>::removeMax() {

	if (L.size() > 1) {

		Position rot = L.root();
		L.swap(rot, L.last());
		L.removeLast();
		while (L.hasLeft(rot)) {

			Position children = L.left(rot);
			if (L.hasRight(rot) && comparator(*L.right(rot), *children)) {
				children = L.right(rot);
			}
			if (comparator(*children, *rot)) {
				L.swap(children, rot);
				rot = children;
			}
			else {
				break;
			}
		}
		return;
	}
	L.removeLast();
}

