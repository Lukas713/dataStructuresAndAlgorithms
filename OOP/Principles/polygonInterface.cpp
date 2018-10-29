// testing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Polygon { //abstract class
public:
	void getInfo(); 
protected:
	virtual double area() = 0;
	virtual double perimeter() = 0; 
};
//TRIANGLES!
class Triangle : public Polygon { 
protected:
	double a;

public:
	Triangle(const double size = 5)	//constructor
		: a(size) {}; //init list
	~Triangle();	//destructor
protected:
	virtual double area() = 0;	//polymoprhism
	virtual double perimeter() = 0;
};

class IsoscelesTriangle : public Triangle {
protected:
	double b;
	double v;

public:
	//constructor & destructor
	IsoscelesTriangle(const double aSide, const double bSide, const double height)
		:Triangle(aSide), b(bSide), v(height) {};
	~IsoscelesTriangle(); 

protected:
	virtual double area();
	virtual double perimeter();
};

class EquilateralTriangle : public Triangle {
protected:
	double v;

public:
	EquilateralTriangle(const double aSide, const double height)
		: Triangle(aSide), v(height) {}; 
	~EquilateralTriangle();

protected:
	virtual double area();
	virtual double perimeter();
};

class RecktangularTriangle : public Triangle {
protected:
	double b;
	double c;

public:
	RecktangularTriangle(const double bSide, const double cSide, const double aSide)
		: Triangle(aSide), b(bSide), c(cSide) {}; 
	~RecktangularTriangle(); 

protected:
	virtual double area();
	virtual double perimeter();
};

//QUADRILATERALS 
class Quadrilateral : public Polygon {
protected:
	double a;
	double b;
public:
	Quadrilateral(const double aSide, const double bSide = 0)	//constructor
		: a(aSide), b(bSide) {}; //init list
	~Quadrilateral(); //destructor
protected:
	virtual double area() = 0;
	virtual double perimeter() = 0;  
};

class Recktangle : public Quadrilateral { 
public:
	Recktangle(const double aSide, const double bSide)
		: Quadrilateral(aSide, bSide) {}; 
	~Recktangle(); 

protected:
	virtual double area();
	virtual double perimeter(); 
};

class Square : public Quadrilateral {
public:
	Square(const double aSide)
		: Quadrilateral(aSide) {}; 
	~Square(); 
protected:
	virtual double area();
	virtual double perimeter(); 
};

class Parallelogram : public Quadrilateral {
protected:
	double v;
public:
	Parallelogram(const double aSide, const double bSide, const double height)
		: Quadrilateral(aSide, bSide), v(height) {}; 
	~Parallelogram(); //destructor
protected:
	virtual double area();
	virtual double perimeter(); 
};

class Trapeze : public Quadrilateral {
protected:
	double c;
	double d;
	double v;
public:
	Trapeze(const double aSide, const double bSide, const double cSide, const double dSide, const double height)
		: Quadrilateral(aSide, bSide), c(cSide), d(dSide), v(height) {}; 
	~Trapeze();
protected:
	virtual double area();
	virtual double perimeter(); 
};

