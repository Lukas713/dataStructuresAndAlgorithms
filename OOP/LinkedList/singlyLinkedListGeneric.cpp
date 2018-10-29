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

template <typename O> class LinkedList;
template <typename O>
class Node {
private:
	O value;
	Node<O>* next;

	LinkedList<O> list;
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
	void display();
};


int main()
{
	int choice;
	std::string txt;

	LinkedList<std::string> list; //LinkedList<int> list if want integers 
	while (1) {
		std::cout << "***************************************************" << std::endl;
		std::cout << "Linked List basic operation" << std::endl;
		std::cout << "***************************************************" << std::endl;
		std::cout << "1. Add front" << std::endl;
		std::cout << "2. Remove front" << std::endl;
		std::cout << "0. Exit" << std::endl;
		std::cout << "enter option: ";
		std::cin >> choice;
		try {
			switch (choice) {
			case 1:
				std::cout << "Enter text" << std::endl;
				std::cin >> txt;
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
			std::cout << err.getError();
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
		return false;

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
void LinkedList<O>::display() {
	while (!head) {
		std::cout << head->value << " ";
		head = head->next;
	}
}
