#include "pch.h"
#include <iostream>
#include <string>
#include <vector>



//cout elements of the array
int recursionArray(int* x, int n) {
	if (n == 1) {	//base test
		return x[0]; 
	}

	return recursionArray(x, n - 1) + x[n - 1];	//recur
}

//count factorial
int recursiveFactorial(int x) {
	if (x == 0) {	//base test
		return 1; 
	}

	return x * recursiveFactorial(x - 1); //recur
}

void countdown(int n) {
	std::cout << "Counting down " << n << " address: " << &n << std::endl; 
	if (n > 0) {

		countdown(n - 1); 
	}
	std::cout << "kaboom " << n << " adress: " << &n <<std::endl;
}
int main()
{
	int n = 4;
	countdown(n); 
	

	return 0; 
}






