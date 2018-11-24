#include "pch.h"
#pragma warning( disable : 4290 )  //https://msdn.microsoft.com/en-us/library/sa28fef8.aspx
#include <iostream>
#include <string>
#include <vector>

/*
Implement a program that can input an expression in postfix notation and output its value.
*/


typedef std::string error;
class Exeption {
	error txt;
public:
	Exeption(error err)
		: txt(err) {};
	error& getError() { return this->txt; };
};


class Stack {
	int n;  
	int* expresion; 
	int limit; 
public:
	Stack(int max = 100)
		:n(-1), expresion(new int[max]), limit(max - 1) {};
	const int& peek() const;
	int size() const; 
	bool isEmpty() const;  
	void push(const int& x);
	void pop() throw(Exeption);
};

void evaluate(Stack& a, char op) {
	int x, y, result;
	x = a.peek(); a.pop(); 
	y = a.peek(); a.pop(); 
	switch (op) {
	case '+':
		result = y + x; 
		break;
	case '-':
		result = y - x;
		break;
	case '/':
		result = y / x;
		break;
	case '*':
		result = y * x;
		break;
	}
	a.push(result); 
}
int main()
{
	
	Stack a;
	std::string expresion; 
	int i = 0; 

	std::cout << "Enter postFix expression \n"; 
	std::cin >> expresion; 

	while (expresion[i] != '\0') {
		if (expresion[i] >= '0' && expresion[i] <= '9') {
			a.push(int(expresion[i]) - 48); 
		}
		else if (expresion[i] == '-') {
			evaluate(a, '-'); 
		}
		else if (expresion[i] == '+') {
			evaluate(a, '+');
		}
		else if (expresion[i] == '/') {
			evaluate(a, '/');
		}
		else if (expresion[i] == '*') {
			evaluate(a, '*');
		}
		i++;
	}

	std::cout << a.peek() << " : resultat"; 


	return 0;
}
const int& Stack::peek() const {
	return expresion[n];
}
int Stack::size() const {
	return n;
}
bool Stack::isEmpty() const {
	return (n < 0);
}
void Stack::push(const int& x) {
	try {
		if (size() < limit) {
			n++;
			expresion[n] = x;
			return;
		}
		throw Exeption("Stack overflow");
	}
	catch (Exeption& err) {
		std::cout << err.getError();
	}
}
void Stack::pop() throw(Exeption) {
	try {
		if (!isEmpty()) {
			n--;
			return;
		}
		throw Exeption("Stack undeflow");
	}
	catch (Exeption& err) {
		std::cout << err.getError();
	}
}

