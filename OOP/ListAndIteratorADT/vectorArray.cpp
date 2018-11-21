#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>



typedef std::string error;
class Exeption {
	error txt;
public:
	Exeption(error err)
		: txt(err) {};
	error& getError() { return this->txt; };
};

template <typename T>
class ArrayVector {
	int capacity;	//max elements
	T* field;		//array
	int n;	//counter of elements

public:
	ArrayVector()
		: capacity(0), n(0), field(NULL) {};  //capacity, number of elements, field pointer
	ArrayVector(ArrayVector& V);
	~ArrayVector(); //destructor
	int size() const;	//return n
	bool isEmpty() const;	//check if n is less then 0
	T& operator[](int n);		//operator overload to access indice of array
	T& at(int n);	//return element at index of array
	ArrayVector& operator=(ArrayVector& x); 
	void erase(int i); //erase element on index and shift whole array to left by one spot	
	void insert(int i, const T& value); //insert value to ith element
	void reserve(int n); //Request that the allocated storage space be large enough to hold n elements.
};

int main()
{


 
	





	return 0;
}
//copy constructor
template <typename T>
ArrayVector<T>::ArrayVector(ArrayVector& V) {
	if (V.field != NULL) {	//if vector is not empty
		reserve(V.capacity);	//reserve space with same capacity
		for (int i = 0; i < V.size(); i++) {	//insert i element as V
			insert(i, V.at(i));
		}
	}
}
template <typename T>
ArrayVector<T>::~ArrayVector() {
	if (n == 0) {
		return;
	}
	erase(0);
}
template <typename T>
int ArrayVector<T>::size() const {
	return n;
}
template <typename T>
bool ArrayVector<T>::isEmpty() const {
	return (size() == 0);
}
template <typename T>
T& ArrayVector<T>::operator[](int n) {
	return field[n];
}
template <typename T>
T& ArrayVector<T>::at(int i){
	try {
		if (i >= 0 || i < n)
			return field[i];
		throw Exeption("Index out of bounds!");
	}
	catch (Exeption& err) {
		std::cout << err.getError() << "\n";
	}
}
template <typename T>
void ArrayVector<T>::erase(int i) {
	for (int j = i + 1; j < n; j++)
		field[j - 1] = field[j];
	n--;
}
template <typename T>
void ArrayVector<T>::reserve(int N) {
	if (N < capacity)	//if N is less then cap
		return;
	int* newField = new T[N]; //alocate new array
	for (int i = 0; i < n; i++) {
		newField[i] = field[i];	//copy elements from first array to second
	}
	if (field != NULL) {
		delete[] field;
	}
	field = newField; //change pointer to new array
	capacity = N;	//change capacity
}
template <typename T>
void ArrayVector<T>::insert(int i, const T& value) {
	if (n == capacity)
		reserve(std::max(i, capacity * 2)); //double size array coz of overflow
	for (int j = n - 1; j >= i; j--) {	//traverse untill searched index from en of 
		field[j + 1] = field[j];
	}
	field[i] = value;
	n++;
}
template <typename T>
ArrayVector<T>& ArrayVector<T>::operator=(ArrayVector& x) {
	if (x.capacity > 0) {
		reserve(x.capacity); 
	}
	if (x.field != NULL) {
		for (int i = 0; i < x.size(); i++) {
			insert(i, x.at(i)); 
		}
	}
	return*this;
}
