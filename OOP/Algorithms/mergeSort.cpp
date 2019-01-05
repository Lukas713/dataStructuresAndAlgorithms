#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <list>


template <typename C>
class isLess {	/*comparator class*/
public:
	bool operator()(const C& p, const C& q) const;	//compares two values
};

template <typename E>
class isHigher {	/*comparator class*/
public:
	const bool operator()(const E& p, const E& q);	//compares two values
};


template <typename K, typename C>
void mergeSort(std::list<K>& S, const isLess<C>& comp);

template <typename K, typename C>
void merge(std::list<K>& S1, std::list<K>& S2, std::list<K>& S, const isLess<C>& comp);

int main()
{

	std::list<int> S = { 9, 1, 8, 2, 7, 3, 6, 4, 5, 0 }; 
	isLess<int> a;
	mergeSort(S, a); 






	std::list<int>::iterator p; 
	for (p = S.begin(); p != S.end(); ++p)
		std::cout << *p << " "; 
	





	return 0;
}
/*
2 params: const references to templated type
return true if first is lower value then second
return bool
*/
template <typename C>
bool isLess<C>::operator()(const C& p, const C& q) const{
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
@param: two list halfs, list, comparator
compare every item and push into list
no return value
*/
template <typename K, typename C>
void merge(std::list<K>& S1, std::list<K>& S2, std::list<K>& S, const isLess<C>& comp) {
	typename std::list<K>::iterator p1 = S1.begin(); //iterator at first half
	typename std::list<K>::iterator p2 = S2.begin();	//iterator at second half

	while (p1 != S1.end() && p2 != S2.end()) {
		if (!comp(*p1, *p2)) {	//compares elements and pushes them on the main list
			S.push_back(*p2++);
			continue;
		}
		S.push_back(*p1++);
	}
	//push rest of elements if needed

	while (p1 != S1.end())
		S.push_back(*p1++);
	while (p2 != S2.end())
		S.push_back(*p2++);
}

/*
@param: list and comparator
recursively divide list
call merge()
no return value
*/
template <typename K, typename C>
void mergeSort(std::list<K>& S, const isLess<C>& comp) {
	int n = S.size(); //tak size of list
	if (n <= 1) return;		//if there is only one element, its laready srted
	std::list<K> S1, S2;	//create two aditional lists
	typename std::list<K>::iterator p = S.begin();

	for (int i = 0; i < (n / 2); ++i)
		S1.push_back(*p++); 	//first half of the list
	for (int i = (n / 2); i < n; ++i)
		S2.push_back(*p++);  //second half of the list

	S.clear();	//clear main list
	mergeSort(S1, comp); //divide first half recusively
	mergeSort(S2, comp); //divide second half recursively
	merge(S1, S2, S, comp);	//invoke function that compares elements and push them in main list
}
