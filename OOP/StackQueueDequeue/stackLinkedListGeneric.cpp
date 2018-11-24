#include "pch.h"
#pragma warning( disable : 4290 )  //https://msdn.microsoft.com/en-us/library/sa28fef8.aspx
#include <iostream>
#include <string>
#include <vector>
/*
Implementation of linked list with full generic stack
*/
typedef std::string error;
class Exeption {
	error txt;
public:
	Exeption(const error& err)
		: txt(err) {};
	error getError() {
		return this->txt;
	}
};


template <typename T> class LinkedList;
template <typename T>
class Node {
	T value; //typename value
	Node<T>* next;	//pointer to next node

	friend class LinkedList<T>; //LinkedList can access private members
};

template <typename T>
class LinkedList {
	Node<T>* head; //head node

public:
	LinkedList()	//constructor
		:head(NULL) {};
	bool isEmpty() const;	//check if list is empty
	const T& front() const;	//return front value
	void addFront(const T& value);	//add Node to front
	void removeFront() throw(Exeption);//remove first Node
};

template <typename T>
class Stack {
	int n; //current size of the list
	LinkedList<T> S;	//generic linked list type Elem (string)

public:
	Stack()	//init Linked list in stack, and number of items
		: S(), n(0) {};
	int size() const;	//return number of elements in list
	bool isEmpty() const;	//asks if list is totaly empty
	const T& top() const throw(Exeption);	//invoke S.front()
	void push(const T& newElement);	//ivoke S.addFront()
	void pop() throw(Exeption);		//invoke S.removeFront()
	void emptyRecursive(); //remove all elements recursively
};

template <typename T>
void menu(Stack<T>& stack);

int main()
{


	Stack<int> stack;
	menu(stack);










	return 0;
}
/*
Linked list methods declaration
*/
template <typename T>
bool LinkedList<T>::isEmpty() const {
	return (head == NULL);
}
template <typename T>
const T& LinkedList<T>::front() const {
	return head->value;
}
template <typename T>
void LinkedList<T>::addFront(const T& value) {
	Node<T>* newNode = new Node<T>; //create new nde
	newNode->value = value;	//set value
	newNode->next = head; //set pointer to next
	head = newNode; //set head pointer to points to newly created node
}
template <typename T>
void LinkedList<T>::removeFront() throw(Exeption) {
	try {
		if (!isEmpty()) {
			Node<T>* oldNode = head;
			head = head->next;
			delete oldNode;
			return;
		}
		throw Exeption("List is empty!");
	}
	catch (Exeption& err) {
		std::cout << err.getError() << "\n";
	}
}
/*
Stack methods declarations
*/
template <typename T>
int Stack<T>::size() const {
	return n;	//return size of the stack
}
template <typename T>
bool Stack<T>::isEmpty() const {
	return (n == 0); //check if number of items in stack is 0
}
template <typename T>
const T& Stack<T>::top() const throw(Exeption) {
	try {
		if (!isEmpty()) {
			return S.front(); 
		}
		throw Exeption("Stack is empty!"); 
	}
	catch (Exeption& err) {
		std::cout << err.getError() << "\n"; 
	}
}
template <typename T>
void Stack<T>::push(const T& value) {
	n++;
	S.addFront(value);
}
template <typename T>
void Stack<T>::pop() throw(Exeption) {
	try {
		if (!isEmpty()) {
			n--;
			S.removeFront();
			return;
		}
		throw Exeption("List is empty!");
	}
	catch (Exeption& err) {
		std::cout << err.getError() << "\n";
	}
}
//Give a recursive function for removing all the elements in a stack
template <typename T>
void Stack<T>::emptyRecursive() {
	if (n == 0) {
		return; 
	}
	pop(); 
	return emptyRecursive(); 
}
/*
Menu
*/
template <typename T>
void menu(Stack<T>& stack) {
	int choice;
	T value;

	while (1) {
		std::cout << "Stack operations \n";
		std::cout << "1. Push element \n";
		std::cout << "2. Pop element \n";
		std::cout << "3. Display top most element \n";
		std::cout << "4. Display filled size of stack \n";
		std::cout << "5. Remove all elements recursively \n";
		std::cout << "0. Exit \n";
		std::cout << "Enter option: ";
		std::cin >> choice;
		switch (choice) {
		case 1:
			std::cout << "Enter number: ";
			std::cin >> value;
			stack.push(value);
			break;
		case 2:
			stack.pop();
			break;
		case 3:
			std::cout << stack.top() << "\n";
			break;
		case 4:
			std::cout << stack.size() << "\n";
			break;
		case 5:
			 stack.emptyRecursive();
			break;
		case 0:
			exit(1);
			break;
		default:
			std::cout << "Wrong option! \n";
			break;
		}
	}
}
