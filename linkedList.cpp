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
		
		void deleteNode(Node* node) {
			Node* temp = new Node;
			temp = head;
			head = temp->next;
			delete temp;
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
		
		void deleteFromPosition(int data) {
	
			Node* prev = new Node;
			prev = head;
			
			if(prev == NULL){
				cout << "List is empty!" << endl;
				return;
			}else {
				
				Node* current = new Node;
				current = head->next;
				while(current->next != NULL){
					if(prev->data == data){ //if previus node is right one (delete him)
						head = current;
						delete prev;
						return;
					}else if(current->data == data){
						prev->next = current->next;
						delete current;
						cout << "Succesfully deleted " << data << endl; 
						return;
					}
					prev = prev->next;
					current = current->next;
				}
				
				if(current->next == NULL && current->data == data) { 
				
					prev->next = current->next;
					delete current;
					cout << "Succesfully deleted " << data << endl; 
					return;
				}else {
					cout << "Number is not in the list!" << endl;
				}
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
		
		void createNodeAfter(int limit, int data) {
			
			Node* temp = new Node;
			temp->data = data;
			Node* counter = new Node;
			counter = head;
			if(counter == NULL){
				
				cout << "List is empty!" << endl;
			}else {
				
				while(counter->data != limit && counter->next != NULL){
					counter = counter->next;
					
					if(counter->data == limit) {
						
						temp->next = counter->next;
						counter->next = temp;		
					}
				}
			}
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
};

int main() {
	
	List a;
	a.listInit();
	
	a.createNode(5);
	a.createNode(10);
	a.createNode(11);
	a.createNode(12);
	a.createNode(13);
	a.createNode(14);
	a.createNode(15);
	a.createNode(16);					

	List::displayRecursion(a.getHead());
	
	return 0;
}
