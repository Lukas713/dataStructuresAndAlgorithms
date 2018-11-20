#include "pch.h"
#pragma warning( disable : 4290 )  //https://msdn.microsoft.com/en-us/library/sa28fef8.aspx
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>

typedef std::string error;
class Exeption {
	error txt;
public:
	Exeption(error err)
		: txt(err) {};
	error& getError() { return this->txt; };
};

typedef int Elem;
typedef NodeList::Iterator iterator; 
class NodeList {	//node base type List
private:
	struct Node {	//nested struct inside class
		Elem value;
		Node* next;
		Node* previous;
	};

public:
	class Iterator {	//nested class
		Node* v;	//pointer to node
		Iterator(Node* x);	//create from node
	public:
		Elem& operator*();	//dereferance operator that acces data stored
		bool operator==(const Iterator& p) const; //comparison operator to check if two iterators pointing/not poining to same object (not just value)
		bool operator!=(const Iterator& x) const;	//to same object (not just value)
		Iterator& operator++(); //move to next position and return referance to it
		Iterator& operator--(); //move to previous position and return referance to it
		friend class NodeList; //only Node list can access private memers and create new operator
	};

private:
	Node* header;	//head of the list
	Node* trailer;	//tail of the list
	int n;	//node counter

public:
	NodeList();
	int size() const;
	bool isEmpty() const;
	Iterator begin() const;	//beggining position
	Iterator end() const;		//position after last node
	void insertFront(const Elem& value);	//ivoke insert(begin(), value)
	void insertBack(const Elem& value);		//ivoke insert(end(), value)
	void insert(const Iterator& p, const Elem& value);	//insert Element before position p
	void eraseFront(); //ivoke erase(begin())
	void eraseBack(); //invoke erase(--end()), have to decrement to position bacwards one node
	void erase(const Iterator& p);	//remove element at position p
};

class SequenceList : public NodeList {
public:
	Iterator atIndex(int i) const;	//returns position from index i
	int indexOf(const Iterator& p) const;	//returns index int of Iterator(referance) p
};

int main() {

	

	
	
	
	







	return 0;
}
NodeList::Iterator::Iterator(Node* u) {
	v = u;
}
Elem& NodeList::Iterator::operator*() {	//referance to the element
	return v->value;
}
bool NodeList::Iterator::operator==(const Iterator& p) const {	//compare positions
	return (v == p.v);
}
bool NodeList::Iterator::operator!=(const Iterator& p) const {
	return (v != p.v);
}
NodeList::Iterator& NodeList::Iterator::operator++() {
	v = v->next;	//move to next position
	return *this;
}
NodeList::Iterator& NodeList::Iterator::operator--() {
	v = v->previous;	//move to previous position
	return *this;
}
//Node list methods declaration
NodeList::NodeList() {
	n = 0;	//0 nods in the list
	header = new Node;	//alocate node to node pointer
	trailer = new Node;
	header->next = trailer; header->previous = NULL; //set up links
	trailer->previous = header; trailer->next = NULL;
}
int NodeList::size() const {
	return n;
}
bool NodeList::isEmpty() const {
	return (n == 0);
}
NodeList::Iterator NodeList::begin() const {
	return	Iterator(header->next); //construct Iterator to first node of the list
}
NodeList::Iterator NodeList::end() const {
	return Iterator(trailer);	//construct Iterator to AFTER last node of the list
}
void NodeList::insertFront(const Elem& value) {
	return insert(begin(), value);
}
void NodeList::insertBack(const Elem& value) {
	return insert(end(), value);
}
/*
2 params
position and value
insert newNode before p
increment n by 1
no return value
*/
void NodeList::insert(const Iterator& p, const Elem& value) {	//insert element before p
	Node* position = p.v;	//pointer to p's node
	Node* predecessor = position->previous; //u is a pointer to p's previous node
	Node* newNode = new Node;	//new node to insert
	newNode->value = value;
	newNode->next = position; position->previous = newNode;	//newNode's next is pointing to position, and position's previous to newNode
	newNode->previous = predecessor; predecessor->next = newNode;	//newNode's previous is pointing to previous, and previous next to newNode
	n++; //increment n by 1 
}
void NodeList::eraseFront() {
	return erase(begin());
}
void NodeList::eraseBack() {
	return erase(--end());
}
/*
1 param, position
create position->next and position->previous
link them
delete node at p
decrement n by one
no return value
*/
void NodeList::erase(const Iterator& p) {
	Node* oldNode = p.v;
	Node* predecessor = oldNode->previous; //set position's predecessor
	Node* successor = oldNode->next;	//set position's next node
	predecessor->next = successor;	successor->previous = predecessor; //change links
	delete oldNode;
	n--;	//decrement n by 1
}
/*
int param
traverse from 0 to i
return iterator at i - 1 indice
*/
SequenceList::Iterator SequenceList::atIndex(int i) const {
	iterator p = begin();	//set iterator to header
	for (int j = 0; j < i; j++)	//traverse untill i
		++p;
	return p; //return that iterator
}
/*
param iterator
traverse untill iterator
count hops
return i (number of hops)
*/
int SequenceList::indexOf(const Iterator& p) const {
	iterator x = begin();	//set iterator to header
	int i = 0;
	while (x != p) {	//traverse untill x is diferent of p and count evry hop
		++x;
		i++;
	}
	return i; //return number of hops
}
