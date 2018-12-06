#include "pch.h"
#include <iostream>
#include <string>
#include <list>
#include <queue>

/*
A priority queue is an abstract data type for storing a collection of prioritized elements
that supports arbitrary element insertion but supports removal of elements in
order of priority, that is, the element with first priority can be removed at any time.

implementation with sorted list (created insert function)
implementation with unsorted list (vector)

selection sort: O(n2)
we repeatedly remove an element with smallest key from the priority queue P. The size of P starts
at n and decreases to 0 with each removeMin. Thus, the first removeMin operation
takes time O(n), the second one takes time O(n-1), and so on.

insertion sort: O(n) - O(n2)
Execution of insertion-sort on list L = {1, 9, 2, 8, 3, 7, 5, 6}. In Phase 1,
we repeatedly remove the first element of L and insert it into P, by scanning the
list implementing P until we find the correct place for this element. In Phase 2,
we repeatedly perform removeMin operations on P, each of which returns the first
element of the list implementing P, and we add the element at the end of L
*/


template <typename E, typename C>
class PriorityQueueList {
public:
	int size() const;	//return size of the list
	bool isEmpty() const;	//return true if list is empty, false othervise
	const E& min() const;	//return constant referance to element (can't modifiy)
	void removeMin();	//remove mnimum value
	void insert(const E& elem);		//inserts element
private:

	std::list<E> L;		//content of priority queue
	C isLess;	//comparator
};


/*comparator class that compares two objects*/
template <typename E>
class isLess {
public:
	bool operator()(const E& p, const E& q) const;
};

/*
selection sort
*/
template <typename E>
void selectionSort(std::vector<E>& L, std::priority_queue<E, std::vector<E>, isLess<E>>& Q) {
	/*phase 1: inserting elements into priority queue*/
	while (!L.empty()) {
		Q.push(L.back());
		L.pop_back();
	}
	/*phase 2: inserting minimum value inside list*/
	while (!Q.empty()) {
		L.push_back(Q.top());
		Q.pop();
	}
}

/*insertion sort*/
template <typename E, typename C>
void insertionSort(std::list<E>& f, PriorityQueueList<E, C>& queue) {
	//phase 1: inserting elements into queue and finding best spot for each element
	while (!f.empty()) {
		queue.insert(f.front());
		f.pop_front();
	}
	//phase 2: SELECTING min elements and inserting back to the list
	while (!queue.isEmpty()) {
		f.push_front(queue.min());
		queue.removeMin();
	}
}
int main()
{

	std::vector<int> L;
	std::priority_queue<int, std::vector<int>, isLess<int>> Q;

	for (int i = 0; i < 10; i++) {
		L.push_back(rand() % 100);
	}


	selectionSort(L, Q);

	std::vector<int>::iterator p;
	for (p = L.begin(); p != L.end(); ++p) {
		std::cout << *p << " ";
	}








	return 0;
}
template <typename E>
bool isLess<E>::operator()(const E& p, const E& q) const {
	return (p < q);
}
template <typename E, typename C>
int PriorityQueueList<E, C>::size() const {	//return number of elements
	return L.size();
}
template <typename E, typename C>
bool PriorityQueueList<E, C>::isEmpty() const {	//return true if list is empty
	return L.empty();
}
/*
1 param: cocnst referance to element
creates iterator and checking righ position for element (element < p && element > ++p)
insert at right position
o return value
*/
template <typename E, typename C>
void PriorityQueueList<E, C>::insert(const E& elem) {	//return number of elements
	typename std::list<E>::iterator p = L.begin();
	while (p != L.end() && isLess(elem, *p)) {
		++p;
	}
	L.insert(p, elem);
}
/*
list is sorted becouse insert method
return front element for min element
*/
template <typename E, typename C>
const E& PriorityQueueList<E, C>::min() const {	//return number of elements
	return L.front();
}
/*
list is sorted becouse insert method
only front node must be removed
*/
template <typename E, typename C>
void PriorityQueueList<E, C>::removeMin() {	//return number of elements
	L.pop_front();
}
