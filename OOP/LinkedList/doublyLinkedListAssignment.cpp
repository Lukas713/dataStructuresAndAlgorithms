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
		:head(NULL), limit(10), counter(1) {};
	~Scores();
	void add(const user, const double points);
	void print();
protected:
	Node* lastNode();
	void addFront(Node* newNode);
	void addAfter(Node* newNode);
	void removeBack();
	bool isFull() const;
	bool isEmpty() const;
	void removeFront();
};
void menu(Scores& list);
int main()
{

	Scores list;
	menu(list);





	return 0;
}
Scores::~Scores() {	//destrutor
	while (!isEmpty()) {
		removeFront();
	}
}
bool Scores::isFull() const {
	if (counter != limit) {
		return false;
	}
	return true;
}
void Scores::addAfter(Node* newNode) {
	if (!isEmpty()) {
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
	std::cout << "List is empty! \n";
}
void Scores::addFront(Node* newNode) {	//add first node
	newNode->next = head;
	head = newNode;
}
Node* Scores::lastNode() {	//return last node of the list
	if (!isEmpty()) {
		Node* temp = head;
		while (temp->next != NULL)
			temp = temp->next;	//traverse untill last node
		return temp;
	}
	std::cout << "List is empty! \n";
	return head; 
}
void Scores::print() {
	if (!isEmpty()) {
		Node* temp = head;
		while (temp != NULL) {
			std::cout << temp->nickname << " : " << temp->points << std::endl;
			temp = temp->next;
		}
		return;
	}
	std::cout << "List is empty \n";
}
void Scores::removeFront() {
	if (!isEmpty()) {
		Node* temp = head;
		head = head->next;
		delete temp;
		return;
	}
	std::cout << "List is empty! \n";
}
void Scores::removeBack() {
	Node* temp = head;
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
				delete newNode;
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

bool Scores::isEmpty() const {
	if (head != NULL) {
		return false;
	}
	return true;
}

void menu(Scores& list) {
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
