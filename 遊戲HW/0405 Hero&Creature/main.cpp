// Name: 張永承	
// Date: 2020.03.31
// Last Update: 2020.03.27
// Problem statement: Hero & Creature
using namespace std;
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define RESET   "\033[0m"
#define allCommand 7
#include<iostream>
#include<conio.h>
#include "board.h"
#include"herocreature.h"
#include "allStruct.h"
#include "trigger.h"
//#include"creature.h"
const char GFIND = '!';
const int gnumOfCreature = 3;
const int gNumOfTrigger = 3;
Board gBoard_obj;
Hero gHero_obj(gBoard_obj);
Creature* gCreature[3];
Trigger* gTrigger[3];

// 印出資訊
void printoutText(void);
// set
void initialize(void);
// 接收user 的指令
bool getInputCommand(bool(&inputState)[allCommand]);
// update creature x,y
void updateCreature(void);
// print board
void printBoard();
// check all creature dead?
bool allCreatureDead();


int main() {
	bool inputState[7];
	initialize();
	while (gHero_obj.hp > 0 && Creature::numofC > 0) {
		// 生物偵查
		for (int i = 0; i < gnumOfCreature; i++) {
			if(gCreature[i]->exist==true)
				gCreature[i]->creatureDetectHero(gHero_obj);
		}
		system("CLS");
		printoutText();
		printBoard();
		if (getInputCommand(inputState)) {
			break;
		}
		gHero_obj.carryoutCommand(inputState, gCreature);
		gHero_obj.heroPassTrigger(gTrigger);
		// check if there any creature is dead
		for (int i = 0; i < Creature::numofC; i++) {
			if (gCreature[i]->hp == 0) {
				gCreature[i]->exist = false;
			}
			//update creature position
			if (gCreature[i]->exist) {
				Position posC = gCreature[i]->getPos();
				gCreature[i]->setPosition(posC.x + gCreature[i]->cDirection.x, posC.y + gCreature[i]->cDirection.y);
				gCreature[i]->attackHero(gHero_obj);
			}
		}


	}
	system("CLS");
	printoutText();
	printBoard();
	return 0;
}

void initialize() {
	//gCreature[0] = new Creature(gBoard_obj);   // build first creature
	Creature::numofC++;
	for (int i = 0; i < gnumOfCreature; i++) {
		if (i == 0)
			gCreature[i] = new Creature(gBoard_obj);   // build first creature
		else
			gCreature[i] = new Creature(gBoard_obj, gCreature[0]->getIcon());
	}

	gCreature[0]->exist = true;
	Position posCreature = gCreature[0]->getPos();
	gBoard_obj.setBoard(posCreature.x, posCreature.y,gCreature[0]->getIcon());

	//gTrigger[0] = new Trigger(gBoard_obj);
	Trigger::numofT++;
	for (int i = 0; i < gNumOfTrigger; i++) {
		if (i == 0)
			gTrigger[i] = new Trigger(gBoard_obj);
		else
			gTrigger[i] = new Trigger(gBoard_obj,gTrigger[0]->getIcon());
	}
	gTrigger[0]->exist = true;
	Position posTrigger = gTrigger[0]->getPos();
	gBoard_obj.setBoard(posTrigger.x, posTrigger.y, gTrigger[0]->getIcon());
}

void printoutText() {
	std::cout << "Use wasd to control Hero, press \"k\" to attack " << endl;
	std::cout << "Press ESC to end the game\n" << endl;
	std::cout << "\n\nHero's HP :  " << gHero_obj.hp << "/100	Hero's level : " << gHero_obj.level << endl;
	for (int i = 0; i < gnumOfCreature; i++) {
		if (gCreature[i]->exist == true) {
			std::cout << "Creature "<<i<<"'s HP :　" << gCreature[i]->hp;
			if (gCreature[i]->findHero) {
				std::cout << "	Creture " << i << " has find the Hero in the ( " << gCreature[i]->cDirection.x << "," << gCreature[i]->cDirection.y << " ) direction.\n";
			}
			else {
				std::cout << "	Creature " << i << " hasn't find the Hero\n";
			}
		}
	}
	if (gHero_obj.invalidDirection) {
		std::cout << "Invalid direction" << endl;
	}
}

