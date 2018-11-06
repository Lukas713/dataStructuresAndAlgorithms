
#include <iostream>
#include <string>
#include <vector>



//cout elements of the array
int sumLinear(int* x, int n) {
	if (n == 1) {	//base test
		return x[0]; 
	}

	return recursionArray(x, n - 1) + x[n - 1];	//recur
}
//Binary recursion
int sumBinary(int* f, int i, int n){
	if(n <= 1){
		return f[0]
	}
	
	return sumBinary(f, i, n/2) + sumBinary(f, i+(n/2), n/2); 
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

//Describe a recursive algorithm for finding the maximum element in an array A of n elements. 
/*LINEAR APROACH*/
int findMaxRecur(int* f, int n){
	int max;
	if(n == 1){
		return f[0]; 
	}
	
	max = findMaxRecur(f, n-1); 
	if(max < f[n-1]){
		max = f[n-1]; 
	}
	return max; 
}
/*BINARY RECURSION*/
int maxBinary(int* f, int i, int n){
	if(n == i){
		return f[i]; 
	}
	int mid = (i + n) / 2; 
	int left = maxBinary(f, i, mid);
	int right = maxBinary(f, mid+1, n); 
	
	return (left < right) ? left : right;  
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
int main()
{
 	int field[] = {1, 2, 3, 4, 5, 6};
 	int x = sumBinary(field, 0, 6);
 	std::cout << x; 


	return 0; 
}






