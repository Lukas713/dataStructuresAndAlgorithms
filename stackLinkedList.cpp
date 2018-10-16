#include <iostream>

using namespace std;

struct Node{
	int data;
	Node* next;
};

class StackList{
	
	private:
		Node* top;
		
	public:
		StackList() { //constructor
			top = NULL;
		}
		
		Node* peek();
		
		void push(int data);
		
		void pop();
		
		void display();
		
		bool isEmpty(Node* top);	
};

int main() {
	
	StackList a;
	int x, choice;
	
	while(1){
		cout << "******************" << endl;
		cout << "Stack operations" << endl;
		cout << "******************" << endl;
		cout << "1. Push element" << endl;
		cout << "2. Pop element" << endl;
		cout << "3. Display list" << endl;
		cout << "0. Exit" << endl;
		cout << "Enter option: ";
		cin >> choice;
		
		switch(choice){
			
			case 1:
				cout << "Input value" << endl;
				cin >> x ;
				a.push(x);
				break;
			
			case 2:
				a.pop();
				break;
				
			case 3:
				a.display();
				break;
				
			case 0:
				exit(1);
				break;
				
			default:
				cout << "Wrong option!" << endl;
				break;	
		}
	}

	return 0 ;
}
Node* StackList::peek() {	//returns top element
		return top;
	}
		
void StackList::push(int data) {
	
	Node* temp = new Node;
	temp->data = data;
	
	if(!top){ //if top is NULL
		temp->next = top;
		top = temp;
		return;
	}
	temp->next = top;
	top = temp;
	return;
}
		
void StackList::pop() {
	
	Node* temp = new Node;
	temp = top;
	top = top->next;
	delete temp;
	cout << "element poped" << endl;
	return;	
}
		
void StackList::display(){
	
	Node* temp = new Node;
	temp = top;
	while(temp != NULL){
		cout << temp->data << endl;
		temp = temp->next;
	}
	return;
}
		
bool StackList::isEmpty(Node* top){
	if(!top){ //if list is empty
		return true;
	}
	return false;
}	
