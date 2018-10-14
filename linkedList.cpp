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
		
		void update(int data, int flag);
		
		void reverse();
};

int main() {
	
	int choice, node, position, x, flag; 
	List a;
	a.listInit();
	a.createNode(5);
	a.createNode(6);
	a.createNode(7);
	a.createNode(8);
	a.createNode(9);


	a.reverse();
	a.displayRecursion(a.getHead());
	
	/*
	while(1) {
		cout << "-------------------------------------" << endl;
		cout << "Single link lit operations" << endl;
		cout << "-------------------------------------" << endl;
		cout << "1. Insert node at begining." << endl;
		cout << "2. Insert node at the end." << endl;
		cout << "3. Insert node after specific node." << endl;
		cout << "4. Delete first node." << endl;
		cout << "5. Delete last node." << endl;
		cout << "6. Delete node with specific data." << endl;
		cout << "7. Show list lenght." << endl;
		cout << "8. Show position of node with specific data." << endl;
		cout << "9. Concatenate two lists." << endl;
		cout << "10. Display" << endl;
		cout << "0. exit" << endl;
		cin >> choice ;
		
		switch(choice) {
			case 1:
				cout << "Insering node at begining: " << endl;
				cin >> x;
				a.createFirstNode(x);
				cout << endl;
				break;
				
			case 2:
				cout << "Inserting node at the end: " << endl;
				cin >> x;
				a.createLastNode(x);
				cout << endl;
				break;
				
			case 3:
				cout << "Inserting node after specific node: " << endl;
				cout << "Insert data for new node" << endl;
				cin >> node;
				cout << endl;
				cout << "Enter limit, after which node new node will fall into: " << endl;
				cin >> flag;
				cout << endl;
				a.createAfter(node, flag);
				break;
				
			case 4:
				cout << "Deleting firstnode: " << endl;
				a.deleteNode(a.getHead());
				break;
				
			case 5:
				cout << "Deleting last node: " << endl;
				a.deleteLastNode();
				break;
				
			case 6:
				cout << "Delete specific node: " << endl;
				cout << "Enter specific value that you wanna delete" << endl;
				cin >> node;
				a.deleteNodeWithData(node) ;
				break;
			
			case 7:
				cout << "List lenght: " << endl;
				cout << "List got" << a.listLenght(a.getHead()) << " elements" << endl;
				break;
			
			case 8:
				cout << "Specific node postiion:" << endl;
				cin >> position;
				cout << "Node is on position: " << a.nodeOnPosition(a.getHead(), position) << endl;
				break;
				
			case 9:
				cout << "Concatenate two lists: " << endl;
				break;
			
			case 10: 
				cout << "Display: " << endl;
				a.displayRecursion(a.getHead());
				break;
				
			case 11:
				cout << "Update element" < endl;
				cout << "Enet value that you wanna update" << endl;
				cin >> node;
				cout << "Enter new value" << endl;
				cin >> x;
				a.update(x, node);
				break;
				
			case 0:
				exit(1);
				break;
				
			default:
				cout << "Wrong choice" << endl;		
		}
	}*/
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

//update existing node
void List::update(int data, int flag){
			
	Node* temp = new Node;
	temp = head->next;
	
	while(temp != NULL){
		if(temp->data == flag){
			temp->data = data;
			cout << "Succesfully updated" << endl;
			return;
		}
		temp = temp->next;
	}		
}	

void List::reverse() {
	
	Node* current = new Node;
	Node* previous = new Node;
	Node* next = new Node;
	
	next = NULL;
	previous = NULL;
	current = head;
	
	while(current != NULL){
		
		next = current->next;
		current->next = previous;
		previous = current;
		current = next;
	}
	head = previous;
}


