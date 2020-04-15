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
	bool checkValid(int x, int y); // 確認位置是否存在
	//void printoutBoard(void);
	void setBoard(int x, int y, char in);
	void resetBoard(void) { this->tmpBoard = this->board; }
	vector<vector<char>>*getTmpboard() { return &tmpBoard ;}		//暫時的 pass by reference
	vector<vector<char>>getBoard() { return tmpBoard; }		//給攻擊艦使用
	//void carryoutCommand(bool(&inputState)[7], Creature* gCreature[3], Hero& hero);
	
	

};


#endif // !BOARD_H