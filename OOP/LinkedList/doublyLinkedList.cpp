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
	Node* prev;
	Node* next;
	friend class DoublyLinkedList;
};

class DoublyLinkedList {

private:
	Node* head;
	Node* tail;
public:
	DoublyLinkedList();
	~DoublyLinkedList();
	value& front() const;
	value& back() const;
	bool isEmpty() const;
	void addFront(const value& txt);
	void addBack(const value& txt);
	void removeFront();
	void removeBack();
	void display() const;
protected:
	void addAfterX(Node* x, const value& o);
	void remove(Node* x);
};

int main()
{

	DoublyLinkedList list;
	int choice;
	std::string txt;



	while (1) {
		std::cout << "***************************************************" << std::endl;
		std::cout << "Linked List basic operation" << std::endl;
		std::cout << "***************************************************" << std::endl;
		std::cout << "1. Add front" << std::endl;
		std::cout << "2. Remove front" << std::endl;
		std::cout << "3. Display" << std::endl;
		std::cout << "4. Add Back" << std::endl;
		std::cout << "5. Remove back" << std::endl;
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


				break;
			case 3:
				list.display();
				break;
			case 4:
				std::cout << "Enter text" << std::endl;
				std::cin >> txt;
				list.addBack(txt);
				break;
			case 5:
				list.removeBack();
				break;
			case 0:
				exit(1);
				break;
			}
	}

	return 0;
}
DoublyLinkedList::DoublyLinkedList() {	//constructor
	head = new Node;
	tail = new Node;
	head->next = tail;	//set head referencing to tail
	tail->prev = head;	//set tail referencing to head
}
DoublyLinkedList::~DoublyLinkedList() {	//destructor
	while (!isEmpty()) {	//remove every node
		removeFront();
	}
	delete head;	//delete alocated head
	delete tail;	//delete alocated tail
}
bool DoublyLinkedList::isEmpty() const {
	if (head->next != tail) {	//is empty? 
		return false;
	}
	return true;
}
value& DoublyLinkedList::front() const {
	return head->next->txt;		//get head element
}
value& DoublyLinkedList::back() const {
	return tail->prev->txt;		//get tail element
}
//ADD nodes
void DoublyLinkedList::addAfterX(Node* x, const value& o) {	//add node after x
	Node* newNode = new Node;	//creaate new node
	newNode->txt = o;	//set text 
	newNode->next = x;	 //set next-> to x
	newNode->prev = x->prev; 		//set previus of newNode to x's previous
	x->prev->next = newNode;	//set next of node before new node to new node and x's previus to new node
	x->prev = newNode;
}
void DoublyLinkedList::addFront(const value& txt) {	//invoke addAfter and send head's next
	return addAfterX(head->next, txt);
}
void DoublyLinkedList::addBack(const value& txt) {	//invoke addAfter and send tail
	return addAfterX(tail, txt);
}
//DELETE nodes
void DoublyLinkedList::remove(Node* x) {
	Node* previousNode = x->prev;
	Node* nextNode = x->next;
	previousNode->next = nextNode;
	nextNode->prev = previousNode;
	delete x;
}
void DoublyLinkedList::removeFront() {	//invoke after head
	try{
		if (head->next != tail) {
			return remove(head->next);
		}
		throw ListExeption("List is empty!"); 
	}
	catch (ListExeption& err){
		std::cout << err.getError(); 
	}	
}
void DoublyLinkedList::removeBack() {	//invoke before last to remove last
	try {
		if (head->next != tail) {
			return remove(tail->prev);
		}
		throw ListExeption("List is empty!");
	}
	catch (ListExeption& err) {
		std::cout << err.getError();
	}
}
void DoublyLinkedList::display() const {
	try {
		if (head->next != tail) {
			Node* temp = head;
			while (temp != NULL) {
				std::cout << temp->txt << " ";
				temp = temp->next;
			}
			delete temp;
			return;
		}
		throw ListExeption("List is empty!"); 
	}
	catch (ListExeption& err) {
		std::cout << err.getError(); 
	}
	
}
