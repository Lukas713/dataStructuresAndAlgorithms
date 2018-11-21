#include "pch.h"
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
/*
A list container is a doubly linked list that enables bidirectional access,
fast insertions, and fast deletions anywhere in the container, but you cannot randomly access an element in the container.
*/

typedef std::string error;
class Exeption {
	error txt;
public:
	Exeption(error err)
		: txt(err) {};
	error& getError() { return this->txt; };
};



class NodeList {	//node base type List
private:
	struct Node {	//nested struct inside class
		int value;
		Node* next;
		Node* previous;
	};

public:
	class Iterator {	//nested class
		Node* v;	//pointer to node
		Iterator(Node* x);	//create from node
	public:
		int& operator*();	//dereferance operator that acces data stored
		bool operator==(const Iterator& p) const; //comparison operator to check if two iterators pointing/not poining to same object (not just value)
		bool operator!=(const Iterator& x) const;	//to same object (not just value)
		Iterator& operator++(); //move to next position and return referance to it
		Iterator operator++(int); 
		Iterator& operator--(); //move to previous position and return referance to it
		friend class NodeList; //only Node list can access private memers and create new operator
	};

private:
	Node* header;	//head of the list
	Node* trailer;	//tail of the list
	int n;	//node counter

public:
	NodeList();		//constructor
	NodeList(NodeList& L); 
	~NodeList();	//destructor
	int size() const;
	bool isEmpty() const;
	Iterator begin() const;	//beggining position
	Iterator end() const;		//position after last node
	void operator=(NodeList& L);
	void insertFront(const int& value);	//ivoke insert(begin(), value)
	void insertBack(const int& value);		//ivoke insert(end(), value)
	void insert(const Iterator& p, const int& value);	//insert Element before position p
	void eraseFront(); //ivoke erase(begin())
	void eraseBack(); //invoke erase(--end()), have to decrement to position bacwards one node
	void erase(const Iterator& p);	//remove element at position p
};


//LIST, access anywhere in the list
class SequenceList : public NodeList{
public:
	Iterator atIndex(int i) const;	//returns position from index i
	int indexOf(const Iterator& p) const;	//returns index int of Iterator(referance) p
};


/*BUBBLE SORT*/
//at the end of the ith pass, the right-most i elements of the sequence
//(that is, those at indices from n-1 down to n-i) are in final position.
/*
take sequence as parametar
efficent with arrays, not list
atIndex() is O(1) with array and O(n) with list
List O(n^3)
Array O(n^2)
*/
void bubbleSort1(SequenceList& S) {

	int n = S.size(); //take size of the list
	for (int i = 0; i < n; i++) {	//untill end of the list
		for (int j = 1; j < n - i; j++) {	//i-th pass
			SequenceList::Iterator predecessor = S.atIndex(j - 1);
			SequenceList::Iterator successor = S.atIndex(j);
			if (*predecessor > *successor) {
				//swap
				int temp = *predecessor;
				*predecessor = *successor;
				*successor = temp;
			}
		}
	}
}
/*
Sequence param
takes size of it
looping within list and swap elements if previousElement is higher then Element
O(n^2) worst case, with List
no return value
*/
void bubbleSort2(SequenceList& S) {

	int n = S.size();	//take size of the list
	for (int i = 0; i < n; i++) {	//i-th pass
		SequenceList::Iterator predecessor = S.begin(); //set precessor
		for (int j = 1; j < n - i; j++) {
			SequenceList::Iterator successor = predecessor;
			++successor; //move sucesor to next (now got S[i - 1] and S[i])
			if (*predecessor > *successor) {
				//swap
				int temp = *successor;
				*successor = *predecessor;
				*predecessor = temp;
			}
			++predecessor;	//set predecessor iterator to one next node
		}
	}
}
int main() {

	


	NodeList a; 
	a.insertBack(1);
	a.insertBack(2);
	
	NodeList b = a; 
	for (NodeList::Iterator p = b.begin(); p != b.end(); ++p) {
		std::cout << *p << " "; 
	}
	






	return 0;
}
/*Iterator methods declaration*/
NodeList::Iterator::Iterator(Node* u) {
	v = u;
}
int& NodeList::Iterator::operator*() {	//referance to the element
	return v->value;
}

bool NodeList::Iterator::operator==(const Iterator& p) const {	//compare positions
	return (v == p.v);
}
bool NodeList::Iterator::operator!=(const Iterator& p) const {
	return (v != p.v);
}
NodeList::Iterator& NodeList::Iterator::operator++() {	//prefix increment
	v = v->next;	//move to next position
	return *this;
}
NodeList::Iterator NodeList::Iterator::operator++(int) {	//postfix increment
	NodeList::Iterator old = *this;
	++(*this);
	return old;
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
//copy constructor
NodeList::NodeList(NodeList& L) {
	n = 0;	//0 nods in the list
	header = new Node;	//alocate node to node pointer
	trailer = new Node;
	header->next = trailer; header->previous = NULL; //set up links
	trailer->previous = header; trailer->next = NULL;

	for (NodeList::Iterator p = L.begin(); p != L.end(); ++p) {
		insertBack(*p);
	}
}
NodeList::~NodeList() {
	while (!isEmpty()) {
		eraseFront(); 
	}
	delete header; 
	delete trailer; 
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
void NodeList::operator=(NodeList& L) {
	if (!L.isEmpty()) {
		for (NodeList::Iterator p = L.begin(); p != L.end(); ++p) { //traverse untill end
			insertBack(*p);	//insert at back of the list
		}
	}
}
void NodeList::insertFront(const int& value) {
	return insert(begin(), value);
}

void NodeList::insertBack(const int& value) {
	return insert(end(), value);
}
/*
2 params
position and value
insert newNode before p
increment n by 1
no return value
*/

void NodeList::insert(const Iterator& p, const int& value) {	//insert element before p
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
	SequenceList::Iterator p = begin();	//set iterator to header
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
int SequenceList::indexOf(const SequenceList::Iterator& p) const {
	SequenceList::Iterator x = begin();	//set iterator to header
	int i = 0;
	while (x != p) {	//traverse untill x is diferent of p and count evry hop
		++x;
		i++;
	}
	return i; //return number of hops
}
