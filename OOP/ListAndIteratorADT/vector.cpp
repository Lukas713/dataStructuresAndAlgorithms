#include "pch.h"
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>

/*
A vector container behaves like an array, but can automatically grow as required.
It is random access and contiguously stored, and length is highly flexible.
For these reasons and more, vector is the preferred sequence container for most applications.
When in doubt as to what kind of sequence container to use, start by using a vector!
*/

typedef std::string error;
class Exeption {
	error txt;
public:
	Exeption(error err)
		: txt(err) {};
	error& getError() { return this->txt; };
};


template <typename T>
class Vector {
	int capacity;
	int n;
	T* field;

public:
	class Iterator {	//nested class as iterator
		Iterator(T& p);		//only vector can create iterator
		T* p; //position pointer

	public:
		T& operator*();	//acces value
		bool operator==(Iterator p) const; 
		bool operator!=(Iterator p) const; 
		Iterator& operator++(); //move to next position
		Iterator& operator++(int); 
		Iterator& operator--();
		Iterator& operator--(int);
		template <typename T> friend class Vector; 
	};

	Vector();	//constructor
	Vector(Vector& V);	//copy constructor
	~Vector();	//destructor
	int size() const;	//return n
	bool isEmpty() const;	//if vector is empty
	T& operator[](int i);	//acces operator
	T& at(int i);	//acces function
	Iterator begin() const;
	Iterator end() const; 
	void insert(const int where, const T& value);	//insert value at indice where
	void erase(const int where);	//delete indice where
	void reserve(const int N);	//create array of N spots
	void pushBack(const T& value);
	void removeFront();
};


int main() {

	
	Vector<int> x; 
	x.reserve(5);
	x.insert(0, 1);
	x.insert(1, 6);
	x.insert(2, 3);
	x.insert(3, 4);
	x.pushBack(12); 
	
	Vector<int> z(x); 
	
	for (Vector<int>::Iterator p = z.begin(); p != z.end(); ++p) {
		std::cout << *p << " "; 
	}
	



	return 0;
}
template <typename T>
Vector<T>::Vector()	//constructor
	: n(0), capacity(0), field(NULL) {};	//init members

template <typename T>
Vector<T>::~Vector() {	//destructor
	while (!isEmpty()) {
		removeFront();
	}
}

template <typename T>
Vector<T>::Vector(Vector& V) {	//copy constructor
	if (!V.isEmpty()) {
		reserve(V.capacity);
		for (Vector<T>::Iterator p = V.begin(); p != V.end(); ++p)
			pushBack(*p);
	}
}

template <typename T>
int Vector<T>::size() const {
	return n;	//return number of elements
}

template <typename T>
bool Vector<T>::isEmpty() const {
	return (n == 0);	//is Vector list empty?
}

template <typename T>
T& Vector<T>::operator[](int i) {
	return field[i];	//return specific indice value
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::end() const {
	return Iterator(field[n]);	//invoke Iterator constructor on last element
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::begin() const {
	return Iterator(field[0]);	//invoke Iterator constructor on first element
}

template <typename T>
T& Vector<T>::at(int i) {
	try {
		if (i >= 0 && i <= n) {
			return field[i];
		}
		throw Exeption("Index out of bounds");
	}
	catch (Exeption& err) {
		std::cout << err.getError() << "\n";
	}
}

template <typename T>
void Vector<T>::erase(const int i) {
	for (int j = i - 1; j < n; j++)
		field[j - 1] = field[j];		//delete element in arra and shift rest of array
	n--;
}

template <typename T>
void Vector<T>::removeFront() {
	erase(0);
}

template <typename T>
void Vector<T>::reserve(const int N) {
	if (N <= capacity) {
		return;
	}
	T* newField = new T[N];	//alocate storge for values

	if (field != NULL) {	//if first array is not empty
		for (int i = 0; i < n; i++) {
			newField[i] = field[i];	//copy elements into new array
		}
		delete[] field; //delete old one
	}
	field = newField;	//set field  
	capacity = N;	//capacity
}

template <typename T>
void Vector<T>::insert(const int i, const T& value) {
	if (n == capacity) {
		reserve(std::max(i, capacity * 2));
	}
	for (int j = n - 1; j >= i; j--)
		field[j + 1] = field[j];	//shift elements up
	field[i] = value;
	n++;
}

template <typename T>
void Vector<T>::pushBack(const T& value) {
	insert(n, value);
}

/*
Iterator declaration
*/
template <typename T>
Vector<T>::Iterator::Iterator(T& position) {	//Iterator constructor
	p = &position;	//sets adress of position to position pointer
}

template <typename T>
typename Vector<T>::Iterator& Vector<T>::Iterator::operator++() {	//prefix increment
	p = (p + 1);	//move to next position
	return *this;
}

template <typename T>
typename Vector<T>::Iterator& Vector<T>::Iterator::operator++(int) {	//post increment
	Vector<T>::Iterator old = *this;
	++(*this);
	return old;
}

template <typename T>
typename Vector<T>::Iterator& Vector<T>::Iterator::operator--() {	//prefix increment
	p = (p - 1);	//move to previous position
	return *this;	
}

template <typename T>
typename Vector<T>::Iterator& Vector<T>::Iterator::operator--(int) {	//post increment
	Vector<T>::Iterator old = *this; 
	--(*this); 
	return old; 
}

template <typename T>
bool Vector<T>::Iterator::operator==(Iterator v) const {
	return (p == v.p);	//if pointer that points to T element is same as 
}

template <typename T>
bool Vector<T>::Iterator::operator!=(Iterator v) const {	//diference operator
	return (p != v.p);
}

template <typename T>
T& Vector<T>::Iterator::operator*() {	//acces position pointer value
	return *p;
}
