#include "pch.h"
#include <iostream>
#include <string>
#include <vector>

class ThreeDimensions {
	int x; 
	int y; 
	int z;
	int*** Matrix; 
public:
	ThreeDimensions(const int i = 3, const int j = 3, const int k = 3);
	virtual ~ThreeDimensions();
	void createMatrix();	//create matrixx with dinamic alocation
	void fillMatrix();		//feed up matriwith random numbers
};
			
int main()
{
 










	return 0;
}
//constructor
ThreeDimensions::ThreeDimensions(const int i = 3, const int j = 3, const int k = 3)
	:x(i), y(j), z(k) {};
//Destrutor
ThreeDimensions::~ThreeDimensions() {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			delete[] Matrix[i][j];
		}
		delete[] Matrix[i];
	}
	delete[] Matrix;
}
void ThreeDimensions::createMatrix() {
	//dinamic alocation
	Matrix = new int**[x];
	for (int i = 0; i < x; i++) {
		Matrix[i] = new int*[y];
		for (int j = 0; j < y; j++) {
			Matrix[i][j] = new int[z];
		}
	}
	//invoke function that will feed up 3D matrix with random number from 1 to 100
	fillMatrix();
}
void ThreeDimensions::fillMatrix() {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			for (int k = 0; k < z; j++) {
				Matrix[i][j][k] = rand() % 100;
			}
		}
	}
}

