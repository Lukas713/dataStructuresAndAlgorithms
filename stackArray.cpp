#include <iostream>
#include <string>

using namespace std;
#define MAX 10
int stack[MAX];
int top = -1;

	void push(int data){
		
		if(top == (MAX - 1)){
			cout << "List is full" << endl;
			return;
		}
		
		top ++;
		stack[top] = data;
		cout << "element pushed" << endl;
		return;
	}
	
	void pop() {
		
		if(top == -1){
			cout << "List is empty!" << endl;
			return;
		}
		
		top--;
		cout << "element " << stack[top] << " poped" << endl;
		return;
	}
	
	void display() {
		int i;
		for(i=top; i>=0; i--){
			cout << stack[i] << endl;
		}
		return;
	}

int main() {
	
	int x, choice;
	while(1) {
		cout << "**********************" << endl;
		cout << "Array stack operations" << endl;
		cout << "**********************" << endl;
		cout << "1. push element" << endl;
		cout << "2. pop element" << endl;
		cout << "3. display" << endl;
		cout << "0. exit" << endl;
		cout << "Enter option: " ;
		cin >> choice ;
		
		switch(choice) {
			
			case 1:
				cout << "Enter value" << endl;
				cin >> x;
				push(x);
				break;
			
			case 2:
				pop();
				break;
				
			case 3:
				display();
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
