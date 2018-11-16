#include "pch.h"
#pragma warning( disable : 4290 )  //https://msdn.microsoft.com/en-us/library/sa28fef8.aspx
#include <iostream>
#include <string>
#include <vector>

/*
Queue circular implementation
*/
typedef std::string error;
class Exeption {
	error txt; 
public:
	Exeption(error err)
		: txt(err) {}; 
	error& getError() { return this->txt; };
};

template <typename T> class CircleList; 
template <typename T>
class Node {
	T value; 
	Node<T>* next;
	friend class CircleList<T>; //can use private members
};

template <typename T>
class CircleList {
	Node<T>* cursor;	

public:
	CircleList()
		: cursor(NULL) {}; 
	bool isEmpty() const; //check if list is empty
	const T& front() const throw(Exeption); //return referance to front element
	const T& rear() const throw(Exeption);	//return referance to rear element
	void advance() throw (Exeption); //move cursor to next position
	void addNode(const T& value);	//add new node 
	void removeNode() throw(Exeption);	//remove node from front
};

typedef int value; 
class Queue {
	int n;	//counter of elements
	CircleList<value> L; //init CircleList inside Queue

public:
	Queue()	//constructor, init List(set cursor to NULL), init counter to 0
		: L(), n(0) {}; 
	int size() const;	//return number of elements in queue
	bool isEmpty() const;	//check if Queue is empty
	const value& front() const throw(Exeption);	//return constant referance to front node (cant modifi)
	void enqueue(const value& x); //invoke addNode() and advance(), increment n by 1
	void dequeue() throw(Exeption); //invoke removeNode() decrement n by 1
};

/*Program menu*/
void menu();

int main()
{
	menu(); 








	return 0;
}
/*
Circular Linked List methods decaration
*/
template <typename T>
bool CircleList<T>::isEmpty() const {
	return (cursor == NULL);
}
template <typename T>
const T& CircleList<T>::front() const throw(Exeption) {
	try {
		if (!isEmpty()) {
			return cursor->next->value;
		}
		throw Exeption("Queue is empty!");
	}
	catch (Exeption& err) {
		std::cout << err.getError() << "\n";
		return cursor->value;
	}

}
template <typename T>
const T& CircleList<T>::rear() const throw(Exeption) {
	try {
		if (!isEmpty()) {
			return cursor->value;
		}
		throw Exeption("Queue is empty!");
	}
	catch (Exeption& err) {
		std::cout << err.getError() << "\n";
		return cursor;
	}
}
template <typename T>
void CircleList<T>::advance() throw(Exeption) {
	try {
		if (!isEmpty()) {
			cursor = cursor->next;
			return;
		}
		throw Exeption("Queue is empty!");
	}
	catch (Exeption& err) {
		std::cout << err.getError() << "\n";
	}
}
template <typename T>
void CircleList<T>::addNode(const T& value){
	Node<T>* newNode = new Node<T>;
	newNode->value = value;

	if (!isEmpty()) {
		newNode->next = cursor->next;
		cursor->next = newNode;
		return;
	}
	newNode->next = newNode;
	cursor = newNode;
}
template <typename T>
void CircleList<T>::removeNode() throw(Exeption) {
	try {
		if (!isEmpty()) {
			Node<T>* oldNode = cursor->next;
			if (oldNode != cursor) {
				cursor->next = oldNode->next;
				delete oldNode;
				return;
			}
			cursor = NULL;
			delete oldNode;
			return;
		}
	}
	catch (Exeption& err) {
		std::cout << err.getError() << "\n";
	}
}
/*
Queue interface declaration
*/
int Queue::size() const {
	return n;
}
bool Queue::isEmpty() const {
	return (n == 0);
}
const value& Queue::front() const throw(Exeption) {
	try {
		if (!isEmpty()) {
			return L.front();
		}
		throw Exeption("Queue is empty!");
	}
	catch (Exeption& err) {
		std::cout << err.getError() << "\n";
	}
}
void Queue::enqueue(const value& x) {
	L.addNode(x); //add node to the begining of circular linked list
	L.advance();	//move cursor to next position (rule of queue,becouse we added into rear)
	n++;	//increment size by 1
}
void Queue::dequeue() throw(Exeption) {
	try {
		if (!isEmpty()) {
			L.removeNode();	//remove first node
			n--;	//decrement size by 1
		}
	}
	catch (Exeption& err) {
		std::cout << err.getError() << "\n";
	}
}
/*Program menu*/
void menu() {

	int choice, n;
	std::cout << "*************************** \n";
	std::cout << "Queue operations with circular linked list\n";
	std::cout << "*************************** \n";
	Queue Q;

	while (1) {
		std::cout << "1. Enqueue \n";
		std::cout << "2. Dequeue \n";
		std::cout << "3. Size of queue \n";
		std::cout << "4. Front element \n";
		std::cout << "0. Exit \n";
		std::cout << "Enter option: ";
		std::cin >> choice;
		switch (choice) {
		case 1:
			std::cout << "Enter value: ";
			std::cin >> n;
			Q.enqueue(n);
			break;
		case 2:
			Q.dequeue();
			break;
		case 3:
			std::cout << Q.size() << " elements \n";
			break;
		case 4:
			std::cout << Q.front() << "\n";
			break;
		case 0:
			exit(1);
			break;
		}
	}
}
