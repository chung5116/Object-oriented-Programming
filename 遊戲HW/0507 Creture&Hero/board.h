// Name: Yung-Cheng Chang B10706009
// Date: 2020.04.09
// Last Update: 2020.04.11
// Problem statement: Hero & Creature
#ifndef BOARD_H
#define BOARD_H
using namespace std;
#include<vector>
#include<iostream>
#include<fstream>
#include <time.h>
#include"allStruct.h"


class Creature;
class Hero;



class Board {

private:
	vector<vector<char>>board;
	vector<vector<char>>tmpBoard;
public:
	Board();

	int height = 0;	// board height
	bool checkValid(int x, int y); // �T�{��m�O�_�s�b
	//void printoutBoard(void);
	void setBoard(int x, int y, char in);
	void resetBoard(void) { this->tmpBoard = this->board; }
	vector<vector<char>>* getTmpboard() { return &tmpBoard; }		//�Ȯɪ� pass by reference
	vector<vector<char>>getBoard() { return tmpBoard; }		//������ĥ�ϥ�
	//void carryoutCommand(bool(&inputState)[7], Creature* gCreature[3], Hero& hero);


};


#endif // !BOARD_H