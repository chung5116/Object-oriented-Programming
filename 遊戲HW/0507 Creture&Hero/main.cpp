// Name: Yung-Cheng Chang B10706009
// Date: 2020.04.09
// Last Update: 2020.04.11
// Problem statement: Hero & Creature
using namespace std;
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define RESET   "\033[0m"
#define allCommand 8
#include<iostream>
#include<conio.h>
#include "board.h"
#include"herocreature.h"
#include "allStruct.h"
#include "trigger.h"
//#include"creature.h"
const char GFIND = '!';
const int gnumOfCreature = 6;
const int gNumOfTrigger = 3;
int gUltimate = 3;
Board gBoard_obj;
Hero gHero_obj(gBoard_obj);
Creature* gCreature[gnumOfCreature];
Trigger* gTrigger[gNumOfTrigger];

map<int, char>gCreatureMap = {
	{0,'B'},
	{1,'W'},
	{2,'G'},
	{3,'C'},
	{4,'T'},
	{5,'L'}
};
// �L�X��T
void printoutText(void);
// set
void initialize(void);
// ����user �����O
bool getInputCommand(bool(&inputState)[allCommand]);
// carryout 
void carryoutCommand(bool(&inputState)[8]);
// update creature x,y
void updateCreature(void);
// print board
void printBoard();
// check all creature dead?
bool allCreatureDead();
// Position +-
const Position operator+(const Position& a, const Position& b);
//const Position operator=(const Position& a, const Position& b);
void ClearScreen();
//force field
void forceField();


