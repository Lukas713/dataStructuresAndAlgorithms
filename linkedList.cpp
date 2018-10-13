#include <iostream>

using namespace std;

struct Node {
	int data;
	Node* next;
};

class List {
	
	private: 
		Node* head;
		Node* tail;

	public:
		void listInit();
		
		Node* getHead();
		
		Node* getTail();


		void createNode(int data);

		void createFirstNode(int data);
		
		void createLastNode(int data);
		
		void createAfter(int data, int flag);
			

		void deleteNode(Node* node);
		
		void deleteLastNode();

		void deleteNodeWithData(int data);
				

		static void displayRecursion(Node* head);
		
		static void concatenate(Node* a, Node* b);
		
		static int listLenght(Node* head);
		
		static int nodeOnPosition(Node* head, int position);
};

int main() {
	
	List a;
	a.listInit();
	a.createNode(1);
	a.createNode(2);
	a.createNode(3);
	a.createNode(4);
	a.createNode(5);			

	List::displayRecursion(a.getHead());
	
	return 0;
}
void List::listInit() {
	head = NULL;
	tail = NULL;
}
Node* List::getHead() {
	return head;
}
		
Node* List::getTail(){
	return tail;
}
//create node
void List::createNode(int data) {

	Node* temp = new Node;
	temp->data = data;
	temp->next = NULL;
	
	if(head == NULL){ //if list is empty
		head = temp;	
		tail = temp;	
	}else {
		tail->next = temp; 	
		tail = tail->next;
	}
}
//create first node in the list
void List::createFirstNode(int data) {
			
	Node* temp = new Node;	
	temp->data = data;
	
	if(head != NULL){
		temp->next = head;
		head = temp;	
	}else {
		temp->next = NULL;
		head = temp;
		tail = temp; 
	}
}
//create last node in the list		
void List::createLastNode(int data) {
			
	Node* last = new Node;
	last->data = data;
	last->next = NULL;
	
	if(head == NULL) {
		head = last;
		tail = last;
	}else{
		Node* temp = new Node;
		temp = head;
		while(temp->next != NULL){
			temp = temp->next; 
		}
		
		temp->next = last;
		tail = last;
	}
}
//create node after specific node
void List::createAfter(int data, int flag){
			
	Node* temp = new Node;
	temp = head;
	
	while(temp != NULL){
		if(temp->data == flag){
			Node* x = new Node;
			x->data = data;
			x->next = temp->next;
			temp->next = x;
			cout << "Succesfully added" << endl;
			return;
		}
		
		temp = temp->next;
	}
}

//delete first node
void List::deleteNode(Node* node) {
	Node* temp = new Node;
	temp = head;
	head = temp->next;
	delete temp;
}
//delete last node		
void List::deleteLastNode() {
			
	Node* temp = new Node;
	temp = head->next;
	Node* x = head;
	while(temp != NULL){
		if(temp->next == NULL){
			x->next = temp->next;
			delete temp;
			cout << "Succesfully deleted" << endl;
			return;
		}
		temp = temp->next;
		x = x->next;
		
	}
}
//delete specific node
void List::deleteNodeWithData(int data) {
	
	Node* prev = new Node;
	prev = head;
	
	if(prev == NULL){
		cout << "List is empty!" << endl;
		return;
	}else if(prev->data == data){
		head = prev->next;
		delete prev;
		cout << "Succesfully deleted number " << data << endl;
		return;
		
	}else {
		
		Node* current = new Node;
		current = head->next;
		while(current->next != NULL){
			current = current->next;
			prev = prev->next;
			if(current->data == data){
				prev->next = current->next;
				delete current;
				cout << "Succesfully deleted number " << data << endl;
				return;
			}
		}
	}
	cout << "Number " << data << " is not in the list." << endl;
}	
//display list with recursive funtion
void List::displayRecursion(Node* head) {
	
	if(head == NULL){
		cout << "NULL" << endl;
	}else {
		cout << head->data << endl;
		displayRecursion(head->next);
	}
}
//concatenate two lists
void List::concatenate(Node* a, Node* b) {
			
	if(a != NULL && b != NULL){
		if(a->next == NULL){
			a->next = b;
		}else {
			concatenate(a->next, b);
		}
	}else {
		cout << "Both nodes are null!"; 
	}
}	
//return list lenght
int List::listLenght(Node* head) {
	Node* temp = new Node;
	temp = head;
	int counter = 0;
	
	while(temp != NULL){
		counter ++ ;
		temp = temp->next;
	}
	return counter;
}
//return node position
int List::nodeOnPosition(Node* head, int position){
	
	Node* temp = new Node;
	temp = head;
	int counter = 0;
	
	while(temp != NULL){
		if(counter == position){
			return counter;
		}
		counter ++;
		temp = temp->next;
	}
	return 0;
}	


