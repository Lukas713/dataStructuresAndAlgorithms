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
		
		Node* getHead();
		
		Node* getTail();
		
		void createNode(int data);
		
		void createNodeAtBeggining(int data);
		
		void createAtEnd(int data);
		
		void createNodeAfter(int data, int flag);
		
		
		void deleteNode(int data);
		
		void deleteFirstNode();
		
		void deleteLastNode();
		
		
		void display();
		
		static void displayRecursion(Node* head);
		
		void reverseDoublyList();
};


int main() {
	
	int x, flag, choice ;
	
	DoublyList a;
	a.ListInit();
	
		while(1) {
			cout << "-------------------------------------" << endl;
			cout << "Doubly link list operations" << endl;
			cout << "-------------------------------------" << endl;
			cout << "1. Create node." << endl;
			cout << "2. Create node at begining." << endl;
			cout << "3. Create node at end." << endl;
			cout << "4. Create node after specific noe." << endl;
			cout << "5. Delete node." << endl;
			cout << "6. Delete first node." << endl;
			cout << "7. Delete last node." << endl;
			cout << "8. Display list." << endl;
			cout << "9. Display list with recursive function" << endl;
			cout << "10. Reverse list order" << endl;
			cout << "0. exit" << endl;
			cin >> choice ;
			
			switch(choice) {
				case 1:
					cout << "Inserting first node: " << endl;
					cin >> x;
					a.createNode(x);
					cout << endl;
					break;
					
				case 2:
					cout << "Inserting node at the begining: " << endl;
					cin >> x;
					a.createNodeAtBeggining(x);
					cout << endl;
					break;
					
				case 3:
					cout << "Inserting node at the end: " << endl;
					cout << "Insert data for new node" << endl;
					cin >> x;
					a.createAtEnd(x);
					cout << endl;
					break;
					
				case 4:
					cout << "Insert node after specific node: " << endl;
					cout << "Insert data" << endl;
					cin >> x;
					cout << endl;
					cout << "Insert limit node" << endl;
					cin >> flag;
					a.createNodeAfter(x, flag);
					break;
					
				case 5:
					cout << "Delete specifi node node: " << endl;
					cout << "Insert node you wish to delete" << endl;
					cin >> x;
					a.deleteNode(x);
					break;
					
				case 6:
					cout << "Delete first node: " << endl;
					a.deleteFirstNode();
					break;
				
				case 7:
					cout << "Delete last node: " << endl;
					a.deleteLastNode();
					break;
				
				case 8:
					cout << "List:" << endl;
					a.display();
					break;
					
				case 9:
					a.displayRecursion(a.getHead());
					break;
					cout << "Reversed list: " << endl;
	
				
				case 10: 
					a.reverseDoublyList();
					break;
					
				case 0:
					exit(1);
					break;
					
				default:
					cout << "Wrong choice" << endl;		
			}
		}




	
	return 0;
}


//list initialization
void DoublyList::ListInit(){
	head = NULL;
	tail = NULL;
}

Node* DoublyList::getHead() {
	return head;
}

Node* DoublyList::getTail() {
	return tail;
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
		cout << "List is empty" << endl;
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
	Node* next = new Node;
	temp = getHead();
	
	if(temp->data == data){
		next = temp->next;
		next->prev = NULL;
		head = next;
		delete temp;
		cout << "Node deleted!" << endl;
		return;	
	}
	
	while(temp != NULL){
		
		if(temp->data == data){
			Node* previous = new Node;
			next = temp->next;
			if(!next){
				previous = temp->prev;
				previous->next = NULL;
				delete temp;
				cout << "Node deleted" << endl;
				return;
			}
			previous = temp->prev;
			next->prev = previous;
			previous->next = next;
			head = previous;
			delete temp;
			cout << "Node deleted" << endl;	
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


void DoublyList::displayRecursion(Node* head) {
			
	if(head == NULL){
		cout << "NULL" << endl;
		return;	
	}
	
	cout << head->data <<  endl;
	displayRecursion(head->next);
}

void DoublyList::reverseDoublyList() {
			
	Node* current = new Node;
	Node* next = new Node;
	
	current = head;
	next = current->next;
	current->prev = next;
	current->next = NULL;
	
	while(next != NULL){
		next->prev = next->next;
		next->next = current;
		current = next;
		next = next->prev;
	}
	
	head = current;
	
	cout << "List is reversed" << endl;
	return;	
}

