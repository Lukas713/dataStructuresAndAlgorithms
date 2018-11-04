#include "pch.h"
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
	T& front(); 
	T& back(); 
	void addFront(const T& value); 
	void addBack(const T& value); 
	void removeBack();
	void removeFront(); 
	void display();
protected:
	void add(Node<T>* x, const T& value);
	void remove(Node<T>* x);
};

int main()
{

 

	DoublyLinkedList<int> list;
	int choice;
	int number; 



	while (1) {
		std::cout << "***************************************************" << std::endl;
		std::cout << "Doubly Linked List basic operation" << std::endl;
		std::cout << "***************************************************" << std::endl;
		std::cout << "1. Add front" << std::endl;
		std::cout << "2. Remove front" << std::endl;
		std::cout << "3. Display" << std::endl;
		std::cout << "4. Add Back" << std::endl;
		std::cout << "5. Remove back" << std::endl;
		std::cout << "0. Exit" << std::endl;
		std::cout << "enter option: ";
		std::cin >> choice;

		switch (choice) {
		case 1:
			std::cout << "Enter text" << std::endl;
			std::cin >> number;
			list.addFront(number);
			break;
		case 2:
			list.removeFront();
			break;

		case 3:
			list.display();
			break;
		case 4:
			std::cout << "Enter number" << std::endl;
			std::cin >> number;
			list.addBack(number);
			break;
		case 5:
			list.removeBack();
			break;
		case 0:
			exit(1);
			break;
		}
	}

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
	return;
}
template <typename T>
bool DoublyLinkedList<T>::isEmpty() const {	//function thatchecks if list is empty or not
	if (head->next != tail) {	
		return false;
	}
	return true;
}
template <typename T>
T& DoublyLinkedList<T>::front() {	//return first node value
	return head->next->value;
}
template <typename T>
T& DoublyLinkedList<T>::back() {	//return last node value
	return tail->prev->value;
}
template <typename T>
void DoublyLinkedList<T>::addFront(const T& value) {
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
void DoublyLinkedList<T>::display(){
	Node<T>* temp = head->next;
	while (temp != tail) {
		std::cout << temp->value << " ";
		temp = temp->next;
	}
	return; 
}
template <typename T>
void DoublyLinkedList<T>::add(Node<T>* x, const T& value) {
	Node<T>* newNode = new Node<T>;	//create pointer to Node, dinamic alocate memory
	newNode->value = value; 
	newNode->next = x->next; 
	newNode->prev = x;
	x->next = newNode; 
	x->next->prev = newNode; 
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
		}
		throw Exeption("List is empty.");	//throw exeption if list is not empty
	}
	catch (Exeption& err) {
		std::cout << err.getError() << std::endl;
	}
}
