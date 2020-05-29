// Name: ±i¥Ã©Ó	
// Date: 2020.03.31
// Last Update: 2020.03.27
// Problem statement: Hero & Creature

#ifndef TRIGGER_H
#define TRIGGER_H

#include"allStruct.h"
#include"board.h"


class Trigger {
private:
	Position posTrigger;
	char icon = 'T';
public:
	int static numofT;   //how many trigger in the board
	int boardHeight = 0;
	bool exist = false;

	Trigger(Board& bd);
	Trigger(Board& bd, char icon);
	Position getPos(void) { return this->posTrigger; }
	char getIcon(void) { return this->icon; }
	void setPosition(int x, int y) { this->posTrigger.x = x; this->posTrigger.y = y; }
	Position generateRandomXY(Board& bd);
};



#endif // !TRIGGER_H