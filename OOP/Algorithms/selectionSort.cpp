#include "pch.h"
#include <iostream>
#include <string>
#include <list>
#include <map>
#include <vector>



void selectionSort(std::vector<int>& V, int size) {
	int min;
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			if (V[i] > V[j]) {
				std::swap(V[i], V[j]); 
			}
		}
	}
}
int main()
{
	std::vector<int> A = { 9, 1, 8, 2, 7, 3, 6, 4, 5 }; 
	selectionSort(A, 9); 
	for (int i = 0; i < 9; i++) {
		std::cout << A[i] << " "; 
	}
	

	return 0;
}

