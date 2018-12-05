#include "pch.h"
#include <iostream>
#include <string>
#include <list>
#include <queue>


template <typename E>
class isLess {	/*comparator class*/
public:
	const bool operator()(const E& p, const E& q);	//compares two values
};


template <typename E>
class BinaryTreeVector {
	std::vector<E> V;	//tree elements

public:
	typedef typename std::vector<E>::iterator Position; //position in the tree
protected:
	Position getPosition(int i); //map index on position
	int getIndex(const Position& p); //map position on index
public:
	BinaryTreeVector()
		:V(1) {};
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
class PriorityQueueHeap {
public:
	int size() const;	//invoke V.size()
	bool isEmpty() const;	//compare size to 0
	const E& minimum();		//invoke V.root() 
	void insert(const E& value);
	void removeMin();

private:
	BinaryTreeVector<E> V;	//Heap's elements inside BinaryTreeVector class
	K isLess;		//comparator
	typedef typename BinaryTreeVector<E>::Position Position; //iterator on vector 
};



int main()
{
	
	PriorityQueueHeap<int, isLess<int>> H;
	
	for (int i = 0; i < 10; i++) {
		H.insert(rand() % 100); 
	}
	H.removeMin(); 
	std::cout << H.minimum(); 







	return 0;
}
/*
1 param: integer
return i-th position
*/
template <typename E>
typename BinaryTreeVector<E>::Position BinaryTreeVector<E>::getPosition(int i) {
	return (i + V.begin());
}
/*
1 param: const referance to Position object
return int as indice
*/
template <typename E>
int BinaryTreeVector<E>::getIndex(const Position& p) {
	return (p - V.begin());
}
/*
no params
return size of vector - 1
return int
*/
template <typename E>
int BinaryTreeVector<E>::size() const {
	return (V.size() - 1);
}
/*
1 param: const referance to position object
return position on left child
*/
template <typename E>
typename BinaryTreeVector<E>::Position BinaryTreeVector<E>::left(const Position& ofMine) {
	return getPosition(2 * getIndex(ofMine));
}
/*
1 param: const referance to position object
return position on right child
*/
template <typename E>
typename BinaryTreeVector<E>::Position BinaryTreeVector<E>::right(const Position& ofMine) {
	return getPosition(2 * getIndex(ofMine) + 1);
}
/*
1 param: const referance to position object
return position on parent node
*/
template <typename E>
typename BinaryTreeVector<E>::Position BinaryTreeVector<E>::parent(const Position& ofMine) {
	return getPosition(getIndex(ofMine) / 2);
}
/*
1 param: const referance to position object
return true if node has left child
*/
template <typename E>
bool BinaryTreeVector<E>::hasLeft(const Position& position) {
	return ((2 * getIndex(position)) <= size());
}
/*
1 param: const referance to position object
return true if node has right child
*/
template <typename E>
bool BinaryTreeVector<E>::hasRight(const Position& position) {
	return ((2 * getIndex(position) + 1) <= size());
}
/*
1 param: const referance to position object
return true if node on position is root
*/
template <typename E>
bool BinaryTreeVector<E>::isRoot(const Position& position) {
	return (getIndex(position) == 1);
}
/*
no params
construct root position
return position
*/
template <typename E>
typename BinaryTreeVector<E>::Position BinaryTreeVector<E>::root() {
	return getPosition(1);
}
/*
no params
construct last node position
return position
*/
template <typename E>
typename BinaryTreeVector<E>::Position BinaryTreeVector<E>::last() {
	return getPosition(size());
}
/*
1 param: const referance to templated value
insert node on back of vector
no return value
*/
template <typename E>
void BinaryTreeVector<E>::addLast(const E& value) {
	V.push_back(value);
}
/*
no params
remove node from back of vector
no return value
*/
template <typename E>
void BinaryTreeVector<E>::removeLast() {
	V.pop_back();
}
/*
2 params: const reference to Position A and const reference to Position B
swap their values
no return value
*/
template <typename E>
void BinaryTreeVector<E>::swap(const Position& p, const Position& q) {
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
no param
return size of Heap
return int
*/
template <typename E, typename K>
int PriorityQueueHeap<E, K>::size() const {
	return V.size();
}
/*
no params
compare size with 0
return bool
*/
template <typename E, typename K>
bool PriorityQueueHeap<E, K>::isEmpty() const {
	return (size() == 0);
}
/*
no param
construct root position
return const referance to value
return templated E
*/
template <typename E, typename K>
const E& PriorityQueueHeap<E, K>::minimum() {
	return *(V.root());
}
/*
no params
change first's vlaue to last
heap down bubble to perfect spot
no ret value
*/
template <typename E, typename K>
void PriorityQueueHeap<E, K>::removeMin() {

	if (size() != 1) {	//if root is only node in the list

		Position u = V.root();	//get root position
		V.swap(u, V.last());	//swap values with last node
		V.removeLast();	//remove last node
			//heap down bubbling
		while (V.hasLeft(u)) {		//while there is children	
			Position v = V.left(u);	//get first children position

			if (V.hasRight(u) && isLess(*(V.right(u)), *v)) {	//if node has right children and its less then left
				v = V.right(u);	//change diretion of heap down bubling
			}
			if (isLess(*v, *u)) {	//if left/right childre's value is less then root's value
				V.swap(v, u);	//swap values
				u = v;	//set root to one lvl lower node
			}
			else {
				break;	//else close loop
			}
		}
		return;
	}
	V.removeLast();	//remove only node in the list
}
/*
1 param: const referance to templated value
insert element to last position
Up heap bubbling if its necessary
no return value
*/
template <typename E, typename K>
void PriorityQueueHeap<E, K>::insert(const E& value) {
	V.addLast(value);	//add last element to vector
	Position u = V.last();	//get last position
	//upHeap bubbling
	while (!V.isRoot(u)) {	//from last to root 
		Position p = V.parent(u);	//get u's parent position
		if (!isLess(*u, *p)) {	//if u is not lower then parent
			break;	//stay down
		}	
		else {
			V.swap(p, u);	//swap values
			u = p;	//set u to one lvl higher
		}
	}
}
