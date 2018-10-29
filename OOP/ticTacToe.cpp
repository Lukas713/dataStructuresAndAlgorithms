// testing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>


using namespace std;

const int boardRows = 3;
const int boardColumns = 3;
const int O = 1;
const int X = -1;

class Game {
	int empty;
	int board[boardRows][boardColumns];
	int currentPlayer; 
	bool play; 
public:
	Game(); 
	void createBoard();
	void move(int i, int j);
	bool isWinner(int mark);
	void printBoard();
	bool checkPlay();
};
Game::Game() { 
	this->empty = 0; 
	play = true; 
	createBoard();
}
void Game::createBoard() {
	for (int i = 0; i < boardRows; i++) {
		for (int j = 0; j < boardColumns; j++) {
			board[i][j] = empty;
		} 
	}
	currentPlayer = 1; 
}

void Game::move(int i, int j) {

	board[i][j] = currentPlayer;
	printBoard(); 

	if (!isWinner(currentPlayer)) {
		currentPlayer = -currentPlayer; 
		return; 
	}
	cout << "winner is player: " << currentPlayer << endl;
	return;
}

bool Game::isWinner(int mark) {
	int winner = 3 * mark; 

	if (((board[0][0] + board[0][1] + board[0][2]) == winner)		//1. row
		|| ((board[1][0] + board[1][1] + board[1][2]) == winner)	//2. row
		|| ((board[2][0] + board[2][1] + board[2][2]) == winner)	//3. row
		|| ((board[0][0] + board[1][0] + board[2][0]) == winner)	//1. column
		|| ((board[0][1] + board[2][1] + board[2][1]) == winner)	//2. column
		|| ((board[0][2] + board[1][2] + board[2][2]) == winner)	//3. column
		|| ((board[0][0] + board[1][1] + board[2][2]) == winner)	//1. diagonal
		|| ((board[0][2] + board[1][1] + board[2][0]) == winner))	//2. diagonal
	{
		play = false; 
		return true;
	}
	
	return false; 
}

void Game::printBoard() {
	for (int i = 0; i < boardRows; i++) {
		for (int j = 0; j < boardColumns; j++) {
			switch (board[i][j]) {
			case O:
				cout << "O";
				break;
			case X:
				cout << "X";
				break;
			case 0:
				cout << "";
				break;
			}
			if (j < 2) 
				cout << " | ";
		}
		if(i < 2)
			cout << "\n-+--+-\n";
	}
}

bool Game::checkPlay() {
	if (!play)
		return false;
	
	return true; 
}
int main()
{
	int i, j;
	Game first; 
	
	
	while (first.checkPlay()) {
		cout << endl; 
		cout << "enter i: ";
		cin >> i;
		cout << "enter j: "; 
		cin >> j;
		first.move(i, j); 
	}

	return 0;
}

