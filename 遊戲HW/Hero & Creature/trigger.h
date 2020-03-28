// Name: ±i¥Ã©Ó	
// Date: 2020.03.24
// Last Update: 2020.03.20
// Problem statement: Creature Class

#pragma once
//#include "allStruct.h"



class Trigger {
private:
	Position posTrigger;
	char icon = 'T';
public:
	Trigger(int x, int y) { this->posTrigger.x = x, this->posTrigger.y = y; }
	Position getPos(void) { return this->posTrigger; }
	char getIcon(void) { return this->icon; }
	void setPosition(int x, int y) { this->posTrigger.x = x; this->posTrigger.y = y; }
};