#include "pch.h"
#include <iostream>
#include <string>
#include <list>
#include <queue>

/*
selection sort: O(n2)

insertion sort: O(n) - O(n2)
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
