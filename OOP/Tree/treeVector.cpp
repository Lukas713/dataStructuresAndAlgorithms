#include "pch.h"
#include <iostream>
#include <string>
#include <list>
#include <queue>

template <typename E>
class BinaryTree {

	std::vector<E> V;	//tree elements
public:
	typedef typename std::vector<E>::iterator Position; //position in the tree
protected:
	Position getPosition(int i); //map index on position
	int getIndex(const Position& p); //map position on index
public:
	BinaryTree()
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

int main()
{
	








	return 0;
}
/*
1 param: integer
return i-th position
*/
template <typename E>
typename BinaryTree<E>::Position BinaryTree<E>::getPosition(int i) {
	return (i + V.begin());
}
/*
1 param: const referance to Position object
return int as indice
*/
template <typename E>
int BinaryTree<E>::getIndex(const Position& p) {
	return (p - V.begin());
}
/*
no params
return size of vector - 1
return int
*/
template <typename E>
int BinaryTree<E>::size() const {
	return (V.size() - 1);
}
/*
1 param: const referance to position object
return position on left child
*/
template <typename E>
typename BinaryTree<E>::Position BinaryTree<E>::left(const Position& ofMine) {
	return getPosition(2 * getIndex(ofMine));
}
/*
1 param: const referance to position object
return position on right child
*/
template <typename E>
typename BinaryTree<E>::Position BinaryTree<E>::right(const Position& ofMine) {
	return getPosition(2 * getIndex(ofMine) + 1);
}
/*
1 param: const referance to position object
return position on parent node
*/
template <typename E>
typename BinaryTree<E>::Position BinaryTree<E>::parent(const Position& ofMine) {
	return getPosition(getIndex(ofMine) / 2);
}
/*
1 param: const referance to position object
return true if node has left child
*/
template <typename E>
bool BinaryTree<E>::hasLeft(const Position& position) {
	return ((2 * getIndex(position)) <= size());
}
/*
1 param: const referance to position object
return true if node has right child
*/
template <typename E>
bool BinaryTree<E>::hasRight(const Position& position) {
	return ((2 * getIndex(position) + 1) <= size());
}
/*
1 param: const referance to position object
return true if node on position is root
*/
template <typename E>
bool BinaryTree<E>::isRoot(const Position& position) {
	return (getIndex(position) == 1);
}
/*
no params
construct root position
return position
*/
template <typename E>
typename BinaryTree<E>::Position BinaryTree<E>::root() {
	return getPosition(1);
}
/*
no params
construct last node position
return position
*/
template <typename E>
typename BinaryTree<E>::Position BinaryTree<E>::last() {
	return getPosition(size());
}
/*
1 param: const referance to templated value 
insert node on back of vector
no ret value
*/
template <typename E>
void BinaryTree<E>::addLast(const E& value) {
	V.push_back(value);
}
/*
no params
remove node from back of vector
no return value
*/
template <typename E>
void BinaryTree<E>::removeLast() {
	V.pop_back();
}
/*
2 params: const reference to Position A and const reference to Position B
swap their values
no return value
*/
template <typename E>
void BinaryTree<E>::swap(const Position& p, const Position& q) {
	E temp = *p;
	*p = *q;
	*q = temp;
}
