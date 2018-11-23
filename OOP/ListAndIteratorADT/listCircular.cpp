#include "pch.h"
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>

/*
Design a circular node list ADT that abstracts a circularly linked list in the
same way that the node list ADT abstracts a doubly linked list.
*/

typedef std::string error;
class Exeption {
	error txt;
public:
	Exeption(error err)
		: txt(err) {};
	error& getError() { return this->txt; };
};


class CircularList {
	struct Node {	//nested Node struct
		int value;
		Node* next;
	};

public:
	class Iterator {
	private:
		Iterator(Node* p);
		Node* v;
	public:
		int operator*(); 
		bool operator!=(const Iterator& p); 
		Iterator& operator++();
		Iterator& operator++(int); 
		friend class CircularList;
	};
	CircularList();
	int size() const;
	bool isEmpty() const;
	int front() const;
	int back() const;
	Iterator begin();	//creates iterator on first node
	Iterator end();		//ceates iterator on last node
	void pushAfter(Iterator& p, int value);	//push value after position p
	void pushFront(int value);	//invoke pushAfter(end(), value)
	void pushBack(int value); 
	void removeAfter(Iterator& p); //remove node after position p
	void removeFront(); 
	void removeBack();
	void display() {
		std::cout << cursor->value; 
	}

private:
	void advance();
	int n;
	Node* cursor;
};


int main() {

	CircularList a; 
	a.pushFront(10); 
	a.pushFront(5); 
	a.pushFront(1); 
	a.pushBack(15);
	CircularList::Iterator p = a.end(); 
	a.pushAfter(p, 0); 
	for (CircularList::Iterator ptr = a.begin(); ptr != a.end(); ptr++) {
		std::cout << *ptr << " "; 
	}
	p = a.end();
	std::cout << *p << " ";
 




	return 0;
}
CircularList::CircularList()
	:n(0), cursor(NULL) {};


int CircularList::size() const {
	return n;
}

bool CircularList::isEmpty() const {
	return (cursor == NULL);
}

int CircularList::front() const {
	if (!isEmpty()) {
		return cursor->next->value;
	}
	return 0; 
}

int CircularList::back() const {
	return cursor->value;
}

void CircularList::advance() {
	if (!isEmpty()) {
		cursor = cursor->next;
	}
}

void CircularList::pushAfter(Iterator& p, int value) {
	Node* newNode = new Node;	//creates new node
	newNode->value = value;
	if (p.v != NULL) {	//if list is not empty
		Node* position = p.v;
		newNode->next = position->next;	//new node between position p and position p->next
		position->next = newNode;
		return;
	}
	newNode->next = newNode; //newNode is pointing to himself
	cursor = newNode;	//cursor is on first node too
}

void CircularList::pushFront(int value) {
	CircularList::Iterator temp = end();
	pushAfter(temp, value);
}

void CircularList::pushBack(int value) {
	Node* newNode = new Node; 
	newNode->value = value; 
	newNode->next = cursor->next; 
	cursor->next = newNode; 
	cursor = newNode; 
}

void CircularList::removeAfter(Iterator& p) {
	try {
		if (p.v != NULL) {
			Node* position = p.v;
			Node* old = position->next;
			if (old != position) {	//there is not only one node in the list
				position->next = old->next;
				if (cursor == old) {
					advance();
				}
				delete old;
				return;
			}
			cursor = NULL;
			delete old;
		}
		throw Exeption("List is empty!"); 
	}
	catch (Exeption& err) {
		std::cout << err.getError() << "\n"; 
	}
	
	
}

void CircularList::removeFront() {
	CircularList::Iterator p = end();
	removeAfter(p);
}

void CircularList::removeBack() {
	CircularList::Iterator p = begin();	//set iterator to first node
	Node* predecessor = NULL;
	if (p.v != cursor) {	//if there is only one node in the list	invoke removeFront()
		while (p != end()) {	//traverse untill last node
			predecessor = p.v; //set previous node
			++p;
		}
		Node* old = p.v;	
		predecessor->next = old->next;	
		cursor = predecessor;	//previus node is last node now
		delete old;	//delete old node
		return;
	}
	removeFront();
}

CircularList::Iterator::Iterator(Node* p) {
	v = p;
}

CircularList::Iterator CircularList::begin() {
	if (!isEmpty()) {	//if list is empty
		return Iterator(cursor->next); 
	}
	end(); //construct iterator on cursor
}

CircularList::Iterator CircularList::end() {
	return Iterator(cursor);
}

int CircularList::Iterator::operator*() {
	return v->value;
}

bool CircularList::Iterator::operator!=(const Iterator& p) {
	return (v != p.v);
}

CircularList::Iterator& CircularList::Iterator::operator++() {
	v = v->next;
	return *this;
}
CircularList::Iterator& CircularList::Iterator::operator++(int) {
	CircularList::Iterator old = *this; 
	++(*this); 
	return old; 
}





