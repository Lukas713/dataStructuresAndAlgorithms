#include "pch.h"
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>

/*
Implement the sequence ADT by means of a singly linked list.
*/

typedef std::string error;
class Exeption {
	error txt;
public:
	Exeption(error err)
		: txt(err) {};
	error& getError() { return this->txt; };
};

class List {
	struct Node {
		int value; 
		Node* next;
	};
public:
	class Iterator {
		Iterator(Node* p); 
		Node* v; 
	public:
		bool operator==(const Iterator& p) const; 
		bool operator!=(const Iterator& p) const; 
		int& operator*(); 
		Iterator& operator++(); 
		Iterator& operator++(int); 
		friend class List; 
	};

	List(); 
	~List(); 
	int size() const; 
	bool isEmpty() const; 
	Iterator begin(); 
	Iterator end(); 
	void insertFront(const int value);
	void insertAfter(Iterator& p, const int value);
	void removeFront();
	void removeAfter(Iterator& p);

private:
	Node* head; 
	int n;	//list size
};

int main() {

	
	List a; 
	List::Iterator p = a.begin(); 
	a.insertAfter(p, 4);
	a.insertFront(2); 
	a.insertFront(1); 
	a.insertFront(0);
	a.removeFront(); 
	for (List::Iterator ptr = a.begin(); ptr != a.end(); ++ptr) {
		std::cout << *ptr << " "; 
	}


	



	return 0;
}
List::List()	//constructor
	:head(NULL), n(0) {};

List::~List() {
	while (!isEmpty()) {
		removeFront();
	}
}

int List::size() const {
	return n;
}

bool List::isEmpty() const {	//is list empty?
	return (n == 0);
}

List::Iterator::Iterator(Node* p) {	//take position node 
	v = p;
}

List::Iterator List::begin() {
	return Iterator(head);	//construt Iterator on first node
}

List::Iterator List::end() {
	return Iterator(NULL); 
}

List::Iterator& List::Iterator::operator++() {
	v = v->next;
	return *this;
}

void List::insertAfter(Iterator& p, const int value) {
	Node* newNode = new Node;
	newNode->value = value;
	if (!isEmpty()) {
		Node* position = p.v;
		if (position->next != NULL) {
			newNode->next = position->next;
		}
		else {
			newNode->next = NULL;
		}
		position->next = newNode;
		n++;
		return;
	}
	newNode->next = head;
	head = newNode;
	n++;
}
void List::insertFront(const int value) {
	Node* newNode = new Node; 
	newNode->value = value; 
	newNode->next = head; 
	head = newNode; 
}

void List::removeFront() {
	Node* old = head;
	head = head->next;
	delete old;
}

void List::removeAfter(Iterator& p) {
	Node* old = p.v->next;
	p.v->next = old->next;
	delete old;
}

bool List::Iterator::operator==(const Iterator& p) const {
	return (v == p.v);
}

bool List::Iterator::operator!=(const Iterator& p) const {
	return (v != p.v);
}

int& List::Iterator::operator*() {	//referance to the element's value
	return v->value;
}

List::Iterator& List::Iterator::operator++(int) {
	Iterator old = v;
	++(*this);
	return old;
}
