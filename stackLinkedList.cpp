#include <iostream>
#include <cstdlib>

using namespace std;

struct Node {
	int data;
	Node* next;	
	
}*top;

class StackList {
	
	public:
		
		void stackInit() {
			top = NULL;
		}
		
		Node* push(Node* top, int data) {
			
			Node* temp = new Node;
			temp->data = data;
			temp->next = top;
			top = temp;
			return top;	
		} 
		
		void traverse(Node* top) {
			
			Node* temp = new Node;
			temp = top;
			if(temp == NULL){
				cout << "List is empty!" << endl;
				return;
			}else {
				while(temp != NULL){
					cout << temp->data << endl;
					temp = temp->next;
				}	
			}
		}	
		
		Node* pop(Node* top) {
			
			if(top == NULL){
				cout << "List is empty!" << endl;
			}else {
				Node* temp = new Node;
				temp = top;
				top = temp->next;
				cout << "Node with value " << temp->data << " is poped." << endl;
				delete temp;
			}
			return top;	
		}
};


int main() {
	
	StackList a;
	a.stackInit();
	int choice, x;
	
	while(1) {
		
        cout<<"Operations on Stack"<<endl;
        cout<<"-----------------------"<<endl;
        cout<<"1.Push Element into the Stack"<<endl;
        cout<<"2.Pop Element from the Stack"<<endl;
        cout<<"3.Traverse the Stack"<<endl;
        cout<<"4.Quit"<<endl;
        cout<<"Enter your Choice: ";
        cin>>choice;
        switch(choice) {
        	case 1:
        		cout << "Enter elements value" << endl;
        		cin >> x;
        		top = a.push(top, x);
        		break;
        	
        	case 2:
        		top = a.pop(top);
        		break;
        		
        	case 3:
        		a.traverse(top);
        		break;
        	
        	case 4:
        		exit(1);
        		break;
        		
        	default:
        		cout << "Wrong option" << endl;	
		}
	}
	return 0 ;
}
