#include "pch.h"
#include <iostream>
#include <string>
#include <list>
#include <queue>

template <typename E>
class isLess {
public:
	bool operator()(const E& p, const E& q); 
};
template <typename E>
class isHigher {
public:
	bool operator()(const E& p, const E& q);
};


template <typename E, typename C>
class AdaptablePQueue { 
public:
	class Position {	//position inside Queue
	private:
		typename std::list<E>::iterator p;	//iterator for accesing values
	public:
		const E& operator*();	//overloaded operator
		friend class AdaptablePQueue<E, C>;	//AdaptableQueue can acces private member iterator
	};

	int size() const;	//number of elements
	bool isEmpty() const;	//return true if list is empty
	const E& minimum();	//return const referance to minimum value
	void removeMin();	//removes minimum value
	void remove(const Position& p);		//remove node on specific position
	Position insert(const E& value);	//inserts value and eturns position
	Position replace(const Position& p, const E& value);	//replace value at position
private:
	std::list<E> L;		//priority queue content
	C comparator;	//comparator
};



int main()
{








	return 0;
}
/*
position accessor
*/
template <typename E, typename C>
const E& AdaptablePQueue<E, C>::Position::operator*() {
	return *p; 
}
template <typename E>
bool isLess<E>::operator()(const E& p, const E& q) {
	return (p < q); 
}
template <typename E>
bool isHigher<E>::operator()(const E& p, const E& q) {
	return (p > q);
}
template <typename E, typename C>
int AdaptablePQueue<E, C>::size() const {
	return L.size();
}
template <typename E, typename C>
bool AdaptablePQueue<E, C>::isEmpty() const {
	return L.empty();
}
/*
list is sorted becouse insert method
return front element for min element
*/
template <typename E, typename C>
const E& AdaptablePQueue<E, C>::minimum() {
	return L.front();
}
/*
list is sorted becouse insert method
only front node must be removed
*/
template <typename E, typename C>
void AdaptablePQueue<E, C>::removeMin() {
	L.pop_front();
}
/*
1 param: const referance to value
iterate untill higher value
insert prior 
return Position of insertion
*/
template <typename E, typename C>
typename AdaptablePQueue<E, C>::Position AdaptablePQueue<E, C>::insert(const E& value) {
	typename L::iterator p = L.begin();		//iterator on begining of list
	while (p != L.end() && !comparator(*p, value)) {
		++p;	//search untill node value is higher then value
	}
	L.insert(p, value); //insert prior to higher value
	Position pos;
	pos.p = --p; //return one position back
	return pos; //return
}
/*
1 param: const referance to position
invoke erase(iterator)
erase element
no return value
*/
template <typename E, typename C>
void AdaptablePQueue<E, C>::remove(const Position& position) {
	L.erase(position.p);	
}
/*
2 params: const referance to position and value
erase element at position from argument
insert value into the List
return Position of inserted value
*/
template <typename E, typename C>
typename AdaptablePQueue<E, C>::Position AdaptablePQueue<E, C>::replace(const Position& position, const E& value) {
	L.erase(position.p);	//removes element at position	 
	return insert(value);	//insert new value and return position
}
