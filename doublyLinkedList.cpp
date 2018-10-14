#include <iostream>

using namespace std;

struct Node {
	int data;
	Node* next;
	Node* prev;
};

class DoublyList {
	
	private:
		Node* head;
		Node* tail;
		
	public:
		void ListInit();
		
		void createNode(int data);
		
		void createNodeAtBeggining(int data);
		
		void createAtEnd(int data);
		
		void createNodeAfter(int data, int flag);
		
		
		void deleteNode(int data);
		
		void deleteFirstNode();
		
		void deleteLastNode();
		
		void deleteSpecificNode(int data);
		
		void display();
		

};

int main() {
	
	DoublyList a;
	a.ListInit();
	a.createNode(2);
	a.createNode(4);
	a.createNode(6);
	a.createNode(8);
	a.deleteSpecificNode(81);



	a.display();
	
	return 0;
}
//list initialization
void DoublyList::ListInit(){
	head = NULL;
	tail = NULL;
}
//create node
void DoublyList::createNode(int data){
			
	Node* temp = new Node;
	Node* x = new Node;
	temp->data = data;
	temp->next = NULL;
	
	if(head == NULL){
		head = temp;
		temp->prev = NULL;
		tail = temp;
	}else {
		
		x = head;
		while(x->next != NULL){
			x = x->next;
		}
		x->next = temp;
		temp->prev = x;
		tail = temp;	
	}
}

void DoublyList::display() {
	
	Node* temp = new Node;
	temp = head;
	while(temp != NULL){
		cout << temp->data << endl;
		temp = temp->next;
	}
}

void DoublyList::createNodeAtBeggining(int data) {
	
	Node* temp = new Node;
	temp->data = data;
	temp->next = head->next;
	temp->prev = NULL;
	head = temp;
	if(temp->next == NULL){
		tail = temp;
	}
	cout << "Node inserted!" << endl;
	return;
}

void DoublyList::createAtEnd(int data) {
	
	Node* temp = new Node;
	temp = head;
	
	if(temp == NULL){
		cout << "List is empty!" << endl;
		return;
	}
	
	while(temp->next != NULL){
		temp = temp->next;
	}
	Node* x = new Node;
	x->data = data;
	x->next = temp->next;
	temp->next = x;
	x->prev = temp;
	cout << "Node inserted!" << endl;
	return;
}

void DoublyList::createNodeAfter(int data, int flag) {
	
	Node* temp = new Node;
	
	temp = head;
	while(temp->next != NULL){
		
		if(temp->data == flag){
			Node* x = new Node;
			
			x->next = temp->next;
			temp->next = x;
			x->prev = temp;
			x->data = data;	
			cout << "Node inserted!" << endl;
			return;
		}
		temp = temp->next;
	}
}

void DoublyList::deleteNode(int data) {
	
	Node* temp = new Node;
	
	temp = head;
	while(temp != NULL){
		
		if(temp->data == data){
			Node* next = new Node;
			Node* previous = new Node;
			
			next = temp->next;
			previous = temp->prev;
			if(next != NULL){
				next->prev = previous;
				previous->next = next;
				delete temp;
				cout << "Node deleted!" << endl;
				return;
			}
			previous->next = next;
			delete temp;
			cout << "Node deleted!" << endl;
			return;
		}
			
		temp = temp->next;
	}		
}

void DoublyList::deleteFirstNode() {
	
	Node* temp = new Node;
	Node* x = new Node;
	
	temp = head;
	if(temp == NULL){
		cout << "List is empty!" << endl;
		return;
	}
	head = temp->next;
	x = temp->next;
	x->prev = NULL;
	delete temp;
	cout << "first Node deleted!" << endl;
	return;
}

void DoublyList::deleteLastNode() {
	
	Node* temp = new Node;
	temp = head;
	if(temp != NULL){
		while(temp->next != NULL){
			temp = temp->next;
		}
		Node* x = new Node;
		x = temp->prev;
		x->next = temp->next;
		delete temp;
		cout << "Last node deleted!" << endl;
		return;
	}
	cout << "List is empty!" << endl;
	return;
}

void DoublyList::deleteSpecificNode(int data) {
			
	Node* temp = new Node;
	Node* next = new Node;

	
	temp = head;
	if(temp == NULL){
		cout << "List is empty!" << endl;
		return;
		
	}else if(temp->data == data){
		next = temp->next;
		next->prev = NULL;
		head = next;
		delete temp;
		cout << "Node deleted" << endl;
		return;
	}
		
	
	while(temp != NULL){
		
		if(temp->data == data){
			Node* previous = new Node;
			next = temp->next;
			previous = temp->prev;
			if(next == NULL){
				previous->next = NULL;
				delete temp;
				cout << "Node is deleted" << endl;
				return;
			}else {
				next->prev = previous;
				previous->next = next;
				delete temp;
				cout << "Node is deleted" << endl;
				return;	
			}	
		}
		temp = temp->next;
	}
	
	cout << "Node is not in the list" << endl;
	return;
}


