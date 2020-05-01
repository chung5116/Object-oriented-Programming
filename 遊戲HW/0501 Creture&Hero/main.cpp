// Name: Yung-Cheng Chang B10706009
// Date: 2020.04.29
// Last Update: 2020.05.01
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
const int gnumOfCreature = 3;
const int gNumOfTrigger = 3;
const vector<string>gMazeFileName = { "maze1.txt","maze2.txt" ,"maze3.txt" ,"maze4.txt" ,"maze5.txt" };
int gUltimate = 3;
int gLevel = 1;   //紀錄現在關卡等級
char gHIconRecord;		// openRecord
int gHhp;
int gHPosXRecord;
int gHPosYRecord;
char gCIconRecord;	//openRecord
vector<Position>gCPosRecord{ 3,Position() };
vector<int>gChp{ 3,0 };
Board gBoard_obj;
Hero gHero_obj(gBoard_obj);
Creature* gCreature[gnumOfCreature];
Trigger* gTrigger[gNumOfTrigger];

const enum ValidInput
{
	w = 0,		//up
	a = 1,		//left
	s = 2,		//down
	d = 3,		//right
	k = 4,		//attack
	j = 5,		//add creature
	l = 6,		//add trigger
	space = 7,	//space
};

// 印出資訊
void printoutText(void);
// set
void initialize(void);
// 接收user 的指令
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
// storeing  @時呼叫，儲存下一張地圖的資訊
void storeing();
//loading  new maze and update information
void loadingMaze();


