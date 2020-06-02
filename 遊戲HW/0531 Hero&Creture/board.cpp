// Name: Yung-Cheng Chang B10706009
// Date: 2020.04.09
// Last Update: 2020.04.11
// Problem statement: Hero & Creature
//#pragma once
#include "board.h"

vector<vector<char>>maze();

Board::Board() {
	int height = 0; int width = 0;
	//cout << "Enter height and width. 5~30\n";
	/*while (true){
		cout << "Enter height and width. 5~30\n";
		cin >> height >> width;
		if (height >= 5 && height <= 30 && width >= 5 && width <= 30)
			break;
	}*/
	this->board = maze();
	this->height = board.size();
	tmpBoard = board;
}

bool Board::checkValid(int x, int y) {
	if (x >= 0 && x < board.size()) {
		if (y >= 0 && y < board[x].size()) {
			if (this->board[x][y] == ' ')
				return true;
		}
	}
	return false;
}


void Board::setBoard(int x, int y, char in) {
	tmpBoard[x][y] = in;
}

Position Board::generateRandomXY() {
	Position random;
	int min = 1;
	int max = board.size() - 1;
	int dx = 0;
	int dy = 0;
	while (true) {
		dx = (rand() % (max - min + 1)) + min;
		dy = (rand() % tmpBoard[dx].size() - 1 - min + 1)+ min;
		if (checkValid(dx, dy))
			break;
	}
		random.x = dx;
		random.y = dy;
		return random;
}