// testing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename T>	//declaring template	

class BasicVector {
public:
	BasicVector(int cap = 10);
	T& operator[](int i) { return a[i]; }

private:
	int capacity;
	T* a;
};
int main()
{
	
	BasicVector<int> intgrs(10);
	BasicVector<BasicVector<int> >xv(5); //vector of vectors
	intgrs[2] = 5;
	cout << intgrs[2] << endl;

	BasicVector<double> doubls(15);
	doubls[12] = 12;
	cout << doubls[12] << endl;

	BasicVector<string> strngs(25);
	strngs[21] = "This is a string";
	cout << strngs[21] << endl;
}

template <typename T>
BasicVector<T>::BasicVector(int cap) {
	capacity = cap;
	a = new T[capacity]; //allocate new storage
}

