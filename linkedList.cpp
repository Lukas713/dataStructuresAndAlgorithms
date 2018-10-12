#include <iostream>

using namespace std;
//node struct
struct Node {
	int data;
	Node* next;
};

//creating class List
class List {
	
	private: 
		Node* head;
		Node* tail;

	public:
		void listInit() {
			head = NULL;
			tail = NULL;
		}
		
		Node* getHead(){
			return head;
		}
		
		Node* getTail(){
			return tail;
		}
		//CREATING NODES
		void createNode(int data) {

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

		void createFirstNode(int data) {
			
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
		
		void createLastNode(int data) {
			
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
		
		void createAfter(int data, int flag){
			
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
			

			

		//DELETE NODES
		void deleteNode(Node* node) {
			Node* temp = new Node;
			temp = head;
			head = temp->next;
			delete temp;
		}
		
		void deleteLastNode() {
			
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
		//delete node with data you choose
		void deleteNodeWithData(int data) {
	
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

		static void displayRecursion(Node* head) {
				if(head == NULL){
					cout << "NULL" << endl;
				}else {
					cout << head->data << endl;
					displayRecursion(head->next);
				}
			}
		
		static void concatenate(Node* a, Node* b) {
			
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
		
		static int listLenght(Node* head) {
			Node* temp = new Node;
			temp = head;
			int counter = 0;
			
			while(temp != NULL){
				counter ++ ;
				temp = temp->next;
			}
			
			return counter;
		}
		
		static int nodeOnPosition(Node* head, int position){
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
};

int main() {
	
	List a;
	a.listInit();
	a.createNode(1);
	a.createNode(2);
	a.createNode(3);
	a.createNode(4);
	a.createNode(5);			

	cout << a.nodeOnPosition(a.getHead(), 11);

	//List::displayRecursion(a.getHead());
	//List::nThNode(13);
	
	return 0;
}
