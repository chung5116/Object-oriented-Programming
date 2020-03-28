// Name: ±i¥Ã©Ó	
// Date: 2020.03.24
// Last Update: 2020.03.20
// Problem statement: Creature Class
#pragma once
#include "allStruct.h"


// Hero class
class Hero {
private:
	Position posHero;

	char icon = 'H';
public:
	int hp;
	int level = 0;
	Hero(int x, int y, int hp) { this->posHero.x = x, this->posHero.y = y; this->hp = hp; }
	Position getPos(void) { return this->posHero; }
	char getIcon(void) { return this->icon; }
	void setPosition(int x, int y) { this->posHero.x = x; this->posHero.y = y; }
};