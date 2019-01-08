#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <set>

template <typename T>
class Merge {
public:
	/*method that merges two sets A & B and stores the result in C*/
	void merge(std::list<T>& A,
				std::list<T>& B,
					std::list<T>& C); 
protected:
	virtual void fromA(const T& a, std::list<T>& C) = 0; 
	virtual void fromBoth(const T& a, const T& b, std::list<T>& C) = 0; 
	virtual void fromB(const T& b, std::list<T>& C) = 0; 
};

/*
A U B = {x: x is in A or x is in B}
Replace A with the union of A and B, that is, execute: A <- A U B
*/
template <typename T>
class UnionMerge : public Merge<T> {
protected:
	virtual void fromA(const T& a, std::list<T>& C);
	virtual void fromBoth(const T& a, const T& b, std::list<T>& C);
	virtual void fromB(const T& b, std::list<T>& C);
};
/*
A ? B = {x: x is in A and x is in B}
Replace A with intersectiion of A, that is execute: A <- A ? B
*/
template <typename T>
class IntersectMerge : public Merge<T> {
protected:
	virtual void fromA(const T& a, std::list<T>& C);
	virtual void fromBoth(const T& a, const T& b, std::list<T>& C);
	virtual void fromB(const T& b, std::list<T>& C);
};
/*
A - B = {x: x is in A and x is not in B}
Replace A with diference of A and B, that is, execute: A <- A - B
*/
template <typename T>
class SubtractMerge : public Merge<T> {
protected:
	virtual void fromA(const T& a, std::list<T>& C);
	virtual void fromBoth(const T& a, const T& b, std::list<T>& C);
	virtual void fromB(const T& b, std::list<T>& C);
};


int main()
{
	
	
	
	SubtractMerge<int> O; 
	std::list<int> A = { 1, 2, 3, 4, 5 }; 
	std::list<int> B = { 1, 6, 7, 8, 9 }; 
	std::list<int> C; 

	O.merge(A, B, C); 

	std::list<int>::iterator p; 
	for (p = C.begin(); p != C.end(); ++p)
		std::cout << *p << " "; 
	


	return 0;
}

template <typename T>
void Merge<T>::merge(std::list<T>& A, std::list<T>& B, std::list<T>& C) {
	//iterators to first and second list
	typename std::list<T>::iterator pA = A.begin();	
	typename std::list<T>::iterator pB = B.begin();

	while (pA != A.end() && pB != B.end()) {
		if (*pA < *pB)	
			fromA(*pA++, C);	
		else if (*pA > *pB)
			fromB(*pB++, C);	
		else
			fromBoth(*pA++, *pB++, C);	
	}

	while (pA != A.end())
		fromA(*pA++, C);
	while (pB != B.end())
		fromB(*pB++, C);
}

/*Union of two sets*/
template <typename T>
void UnionMerge<T>::fromA(const T& a, std::list<T>& C) {
	C.push_back(a);		//add a
}

template <typename T>
void UnionMerge<T>::fromB(const T& b, std::list<T>& C) {
	C.push_back(b);	//add b
}

template <typename T>
void UnionMerge<T>::fromBoth(const T& a, const T& b, std::list<T>& C) {
	C.push_back(a); //add a only
}
/*Intersect of two sets*/
template <typename T>
void IntersectMerge<T>::fromA(const T& a, std::list<T>& C) {
	//ignore
}

template <typename T>
void IntersectMerge<T>::fromB(const T& b, std::list<T>& C) {
	//ignore
}

template <typename T>
void IntersectMerge<T>::fromBoth(const T& a, const T& b, std::list<T>& C) {
	C.push_back(a); //add b only
}

/*Subtract of two sets*/
template <typename T>
void SubtractMerge<T>::fromA(const T& a, std::list<T>& C) {
	C.push_back(a);
}

template <typename T>
void SubtractMerge<T>::fromB(const T& b, std::list<T>& C) {
	//ignore
}

template <typename T>
void SubtractMerge<T>::fromBoth(const T& a, const T& b, std::list<T>& C) {
	//ignore
}
