// testing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std; 

class Exeption {
	string error;
public:
	Exeption(string& err)
		: error(err) {}; 
	string getError() const {
		return this->error; 
	}
};

class ListExeption : public Exeption {
public:
	ListExeption(string err)
		: Exeption(err) {}; 
};


class Node {
	string name;
	Node* next;

	friend class SinglyLinkedList;	//can access private members
};

class SinglyLinkedList{

	Node* head;	//head of the list
public:
	SinglyLinkedList();
	~SinglyLinkedList();
	bool isEmpty() const;	//checks if list is empty
	const string& front() const;	//return first node
	void addFront(const string& o);	//add node to the front
	void removeFront();		//remove first node
	void display();
	int penultimate() //find second highest in linked list (need to ave list with integers)	 
};
int main()
{

	int choice;
	string txt; 

	SinglyLinkedList list; 
	while (1) {
		cout << endl;  
		cout << "***************************************************" << endl;
		cout << "Linked List basic operation" << endl;
		cout << "***************************************************" << endl;
		cout << "1. Add front" << endl;
		cout << "2. Remove front" << endl;
		cout << "3. Display" << endl; 
		cout << "0. Exit" << endl; 
		cout << "enter option: ";
		cin >> choice;
		try {
			switch (choice) {
			case 1:
				cout << "Enter text" << endl;
				cin >> txt;
				list.addFront(txt);
				break;
			case 2:
				if (!list.isEmpty()) {
					list.removeFront();
					break;
				}
				throw ListExeption("List is empty!");
				break; 
			case 3:
				list.display();
				break; 
			case 0:
				exit(1); 
				break; 
			}
		}
		catch (ListExeption& err) {
			cout << err.getError(); 
		}
	}
	
	return 0;
}
SinglyLinkedList::SinglyLinkedList()
	: head(NULL) {};
SinglyLinkedList::~SinglyLinkedList() {
	while (!isEmpty()) {
		removeFront();
	}
	return;
}
bool SinglyLinkedList::isEmpty() const {
	if (head != NULL) {
		return false;
	}
	return true;
}
const string& SinglyLinkedList::front() const {
	return head->name;
}
void SinglyLinkedList::addFront(const string& txt) {
	Node* newNode = new Node;	//create new node
	newNode->name = txt;	//set value
	newNode->next = head;	//next is head
	head = newNode;		//head is next (newNode is first)
}
void SinglyLinkedList::removeFront() {

	Node* oldNode = head;
	head = oldNode->next;
	delete oldNode;
}

void SinglyLinkedList::display() {

	while (head != NULL) {
		cout << head->name << " ";
		head = head->next;
	}
}
int LinkedList::penultimate() {
	
	Node* temp = head; 
	Node* max = head;
	Node* secondMax = max->next;

	while (temp != NULL) {
		if (max->number < temp->number) {
			secondMax = max; 
			max = temp;
		}
		if (max->number > temp->number && secondMax->number < temp->number) {
			secondMax = temp;
		}
		temp = temp->next;
	}
	
	return secondMax->number;
}
