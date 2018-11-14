#include "pch.h"
#pragma warning( disable : 4290 )  //https://msdn.microsoft.com/en-us/library/sa28fef8.aspx
#include <iostream>
#include <string>
#include <vector>

class Exeption {
	std::string error; 
public:
	Exeption(std::string err)
		:error(err) {}; 
	std::string getError() { return this->error; }
};

template <typename T>
class Stack {
	int N; //number of max elements	
	int counter;	//counter (-1 at start)
	T* item; //pointer to "that" type
public:
	Stack(int limit = 10);	//constructor, set max elements and counter
	int size() const; //return current size of array
	bool empty() const; //return if array is empty
	const T& top() const throw(Exeption); //return top'es element
	void push(const T& x) throw(Exeption);	//push item reference to stack
	void pop() throw(Exeption); //removes top'est element
};

template <typename T>	
void reverse(std::vector<T>& V){	//reverse vector elements
	Stack<T> S(V.size())); 	//create stack of size same as vector
	for(int i=0; i<V.size()); i++){	
		S.push(V[i]));	//push vector elements into stack
	}
	for(int i=0; i<V.size()); i++){
		V[i] = S.top();	//return top element from stack
		S.pop();	//pop element from stack
	}
}

template <typename T>
void menu(Stack<T>& stack);

int main()
{	
	
	int n; 
	std::cout << "Enter number of elements: "; 
	std::cin >> n; 
	Stack<int> stack(n); 
	menu(stack); 









	return 0;
}
/*
param int
init max elements
counter to -1
alocate N type elements as array
*/
template <typename T>
Stack<T>::Stack(int limit)
	: N(limit), counter(-1), item(new T[N]) {};
/*
no param
return number of elements
*/
template <typename T>
int Stack<T>::size() const {
	return (counter + 1);
}
/*
no param
return if list is empty
*/
template <typename T>
bool Stack<T>::empty() const {
	return (counter < 0);
}
/*
no param
return top elements
throw exeption if list is empty
*/
template <typename T>
const T& Stack<T>::top() const throw(Exeption){
	try {
		if (!empty()) {
			return item[counter];
		}
		throw Exeption("Stack is empty!");
	}
	catch (Exeption& err) {
		std::cout << err.getError() << "\n";
	}
}
/*
param const referece to element
check if element is full
add referance to stack
or throws exeption
*/
template <typename T>
void Stack<T>::push(const T& x) throw(Exeption){
	try {
		if (size() < N) {
			counter += 1;
			item[counter] = x;
			return;
		}
		throw Exeption("Stack is full!");
	}
	catch (Exeption& err) {
		std::cout << err.getError() << "\n";
	}
}
/*
no param
check if stack is empty
decrese counter by one (remove top element)
or throw exeption
*/
template <typename T>
void Stack<T>::pop() throw(Exeption){
	try {
		if (!empty()) {
			counter -= 1;
			std::cout << "element poped \n"; 
			return;
		}
		throw Exeption("Stack is empty!");
	}
	catch (Exeption& err) {
		std::cout << err.getError() << "\n";
	}
}

/*
Menu declaration
*/
template <typename T>
void menu(Stack<T>& stack) {

	int choice;
	T value;

	while (1) {
		std::cout << "Stack operations \n";
		std::cout << "1. Push element \n";
		std::cout << "2. Pop element \n";
		std::cout << "3. Display top most element \n";
		std::cout << "4. Display filled size of stack \n";
		std::cout << "0. Exit \n";
		std::cout << "Enter option: ";
		std::cin >> choice;
		switch (choice) {
		case 1:
			std::cout << "Enter number: ";
			std::cin >> value;
			stack.push(value);
			break;
		case 2:
			stack.pop();
			break;
		case 3:
			std::cout << stack.top() << "\n";
			break;
		case 4:
			std::cout << stack.size() << "\n";
			break;
		case 0:
			exit(1);
			break;
		default:
			std::cout << "Wrong option! \n";
			break;
		}
	}
}
