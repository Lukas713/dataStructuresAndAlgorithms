#include "pch.h"
#include <iostream>
#include <string>
#include <list>

template <typename T>
void quickSort(std::list<T>& S);

int main()
{
	
	std::list<int> S = { 9, 1, 8, 2, 7, 3 }; 

 
	quickSort(S);

	std::list<int>::iterator p; 
	for (p = S.begin(); p != S.end(); ++p)
		std::cout << *p << " "; 


	return 0;
}
/*
@param: list referance
chose pivot
divide list into three lists (smaller, equal to pivot and greater)
recursively repeat above steps
push lower elements first
push equal elements second
push greater elements last
no return value
*/
template <typename T>
void quickSort(std::list<T>& S) {
	if (S.size() <= 1) return;	//if list is 0 or 1, return

	T pivot = S.back();	//take pivot from back

	std::list<T> Lower, Greater, Equal;	//create lists
	while (!S.empty()) {
		//fill lists and clear out main list
		if (S.back() > pivot)
			Greater.push_back(S.back());

		else if (S.back() < pivot)
			Lower.push_back(S.back());

		else
			Equal.push_back(S.back());

		S.pop_back();
	}
	//Recursively call on lists with lower and greater elements
	quickSort(Lower);
	quickSort(Greater);

	//push lower elements first
	while (!Lower.empty()) {
		S.push_back(Lower.front());
		Lower.pop_front();
	}
	//push equal elements second
	while (!Equal.empty()) {
		S.push_back(Equal.front());
		Equal.pop_front();
	}
	//push greater elements last
	while (!Greater.empty()) {
		S.push_back(Greater.front());
		Greater.pop_front();
	}
}
