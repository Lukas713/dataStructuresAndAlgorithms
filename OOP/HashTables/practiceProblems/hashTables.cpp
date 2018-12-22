#include "pch.h"
#include <iostream>
#include <string>
#include <unordered_map>

/*
1)
	You have been given an integer array A and a number K.
	Now, you need to find out whether any two different elements of the array A sum to the number K. 
	Two elements are considered to be different if they lie at different positions in the array. 
	If there exists such a pair of numbers, print "YES" (without quotes), else print "NO" without quotes.
	
	Input Format:
	The first line consists of two integers N, denoting the size of array A and K.
	The next line consists of N space separated integers denoting the elements of the array A.
	
	Output Format:
	Print the required answer on a single line.
*/

bool pairSum(int* field, int k, int size);

int main()
{
	
	int size; int k;
	int field[] = { 9, 8, 1, 2, 6, 3, 7, 4, 5,  9, 8, 1, 2, 6, 3, 7, 4, 5,  9, 8, 1, 2, 6, 3, 7, 4, 5,  9, 8, 1, 2, 6, 3, 7, 4, 5 };
	
	pairSum(field, 13, 36); 
	







	return 0;
}

/*
3 @params : int array, searching sum, size of array
1) creates map with false values
2) insert elements into map
3) traverse witin map, if finds missing operand, return true else continue
*/
bool pairSum(int* field, int k, int size) {
	//creates map with false values
	std::unordered_map<int, bool> a(size);

	//insert elements into map
	for (int i = 0; i < size; i++) {
		a.insert(std::make_pair(field[i], false));
	}

	//traverse witin map, if finds missing operand, return true else continue
	std::unordered_map<int, bool>::iterator p;
	for (p = a.begin(); p != a.end(); ++p) {
		if (a.find(k - (*p).first) != a.end()) {
			std::cout << "Yes";
			return true;
		}
	}
	std::cout << "No";
	return false;
}
