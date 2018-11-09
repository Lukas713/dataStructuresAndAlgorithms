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

typedef std::string user;
class Node {
	user nickname;
	double points;
	Node* next;
	friend class Scores;
};

class Scores {
	Node* head;
	int limit;
	int counter;
public:
	Scores()
		:head(NULL), limit(10), counter(1) {
		menu(); 
	};
	virtual ~Scores(); 
	void add(const user, const double points);
	void print();
	void menu();
protected:
	Node* lastNode();
	void addFront(Node* newNode);
	void addAfter(Node* newNode);
	void removeBack();
	bool isFull() const;
	bool isEmpty() const;
	void removeFront(); 
};
int main()
{

	Scores list; 





	return 0;
}
Scores::~Scores() {	//destrutor
	while (!isEmpty()) {
		removeFront();
	}
	return;
}
bool Scores::isFull() const {
	if (counter != limit) {
		return false;
	}
	return true;
}
void Scores::addAfter(Node* newNode) {
	Node* temp = head;	//create pointer to head
	while (temp->points >= newNode->points) {	//find "perfect" spot
		if (temp->next == NULL || temp->next->points < newNode->points) {
			newNode->next = temp->next;
			temp->next = newNode;
			return;
		}
		temp = temp->next;	//traverse
	}
	//if first node is lower
	newNode->next = temp; 
	head = newNode;
	return; 
}
void Scores::addFront(Node* newNode) {	//add first node
	newNode->next = head;
	head = newNode;
	return;
}
Node* Scores::lastNode() {	//return lasst node of the list
	Node* temp = new Node;
	temp = head;
	while (temp->next != NULL)
		temp = temp->next;	//traverse untill last node
	return temp;
}
void Scores::print() {
	try {
		if (!isEmpty()) {
			Node* temp = new Node;
			temp = head;
			while (temp != NULL) {
				std::cout << temp->nickname << " : " << temp->points << std::endl;
				temp = temp->next;
			}
			delete temp;
			return;
		}
		throw Exeption("List is empty!"); 
	}
	catch (Exeption& err) {
		std::cout << err.getError() << "\n"; 
	}
}
void Scores::removeFront() {
	Node* temp = head;
	head = head->next;
	delete temp; 
	return; 
}
void Scores::removeBack() {
	Node* temp = new Node;
	temp = head;
	Node* prev = NULL;	
	while (temp != NULL) {	//traverse untill last node
		if (temp->next == NULL) {
			prev->next = NULL;
			std::cout << "removed " << temp->nickname << " : " << temp->points << "\n";
			delete temp;
			return;
		}
		prev = temp;
		temp = temp->next;
	}
}

void Scores::add(const user nickname, const double points) {
	//create new Node
	Node* newNode = new Node;
	newNode->nickname = nickname;
	newNode->points = points;
	if (head != NULL) {	//check if list is not empty
		if (isFull()) {	// if list is full
			if (points < lastNode()->points) {	//if last node points is higher than new node points
				std::cout << "You failed \n";
				return;
			}
			removeBack();
			addAfter(newNode);
			return;
		}
		counter++; //add counter one point
		addAfter(newNode);
		return;
	}
	return addFront(newNode);
}
void Scores::menu() {
	double points;
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
			add(nickname, points);
			break;
		case 2:
			print();
			break;
		case 0:
			exit(1);
			break;
		default:
			std::cout << "Wrong option!";
		}
	}
}
bool Scores::isEmpty() const {
	if (head != NULL) {
		return false;
	}
	return true;
}