int main() {
	bool inputState[8];
	initialize();
	while (gHero_obj.hp > 0) {
		// �ͪ����d
		for (int i = 0; i < gnumOfCreature; i++) {
			if (gCreature[i]->exist == true)
				gCreature[i]->creatureDetectHero(gHero_obj);
		}
		system("CLS");
		ClearScreen();
		printoutText();
		printBoard();
		if (getInputCommand(inputState)) {
			break;
		}
		carryoutCommand(inputState);
		gHero_obj.heroPassTrigger(gTrigger, gCreature);
		// check if there any creature is dead

		//force field 
		forceField();
		for (int i = 0; i < gnumOfCreature; i++) {
			if (gCreature[i]->hp == 0) {
				gCreature[i]->exist = false;
			}
			if (gCreature[i]->exist) {
				if (gCreature[i]->findHero) {
					Position posC = gCreature[i]->getPos();
					Position newDir = posC + gCreature[i]->cDirection;
					if (gBoard_obj.checkValid(newDir.x, newDir.y)) {
						gCreature[i]->setPosition(newDir);
					}
					gCreature[i]->attackHero(gHero_obj);
				}
				else {
					gCreature[i]->walkAround();   // �S�o�{�N�C��
				}
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
	Creature::numofC = 6;
	for (int i = 0; i < gnumOfCreature; i++) {
		gCreature[i] = new Creature(gBoard_obj, gCreatureMap[i]);
		Position posc = gCreature[i]->getPos();
		gBoard_obj.setBoard(posc.x, posc.y, gCreatureMap[i]);
		gCreature[i]->exist = true;
	}

	//gCreature[0]->exist = true;
	/*Position posCreature = gCreature[0]->getPos();
	gBoard_obj.setBoard(posCreature.x, posCreature.y, gCreature[0]->getIcon());*/

	//gTrigger[0] = new Trigger(gBoard_obj);
	Trigger::numofT++;
	for (int i = 0; i < gNumOfTrigger; i++) {
		if (i == 0)
			gTrigger[i] = new Trigger(gBoard_obj);
		else
			gTrigger[i] = new Trigger(gBoard_obj, gTrigger[0]->getIcon());
	}
	//gTrigger[0]->exist = true;
	Position posTrigger = gTrigger[0]->getPos();
	gBoard_obj.setBoard(posTrigger.x, posTrigger.y, gTrigger[0]->getIcon());
}

void printoutText() {
	std::cout << "Use wasd to control Hero, press \"k\" to attack , press\"j\"to ultimate" << endl;
	//std::cout << "Press \"j\" to add creature, press \"l\" to add trigger, press \"space\" to escape " << endl;
	std::cout << "Press\"space\" to escape " << endl;
	std::cout << "Press ESC to end the game\n" << endl;
	//std::cout << "\n\nHero's HP :  " << gHero_obj.hp << "/100	Hero's level : " << gHero_obj.level << endl;
	std::cout << "Ultimate :  " << gUltimate << "/3 " << endl;
	std::cout << "\n\nHero's HP :  " << gHero_obj.hp << "/100 " << endl;

	for (int i = 0; i < gnumOfCreature; i++) {
		if (gCreature[i]->exist == true) {
			std::cout << "Creature " << gCreatureMap[i] << "'s HP : " << gCreature[i]->hp;
			if (gCreature[i]->findHero) {
				std::cout << "	Creture " << gCreatureMap[i] << " has find the Hero in the ( " << gCreature[i]->cDirection.x << "," << gCreature[i]->cDirection.y << " ) direction.\n";
			}
			else {
				std::cout << "	Creature " << gCreatureMap[i] << " hasn't find the Hero\n";
			}
		}
	}
	if (gHero_obj.invalidDirection) {
		//std::cout << "Invalid direction" << endl;
	}
}

bool getInputCommand(bool(&inputState)[allCommand]) {
	for (int i = 0; i < 8; i++) {
		inputState[i] = false;
	}
	char input = _getch();
	if (input == 27) {      //press ESC
		return true;
	}
	else if (input == 'w' || input == 'W') {
		inputState[ValidInput::w] = true;
	}
	else if (input == 'a' || input == 'A') {
		inputState[ValidInput::a] = true;
	}
	else if (input == 's' || input == 'S') {
		inputState[ValidInput::s] = true;
	}
	else if (input == 'd' || input == 'D') {
		inputState[ValidInput::d] = true;
	}
	else if (input == 'k' || input == 'K') {				//attack
		inputState[ValidInput::k] = true;
	}
	else if (input == 'j' || input == 'J') {			// create creature
		inputState[ValidInput::j] = true;			//Ultimate
	}
	else if (input == 'l' || input == 'L') {			// create trigger
		//inputState[ValidInput::l] = true;
	}
	else if (input == ' ') {
		inputState[ValidInput::space] = true;
	}
	return false;
}

void carryoutCommand(bool(&inputState)[8]) {
	Position tmpPos = gHero_obj.getPos();
	if (inputState[4]) {			//attack
		gHero_obj.invalidDirection = false;
		gHero_obj.drawAttckRange(gCreature);
	}
	else {
		if (inputState[0]) {		// w
			if (gBoard_obj.checkValid(--tmpPos.x, tmpPos.y)) {
				gHero_obj.setPosition(tmpPos);
				gHero_obj.invalidDirection = false;
			}
			else {
				gHero_obj.invalidDirection = true;
			}
		}
		else if (inputState[1]) {			// a 
			if (gBoard_obj.checkValid(tmpPos.x, --tmpPos.y)) {
				gHero_obj.setPosition(tmpPos);
				gHero_obj.invalidDirection = false;
			}
			else {
				gHero_obj.invalidDirection = true;
			}
		}
		else if (inputState[2]) {			// s 
			if (gBoard_obj.checkValid(++tmpPos.x, tmpPos.y)) {
				gHero_obj.setPosition(tmpPos);
				gHero_obj.invalidDirection = false;
			}
			else {
				gHero_obj.invalidDirection = true;
			}
		}
		else if (inputState[3]) {			// d 
			if (gBoard_obj.checkValid(tmpPos.x, ++tmpPos.y)) {
				gHero_obj.setPosition(tmpPos);
				gHero_obj.invalidDirection = false;
			}
			else {
				gHero_obj.invalidDirection = true;
			}
		}
		else if (inputState[5]) {	// add creature		j
			if (gUltimate > 0) {
				gUltimate--;
				while (1) {
					int ran = rand() % 3;
					if (gCreature[ran]->exist) {
						gCreature[ran]->hp--;
						// ����
						PlaySound(L"attack.wav", NULL, SND_FILENAME | SND_ASYNC);
						if (gCreature[ran]->hp == 0)
							gCreature[ran]->exist = false;
						break;
					}
				}
			}
			/*if (Creature::numofC <= 3) {
				for (int i = 0; i < 3; i++) {
					if (gCreature[i]->exist == false) {
						Creature::numofC++;
						gCreature[i]->exist = true;
						// input x,y
						Position newDir = gCreature[i]->generateRandomXY(gBoard_obj);
						gCreature[i]->setPosition(newDir);
						// set x,y;
						break;
					}
				}
			}*/
		}
		else if (inputState[6]) {	//add trigger			l
			/*if (Trigger::numofT <= 3) {
				for (int i = 0; i < 3; i++) {
					if (gTrigger[i]->exist == false) {
						Trigger::numofT++;
						gTrigger[i]->exist = true;
						Position posT = gTrigger[i]->generateRandomXY(gBoard_obj);
						gTrigger[i]->setPosition(posT.x, posT.y);
						// input x,y
						//gTrigger[numofT].
						//�����b+f
						break;
					}
				}
			}*/
		}
		else if (inputState[7]) {
			vector<vector<char>>tmp = gBoard_obj.getBoard();
			if (tmp[tmpPos.x + 1][tmpPos.y] == '@' ||
				tmp[tmpPos.x][tmpPos.y + 1] == '@' ||
				tmp[tmpPos.x - 1][tmpPos.y] == '@' ||
				tmp[tmpPos.x][tmpPos.y - 1] == '@') {
				cout << "You WIN !\n";
				system("pause");
				exit(1);
			}
		}
		//
	}
}

void updateCreature(void) {
	for (int i = 0; i < gnumOfCreature; i++) {
		if (gCreature[i]->findHero && gCreature[i]->exist) {
			Position posC = gCreature[i]->getPos();
			Position newDir = posC + gCreature[i]->cDirection;

			if (gBoard_obj.checkValid(newDir.x, newDir.y)) {
				gCreature[i]->setPosition(newDir);
			}
		}
	}
}

void printBoard() {
	gBoard_obj.resetBoard();
	vector<vector<char>>* tmpBoard = gBoard_obj.getTmpboard();
	Position posH = gHero_obj.getPos();
	(*tmpBoard)[posH.x][posH.y] = gHero_obj.getIcon();      //hero 
	//force field
	/*if (gBoard_obj.checkValid(posH.x - 1, posH.y)) {
		(*tmpBoard)[posH.x - 1][posH.y] = '.';		// top
	}
	if (gBoard_obj.checkValid(posH.x + 1, posH.y)) {
		(*tmpBoard)[posH.x + 1][posH.y] = '.';		// bottom
	}

	if (gBoard_obj.checkValid(posH.x, posH.y - 1)) {
		(*tmpBoard)[posH.x][posH.y - 1] = '.';		// left
	}
	if (gBoard_obj.checkValid(posH.x, posH.y + 1)) {
		(*tmpBoard)[posH.x][posH.y + 1] = '.';		//right
	}

	if (gBoard_obj.checkValid(posH.x - 1, posH.y + 1)) {
		(*tmpBoard)[posH.x - 1][posH.y + 1] = '.';			//�k�W
	}
	if (gBoard_obj.checkValid(posH.x - 1, posH.y - 1)) {
		(*tmpBoard)[posH.x - 1][posH.y - 1] = '.';			//���W
	}
	if (gBoard_obj.checkValid(posH.x + 1, posH.y + 1)) {
		(*tmpBoard)[posH.x + 1][posH.y + 1] = '.';			//�k�U
	}
	if (gBoard_obj.checkValid(posH.x + 1, posH.y - 1)) {
		(*tmpBoard)[posH.x + 1][posH.y - 1] = '.';			//���U
	}*/


	char c = gCreature[0]->getIcon();
	char t = gTrigger[0]->getIcon();
	Position posC[gnumOfCreature];
	Position posT[3];

	for (int i = 0; i <gnumOfCreature ; i++) {						//get pos
		posC[i] = gCreature[i]->getPos();
		//posT[i] = gTrigger[i]->getPos();
	}

	for (int i = 0; i < gnumOfCreature; i++) {     // if c exist -> put in the  board
		if (gCreature[i]->exist) {
			(*tmpBoard)[posC[i].x][posC[i].y] = gCreatureMap[i];
			/*if (gCreature[i]->findHero) {
				(*tmpBoard)[posC[i].x][posC[i].y] = GFIND;
			}*/
		}
	}

	/*for (int i = 0; i < 3; i++) {				//if t exist->put in the board
		if (gTrigger[i]->exist) {
			(*tmpBoard)[posT[i].x][posT[i].y] = t;
		}
	}*/

	for (int i = 0; i < (*tmpBoard).size(); i++) {
		for (int j = 0; j < (*tmpBoard)[i].size(); j++) {
			bool print = true;  // avoid cout twice

			if (print) {
				for (int k = 0; k < Trigger::numofT; k++) {
					if (gCreature[k]->exist) {
						if (i == posT[k].x && j == posT[k].y) {
							std::cout << " " << RED << (*tmpBoard)[i][j];
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
							std::cout << " " << YELLOW << (*tmpBoard)[i][j];
							print = false;
							continue;
						}
					}
				}
			}
			std::cout << RESET;
			if (print)
				std::cout << " " << (*tmpBoard)[i][j];
		}
		std::cout << endl;
	}
	if (gHero_obj.hp <= 0) {
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

const Position operator+(const Position& a, const Position& b) {
	Position res;
	res.x = a.x + b.x;
	res.y = a.y + b.y;
	return res;
}

void forceField() {
	Position posh = gHero_obj.getPos();
	for (int i = 0; i < gnumOfCreature; i++) {
		if (gCreature[i]->exist == true) {
			Position posc = gCreature[i]->getPos();
			int dx = posh.x - posc.x;
			int dy = posh.y - posc.y;
			double dis = abs(dx) + abs(dy);
			if (dis <= 2)
				gCreature[i]->hp--;
		}
	}
}