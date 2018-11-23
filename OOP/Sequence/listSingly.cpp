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
		Iterator& operator--();
		Iterator& operator--(int); 
		friend class List; 
	};

	List(); 
	List(List& L); 
	//~List(); 
	int size() const; 
	bool isEmpty() const; 
	Iterator begin(); 
	Iterator end(); 
	void insertFront(const int value);
	void insertBack(const int value); 
	void insertAfter(Iterator& p, const int value);
	void removeFront();
	void removeBack();
	void remove(const int where); 


private:
	Node* head; 
	int n;	//list size
};

void List::insertBack(const int value) {
	List::Iterator p = end(); 
	insertAfter(p, value); 
	
}








int main() {

	List a; 
	a.insertFront(5); 
	a.insertBack(3); 
	a.insertBack(12); 



	



	return 0;
}
List::List()	//constructor
	:head(NULL), n(0) {};

int List::size() const {
	return n;
}

bool List::isEmpty() const {	//is list empty?
	return (n == 0);
}

void List::insertAfter(Iterator& p, const int value) {
	Node* newNode = new Node;
	newNode->value = value;
	newNode->next = p.v->next; 
	p.v->next = newNode;
}

void List::insertFront(const int value) {
	Node* newNode = new Node;
	newNode->value = value;
	newNode->next = head;
	head = newNode;
}

List::Iterator::Iterator(Node* p) {	//take position node 
	v = p;
}

List::Iterator List::begin() {
	return Iterator(head);	//construt Iterator on first node
}

List::Iterator List::end() {
	Node* end = head; 
	while (end->next != NULL) {
		end = end->next;
	}
	return Iterator(end); 
}

List::Iterator& List::Iterator::operator++() {
	v = v->next;
	return *this;
}

bool List::Iterator::operator!=(const Iterator& p) const {
	return (v != p.v);
}


