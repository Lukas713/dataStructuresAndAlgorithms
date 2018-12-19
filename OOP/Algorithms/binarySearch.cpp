#include "pch.h"
#include <iostream>
#include <string>
#include <queue>
#include <vector>



/*
We consider three cases:
• If k = e.key(), then we have found the entry we were looking for, and the
search terminates successfully returning e

• If k < e.key(), then we recur on the first half of the vector, that is, on the
range of indices from low to mid -1

• If k > e.key(), we recur on the range of indices from mid +1 to high
*/
int binarySearch(std::vector<int> V, int key, int low, int high) {
	int mid = (low + high) / 2; 

	if(V[mid] == key)
		return mid; 

	else if (key > V[mid]) 
		return binarySearch(V, key, mid + 1, high); 

	else 
		return binarySearch(V, key, low, mid - 1); 
}

void bubbleSort(std::vector<int>& V, int size);

int main()
{
	

	std::vector<int> V = { 9, 1, 8, 2, 7, 3, 6, 4, 5 }; 
	bubbleSort(V, 9); 

	int x = binarySearch(V, 8, 0, 9); 
	for (int i = 0; i < 9; i++) {
		std::cout << V[i] << " "; 
	}
	std::cout << "\n"; 
	std::cout << x; 









	return 0;
}
void bubbleSort(std::vector<int>& V, int size) {

	for (int i = 0; i < size; i++) {

		for (int j = 1; j < size - i; j++) {

			if (V[j - 1] > V[j])
				std::swap(V[j], V[j - 1]);
		}
	}
}
