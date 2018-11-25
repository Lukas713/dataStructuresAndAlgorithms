// testing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Vect {
private:
	double x;
	double y;

public:
	Vect();
	Vect(double x);
	Vect(double x, double y);
	//operator override
	Vect& operator+(const Vect& second);	//addition two vectors
	Vect& operator*(const double scalar);	//multiplication two vectors (vector returns)
	double& operator*(const Vect& second);	//multiplication  vector	(scalar returns)
	void swap(Vect& x); 
	
	void showCoords() const;
};




int main()
{
	Vect one(9, 12); 
	Vect two(10, 2); 

	one.showCoords(); 
	one.swap(two);
	std::cout << "\n"; 
	one.showCoords(); 



}
Vect::Vect() {
	this->x = 0;
	this->y = 0;
}
Vect::Vect(double x) {
	this->x = x;
	this->y = 0;
}
Vect::Vect(double x, double y) {
	this->x = x;
	this->y = y;
}
Vect& Vect::operator+(const Vect& second) {
	x = x + second.x;
	y = y + second.y;
	return *this;
}
void Vect::showCoords() const {
	cout << "[" << this->x << "," << this->y << "]" << endl;
}
Vect& Vect::operator*(const double scalar) {
	this->x = x * scalar;
	this->y = y * scalar;

	return *this;
}
double& Vect::operator*(const Vect& second) {

	double coords[2];
	coords[0] = x * second.x;
	coords[1] = y * second.y;

	double* coordPointer = coords;
	return *coordPointer;
}

void Vect::swap(Vect& x) {	//call-by-referance
	Vect temp = static_cast<Vect &&> (x);	//casting x lvalue as rvalue into temp variable (not copy)
	x = static_cast<Vect &&>(*this);
	*this = static_cast<Vect &&> (temp);
}

