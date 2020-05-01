// Name: Yung-Cheng Chang B10706009
// Date: 2020.04.09
// Last Update: 2020.04.11
// Problem statement: Hero & Creature
//#pragma once
#include "board.h"

vector<vector<char>>maze();

Board::Board() {
	openRecord();
	if (gLevel == 1) {
		int height = 0; int width = 0;
		//cout << "Enter height and width. 5~30\n";
		/*while (true){
			cout << "Enter height and width. 5~30\n";
			cin >> height >> width;
			if (height >= 5 && height <= 30 && width >= 5 && width <= 30)
				break;
		}*/

		//this->board = maze();  generate maze map
		openMaze();
		this->height = board.size();
		tmpBoard = board;
	}
}

void Board::openMaze() {
	string maze1 = "maze1.txt";
	char buffer[100];
	fstream file(maze1.c_str());
	if (!file) {
		cout << "Can't find \"maze1.txt\"\n";
		system("PAUSE");
		exit(EXIT_FAILURE);
	}
	// row size
	file.getline(buffer, 100);
	int row = atoi(buffer);
	/* hero's pos*/
	file.getline(buffer, 100);
	string s(buffer);
	istringstream ss(s);
	string token;
	vector<string>vtmp;
	while (getline(ss, token, ' ')) {
		vtmp.push_back(token);
	}
	gHPosXRecord = stoi(vtmp[0]);
	gHPosYRecord = stoi(vtmp[1]);

	/*  maze   */
	for (int i = 0; i < row; i++) {
		file.getline(buffer, 100);
		vector<char>tmpRow;
		for (int j = 0; buffer[j] != '\n' && buffer[j] != '\0'; j++) {
			tmpRow.push_back(buffer[j]);
		}
		this->board.push_back(tmpRow);
	}
	this->board[gHPosXRecord][gHPosYRecord] = ' ';
}

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

void Board::openRecord() {
	string inputFile = "record.txt";
	fstream file(inputFile.c_str());
	if (!file) {
		// first time play game
	}
	else {
		char buffer[100];
		file.getline(buffer, 20);
		int level = atoi(buffer);
		gLevel = level;
		file.getline(buffer, 100);
		int row = atoi(buffer);
		//map
		for (int i = 0; i < row; i++) {
			file.getline(buffer, 100);
			vector<char>tmp;
			for (int i = 0; buffer[i] != '\n' && buffer[i] != '\0'; i++) {
				tmp.push_back(buffer[i]);
			}
			this->board.push_back(tmp);
		}
		this->height = board.size();
		tmpBoard = board;

		// Icons
		file.getline(buffer, 100);
		gHIconRecord = buffer[0];
		gCIconRecord = buffer[2];  //2
		// pos hp ulti
		file.getline(buffer, 100);
		string s(buffer);
		istringstream ss(s);
		string token;
		vector<string>vtmp;
		while (getline(ss,token,' '))
			vtmp.push_back(token);
		gHPosXRecord = stoi(vtmp[0]);
		gHPosYRecord = stoi(vtmp[1]);
		gHhp = stoi(vtmp[2]);
		gUltimate = stoi(vtmp[3]);
		board[gHPosXRecord][gHPosYRecord] = ' ';
		tmpBoard = board;
		/*----------------------------------------------*/
		

		// c pos
		file.getline(buffer, 100);
		int numOfc = atoi(buffer);
		for (int i = 0; i < numOfc ; i++) {
			file.getline(buffer, 100);
			string s(buffer);
			istringstream ss(s);
			string token;
			vector<int>tmp;
			while (getline(ss, token, ' ')) {
				tmp.push_back(stoi(token));
			}
			gCPosRecord[i].x = tmp[0];
			gCPosRecord[i].y = tmp[1];
			gChp[i] = tmp[2];
		}

	}
}