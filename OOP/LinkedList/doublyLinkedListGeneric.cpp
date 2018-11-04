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
	void addFront(const T value); 
	void addBack(const T value); 
	void removeBack();
	void removeFront(); 
	void display();
protected:
	void add(Node<T>* x, const T value);
	void remove(Node<T>* x);
};

int main()
{
	DoublyLinkedList<int>* list = new DoublyLinkedList<int>; 
	list->addFront(1);
	list->addFront(2); 
	list->display(); 



	


	





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
void DoublyLinkedList<T>::addFront(const T value) {
	return add(head->next, value);	//return add function
}
template <typename T>
void DoublyLinkedList<T>::addBack(const T value) {
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
	Node<T>* temp = head;
	while (temp != NULL) {
		std::cout << temp->value << " ";
		temp = temp->next;
	}
	delete temp;
	return;
}
template <typename T>
void DoublyLinkedList<T>::add(Node<T>* x, const T value) {
	Node<T>* newNode = new Node<T>;	//create pointer to Node, dinamic alocate memory
	newNode->value = value;	//set value
	newNode->next = x;	//set next to Node from parameter
	newNode->prev = x->prev;	//set previus to x's previous
	x->prev = newNode;	//x's previous Node is newNode
	x->prev->next = newNode;	//previous Node's next is nodeNode
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
