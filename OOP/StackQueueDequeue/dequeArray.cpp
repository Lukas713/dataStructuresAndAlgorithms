#include "pch.h"
#pragma warning( disable : 4290 )  //https://msdn.microsoft.com/en-us/library/sa28fef8.aspx
#include <iostream>
#include <string>
#include <vector>
/*
Implementation of Deque using array, update operations are O(1)
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
class Deque { 
	T* field; 
	int head; 
	int rear;
	int n; 
public:
	Deque(int max)
		:field(new T[max]), head(-1), rear(-1), n(0) {}; 
	bool isEmpty() const; 
	int size() const;
	const T& front() const;
	const T& back() const; 
	void pushFront(const T& value); 
	void pushBack(const T& value); 
	void removeFront() throw(Exeption); 
	void removeBack() throw(Exeption); 
	T& operator[](int x); //operator overload
};

int main()
{

	int choice, n; 

	Deque<int> D(5);
	std::cout << "Deque operation with array \n"; 
	std::cout << "----------------------------------------------- \n"; 
	std::cout << "1. Add front \n"; 
	std::cout << "2. Add back \n";
	std::cout << "3. Remove front \n";
	std::cout << "4. Remove back \n";
	std::cout << "5. Size of array \n"; 
	while (1) {
		std::cout << "Enter option: ";
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			std::cout << "Enter value: "; 
			std::cin >> n; 
			D.pushFront(n); 
			break; 
		case 2:
			std::cout << "Enter value: ";
			std::cin >> n;
			D.pushBack(n); 
			break;
		case 3:
			D.removeFront();
			break;
		case 4:
			D.removeBack();
			break;
		case 5:
			std::cout << D.size() << "\n"; 
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
bool Deque<T>::isEmpty() const {
	return (n == 0);
}
template <typename T>
int Deque<T>::size() const {
	return n;
}
template <typename T>
const T& Deque<T>::front() const {
	try {
		if (!isEmpty()) {
			return field[head];
		}
		throw Exeption("Deque is empty!");
	}
	catch (Exeption& err) {
		std::cout << err.getError() << "\n";
	}
}
template <typename T>
const T& Deque<T>::back() const {
	try {
		if (!isEmpty()) {
			return field[rear];
		}
		throw Exeption("Deque is empty!");
	}
	catch (Exeption& err) {
		std::cout << err.getError() << "\n";
	}
}
template <typename T>
void Deque<T>::pushFront(const T& value) {
	if (!isEmpty()) {
		field[--head] = value;	//add element before head element
		n++;	//increment counter by 1
		return;
	}
	field[rear] = value;	//add element on rear
	n++;	//increment counter by 1
}
template <typename T>
void Deque<T>::pushBack(const T& value) {
	field[++rear] = value;
	n++;
}
template <typename T>
void Deque<T>::removeFront() throw(Exeption) {
	try {
		if (!isEmpty()) {
			head++;
			n--;
			return;
		}
		throw Exeption("Deque is empty!");
	}
	catch (Exeption& err) {
		std::cout << err.getError() << "\n";
	}
}
template <typename T>
void Deque<T>::removeBack() throw(Exeption) {
	try {
		if (!isEmpty()) {
			rear--;
			n--;
			return;
		}
		throw Exeption("Deque is empty!");
	}
	catch (Exeption& err) {
		std::cout << err.getError() << "\n";
	}
}
template <typename T>
T& Deque<T>::operator[](int x) {
	return field[x];
}
