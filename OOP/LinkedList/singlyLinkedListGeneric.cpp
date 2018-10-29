#include "pch.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std; 

class Exeption {
private:
	string error;
public:
	Exeption(const string& err)
		: error(err) {}; 
	string getError() const {
		return this->error; 
	}
};

class ListExeption : public Exeption {
public:
	ListExeption(const string& err)
		:Exeption(err) {}; 
};


template <typename O>
class Node {
private:
	O value; 
	Node<O>* next; 

	friend class LinkedList<typename O>; 
};

template <typename O>
class LinkedList {
private:
	Node<O>* head; 

public:
	LinkedList()
		:head(NULL) {}; 
	~LinkedList();
	bool isEmpty() const;
	O& front() const;
	void addFront(const O& value);
	void removeFront(); 
	void display() const; 
};
int main()
{
	int choice;
	string txt;

	LinkedList<string> list; //LinkedList<int> list if want integers 
	while (1) {
		cout << endl;
		cout << "***************************************************" << endl;
		cout << "Linked List basic operation" << endl;
		cout << "***************************************************" << endl;
		cout << "1. Add front" << endl;
		cout << "2. Remove front" << endl;
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
	
	return 0; 
}
template <typename O>
LinkedList<O>::~LinkedList() {
	while (!isEmpty()) {
		removeFront();
	}
	return;
}

template <typename O>
bool LinkedList<O>::isEmpty() const {
	if (head != NULL)
		return false
		return true;
}

template <typename O>
O& LinkedList<O>::front() const {
	return head->value;
}

template <typename O>
void LinkedList<O>::addFront(const O& value) {
	Node<O>* newNode = new Node<O>;
	newNode->value = value;
	newNode->next = head;
	head = newNode;
}

template <typename O>
void LinkedList<O>::removeFront() {
	Node<O>* newNode = head;
	head = head->next;
	delete newNode;
}

template <typename O>
void LinkedList<O>::display() const {
	while (!head) {
		cout << head->value << " ";
		head = head->next;
	}
}
