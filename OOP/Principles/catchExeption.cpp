// testing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ArrayExeption {
private:
	string errorMsg;
public:
	ArrayExeption(const string& err);
	void getError() {cout << errorMsg;}
};

class Array {
private:
	int size;
	int* data;

public:
	Array(int n) throw (ArrayExeption); //specifing which errorMSG coud be thrown
	void setValues();

	void getValues();
};
int main()
{
	int n;

	try {
		cout << "Insert number of integers" << endl;
		cin >> n;
		if (n > 10) {
			throw ArrayExeption("Your n is to large!"); //throw construct
		}
		else if (n < 1) {
			throw ArrayExeption("Your n cant be less the 1");
		}
		Array* a = new Array(n);
		a->setValues();
		a->getValues();
	}
	catch (ArrayExeption& exp) {	//catching consstructed exeption
		exp.getError();	
	}
}
ArrayExeption::ArrayExeption(const string& err)
	: errorMsg(err) {};

Array::Array(int n) {
	size = n;
	data = new int[size];
}

void Array::getValues() {
	for (int i = 0; i < size; i++) {
		cout << data[i] << endl;
	}
	return;
}

void Array::setValues() {
	for (int i = 0; i < size; i++) {
		cin >> data[i];
	}
	return;
}
