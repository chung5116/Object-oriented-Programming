//// Name: 張永承	
//// Date: 2020.03.31
//// Last Update: 2020.03.27
//// Problem statement: Hero & Creature
//#ifndef CREATURE_H
//#define CREATURE_H
//#include<iostream>
//#include "allStruct.h"
//#include"board.h"
//#include"hero.h"
//#include <stdlib.h> /* 亂數相關函數 */
//
//// Creature class
//class Creature {
//private:
//	Position posCreature;
//	char icon = 'C';
//public:
//	int static numofC;	//how many creature in the board
//	int hp = 3;
//	int boardHeight = 0;
//	bool exist = false;
//	bool findHero = false;
//	Position cDirection;				//判斷英雄在哪個方向
//
//	Creature(Board& bd);
//	Position getPos(void) { return this->posCreature; }
//	Position generateRandomXY(Board& bd);
//	char getIcon(void) { return this->icon; }
//	void setPosition(int x, int y) { this->posCreature.x = x; this->posCreature.y = y; }
//	void creatureDetectHero( Hero& gHero_obj);
//};
//
//
//#endif // !CREATURE_H