int main()
{
	int choice, secondChoice;
	int a, b, c, d, v; 

	while (1) {
		cout << "********************************************" << endl;
		cout << "Polygon area & perimetar calculator	by Lukas" << endl;
		cout << "********************************************" << endl;
		cout << "1. Triangle" << endl;
		cout << "2. Quadriateral" << endl;
		cout << "0. Exit" << endl;
		cout << "enter option: ";
		cin >> choice; 
		switch (choice) {
			case 1:
				Triangle* polygonOne; //creates pointer to triangle
				cout << "1. Equilateral" << endl;
				cout << "2. Isosceles" << endl;
				cout << "3. Recktangular" << endl;
				cout << "0. Exit" << endl;
				cout << "enter option: ";
				cin >> secondChoice; 
				switch (secondChoice) {
					case 1:
						cout << "Enter a side: ";
						cin >> a;
						cout << endl;
						cout << "Enter height: ";
						cin >> v;
						polygonOne = new EquilateralTriangle(a, v);
						cout << endl;
						polygonOne->getInfo(); 
						break;
					case 2:
						cout << "Enter a side: ";
						cin >> a;
						cout << endl;
						cout << "Enter b side: ";
						cin >> b;
						cout << endl;
						cout << "Enter height: ";
						cin >> v;
						polygonOne = new IsoscelesTriangle(a, b, v);
						cout << endl;
						polygonOne->getInfo();
						break;
					case 3:
						cout << "Enter a side: ";
						cin >> a;
						cout << endl;
						cout << "Enter b side: ";
						cin >> b;
						cout << endl;
						cout << "Enter hipotenuse: ";
						cin >> c;
						polygonOne = new RecktangularTriangle(a, b, c);
						cout << endl;
						polygonOne->getInfo();
						break;
					case 0:
						exit(1);
						break;
					default:
						cout << "Wrong option" << endl; 
				}
			case 2:
				Quadrilateral* polygonTwo;
				cout << "1. Recktangle" << endl;
				cout << "2. Square" << endl;
				cout << "3. Paralelogram" << endl;
				cout << "4. Trapeze" << endl;
				cout << "0. Exit" << endl;
				cout << "enter option: ";
				cin >> secondChoice;
				switch (secondChoice) {
					case 1:
						cout << "Enter a side: ";
						cin >> a;
						cout << endl;
						cout << "Enter b side: ";
						cin >> b;
						polygonTwo = new Recktangle(a, b);
						cout << endl;
						polygonTwo->getInfo();
						break;
					case 2:
						cout << "Enter a side: ";
						cin >> a;
						cout << endl;
						polygonTwo = new Square(a);
						cout << endl;
						polygonTwo->getInfo();
						break;
					case 3:
						cout << "Enter a side: ";
						cin >> a;
						cout << endl;
						cout << "Enter b side: ";
						cin >> b;
						cout << endl;
						cout << "Enter height: ";
						cin >> v;
						polygonTwo = new Parallelogram(a, b, v); 
						cout << endl;
						polygonTwo->getInfo();
						break;
					case 4:
						cout << "Enter a side: ";
						cin >> a;
						cout << endl;
						cout << "Enter b side: ";
						cin >> b;
						cout << endl;
						cout << "Enter c side: ";
						cin >> c;
						cout << endl;
						cout << "Enter d side: ";
						cin >> d;
						cout << endl;
						cout << "Enter height: ";
						cin >> v;
						polygonTwo = new Trapeze(a, b, c, d, v); 
						cout << endl;
						polygonTwo->getInfo();
						break;
					case 0:
						exit(1);
						break;
					default:
						cout << "Wrong option" << endl;
				}
			case 0:
				exit(1);
				break;
			default:
				cout << "Wrong option" << endl; 
		}
	}
	return 0; 
}

void Polygon::getInfo() {
	cout << "Area: " << area() << " m^2" << endl;
	cout << "Perimeter: " << perimeter() << " m" << endl;
}
//TRIANGLE
//IsoscelesTriangle
double IsoscelesTriangle::area() {
	return  ((a * v) / 2);
}
double IsoscelesTriangle::perimeter() {
	return  (a + (2 * b)); 
}
//EquilateralTriangle 
double EquilateralTriangle::area() {
	return ((a * v) / 2);
}
double EquilateralTriangle::perimeter() {
	return (3 * a);
}
//RecktangularTriangle
double RecktangularTriangle::area() {
	return ((a * b) / 2);
}
double RecktangularTriangle::perimeter() {
	return (a + b + c); 
}

//QUADRILATERAL
//Recktangle
double Recktangle::area() {
	return (a * b);
}
double Recktangle::perimeter() {
	return ((2 * a) + (2 * b)); 
}
//Square
double Square::area() {
	return (a * a); 
}
double Square::perimeter() {
	return (a + a + a + a); 
}
//Parallelogram
double Parallelogram::area() {
	return (a * v);
}
double Parallelogram::perimeter() {
	return ((2 * a) + (2 * b));
}
//Trapeze
double Trapeze::area() {
	return (((a + c) * v ) / 2);
}
double Trapeze::perimeter() {
	return (a + b + c + d); 
}


