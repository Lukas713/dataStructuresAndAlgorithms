#include "pch.h"
#include <iostream>
#include <string>
#include <vector>

class Exeption {
	std::string error; 
public:
	Exeption(std::string err)
		:error(err) {}; 
	std::string getError() { return this->error; }
};

template <typename T>
class Stack {
	int N; 
	int t; 
	T* item; 
public:
	Stack(); 
	int size() const; 
	bool empty() const; 
	const T& top() const; 
	void push(const T& x); 
	void pop(); 
};

int main()
{
	Stack<int> a; 
	a.push(5); 
	a.push(3); 
	std::cout << a.top(); 
	






	return 0;
}
template <typename T>
Stack<T>::Stack()
	: N(5), t(-1), item(new T[N]) {};
template <typename T>
int Stack<T>::size() const {
	return (t + 1);
}
template <typename T>
bool Stack<T>::empty() const {
	return (t < 0);
}
template <typename T>
const T& Stack<T>::top() const {
	try {
		if (empty()) {
			throw Exeption("Stack is empty!");
		}
		return item[t];
	}
	catch (Exeption& err) {
		std::cout << err.getError() << "\n";
	}
}
template <typename T>
void Stack<T>::push(const T& x) {
	try {
		if (size() == N) {
			throw Exeption("Stack is full!");
		}
		t += 1;
		item[t] = x;
		return;
	}
	catch (Exeption& err) {
		std::cout << err.getError() << "\n";
	}
}
template <typename T>
void Stack<T>::pop() {
	try {
		if (!empty()) {
			t -= 1;
			return;
		}
		throw Exeption("Stack is empty!");
	}
	catch (Exeption& err) {
		std::cout << err.getError() << "\n";
	}
}
