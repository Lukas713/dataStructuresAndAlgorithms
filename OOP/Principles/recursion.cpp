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

//reverse array recursive
void recursiveReverse(int* x, int i, int j) {
	if (j == 0) {
		return; 
	}

	int temp = x[j - 1]; 
	x[j - 1] = x[i]; 
	x[i] = temp;
	
	recursiveReverse(x, i + 1, j - 1);
	std::cout << x[i] << " ";
}

//get number of elements in array 
int numberOfRepetition(int* x, int n, int max) {
	
	if (max < 0) {
		return 0 ; 
	}

	if (x[max-1] != n) {
		return numberOfRepetition(x, n, max - 1) + 0; 
	}
	return numberOfRepetition(x, n, max - 1) + 1; 
}


int main()
{
 


	return 0; 
}






