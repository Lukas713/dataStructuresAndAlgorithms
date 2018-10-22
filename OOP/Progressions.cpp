// testing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Progression {

public:
	Progression(long f=0)	//constructor
		: first(f), current(f){}	//init list
	virtual ~Progression() {};	//destructor
	void printProgression(int n); //print first n values

protected:
	 virtual long firstValue();
	 virtual long nextValue();

protected:	//only within derived class
	long first;
	long current;
};
//first derrived class
class ArithProgression : public Progression {

public:
	ArithProgression(long i = 1)
		: Progression(), increment(i) {};
protected:
	 virtual long nextValue();//dynamic bind and polymorphism
protected:
	long increment;
};

//second derrived class
class GeometricProgression : public Progression {

public:
	GeometricProgression(long b = 2)
		: Progression(1), base(b) {};
protected:
	virtual long nextValue();
protected:
	long base;
};

//fibbonaci progression
class FibbonaciProgression : public Progression {
public:
		FibbonaciProgression(long f = 0, long s = 1)
			: Progression(f), second(s), previous(second - first) {};
protected:
	long nextValue();
	long firstValue();
protected:
	long second;
	long previous;
};
int main()
{

	Progression* one[100];
	one[1] = new Progression();
	one[2] = new ArithProgression(5);
	one[3] = new GeometricProgression(5);
	one[4] = new FibbonaciProgression();

	cout << "Regular progression" << endl;
	one[1]->printProgression(5); 
	cout << endl;

	cout << "Arithmetic progression" << endl;
	one[2]->printProgression(5);
	cout << endl;

	cout << "Geometric progressio" << endl;
	one[3]->printProgression(5);
	cout << endl;

	cout << "Fibbonacci progression" << endl;
	one[4]->printProgression(15);


	
	

	
}
//base clase
void Progression::printProgression(int n) {

	for (int i = 0; i < n; i++) {
		cout << ' ' << nextValue();
	}
}

long Progression::firstValue() {
	current = first;
	return current;
}

long Progression::nextValue() {
	return current ++;
}
//derived class
long ArithProgression::nextValue() {
	current += increment;
	return current;
}
//second derrived class
long GeometricProgression::nextValue() {
	current *= base;
	return current;
}
//fibbonaci progression
long FibbonaciProgression::firstValue() {
	current = first;
	previous = second - first;
	return current;
}

long FibbonaciProgression::nextValue() {
	long temp = previous;
	previous = current;
	current += temp;
	return current;
}