int main() {
	bool inputState[8];
	initialize();
	while (gHero_obj.hp > 0 && gLevel<=5) {
		// 生物偵查
		for (int i = 0; i < gnumOfCreature; i++) {
			if(gCreature[i]->exist==true)
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
		gHero_obj.heroPassTrigger(gTrigger,gCreature);
		// check if there any creature is dead
		for (int i = 0; i < 3; i++) {
			if (gCreature[i]->hp == 0) {
				gCreature[i]->exist = false;
			}
			if (gCreature[i]->exist ) {
				if (gCreature[i]->findHero) {
					Position posC = gCreature[i]->getPos();
					Position newDir = posC + gCreature[i]->cDirection;
					if (gBoard_obj.checkValid(newDir.x, newDir.y)) {
						gCreature[i]->setPosition(newDir);
					}
					gCreature[i]->attackHero(gHero_obj);
				}
				else {
					gCreature[i]->walkAround();   // 沒發現就遊蕩
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
	Creature::numofC = 2;
	if (gLevel == 1) {
		for (int i = 0; i < gnumOfCreature; i++) {
			if (i == 0)
				gCreature[i] = new Creature(gBoard_obj);   // build first creature
			else
				gCreature[i] = new Creature(gBoard_obj, gCreature[0]->getIcon());
			//gCreature[i]->exist = true;
			gCreature[i]->exist = false;
		}
		//gCreature[2]->exist = false;
		gCreature[0]->exist = true;
		Position posCreature = gCreature[0]->getPos();
		gBoard_obj.setBoard(posCreature.x, posCreature.y, gCreature[0]->getIcon());
	}
	else {
		for (int i = 0; i < 3; i++) {
			if (gCPosRecord[i].x != 0) {
				gCreature[i] = new Creature(gBoard_obj,gCIconRecord, gCPosRecord[i].x, gCPosRecord[i].y,gChp[i]);
				gCreature[i]->exist = true;
			}
			else {
				gCreature[i] = new Creature(gBoard_obj, gCIconRecord, 0,0,0);
				gCreature[i]->exist = false;
			}
		}
	}
	//gTrigger[0] = new Trigger(gBoard_obj);
	Trigger::numofT++;
	for (int i = 0; i < gNumOfTrigger; i++) {
		if (i == 0)
			gTrigger[i] = new Trigger(gBoard_obj);
		else
			gTrigger[i] = new Trigger(gBoard_obj,gTrigger[0]->getIcon());
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
	std::cout << "Ultimate :  " << gUltimate << "/3 "<< endl;
	std::cout << "\n\nHero's HP :  " << gHero_obj.hp << "/100 "<< endl;
	
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
						// 音效
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
						//等等在+f
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
				if (gLevel == 5) {
					cout << "You WIN !!! ";
					system("pause");
					exit(1);
				}
				else {
					gLevel++;
					for (int i = 0; i < 2; i++) {
						gCreature[i]->exist = true;
					}
					// 下一張地圖
					loadingMaze();
					// 儲存進度
					storeing();
				}
			}
		}
		//
	}
}


void storeing() {
	string recordFileName = "record.txt";
	ofstream output(recordFileName);
	if (!output) {
		cout << "無法儲存進度\n";
		return;
	}
	// if open file successfully
	output << gLevel << endl;

	vector<vector<char>>tmp = gBoard_obj.getBoard();
	output << tmp.size() << endl;
	for (int i = 0; i < tmp.size(); i++) {
		for (int j = 0; j < tmp[i].size(); j++) {
			output << tmp[i][j];
		}
		output << endl;
	}
	output << gHero_obj.getIcon() << " " << gCreature[0]->getIcon() << endl;
	Position posh = gHero_obj.getPos();
	output << posh.x << " " << posh.y << " " << gHero_obj.hp << " " << gUltimate << endl;
	int numOfC = 0;
	for (int i = 0; i < 2; i++) {
		if (gCreature[i]->exist) {
			numOfC++;
		}
	}
	output << numOfC;
	for (int i = 0; i < 2; i++) {
		if (gCreature[i]->exist) {
			Position posc = gCreature[i]->getPos();
			output << endl << posc.x << " " << posc.y << " " << gCreature[i]->hp;
		}
	}
	
	output.close();
}


void loadingMaze(){
	string mazeName = gMazeFileName[gLevel - 1];
	fstream file(mazeName.c_str());
	if (!file) {
		cout << "Can't find " << mazeName << endl;
	}
	else {
		char buffer[100];
		// row
		file.getline(buffer, 100);
		int row = atoi(buffer);
		// hero's pos
		file.getline(buffer, 100);
		string s(buffer);
		istringstream ss(s);
		string token;
		vector<string>vtmp;
		while (getline(ss, token, ' ')) {
			vtmp.push_back(token);
		}
		gHPosXRecord = stoi(vtmp[0]);
		gHPosYRecord = stoi(vtmp[1]);

		// maze
		vector<vector<char>>maze( row );
		for (int i = 0; i < row; i++) {
			file.getline(buffer, 100);
			for (int j = 0; buffer[j] != '\n' && buffer[j] != '\0'; j++) {
				maze[i].push_back(buffer[j]);
			}
		}
		maze[gHPosXRecord][gHPosYRecord] = ' ';
		gBoard_obj.resetBoard(maze);			//更新board
		gBoard_obj.resetBoard();		//更新tmpboard
		gBoard_obj.setBoard(gHPosXRecord, gHPosYRecord, gHero_obj.getIcon());    //加上原本的icons
		gUltimate = 3;
	}
	gHero_obj.hp = 100;
	gHero_obj.setPosition(gHPosXRecord, gHPosYRecord);
	for (int i = 0; i < 2; i++) {
		gCreature[i]->exist = true;
		gCreature[i]->hp = 3;
		Position newDir = gCreature[i]->generateRandomXY(gBoard_obj);
		gCreature[i]->setPosition(newDir);
	}
}


void updateCreature(void) {
	for (int i = 0; i < gnumOfCreature; i++) {
		if (gCreature[i]->findHero && gCreature[i]->exist) {
			Position posC = gCreature[i]->getPos();
			Position newDir = posC + gCreature[i]->cDirection;

			if (gBoard_obj.checkValid(newDir.x,newDir.y)) {
				gCreature[i]->setPosition(newDir);
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
							std::cout << " "<<RED << (*tmpBoard)[i][j];
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
			std::cout<< RESET;
			if(print)
				std::cout << " " << (*tmpBoard)[i][j];
		}
		std::cout << endl;
	}
	if (gHero_obj.hp <= 0) {
		std::cout << "\n You Lose\n";
	}
	else if (allCreatureDead()) {
		//std::cout << "\n You WIN\n";
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