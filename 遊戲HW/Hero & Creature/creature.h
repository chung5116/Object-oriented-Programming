// Name: ±i¥Ã©Ó	
// Date: 2020.03.24
// Last Update: 2020.03.20
// Problem statement: Creature Class

#pragma once
#include "allStruct.h"


// Creature class
class Creature {
private:
	Position posCreature;
	char icon = 'C';
public:
	int hp = 3;
	Creature(int x, int y) { this->posCreature.x = x, this->posCreature.y = y; }
	Position getPos(void) { return this->posCreature; }
	char getIcon(void) { return this->icon; }
	void setPosition(int x, int y) { this->posCreature.x = x; this->posCreature.y = y; }
};