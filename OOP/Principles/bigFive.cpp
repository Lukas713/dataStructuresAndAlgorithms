// testing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>





class intDigit {

public:
	intDigit(int max = 0)	//constructor
		:storedValue(new int[max]) {}; 

	~intDigit() {	//Destructor
		delete storedValue; 
	}

	intDigit(const intDigit& x) {	//copy constructor
		storedValue = new int[*x.storedValue]; 
	}

	intDigit(intDigit&& x)	//move constructor
		:storedValue(x.storedValue)
	{
		x.storedValue = nullptr; 
	}

	intDigit& operator=(const intDigit& x) {	//copy assignment
		if (this != &x)
			*storedValue = *x.storedValue; 
			return *this; 
	}

	intDigit& operator=(intDigit&& x) {		//move assignment
		std::swap(storedValue, x.storedValue);
		return *this; 
	}

private:
	int* storedValue; 
};


int main()
{

	

	
	
	
	




}

