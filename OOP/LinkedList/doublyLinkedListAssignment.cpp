#include "pch.h"
#include <iostream>
#include <string>
#include <vector>

typedef std::string error;
class Exeption {
	error txt;
public:
	Exeption(error err)
		:txt(err) {};
	error getError() const {
		return this->txt;
	}
};

typedef int highscore;
typedef std::string username;
class Node {
	highscore points;
	username name;
	Node* next;
	Node* previous;
	friend class Scores;
};

class Scores {
	Node* head;
	Node* tail;
	int limit;
	int counter;

public:
	Scores();
	//virtual ~Scores(); 
	void add(const username name, const highscore points); //invoke addAfter() || addFront()
	void print() const;	//traverse and print list
protected:
	bool isEmpty() const;	//checks if list is empty
	bool isFull() const;	//check if list is full	
	Node* lastNode();	//return last node
	void addFront(Node* newNode);	//add node on the begining
	void addAfter(Node* newNode);	//add node in perfect position
	void remove(Node* x) {
		Node* prevNode = x->previous; 
		Node* nextNode = x->next; 
		prevNode->next = nextNode;
		nextNode->previous = prevNode;
		delete x; 
	}
};

void menu(Scores& list);
int main()
{

	Scores list;
	menu(list); 




	return 0;
}
Scores::Scores()	//set limit, counter, head and tail
	: limit(10), counter(0) {	//set limit and init counter
	head = new Node;
	tail = new Node;
	head->next = tail;
	tail->previous = head;
}

bool Scores::isFull() const {
	if (counter != limit) {
		return false;
	}
	return true;
}

bool Scores::isEmpty() const {
	if (head->next != tail) {
		return false;
	}
	return true;
}

Node* Scores::lastNode() {
	return tail->previous;	//retur last node
}
void Scores::print() const{
	Node* temp = head->next;
	while (temp != tail) {	//traverse and cout node infos
		std::cout << temp->name << " : " << temp->points << "\n";
		temp = temp->next;
	}
}
void Scores::addAfter(Node* newNode) {
	Node* temp = head->next;	//set pointer to first node
	while (temp->points > newNode->points) {
		temp = temp->next;	//traverse until newNode->points are higher
	}
	newNode->next = temp->previous->next;	
	newNode->previous = temp->previous;
	temp->previous->next = newNode;
	temp->previous = newNode;
}
void Scores::add(const username name, const highscore points) {
	Node* newNode = new Node;	//create new node
	newNode->name = name;
	newNode->points = points;
	if (!isEmpty()) {	//list is not empty
		if (!isFull()) {	//list is not full
			counter++; 
			addAfter(newNode);	//add after specific position
			return;	
		}
		if (newNode->points <= lastNode()->points) {	//if list is full and last node points is higher then new node's points
			std::cout << "You failed! \n";
			delete newNode;
			return;
		}
		remove(tail->previous); 
		addAfter(newNode);	//if list is full, insert node into specific position
		return;
	}
	counter++;	//if list is empty
	addFront(newNode);	//insert node in the front of the list
}
void Scores::addFront(Node* newNode) {
	newNode->next = head->next;
	newNode->previous = head;
	head->next->previous = newNode;
	head->next = newNode;
	return;
}

void menu(Scores& list) {
	highscore points;
	int choice;
	std::string nickname;
	while (1) {
		std::cout << "\n------------------------------------------\n";
		std::cout << "Highscore list \n";
		std::cout << "------------------------------------------ \n";
		std::cout << "1. Add highscore \n";
		std::cout << "2. Print list \n";
		std::cout << "0. Exit \n";
		std::cout << "Enter option: ";
		std::cin >> choice;
		std::cout << "\n";
		switch (choice) {
		case 1:
			std::cout << "Enter nickname: ";
			std::cin >> nickname;
			std::cout << "Enter points: ";
			std::cin >> points;
			list.add(nickname, points);
			break;
		case 2:
			list.print();
			break;
		case 0:
			exit(1);
			break;
		default:
			std::cout << "Wrong option!";
		}
	}
}


