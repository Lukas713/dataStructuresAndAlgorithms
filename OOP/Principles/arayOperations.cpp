// testing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class IndexOutOfBounds {
	string error;
public:
	IndexOutOfBounds(const string err)
		: error(err) {};
};

class GameEntry {

	int score;
	string name;
public:
	GameEntry(const string& nm = "undefined", const int sc = 0);
	int getScore() const;
	string getName() const;
};

class Scores {

	int maxEntries;
	int counter;
	GameEntry* entry;
public:
	Scores(const int maxEntries = 10);
	~Scores();
	void addEntry(const GameEntry& o);
	GameEntry removeEntry(int i) throw(IndexOutOfBounds);
	void display();
};

void insertionSort(int* a, int n) {
	for (int i = 1; i < n; i++) {	//outer loop
		int current = a[i]; 	//take secnd number
		int j = i - 1; 		//take first number
		while (current < a[j] && j >= 0) {	//copare second to first
			a[j + 1] = a[j]; 	//swap if true
			j--;	//first is now first - 1, and second if swaped mean that it is second still
		}
		a[j + 1] = current; //insert current at position
	}

	for (int i = 0; i < 5; i++) {	//display sorted array
		cout << a[i] << endl;
	}
}

int main()
{

	int a[5] = { 1, 2, 3, 6, 8 }; 

	 
	insertionSort(a, 5); 

	




	return 0;
}
GameEntry::GameEntry(const string& nm, const int sc)
	: name(nm), score(sc) {};
string GameEntry::getName() const {
	return this->name;
}
int GameEntry::getScore() const {
	return this->score;
}

Scores::Scores(const int maxEntries) {
	this->maxEntries = maxEntries;
	counter = 0;
	entry = new GameEntry[maxEntries];
}
Scores::~Scores() {
	delete[]entry;
}
void Scores::addEntry(const GameEntry& o) {
	int newScore = o.getScore();

	if (counter == maxEntries - 1) {	//checks if arra is full
		if (newScore < entry[counter].getScore()) {	//if last element is higher then newScore 
			return;
		}
	}
	counter++; //add new field
	int i = counter - 1; //take one left tot he right
	while (i > 0 && newScore > entry[i].getScore()) {
		entry[i + 1] = entry[i]; //copy left to the one spot right to himself
		i--; //iterate
	}
	entry[i + 1] = o;	//push object to spot
}

GameEntry Scores::removeEntry(const int i) throw(IndexOutOfBounds) {
	if (i < 0 || i > maxEntries - 1) {
		throw IndexOutOfBounds("Wrong indeks");
	}

	GameEntry o;
	for (int j = i + 1; j < counter; j++) {
		entry[j - 1] = entry[j];
	}
	counter--;
	return o;
}

void Scores::display() {
	int i = counter - 1;
	while (i >= 0) {
		cout << entry[i].getName() << ": " << entry[i].getScore() << endl;
		i--;
	}
}

