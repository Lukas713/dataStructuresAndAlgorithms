#include <iostream>
#include <cstdlib>


using namespace std;

struct Node {
	int data;
	Node* next;
};

class QueueList {
	
	private:
		Node* front;
		Node* rear;
		
	public:
		QueueList();
		
		void enQueue(int data);
		
		void deQueue();

		void traverse();
		
		void countNodes();
};

int main() {
	
	QueueList a;
	int x, choice ;
	
	while(1) {
		
		cout << "Queue operations" << endl;
		cout << "---------------------------" << endl;
		cout << "1. Add element" << endl;
		cout << "2. Remove Element" << endl;
		cout << "3. Display whole list" << endl;
		cout << "5. Count nodes" << endl;
		cout << "4. Exit" << endl;
		cout << "Enter number" << endl;
		cin >> choice;
		switch(choice) {
			case 1:
				cout << "Enter value: " << endl;
				cin >> x;
				a.enQueue(x);
				break;
			
			case 2:
				a.deQueue();
				break;
				
			case 3: 
				a.traverse();
				break;
				
			case 5: 
				a.countNodes();
				break;
			
			case 4:
				exit(1);
				break;
				
			default:
				cout << "Wrong option!" << endl;
				break;
		}
	}
	return 0 ;
}
//ququq initialization
QueueList::QueueList() {
	
	front = NULL;
	rear = NULL;
}
//add element at front of the list		
void QueueList::enQueue(int data) {
	
	Node* temp = new Node;
	temp->data = data;
	temp->next = NULL;
	if(front == NULL) {
		front = temp;
		rear = temp;
		rear->next = NULL;
	}else {
		rear->next = temp;
		rear = temp;
		temp->next = NULL;	
	}
}
//remove elemet from front of the list
void QueueList::deQueue() {
	
	if(!front){
		cout << "List is empty" << endl;
		return;
	}
	Node* temp = new Node;
	temp = front;
	front = temp->next;
	delete temp;
	cout << "Element deleted" << endl;
	return;
}
//display every element
void QueueList::traverse() {
	
	Node* temp = new Node;
	temp = front;
	
	cout << "front ---> " ;
	while(temp){
		cout << temp->data << " ---> " ;
		temp = temp->next;
	}
	
	cout << " rear" << endl;	
}

void QueueList::countNodes() {
	
	Node* temp = new Node;
	int counter = 0;
	temp = front;
	while(temp) {
		temp = temp->next;
		counter++ ;
	}
	cout << counter << " nodes" << endl;
}