bool getInputCommand(bool(&inputState)[allCommand]) {
	for (int i = 0; i < 7; i++) {
		inputState[i] = false;
	}
	char input = _getch();
	if (input == 27) {      //press ESC
		return true;
	}
	else if (input == 'w' || input == 'W') {
		inputState[0] = true;
	}
	else if (input == 'a' || input == 'A') {
		inputState[1] = true;
	}
	else if (input == 's' || input == 'S') {
		inputState[2] = true;
	}
	else if (input == 'd' || input == 'D') {
		inputState[3] = true;
	}
	else if (input == 'k' || input == 'K') {				//attack
		inputState[4] = true;
	}
	else if (input == 'j' || input == 'J') {			// create creature
		inputState[5] = true;
	}
	else if (input == 'l' || input == 'L') {			// create trigger
		inputState[6] = true;
	}
	return false;
}

void updateCreature(void) {
	for (int i = 0; i < Creature::numofC; i++) {
		if (gCreature[i]->findHero) {
			Position posC = gCreature[i]->getPos();
			if (gBoard_obj.checkValid(posC.x + gCreature[i]->cDirection.x, posC.y + gCreature[i]->cDirection.y)) {
				gCreature[i]->setPosition(posC.x + gCreature[i]->cDirection.x, posC.y + gCreature[i]->cDirection.y);
			}
		}
	}
}

void printBoard() {
	gBoard_obj.resetBoard();
	vector<vector<char>>*tmpBoard = gBoard_obj.getTmpboard();
	Position posH = gHero_obj.getPos();   
	(*tmpBoard)[posH.x][posH.y] = gHero_obj.getIcon();      //hero 
	char c = gCreature[0]->getIcon();
	char t = gTrigger[0]->getIcon();
	Position posC[3];
	Position posT[3];

	for (int i = 0; i < 3; i++) {						//get pos
		posC[i] = gCreature[i]->getPos();
		posT[i] = gTrigger[i]->getPos();
	}

	for (int i = 0; i <3; i++) {     // if c exist -> put in the  board
		if (gCreature[i]->exist) {
			(*tmpBoard)[posC[i].x][posC[i].y] = c;
			if (gCreature[i]->findHero) {
				(*tmpBoard)[posC[i].x][posC[i].y] = GFIND;
			}
		}
	}

	for (int i = 0; i < 3; i++) {				//if t exist->put in the board
		if (gTrigger[i]->exist) {
			(*tmpBoard)[posT[i].x][posT[i].y] = t;
		}
	}

	for (int i = 0; i < (*tmpBoard).size(); i++) {
		for (int j = 0; j < (*tmpBoard)[i].size(); j++) {
			bool print = true;  // avoid cout twice

			if (print) {
				for (int k = 0; k < Trigger::numofT; k++) {
					if (gCreature[k]->exist) {
						if (i == posT[k].x && j == posT[k].y) {
							std::cout << RED << (*tmpBoard)[i][j];
							print = false;
							continue;
						}
					}
				}
			}
			if (print) {
				for (int k = 0; k < Creature::numofC; k++) {
					if (gCreature[k]->exist) {
						if (i == posC[k].x && j == posC[k].y) {
							std::cout << YELLOW << (*tmpBoard)[i][j];
							print = false;
							continue;
						}
					}
				}
			}
			std::cout<< RESET;
			if(print)
				std::cout << (*tmpBoard)[i][j];
		}
		std::cout << endl;
	}
	if (gHero_obj.hp == 0) {
		std::cout << "\n You Lose\n";
	}
	else if (allCreatureDead()) {
		std::cout << "\n You WIN\n";
	}
}


bool allCreatureDead() {
	for (int i = 0; i < 3; i++) {
		if (gCreature[i]->exist) {
			return false;
		}
	}
	return true;
}