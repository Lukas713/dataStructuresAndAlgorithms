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

//queue interface
template <typename T>
class Queue {

	int f; //front of queue
	int r;	//rear of queue
	int n;	//number of elements
	int limit;	
	T* Q; 

public:
	Queue(int max = 5)
		:f(0), r(0), n(0), limit(max), Q(new T[limit]) {};	//dinamicly alocate limit elements
	bool isEmpty() const;	//check if list is empty
	int size() const;		//return number of elements inside queue
	const T& front() const throw(Exeption);	//return referance to first element 
	void enqueue(const T& value);	//add element on rear
	void dequeue() throw(Exeption);		//remove front element 
};

template <typename T>
void menu();
int main()
{
 
	menu<int>(); //invoke menu of the program






	return 0;
}
template <typename T>
bool Queue<T>::isEmpty() const {
	return (n == 0);
}
template <typename T>
int Queue<T>::size() const {
	return n;
}
template <typename T>
const T& Queue<T>::front() const throw(Exeption) {
	return Q[f];
}
template <typename T>
void Queue<T>::enqueue(const T& value) {
	try {
		if (size() < limit) {
			Q[r] = value;	//insert new values
			r = (r + 1) % limit;	//set r to one more, if r = limit, it will become 0 (circular implementation)
			n++;
			return;
		}
		throw Exeption("Queue is full!");
	}
	catch (Exeption& err) {
		std::cout << err.getError() << "\n";
	}
}
template <typename T>
void Queue<T>::dequeue() throw(Exeption){
	try {
		if (!isEmpty()) {
			f = (f + 1) % limit;
			n--;
			std::cout << "Element deleted! \n";
			return;
		}
		throw Exeption("Queue is empty!");
	}
	catch (Exeption& err) {
		std::cout << err.getError() << "\n";
	}
}
/*Program menu*/
template <typename T>
void menu() {

	int max, choice, n;
	std::cout << "*************************** \n";
	std::cout << "Queue operations \n";
	std::cout << "*************************** \n";
	std::cout << "Enter max elements: ";
	std::cin >> max;
	Queue<int> Q(max);

	while (1) {
		std::cout << "1. Enqueue \n";
		std::cout << "2. Dequeue \n";
		std::cout << "3. Size of queue \n";
		std::cout << "4. Front element \n";
		std::cout << "0. Exit \n";
		std::cout << "Enter option: ";
		std::cin >> choice;
		switch (choice) {
		case 1:
			std::cout << "Enter value: ";
			std::cin >> n;
			Q.enqueue(n);
			break;
		case 2:
			Q.dequeue();
			break;
		case 3:
			std::cout << Q.size() << " elements \n";
			break;
		case 4:
			std::cout << Q.front() << "\n";
			break;
		case 0:
			exit(1);
			break;
		}
	}
}
