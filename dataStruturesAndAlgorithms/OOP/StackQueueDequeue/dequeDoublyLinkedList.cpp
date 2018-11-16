#include "pch.h"
#pragma warning( disable : 4290 )  //https://msdn.microsoft.com/en-us/library/sa28fef8.aspx
#include <iostream>
#include <string>
#include <vector>
/*
Give a fully generic implementation of the doubly linked list data structure by using a templated class.
*/
using namespace std;

typedef std::string error;
class Exeption {
	error txt;
public:
	Exeption(const error& err)
		: txt(err) {};
	error& getError() { return this->txt; }
};

template <typename T> class DoublyLinkedList;
template <typename T>
class Node {
	T value;
	Node<T>* next;
	Node<T>* prev;
public:
	friend DoublyLinkedList<T>;
};

template <typename T>
class DoublyLinkedList {
	Node<T>* head;		//pointer to node, pointing to first element of the lit
	Node<T>* tail;		//pointer to node, pointing to last element of the list

public:
	DoublyLinkedList();
	~DoublyLinkedList();
	bool isEmpty() const;
	const T& front() const;
	const T& back() const;
	void addFront(const T value); //takes value, invoke add(head)
	void addBack(const T& value);	//takes value, invoke add(tail)
	void removeBack();	//invoke remove(tail)
	void removeFront();
	void display();

private:
	void add(Node<T>* x, const T value);
	void remove(Node<T>* x);
};

typedef int element; 
class Deque {

	DoublyLinkedList<element> DLL; //init doubly linked list inside Deque
	int n; //size property

public:
	Deque()
		: DLL(), n(0) {}; 
	int size() const;	//return size of the list
	bool isEmpty() const;	// deque is empty?
	const element& front() const throw(Exeption);	//return referance to FIRST element
	const element& back() const throw(Exeption);	//return referance to BACK element
	void pushFront(const element& value);		//add Node to FRONT
	void pushBack(const element& value);	//add Node to BACK
	void removeFront() throw(Exeption);		//remove from FRONT
	void removeBack() throw(Exeption);		//remove from BACK
};
void menu(); 
int main()
{

	menu(); 





	return 0; 
}
//templated constructor
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() {
	head = new Node<T>;	//alocate Node to head pointer
	tail = new Node<T>;	//alocate Node to tail pointer
	//sets empty doubly linked list
	head->next = tail;
	tail->prev = head;
	head->prev = NULL;
	tail->next = NULL;
}
//templated destructor
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
	while (!isEmpty()) {	//checking if not empty
		removeFront();	//remove front
	}
	//delete starting nodes
	delete head;
	delete tail;
}
template <typename T>
bool DoublyLinkedList<T>::isEmpty() const {	//function thatchecks if list is empty or not
	return (head->next == tail);
}
template <typename T>
const T& DoublyLinkedList<T>::front() const {	//return first node value
	return head->next->value;
}
template <typename T>
const T& DoublyLinkedList<T>::back() const {	//return last node value
	return tail->prev->value;
}
template <typename T>
void DoublyLinkedList<T>::addFront(const T value) {
	return add(head, value);	//return add function
}
template <typename T>
void DoublyLinkedList<T>::addBack(const T& value) {
	return add(tail->prev, value);	//return add function
}
template <typename T>
void DoublyLinkedList<T>::removeFront() {
	return remove(head->next);	//return remove function
}
template <typename T>
void DoublyLinkedList<T>::removeBack() {
	return remove(tail->prev);	//return remove function
}
template <typename T>
void DoublyLinkedList<T>::add(Node<T>* x, const T value) {
	Node<T>* newNode = new Node<T>;	//create pointer to Node, dinamic alocate Node memory
	newNode->value = value;
	newNode->next = x->next;
	newNode->prev = x;
	x->next->prev = newNode;
	x->next = newNode;
}
template <typename T>
void DoublyLinkedList<T>::remove(Node<T>* x) {
	try {
		if (!isEmpty()) {
			Node<T>* prevNode = x->prev;	//creates pointer to Node that points to PREVIOUS of Node from parameter
			Node<T>* nextNode = x->next;	//creates poiner to Node that points to NEXT of Node from parameter

			prevNode->next = nextNode;		//sets link to next
			nextNode->prev = prevNode;		//sets link to previous
			delete x;	//delete wishing node
			return;
		}
		throw Exeption("List is empty.");	//throw exeption if list is not empty
	}
	catch (Exeption& err) {
		std::cout << err.getError() << std::endl;
	}
}
template <typename T>
void DoublyLinkedList<T>::display() {
	Node<T>* temp = head->next;
	while (temp != tail) {
		std::cout << temp->value << " ";
		temp = temp->next;
	}
}
/*Deck methods declarations*/
int Deque::size() const {
	return n; 
}
bool Deque::isEmpty() const {
	return (n == 0); 
}
const element& Deque::front() const throw(Exeption){
	try {
		if (!isEmpty()) {
			return DLL.front();
		}
		throw Exeption("Queue is empty!"); 
	}
	catch (Exeption& err) {
		std::cout << err.getError() << "\n"; 
		return DLL.front(); 
	}
}
const element& Deque::back() const throw(Exeption) {
	try {
		if (!isEmpty()) {
			return DLL.back();
		}
		throw Exeption("Queue is empty!");
	}
	catch (Exeption& err) {
		std::cout << err.getError() << "\n";
		return DLL.back();
	}
}
void Deque::pushFront(const element& value) {
	n++;
	return DLL.addFront(value); 
}
void Deque::pushBack(const element& value) {
	n++;
	return DLL.addBack(value);
}
void Deque::removeFront() throw(Exeption) {
	try {
		if (!isEmpty()) {
			std::cout << "element poped \n"; 
			DLL.removeFront(); 
			return;
		}
		throw Exeption("Deque is empty!"); 
	}
	catch (Exeption& err) {
		std::cout << err.getError() << "\n"; 
	}
}
void Deque::removeBack() throw(Exeption) {
	try {
		if (!isEmpty()) {
			std::cout << "element poped \n";
			DLL.removeBack();
			return;
		}
		throw Exeption("Deque is empty!");
	}
	catch (Exeption& err) {
		std::cout << err.getError() << "\n";
	}
}
/*Program menu*/
void menu() {

	int choice, n;
	std::cout << "****************************************************** \n";
	std::cout << "Deque operations with doubly linked list \n";
	std::cout << "****************************************************** \n";
	Deque D; 

	while (1) {
		std::cout << "1. Push front \n";
		std::cout << "2. Push back \n";
		std::cout << "3. Remove front \n";
		std::cout << "4. Remove back \n";
		std::cout << "5. Size of queue \n";
		std::cout << "6. Front element \n";
		std::cout << "0. Exit \n";
		std::cout << "Enter option: ";
		std::cin >> choice;
		switch (choice) {
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
		case 6:
			std::cout << D.front() << " is first element \n";
			break;
		case 7:
			std::cout << D.back() << " is last element \n";
			break;
		case 0:
			exit(1);
			break;
		}
	}
}
