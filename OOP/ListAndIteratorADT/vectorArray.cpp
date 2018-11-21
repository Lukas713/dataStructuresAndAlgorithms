#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

/*
Vector struture implemetation using Array
*/

typedef std::string error;
class Exeption {
	error txt;
public:
	Exeption(error err)
		: txt(err) {};
	error& getError() { return this->txt; };
};

class ArrayVector {
	int capacity;	//max elements
	int* field;		//array
	int n;	//counter of elements

public:
	ArrayVector()
		: capacity(0), n(0), field(NULL) {};  //capacity, number of elements, field pointer
	ArrayVector(ArrayVector& V);
	~ArrayVector(); //destructor
	int size() const;	//return n
	bool isEmpty() const;	//check if n is less then 0
	int& operator[](int n);		//operator overload to access indice of array
	int& at(int n);	//return element at index of array
	ArrayVector& operator=(ArrayVector& x); 
	void erase(int i); //erase element on index and shift whole array to left by one spot	
	void insert(int i, const int& value); //insert value to ith element
	void reserve(int n); //Request that the allocated storage space be large enough to hold n elements.
};



int main()
{


	ArrayVector a;
	a.reserve(5);
	a.insert(0, 1);
	a.insert(1, 5);
	a.insert(2, 1+8);
	std::cout << a.at(0) << "\n"; 

	ArrayVector b(a); 
	





	return 0;
}
//copy constructor
ArrayVector::ArrayVector(ArrayVector& V) {
	if (V.field != NULL) {	//if vector is not empty
		reserve(V.capacity);	//reserve space with same capacity
		for (int i = 0; i < V.size(); i++) {	//insert i element as V
			insert(i, V.at(i));
		}
	}
}
ArrayVector::~ArrayVector() {
	if (n == 0) {
		return;
	}
	erase(0);
}
int ArrayVector::size() const {
	return n;
}
bool ArrayVector::isEmpty() const {
	return (size() == 0);
}
int& ArrayVector::operator[](int n) {
	return field[n];
}
int& ArrayVector::at(int i){
	try {
		if (i >= 0 || i < n)
			return field[i];
		throw Exeption("Index out of bounds!");
	}
	catch (Exeption& err) {
		std::cout << err.getError() << "\n";
	}
}
void ArrayVector::erase(int i) {
	for (int j = i + 1; j < n; j++)
		field[j - 1] = field[j];
	n--;
}
void ArrayVector::reserve(int N) {
	if (N < capacity)	//if N is less then cap
		return;
	int* newField = new int[N]; //alocate new array
	for (int i = 0; i < n; i++) {
		newField[i] = field[i];	//copy elements from first array to second
	}
	if (field != NULL) {
		delete[] field;
	}
	field = newField; //change pointer to new array
	capacity = N;	//change capacity
}
void ArrayVector::insert(int i, const int& value) {
	if (n == capacity)
		reserve(std::max(i, capacity * 2)); //double size array coz of overflow
	for (int j = n - 1; j >= i; j--) {	//traverse untill searched index from en of 
		field[j + 1] = field[j];
	}
	field[i] = value;
	n++;
}
ArrayVector& ArrayVector::operator=(ArrayVector& x) {
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
