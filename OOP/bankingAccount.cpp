// testing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;
class System { 
public:
	void withdraw(double price); 
	void deposit(); 
	void checkBalance(); 
};
class Account : public System {
private:
	string firstName;
	string lastName;
	string email;
	double balance;
public:
	Account(const string fn, const string ln, const string em); 
	void withdraw(const double price);
	void deposit(const double price);
	void checkBalance() const; 
	void setEmail(const string email);  	
};
int main()
{
	int choice, x;
	double n;
	string fn, ln, em; 
	
	cout << "Bank" << endl;
	cout << "Enter name" << endl;
	cin >> fn;
	cout << "Enter last name" << endl;
	cin >> ln; 
	cout << "Enter email" << endl; 
	cin >> em; 
	Account a(fn, ln, em); 
	

	while (1) {
		cout << "1. Withdraw" << endl;
		cout << "2. Deposit" << endl;
		cout << "3. Check balance" << endl;
		cout << "4. Change email" << endl;
		cout << "0. Exit" << endl;
		cout << "Enter option: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "How much?" << endl;
			cin >> n;
			a.withdraw(n);
			break;
		case 2:
			cout << "How much ?" << endl;
			cin >> n;
			a.deposit(n);
			break;
		case 3:
			a.checkBalance();
			break;
		case 4:
			cout << "Enter new email" << endl;
			cin >> em;
			a.setEmail(em);
			break;
		case 0:
			exit(1);
			break;
		default:
			cout << "Wrong option" << endl;
		}
	}
	return 0;
}
Account::Account(const string fn, const string ln, const string em) {
	this->firstName = fn;
	this->lastName = ln;
	this->email = em;
	this->balance = 0.0; 
}
void Account::deposit(const double price) {
	this->balance += price; 
	return; 
}
void Account::withdraw(const double price) {
	this->balance -= price;
	return; 
}
void Account::checkBalance() const {
	cout << "Balance: " << this->balance << endl; 
	return; 
}
void Account::setEmail(const string email) {
	this->email = email; 
	return; 
}


