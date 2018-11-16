#include "pch.h"
#include <iostream>
#include <string>
#include <vector>


class Exeption {
private:
	std::string error;
public:
	Exeption(const std::string& err)
		: error(err) {};
	std::string getError() const {
		return this->error;
	}
};

class ListExeption : public Exeption {
public:
	ListExeption(const std::string& err)
		:Exeption(err) {};
};

typedef std::string value;
class Node {
	value txt;
	Node* next;

	friend class CircularLinkedList;
};

class CircularLinkedList {
private:
	Node* cursor;	//pointer to node that points to some node in the list
public:
	CircularLinkedList();
	~CircularLinkedList();
	bool isEmpty() const;
	value& front() const;
	value& back() const;
	void advance();		//move cursor to the next Node in the list
	void addNode(const value& txt);
	void removeNode();
	void display() const; 
};

int main()
{
	CircularLinkedList list;
	int choice;
	std::string txt;

	while (1) {
		std::cout << std::endl; 
		std::cout << "***************************************************" << std::endl;
		std::cout << "Circular Linked List basic operation" << std::endl;
		std::cout << "***************************************************" << std::endl;
		std::cout << "1. Add node" << std::endl;
		std::cout << "2. Remove front" << std::endl;
		std::cout << "3. Display" << std::endl;
		std::cout << "4. Return front" << std::endl;
		std::cout << "5. Return back" << std::endl;
		std::cout << "0. Exit" << std::endl;
		std::cout << "enter option: ";
		std::cin >> choice;

		switch (choice) {
		case 1:
			std::cout << "Enter text" << std::endl;
			std::cin >> txt;
			list.addNode(txt);
			break;
		case 2:
			list.removeNode();
			break;
		case 3:
			list.display();
			break;
		case 4:
			std::cout << list.front();
			break;
		case 5:
			std::cout << list.back();
			break;
		case 0:
			exit(1);
			break;
		}
	}

	return 0;
}

CircularLinkedList::CircularLinkedList()	//construtor sets cursor to NULL
	:cursor(NULL) {};
CircularLinkedList::~CircularLinkedList() {	//destructor removes nodes
	while (!isEmpty()) {
		removeNode();
	}
}
bool CircularLinkedList::isEmpty() const {	//checs if list is empty
	return (cursor == NULL); 
}
value& CircularLinkedList::back() const {	//returns cursor which points to back
	try {
		if (cursor != NULL) {
			return cursor->txt;
		}
		throw ListExeption("List is empty!");
	}
	catch (ListExeption& err) {
		std::cout << err.getError();	//have to fix this
	}
}
value& CircularLinkedList::front() const {	//return first 
	try {
		if (cursor != NULL) {
			return cursor->next->txt;
		}
		throw ListExeption("List is empty!");
	}
	catch (ListExeption& err) {
		std::cout << err.getError();	//have to fix this
	}
}
void CircularLinkedList::advance() {	//set cursor to next
	if (cursor != NULL) {	//checks if list is not empt
		cursor = cursor->next;
	}
}

void CircularLinkedList::addNode(const value& txt) {
	Node* newNode = new Node;
	newNode->txt = txt;
	if (cursor != NULL) {	//checks if list is not empty
		newNode->next = cursor->next;
		cursor->next = newNode;
		return;
	}
	newNode->next = newNode;
	cursor = newNode;
}
void CircularLinkedList::removeNode() {
	try {
		if (cursor != NULL) {	//checks if list is not empt
			Node* oldNode = cursor->next;
			if (oldNode != cursor) {	//if oldNode is not only Node in the list
				cursor->next = oldNode->next;
				delete oldNode;
				return;
			}
			cursor = NULL;
			delete oldNode;
			return;
		}
		throw ListExeption("List is empty!");
	}
	catch (ListExeption& err) {
		std::cout << err.getError();
	}
}

void CircularLinkedList::display() const {
	Node* temp = cursor;
	std::cout << temp->txt << " ";
	temp = temp->next;
	int counter = 1; 
	while (temp != cursor) {
		std::cout << temp->txt << " ";
		temp = temp->next;
		counter++; 
	}
	std::cout << "\n" << counter << " elements"; 
}
