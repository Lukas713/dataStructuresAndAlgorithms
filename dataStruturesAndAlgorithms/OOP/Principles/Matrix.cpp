#include "pch.h"
#include <iostream>
#include <string>
#include <vector>

class Matrix {
	int x;
	int y;
	int** Matrice;
public:
	Matrix(const int i = 3, const int j = 3);
	virtual ~Matrix();
	void print(); 
	void operator+(Matrix M);
	void operator*(Matrix M);
protected:
	void createMatrix();	//create matrixx with dinamic alocation
	void fillMatrix();		//feed up matriwith random numbers
};

int main()
{








	return 0;
}
//constructor
Matrix::Matrix(const int i, const int j)
	:x(i), y(j){
	createMatrix(); 
};
//destructor
Matrix::~Matrix() {
	for (int i = 0; i < x; i++) {
		delete[] Matrice[i];
	}
	delete[] Matrice;
	std::cout << "Matrice deleted \n";
}
void Matrix::createMatrix() {
	//dinamic alocation
	Matrice = new int*[x];
	for (int i = 0; i < x; i++) {
		Matrice[i] = new int[y];
	}
	//invoke function that will feed up 3D matrix with random number from 1 to 100
	fillMatrix();
}
void Matrix::fillMatrix() {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			Matrice[i][j] = rand() % 100; 
		}
	}
}
void Matrix::print() {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			std::cout << Matrice[i][j] << " "; 
		}
		std::cout << "\n"; 
	}
}

void Matrix::operator+(Matrix M) {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			Matrice[i][j] += M.Matrice[i][j];
		}
	}
}
void Matrix::operator*(Matrix M) {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			Matrice[i][j] *= M.Matrice[i][j];
		}
	}
}

