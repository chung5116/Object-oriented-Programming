// Name: Yung-Cheng Chang B10706009
// Date: 2020.04.09
// Last Update: 2020.04.11
// Problem statement: Hero & Creature
//#pragma once
#include "board.h"



Board::Board() {
	string filename;
	cout << "Enter filename of MAP .  ex : map1.txt ~map3.txt \n";
	cin >> filename;
	//filename = "map3.txt";
	ifstream file;
	char buffer[300];
	file.open(filename);
	if (!file) {
		cout << "Can't open file" << endl;
		system("pause");
		exit(1);
	}
	else {
		while (!file.eof()) {
			file.getline(buffer, sizeof(buffer));
			vector<char>rol;
			int i = 0;
			while (buffer[i] != '\0') {
				rol.push_back(buffer[i]);
				cout << buffer[i];
				i++;
			}
			board.push_back(rol);
			cout << endl;
			
		}
	}
	height = board.size();
	tmpBoard = board;
}


/*void Board::printoutBoard() {
	cout << "Use wasd to control Hero, press \"k\" to attack " << endl;
	cout << "Press ESC to end the game\n\n" << endl;
	for (int i = 0; i < this->board.size(); i++) {
		for (int j = 0; j < this->board[i].size(); j++) {
			cout << board[i][j];
		}
		cout << endl;
	}
}*/

bool Board::checkValid(int x, int y) {
	if (x >= 0 && x < board.size()) {
		if (y >= 0 && y < board[x].size()) {
			if (this->board[x][y	] == ' ')
				return true;
		}
	}
	return false;
}


void Board::setBoard(int x, int y, char in) { 
	tmpBoard[x][y] = in; 
}

