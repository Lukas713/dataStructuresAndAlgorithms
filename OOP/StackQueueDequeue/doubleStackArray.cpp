#include "pch.h"
#pragma warning( disable : 4290 )  //https://msdn.microsoft.com/en-us/library/sa28fef8.aspx
#include <iostream>
#include <string>
#include <vector>
/*
Design an ADT for a two-color, double-stack ADT that consists of two
stacks—one “red” and one “blue”—and has as its operations color-coded
versions of the regular stack ADT operations. For example, this ADT
should allow for both a red push operation and a blue push operation.
Give an efficient implementation of this ADT using a single array whose
capacity is set at some value N that is assumed to always be larger than
the sizes of the red and blue stacks combined
*/
#include "pch.h"
#pragma warning( disable : 4290 )  //https://msdn.microsoft.com/en-us/library/sa28fef8.aspx
#include <iostream>
#include <string>
#include <vector>

/*
Queue ircuar implementation
*/
typedef std::string error;
class Exeption {
	error txt;
public:
	Exeption(error err)
		: txt(err) {};
	error& getError() { return this->txt; };
};

template <typename T>
class Stack {
	int limit; //max numbers
	int n;	//counter of elements
	int red;	//counter for red
	int blue;	//counter for blue
	T* field;	//array

public:
	Stack(int max = 10)
		:limit(max), red(0), blue(limit-1), n(0), field(new T[max]) {};
	int size() const;	//return number of elements
	bool isEmpty() const; //chec if list is empty
	const T& peekRed() const;	//top of red stack
	const T& peekBlue() const;	//top of blue stack
	void pushRed(const T& value);	//push on red stack
	void pushBlue(const T& value);	//push on blue stack
	void popRed() throw(Exeption);	//remove from red stack if there is elements
	void popBlue() throw(Exeption);		//remove from blue stack if there is elements
};
template <typename T>
void menu();
int main()
{

	
	menu<int>(); 










	return 0;
}
template <typename T>
int Stack<T>::size() const {
	return n;
}
template <typename T>
bool Stack<T>::isEmpty() const {
	return (n == 0);
}
template <typename T>
const T& Stack<T>::peekRed() const {
	try {
		if (!isEmpty()) {
			return field[red];
		}
		throw Exeption("Red stack is empty!");
	}
	catch (Exeption& err) {
		std::cout << err.getError() << "\n";
	}
}
template <typename T>
const T& Stack<T>::peekBlue() const {
	try {
		if (!isEmpty()) {
			return field[blue];
		}
		throw Exeption("Red stack is empty!");
	}
	catch (Exeption& err) {
		std::cout << err.getError() << "\n";
	}
}
template <typename T>
void Stack<T>::pushRed(const T& value) {	//red stack goes from start to end of array
	try {
		if (size() < limit) {
			field[red] = value;
			red++;
			n++;
			return;
		}
		throw Exeption("Stack overflow!");
	}
	catch (Exeption& err) {
		std::cout << err.getError() << "\n";
	}
}
template <typename T>
void Stack<T>::pushBlue(const T& value) {	//blue stacks goes from end to start
	try {
		if (size() < limit) {
			field[blue] = value;
			blue--;
			n++;
			return;
		}
		throw Exeption("Stack overflow!");
	}
	catch (Exeption& err) {
		std::cout << err.getError() << "\n";
	}
}
template <typename T>
void Stack<T>::popBlue() throw(Exeption) {
	try {
		if (!isEmpty() && blue < limit - 1) {
			blue++;
			n--;
			return;
		}
		throw Exeption("Blue stack underflow!");
	}
	catch (Exeption& err) {
		std::cout << err.getError() << "\n";
	}
}
template <typename T>
void Stack<T>::popRed() throw(Exeption) {
	try {
		if (!isEmpty() && red > 0) {
			red--;
			n--;
			return;
		}
		throw Exeption("Red stack underflow!");
	}
	catch (Exeption& err) {
		std::cout << err.getError() << "\n";
	}
}

/*Program menu*/
template <typename T>
void menu() {

	int max, choice, n;
	std::cout << "**************************************** \n";
	std::cout << "Double stack operations \n";
	std::cout << "**************************************** \n";
	std::cout << "Enter max elements: ";
	std::cin >> max;
	Stack<int> S(max);

	while (1) {
		std::cout << "1. Push red \n";
		std::cout << "2. Push blue \n";
		std::cout << "3. Peek red \n";
		std::cout << "4. Peek blue \n";
		std::cout << "5. Size of stack \n";
		std::cout << "6. Pop red \n";
		std::cout << "7. Pop blue \n";
		std::cout << "0. Exit \n";
		std::cout << "Enter option: ";
		std::cin >> choice;
		switch (choice) {
		case 1:
			std::cout << "Enter value: ";
			std::cin >> n;
			S.pushRed(n); 
			break;
		case 2:
			std::cout << "Enter value: ";
			std::cin >> n;
			S.pushBlue(n);
			break;
		case 3:
			std::cout << S.peekRed() << "\n";
			break;
		case 4:
			std::cout << S.peekBlue() << "\n";
			break;
		case 5:
			std::cout << S.size() << "\n";
			break;
		case 6:
			S.popRed(); 
			break;
		case 7:
			S.popBlue();
			break;
		case 0:
			exit(1);
			break;
		default:
			std::cout << "Wrong option! \n"; 
		}
	}
}
