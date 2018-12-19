#include "pch.h"
#include <iostream>
#include <string>
#include <list>
#include <map>
#include <vector>


/*
The bubble-sort : O(n2)

The bubble-sort algorithm has the following properties:

• In the first pass, once the largest element is reached, it keeps on being swapped
until it gets to the last position of the sequence.

• In the second pass, once the second largest element is reached, it keeps on
being swapped until it gets to the second-to-last position of the sequence.

• In general, at the end of the ith pass, the right-most i elements of the sequence
(that is, those at indices from n-1 down to n-i) are in final position
*/


void bubbleSort(std::vector<int>& V, int size) {

	for (int i = 0; i < size; i++) {
		
		for (int j = 1; j < size - i; j++) {

			if (V[j - 1] > V[j])
				std::swap(V[j], V[j - 1]);
		}
	}
}
int main()
{

	std::vector<int> V = { 9, 1, 8, 2, 7, 3, 6, 4, 5 }; 

	bubbleSort(V, 9); 

	for (int i = 0; i < 9; i++) {
		std::cout << V[i] << " "; 
	}



	return 0;
}

