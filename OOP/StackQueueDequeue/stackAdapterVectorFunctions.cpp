#include "pch.h"
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
/*
Give an adapter class to support the Stack interface using the functions of
the vector ADT.
*/

typedef std::string error;
class Exeption {
	error txt;
public:
	Exeption(error err)
		: txt(err) {};
	error& getError() { return this->txt; };
};

class Vector {
	int capacity;	//max elements
	int n;	//counter
	int* field;		//array

public:
	Vector()
		:capacity(0), n(0), field(NULL) {};
	int size() const;
	bool isEmpty() const;
	int& operator[](int i);
	int& at(int i);
	void erase(int i);	//delete element at indice e
	void insert(int i, const int& value);	//insert value at indice i 
	void reserve(int N); //request alocation of N elements
};

class Stack {
	int n; //current size of the stack
	Vector V;

public:
	Stack()
		: V(), n(0) {};
	int size() const;
	bool isEmpty() const;
	const int& peek();
	void push(const int& value);
	void pop();
};
int main() {


	Stack a;
	a.push(5);
	a.push(7); 
	a.push(72);
	a.pop();
	std::cout << a.peek();







	return 0;
}
int Vector::size() const {
	return n;
}
bool Vector::isEmpty() const {
	return (n == 0);
}
int& Vector::operator[](int i) {
	try {
		if (size() >= i || i < 0) {
			return field[i];
		}
		throw Exeption("Index out of bounds.");
	}
	catch (Exeption& err) {
		std::cout << err.getError() << " ";
	}
}
int& Vector::at(int i) {
	try {
		if (i >= 0 || i < n) {

			return field[i];
		}
		throw Exeption("Index out of bounds.");
	}
	catch (Exeption& err) {
		std::cout << err.getError() << " \n";
	}
}
void Vector::erase(int i) {
	try {
		if (i >= 0 || i <= size()) {
			for (int j = i + 1; j < n; j++)
				field[j - 1] = field[j];
			n--;
			return;
		}
		throw Exeption("Index out of bounds.");
	}
	catch (Exeption& err) {
		std::cout << err.getError() << "\n";
	}
}
void Vector::reserve(int N) {
	if (N < capacity) {
		return;
	}
	int* newField = new int[N];
	for (int i = 0; i < n; i++)
		newField[i] = field[i];
	if (field != NULL) {
		delete[] field;
	}
	field = newField;
	capacity = N;
}
void Vector::insert(int i, const int& value) {
	if (n == capacity) {		//if cap is less or equal to i, reserve new 
		reserve(std::max(i, capacity * 2));
	}
	for (int j = n - 1; j >= i; j--) {
		field[j + 1] = field[j];
	}
	field[i] = value;
	n++;
}
/*
Stack implementation
*/
int Stack::size() const {
	return V.size();
}
bool Stack::isEmpty() const {
	return	V.isEmpty();
}
const int& Stack::peek() {
	try {
		if (size() > 0) {
			return V.at(size() - 1);
		}
		throw Exeption("Stack underflow.");
	}
	catch (Exeption& err) {
		std::cout << err.getError() << " \n";
	}
}
void Stack::push(const int& value) {
	V.insert(V.size(), value);
	n++;
}
void Stack::pop() {
	try {
		if (size() > 0) {
			V.erase(V.size() - 1);
			n--;
			return;
		}
		throw Exeption("Stack underflow.");
	}
	catch (Exeption& err) {
		std::cout << err.getError() << " \n";
	}
}
