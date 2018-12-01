#include "pch.h"
#include <iostream>
#include <string>
#include <vector>

typedef std::string word;
typedef std::vector<int> vectorInt;

int sumLinear(int* x, int n);

int sumBinary(int* f, int i, int n);

int recursiveFactorial(int x);

void recursiveReverse(int* x, int i, int j);

int numberOfRepetition(int* x, int n, int max);

int findMaxRecur(int* f, int n);

int maxBinary(int* f, int i, int n);

bool checkTwoEarlier(int* f, int n);

int fibonacci(int n);

void fibonaciSequence(int n, int i, int temp)

void rearanger(int* f, int i, int n);

void reverseString(word& f, int i, int n);

bool checkIfPalindrome(word& f, int i, int n);

bool primeOrNot(int n, int i);

void solveHanoiPuzzle(int n, char source, char destination, char temporary);

int product(int n, int m);

void printToZero(int n);

int countZeros(int* x, int i, int n);

void printToZero(int n);
int main()

{
	int field[] = { 1, 2, 3, 4, 5 }; 
	int x = sumBinary(field, 0, 5-1); 
	std::cout << x; 






	return 0;
}
/*
Describe a recursive algorithm that will check if an array A of integers
contains an integer A[i] that is the sum of two integers that appear earlier
in A, that is, such that A[i] = A[ j] +A[k] for j,k < i.
*/
bool checkTwoEarlier(int* f, int n) {
	if (n == 1) {
		return false;
	}

	if (f[n] == (f[n - 2] + f[n - 1])) {
		return true;
	}

	return checkTwoEarlier(f, n - 1);
}
/*BINARY RECURSION*/
int maxBinary(int* f, int i, int n) {
	if (n == i) {
		return f[i];
	}
	int mid = (i + n) / 2;
	int left = maxBinary(f, i, mid);
	int right = maxBinary(f, mid + 1, n);

	return (left < right) ? left : right;
}
//Describe a recursive algorithm for finding the maximum element in an array A of n elements. 
/*LINEAR APROACH*/
int findMaxRecur(int* f, int n) {
	int max;
	if (n == 1) {
		return f[0];
	}

	max = findMaxRecur(f, n - 1);
	if (max < f[n - 1]) {
		max = f[n - 1];
	}
	return max;
}
//get number of elements in array 
int numberOfRepetition(int* x, int n, int max) {

	if (max < 0) {
		return 0;
	}

	if (x[max - 1] != n) {
		return numberOfRepetition(x, n, max - 1) + 0;
	}
	return numberOfRepetition(x, n, max - 1) + 1;
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
}
//count factorial
int recursiveFactorial(int x) {
	if (x == 0) {	//base test
		return 1;
	}

	return x * recursiveFactorial(x - 1); //recur
}
//Binary recursion
int sumBinary(int* f, int i, int n) { 
	if (i > n) {
		return 0; 
	}
	else if (i == n) {
		return f[i]; 
	}
	else {
		int mid = (i + n) / 2; 
		return sumBinary(f, i, mid) + sumBinary(f, mid + 1, n); 
	}
}
//cout elements of the array
int sumLinear(int* x, int n) {
	if (n == 1) {	//base test
		return x[0];
	}

	return sumLinear(x, n - 1) + x[n - 1];	//recur
}
int fibonacci(int n) {
	if (n == 0) {
		return 0;
	}
	if (n == 1) {
		return 1;
	}

	return fibonacci(n - 1) + fibonacci(n - 2);
}
//Write a short recursive C++ function that will rearrange an array of int
//values so that all the even values appear before all the odd values.
void rearanger(int* f, int i, int n) {
	if (i >= n) {
		return;
	}
	if (f[n] % 2 == 0 && f[i] % 2 != 0) {
		int temp = f[n];
		f[n] = f[i];
		f[i] = temp;
		i += 1;
		n -= 1;
	}
	else if (f[i] % 2 == 0) {
		i += 1;
	}
	else {
		n -= 1;
	}

	return rearanger(f, i, n);
}
/*
Write a short recursive C++ function that takes a character string s and
outputs its reverse. So for example, the reverse of "pots&pans" would
be "snap&stop".
*/
void reverseString(word& f, int i, int n) {
	if (i >= n) {
		return;
	}

	char temp = f[n];
	f[n] = f[i];
	f[i] = temp;

	return reverseString(f, i + 1, n - 1);
}
/*
Write a short recursive C++ function that determines if a string s is a
palindrome, that is, it is equal to its reverse. For example, "racecar"
and "gohangasalamiimalasagnahog" are palindromes.
*/
bool checkIfPalindrome(word& f, int i, int n) {
	if (n <= i && f[n] == f[i]) {
		return true;
	}
	if (f[n] != f[i]) {
		return false;
	}
	checkIfPalindrome(f, i + 1, n - 1);
	return true;
}
/*
Hanoi Tower puzzle
*/
void solveHanoiPuzzle(int n, char source, char destination, char temporary) {
	if (n == 1) {
		std::cout << "Move disk " << n << " from " << source << " to " << destination << "\n";
		return;
	}
	solveHanoiPuzzle(n - 1, source, temporary, destination);	//move n-1 disk from A to C
	std::cout << "Move disk " << n << " from " << source << " to " << destination << "\n";	//move last from A to B 
	solveHanoiPuzzle(n - 1, temporary, destination, source);	//move rest from C to B
}
/*
Write n numbers of fibonaci
*/
void fibonaciSequence(int i, int n, int temp){
	if(n == 0){
		return; 
	}
	
	i = (temp + i); 
	std::cout << i << " "; 
	if(i == 0) std::cout << i << " "; 
	temp = (i - temp);
	
	fibonaciSequence(--n, i, temp);  
}
/*
Write a recursive program to determine whether a given integer is prime or not
*/
bool primeOrNot(int n, int i) {
	if (i == n) {
		return true;
	}

	(i == 1) ? ++i : i;

	if (n % i == 0) {
		return false;
	}
	return primeOrNot(n, ++i);
}
/*
Find Product of 2 Numbers using Recursion
*/
int product(int n, int m) {
	if (m == 1) {
		return n; 
	}

	return n + product(n, --m); 
}
/*
Count the number of zeros in an array of integers.
*/
int countZeros(int* x, int i, int n) {
	if (i == n) {
		return 0; 
	}
	
	return (x[i] == 0) ? 1 + countZeros(x, ++i, n) : 0 + countZeros(x, ++i, n); 
}
/*
Write a function using recursion to print numbers from n to 0
*/
void printToZero(int n) {
	if (n == 0) {
		return;
	}
	std::cout << n << " "; 
	return printToZero(--n); 
}
/*
Write a function using recursion to print numbers from 0 to n
*/
void printToZero(int n) {
	if (n == 0) {
		return;
	}
	printToZero(n - 1); 
	std::cout << n << " ";
}
