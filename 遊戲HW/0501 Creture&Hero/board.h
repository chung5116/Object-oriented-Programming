// Name: Yung-Cheng Chang B10706009
// Date: 2020.04.09
// Last Update: 2020.04.11
// Problem statement: Hero & Creature
#ifndef BOARD_H
#define BOARD_H
using namespace std;
#include<vector>
#include<string>
#include<sstream>
#include<iostream>
#include<fstream>
#include <time.h>
#include"allStruct.h"


class Creature;
class Hero;
extern int gLevel;
extern int gUltimate;
extern char gHIconRecord;
extern char gCIconRecord;
extern int gHhp;
extern int gHPosXRecord;
extern int gHPosYRecord;
extern vector<int>gChp;
extern vector<Position>gCPosRecord;

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
	void resetBoard(vector<vector<char>>v) { this->board = v; }			//���@�i�a��
	vector<vector<char>>*getTmpboard() { return &tmpBoard ;}		//�Ȯɪ� pass by reference
	vector<vector<char>>getBoard() { return tmpBoard; }		//������ĥ�ϥ�
	//void carryoutCommand(bool(&inputState)[7], Creature* gCreature[3], Hero& hero);
	void openRecord();
	void openMaze();
};


#endif // !BOARD_H