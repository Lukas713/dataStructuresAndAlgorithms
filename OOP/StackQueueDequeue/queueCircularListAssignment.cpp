#include "pch.h"
#pragma warning( disable : 4290 )  //https://msdn.microsoft.com/en-us/library/sa28fef8.aspx
#include <iostream>
#include <string>
#include <vector>

/*
When a share of common stock of some company is sold, the capital
gain (or, sometimes, loss) is the difference between the share’s selling
price and the price originally paid to buy it. This rule is easy to understand
for a single share, but if we sell multiple shares of stock bought
over a long period of time, then we must identify the shares actually being
sold. A standard accounting principle for identifying which shares of
a stock were sold in such a case is to use a FIFO protocol—the shares
sold are the ones that have been held the longest (indeed, this is the default
method built into several personal finance software packages). For
example, suppose we buy 100 shares at $20 each on day 1, 20 shares at
$24 on day 2, 200 shares at $36 on day 3, and then sell 150 shares on day
4 at $30 each. Then applying the FIFO protocol means that of the 150
shares sold, 100 were bought on day 1, 20 were bought on day 2, and 30
were bought on day 3. The capital gain in this case would therefore be
100 · 10+20 · 6+30 ·(-6), or $940. Write a program that takes as input
a sequence of transactions of the form “buy x share(s) at $y each”
or “sell x share(s) at $y each,” assuming that the transactions occur
on consecutive days and the values x and y are integers. Given this
input sequence, the output should be the total capital gain (or loss) for the
entire sequence, using the FIFO protocol to identify shares.
*/

typedef std::string error;
class Exeption {
	error txt;
public:
	Exeption(error err)
		: txt(err) {};
	error& getError() { return this->txt; };
};

class Node {
	int number;
	double price;
	Node* next; 
	friend class List; 
};

class List {
	Node* cursor; 
	int n; 
public:
	List()
		:cursor(NULL), n(0) {};
	int size() const;
	bool isEmpty() const;
	void push(int n, double price);
	void pop(int n) throw(Exeption);
	void advance() throw(Exeption);
	int front();
	int rear();
};


class Interface {
	double sold;
	double spent;
	double total;
	int TS;	//total shares

	List L;
public:
	Interface()
		:TS(0), total(0.0), sold(0.0), spent(0.0), L() {};
	void buyShares(const int n, const double price);	//invoke List push()
	void sellShares(const int n, const double price) throw(Exeption);	//invoke List pop()
	void checkStatus() const; //print status
private:
	int size() const;
};





void menu(Interface& x) {
	int n, choice;
	double price; 

	while (1) {
		std::cout << "Shares market \n";
		std::cout << "1. Buy \n";
		std::cout << "2. Sell \n";
		std::cout << "3. Check status \n";
		std::cout << "0. Exit \n";
		std::cout << "Enter option: ";
		std::cin >> choice;
		switch (choice) {
			case 1:
				std::cout << "How many? "; 
				std::cin >> n;
				std::cout << "How much kn per one? ";
				std::cin >> price; 
				x.buyShares(n, price); 
				break;
			case 2:
				std::cout << "How many? ";
				std::cin >> n;
				std::cout << "How much kn per one? ";
				std::cin >> price;
				x.sellShares(n, price);
				break;
			case 3:
				x.checkStatus();
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
int main()
{

	Interface b; 
	menu(b); 







	return 0;
}
int List::size() const {
	return n;
}
bool List::isEmpty() const {
	return (cursor == NULL);
}
void List::push(int numberOfElements, double price) {
	Node* newNode = new Node;
	n++; 
	newNode->number = numberOfElements;
	newNode->price = price;
	if (!isEmpty()) {
		newNode->next = cursor->next;
		cursor->next = newNode;
		return;
	}
	newNode->next = newNode;
	cursor = newNode;
}
void List::advance() throw(Exeption) {	//change cursor to one next
	try {
		if (!isEmpty()) {
			cursor = cursor->next;
			return;
		}
		throw Exeption("Queue udnerflow!");
	}
	catch (Exeption& err) {
		std::cout << err.getError() << "\n";
	}
}
int List::front() {
	return cursor->next->number;
}
int List::rear() {
	return cursor->number;
}
void List::pop(int numberOfElements) {
	if (numberOfElements <= 0) {
		return; 
	}
	try {
		if (!isEmpty()) {	//if list is empty
			Node* oldNode = cursor->next;
			if (oldNode != cursor) {	//if there is only one node
				if (oldNode->number > numberOfElements) {
					oldNode->number -= numberOfElements;
					return;
				}
				n--;	//decrement size of nodes by 1
				cursor->next = oldNode->next;	//set cursor next to 2. from front
				numberOfElements -= oldNode->number;
				delete oldNode;	//delete old node
				return pop(numberOfElements);	//recursion with rest of the elements

			}	//only one node in list and number of shares s higher
			if (oldNode->number > numberOfElements) {	
				oldNode->number -= numberOfElements;	//just decrement total shares 
				return;

			}	//only one node in the list and he's shares are equal
			else if (oldNode->number == numberOfElements) {
				n--;
				cursor = NULL;
				delete oldNode;
				return;
			}
			throw Exeption("Queue udnerflow!");
		}
		throw Exeption("Queue udnerflow!");
	}
	catch (Exeption& err) {
		std::cout << err.getError() << "\n"; 
	}
}
int Interface::size() const {
	return TS;
}
void Interface::buyShares(const int n, const double price) {
	L.push(n, price);
	L.advance();
	this->TS += n;
	this->spent += (n * price);
	this->total -= (n * price);
}
void Interface::sellShares(const int n, const double price) throw(Exeption) {
	try {
		if (n <= TS) {
			L.pop(n);
			this->sold += (n * price);
			this->total += (n * price);
			this->TS -= n;
			return;
		}
		throw Exeption("You dont have enough shares.");
	}
	catch (Exeption& err) {
		std::cout << err.getError() << " \n";
	}
}
void Interface::checkStatus() const {	//print status
	std::cout << "sold: " << this->sold << " kn \n";
	std::cout << "spent: " << this->spent << " kn \n";
	std::cout << "total: " << this->total << " kn \n";
	std::cout << "total shares: " << this->TS << " \n";
}
