#include "pch.h"
#pragma warning( disable : 4290 )  //https://msdn.microsoft.com/en-us/library/sa28fef8.aspx
#include <iostream>
#include <string>
#include <vector>
/*
Implementation of generic stack using vector
*/
typedef std::string error;
class Exeption {
	error txt;
public:
	Exeption(const error& err)
		: txt(err) {};
	error getError() {
		return this->txt;
	}
};

template <typename T>
class Stack {

	std::vector<T> vector; 
	int n; 
public:
	Stack(int elements = 5)
		:n(-1), vector(elements) {}; 
	int size() const; 
	bool isEmpty() const; 
	const T& peek() throw(Exeption);
	void push(const T& value);
	void pop() throw(Exeption); 
};


int main()
{
	int choice, n; 
	Stack<int> S; 

	std::cout << "Stack operations with STL vector \n"; 
	std::cout << "1. Push \n"; 
	std::cout << "2. Pop \n"; 
	std::cout << "3. Peek \n"; 
	std::cout << "4. Size \n";
	while (1) {
		std::cout << "Enter option: ";
		std::cin >> choice;
		switch(choice) {
			case 1:
				std::cout << "Enter value: ";
				std::cin >> n; 
				S.push(n); 
				break; 
			case 2:
				S.pop();
				break; 
			case 3:
				std::cout << S.peek() << "\n";
				break; 
			case 4:
				std::cout << S.size() << "\n"; 
				break; 
			case 0:
				exit(1); 
				break; 
			default:
				std::cout << "Wrong option! \n"; 
				break; 
		}
	}

	return 0;
}
template <typename T>
int Stack<T>::size() const {
	return n;
}
template <typename T>
bool Stack<T>::isEmpty() const {
	return (n == 0);
}
template <typename T>
const T& Stack<T>::peek() throw(Exeption) {
	try {
		if (!isEmpty()) {
			return vector[n];
		}
		throw Exeption("Stack is empty!");
	}
	catch (Exeption& err) {
		std::cout << err.getError() << "\n";
	}
}
template <typename T>
void Stack<T>::push(const T& value) {
	n++;
	vector[n] = value;
}
template <typename T>
void Stack<T>::pop() throw(Exeption) {
	try {
		if (!isEmpty()) {
			n--;
			return;
		}
		throw Exeption("Stack is empty!");
	}
	catch (Exeption& err) {
		std::cout << err.getError() << "\n";
	}
}

