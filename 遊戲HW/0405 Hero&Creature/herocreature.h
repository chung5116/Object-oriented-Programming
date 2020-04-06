// Name: 張永承	
// Date: 2020.03.31
// Last Update: 2020.03.27
// Problem statement: Hero & Creature
#ifndef HERO_H
#define HERO_H
#include<iostream>
#include<vector>
#include<thread>
#include <stdlib.h> /* 亂數相關函數 */
#include<math.h>
#include <windows.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

#include "allStruct.h"
#include"board.h"
#include "trigger.h"

extern Board gBoard_obj;
extern Trigger* gTrigger[3];
extern void printoutText(void);
extern void printBoard();

// Hero class
class Hero {
private:
	Position posHero;
	char icon = 'H';
public:
	friend class Creature;
	int hp = 100;
	int level = 0;
	bool invalidDirection = false;   // if true it's invalid
	Hero(Board&bd);
	Position getPos(void) { return this->posHero; }
	char getIcon(void) { return this->icon; }
	void setPosition(int x, int y) { this->posHero.x = x; this->posHero.y = y; }
	void carryoutCommand(bool(&inputState)[7], Creature* gCreature[3]);
	void drawAttckRange(Creature* gCreature[3]);
	void heroPassTrigger(Trigger* gTrigger[3]);
};


// Creature class
class Creature {
private:
	Position posCreature;
	char icon = 'C';
public:
	friend class Hero;
	int static numofC;	//how many creature in the board
	int hp = 3;
	int boardHeight = 0;
	int numOffindHero = 0;
	bool exist = false;
	bool findHero = false;
	Position cDirection;				//判斷英雄在哪個方向

	Creature(Board& bd);
	Creature(Board& bd,char icon);
	Position getPos(void) { return this->posCreature; }
	Position generateRandomXY(Board& bd);
	char getIcon(void) { return this->icon; }
	void setPosition(int x, int y) { this->posCreature.x = x; this->posCreature.y = y; }
	void creatureDetectHero(Hero& gHero_obj);
	void attackHero(Hero&gHero_obj);
};

#endif // !HERO_H