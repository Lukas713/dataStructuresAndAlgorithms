#include "pch.h"
#include <iostream>
#include <string>
#include <vector>

typedef std::string error;
class Exeption {
	error txt;
public:
	Exeption(const std::string& err)
		: txt(err) {};
	std::string getError() const {
		return this->txt;
	}
};

template <typename O> class LinkedList;
template <typename O>
class Node {
public:
	O value;
	Node<O>* next;
	friend class LinkedList<O>;
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
	O penultimate(); //find second highest in linked list (need to ave list with integers)
	Node<O>* getHead() { return this->head; }
	void concatenate(Node<O>* y);
	void reverse(); // algorithm for reversing a singly linked list 
	int count(const Node<O>* hd); //recursive algorithm that counts the number of nodes in a singly linked list
};

int main()
{
	int choice;
	std::string txt;
	int number; 

	LinkedList<std::string> list; //LinkedList<int> list if want integers 
	while (1) {
		std::cout << std::endl;
		std::cout << "***************************************************" << std::endl;
		std::cout << "Linked List basic operation" << std::endl;
		std::cout << "***************************************************" << std::endl;
		std::cout << "1. Add front" << std::endl;
		std::cout << "2. Remove front" << std::endl;
		std::cout << "3. Display" << std::endl;
		std::cout << "4. Second largest element" << std::endl;
		std::cout << "5. Reverse" << std::endl;
		std::cout << "6. Count elements" << std::endl;
		std::cout << "0. Exit" << std::endl;
		std::cout << "enter option: ";
		std::cin >> choice;
		switch (choice) {
		case 1:
			std::cout << "Enter text" << std::endl;
			std::cin >> txt;
			list.addFront(txt);
			break;
		case 2:
			list.removeFront();
			break;
		case 3:
			list.display();
			break;
		case 4:
			std::cout << list.penultimate();
			break;
		case 5:
			list.reverse();
			break;
		case 6:
			number = list.count(list.getHead()); 
			std::cout << number << " elements in list"; 
			break;
		case 0:
			exit(1);
			break;
		}
	}
	return 0;
}
template <typename O>
LinkedList<O>::~LinkedList() {
	while (!isEmpty()) {
		removeFront();
	}
}

template <typename O>
bool LinkedList<O>::isEmpty() const {
	return (head == NULL); 
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
	try {
		if (!isEmpty()) {
			Node<O>* newNode = head;
			head = head->next;
			delete newNode;
		}
		throw Exeption("List is empty!");
	}
	catch (Exeption& err) {
		std::cout << err.getError() << "\n";
	}
}

template <typename O>
void LinkedList<O>::display() {
	try {
		if (!isEmpty()) {
			Node<O>* temp = head;
			while (temp != NULL) {
				std::cout << temp->value << " ";
				temp = temp->next;
			}
			return;
		}
		throw Exeption("List is empty!");
	}
	catch (Exeption& err) {
		std::cout << err.getError() << "\n";
	}
}
/*
Give an algorithm for finding the penultimate (second to last) node in a
singly linked list where the last element is indicated by a null next link.
*/
template <typename O>
O LinkedList<O>::penultimate() {

	Node<O>* temp = head;
	Node<O>* max = head;
	Node<O>* secondMax = max->next;

	while (temp != NULL) {
		if (max->value < temp->value) {
			secondMax = max;
			max = temp;
		}
		if (max->value > temp->value && secondMax->value < temp->value) {
			secondMax = temp;
		}
		temp = temp->next;
	}
	return secondMax->value;
}
/*
Describe a good algorithm for concatenating two singly linked lists L and
M, with header sentinels, into a single list L'that contains all the nodes of L
followed by all the nodes of M.
*/
template <typename O>
void LinkedList<O>::concatenate(Node<O>* y) {
	Node<O>* temp = head; //creates Node pointer
	while (temp->next != NULL) {
		temp = temp->next; //traverse untill end of the list
	}
	temp->next = y; //set last's link to first of second list
}
/*
Describe algorithm for reversing a singly linked list L, so
that the ordering of the nodes becomes opposite of what it was before.
*/
template <typename O>
void LinkedList<O>::reverse() {
	Node<O>* current = head; //set current node pointer to head node
	Node<O>* previous = NULL, *next = NULL;	//init two node pointers to null

	while (current != NULL) {	//untill end of the list
		next = current->next;	//next of current 
		current->next = previous;	//change he's next to previous 
		previous = current;		//move previous pointer to current so step above coud work propertly
		current = next;		//change to next node
	}
	head = previous; //change head to new begining
}
/*
Recursive algorithm that counts the number of nodes in a singly
linked list
*/
template <typename O>
int LinkedList<O>::count(const Node<O>* hd) {
	if (hd != NULL) {
		return count(hd->next) + 1; 
	}

	return 0; 
}


