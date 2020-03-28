// Name: 張永承	
// Date: 2020.03.24
// Last Update: 2020.03.20
// Problem statement: Creature Class
#pragma once
#include<iostream>
#include<windows.h>
#include<conio.h>
#include<vector>
#include<thread>
#include <stdlib.h>
#include "hero.h"
#include "creature.h"
#include "trigger.h"
#include "allStruct.h"
using namespace std;
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define RESET   "\033[0m"
/*--------------------------------------Variable-------------------------------*/
// Constent variable
const int GWIDTH = 10;
const int GHEIGHT = 10;
const char GWALL = 'O';
const char GSPACE = ' ';
const char GFIND = '!';
vector<vector<char>>gBoard;
vector<vector<char>>gtmpBoard;  //暫時儲存
bool gfindHero = false;			//是否找到hero
bool ginvalidDirection = false;    // 防止跑出地圖外
int gnumOffindHero = 0;    //怪物找到在範圍內找到第二次hero，則攻擊

/*---------------------------------------------------function-------------------*/
// 讓玩家決定一開始hero的位置，Creature的位置則是隨機
void buildHero();
// 初始化 board
void initializeBoard();
// 接收user 的指令
bool getInputCommand(bool(&inputState)[5]);
// 把board印出
void printoutBoard(void);
// 印出資訊
void printText(void);
// 執行使用者輸入
void carryoutCommand(bool(&inputState)[5]);
// 畫出攻擊範圍
void drawAttckRange(void);
// 確認要移動的位置是否存在
bool checkValid(int x, int y);
// 更新creature，如果有發現則移動
void updataCreature(void);
// 生物偵查Hero
void creatureDetectHero(void);
// 生物攻擊hero
void attackHero(void);
// 隨機產生座標組
Position generateRandomXY(void);
// 英雄經過trigger
void heroPassTrigger(int hx,int hy);
/*----------------------------------------------Class_Obj--------------------------*/
Hero gHero_obj(3, 2, 5);
Creature gCreature_obj(7, 7);
Trigger gTrigger_obj(5, 2);
cDirection gcDirection;			// 生物要移動的方向
/*--------------------------------------------------------------main ----------------------------*/

int main() {
	//buildHero();
	initializeBoard();
	bool inputState[5];
	// 直接一方獲勝
	while (gHero_obj.hp != 0 && gCreature_obj.hp != 0) {			//其中一方死亡則結束
		//生物先偵查
		creatureDetectHero();
		system("CLS");
		printText();
		printoutBoard();
		if (getInputCommand(inputState)) {
			break;
		}
		carryoutCommand(inputState);
		if (gCreature_obj.hp == 0) {
			break;
		}
		updataCreature();
		attackHero();			// hero 移動完後若還在生物攻擊範圍內則死亡
		
	}
	system("CLS");
	printText();
	printoutBoard();
	system("PAUSE");
	return 0;
}

/*--------------------------------------------------------function ---------------------------*/
void buildHero() {
	int x = 1;
	int y = 1;
	int hp = 1;
	while (1 <= x && x <= 9 && 1 <= y && y <= 9) {
		system("CLS");
		cout << "Enter position of hero (x : 1~9 , y : 1~9)\n";
		cin >> x >> y;
	}
	while (hp>0){
		cout << "Enter hp of hero ( suggest 1~3 )\n";
		cin >> hp;
	}
	gHero_obj.setPosition(x, y);
	gHero_obj.hp = hp;
}

Position generateRandomXY() {
	Position random;
	Position h = gHero_obj.getPos();
	Position c = gCreature_obj.getPos();
	// 隨機產生座標，且座標不能在 h & c上
	int min = 1;
	int max = GWIDTH-2;
	int dx = 0;
	int dy = 0;
	while (dx != h.x && dx != c.x && dy != c.y && dy !=h.y){

		dx = (rand() % (max - min + 1) )+ min;
		dy = (rand() % (max - min + 1) )+ min;
	}
	random.x = dx;
	random.y = dy;
	return random;
}



void initializeBoard() {
	for (int i = 0; i < GHEIGHT; i++) {
		vector<char>tmp;
		gBoard.push_back(tmp);
		gtmpBoard.push_back(tmp);
	}
	for (int i = 0; i < GHEIGHT; i++) {
		for (int j = 0; j < GWIDTH; j++) {
			if (i == 0 || i == GHEIGHT - 1 || j == 0 || j == GWIDTH - 1)
				gBoard[i].push_back(GWALL);
			else
				gBoard[i].push_back(GSPACE);
		}
	}
}


bool getInputCommand(bool(&inputState)[5]) {


	for (int i = 0; i < 5; i++) {
		inputState[i] = false;
	}
	char input = _getch();
	if (input == 27) {      //press ESC
		return true;
	}
	else if (input == 'w') {
		inputState[0] = true;
	}
	else if (input == 'a') {
		inputState[1] = true;
	}
	else if (input == 's') {
		inputState[2] = true;
	}
	else if (input == 'd') {
		inputState[3] = true;
	}
	else if (input == 'k') {				//attack
		inputState[4] = true;
	}
	return false;
}

void carryoutCommand(bool(&inputState)[5]) {
	Position posH = gHero_obj.getPos();
	Position posC = gCreature_obj.getPos();
	int tmpx = posH.x;
	int tmpy = posH.y;
	if (inputState[4]) {			//attack
		ginvalidDirection = false;
		drawAttckRange();
	}
	else {

		if (inputState[0]) {		// w
			if (checkValid(tmpx - 1, tmpy)) {
				gHero_obj.setPosition(tmpx - 1, tmpy);
				ginvalidDirection = false;
			}
			else {
				ginvalidDirection = true;
			}
		}
		else if (inputState[1]) {			// a 
			if (checkValid(tmpx, tmpy - 1)) {
				gHero_obj.setPosition(tmpx, tmpy - 1);
				ginvalidDirection = false;
			}
			else {
				ginvalidDirection = true;
			}
		}
		else if (inputState[2]) {			// s 
			if (checkValid(tmpx + 1, tmpy)) {
				gHero_obj.setPosition(tmpx + 1, tmpy);
				ginvalidDirection = false;
			}
			else {
				ginvalidDirection = true;
			}
		}
		else if (inputState[3]) {			// d 
			if (checkValid(tmpx, tmpy + 1)) {
				gHero_obj.setPosition(tmpx, tmpy + 1);
				ginvalidDirection = false;
			}
			else {
				ginvalidDirection = true;
			}
		}
		posH = gHero_obj.getPos();
		heroPassTrigger(posH.x, posH.y);
	}
	// 清除版面
	//system("CLS");
}

void heroPassTrigger(int hx, int hy) {
	Position posT = gTrigger_obj.getPos();
	if (hx == posT.x && hy == posT.y) {		//如果pass Trigger
		gHero_obj.hp++;
		gHero_obj.level++;
		posT = generateRandomXY();
		gTrigger_obj.setPosition(posT.x, posT.y);
	}
}

void printText() {
	cout << "Use wasd to control Hero, press \"k\" to attack " << endl;
	cout << "Press ESC to end the game\n\n" << endl;
	cout << "Hero's HP :  " << gHero_obj.hp <<"	Hero's level : "<<gHero_obj.level<< endl;
	cout << "Creature's HP :　" << gCreature_obj.hp << endl;
	if (!gfindHero) {
		cout << "Creature hasn't find the Hero\n";
	}
	else {
		cout << "Creture has find the Hero in the ( " << gcDirection.x << "," << gcDirection.y << " ) direction.\n";
	}
	if (ginvalidDirection) {
		cout << "Invalid direction" << endl;
	}
	
}


void printoutBoard(void) {
	gtmpBoard = gBoard;
	Position posH = gHero_obj.getPos();
	Position posC = gCreature_obj.getPos();
	Position posT = gTrigger_obj.getPos();
	gtmpBoard[posH.x][posH.y] = gHero_obj.getIcon();
	gtmpBoard[posT.x][posT.y] = gTrigger_obj.getIcon();
	if (gfindHero) {
		gtmpBoard[posC.x][posC.y] = GFIND;
	}
	else {
		gtmpBoard[posC.x][posC.y] = gCreature_obj.getIcon();
	}
	for (int i = 0; i < GHEIGHT; i++) {
		for (int j = 0; j < GWIDTH; j++) {
			if (i == posT.x && j == posT.y) {
				cout << RED << gtmpBoard[i][j];
			}
			else if (i == posC.x && j == posC.y) {
				cout<<YELLOW<< gtmpBoard[i][j];
			}
			else
				cout << RESET<<gtmpBoard[i][j];
		}
		cout << endl;
	}
	if (gHero_obj.hp == 0) {
		cout << "\n You Lose\n";
	}
	else if (gCreature_obj.hp == 0) {
		cout << "\n You WIN\n";
	}

}



void drawAttckRange(void) {
	Position posH = gHero_obj.getPos();
	Position posC = gCreature_obj.getPos();
	int hx = posH.x;
	int hy = posH.y;


	vector<vector<char>>attackBoard = gtmpBoard;
	attackBoard[hx - 1][hy] = '*';		// 上
	attackBoard[hx + 1][hy] = '*';		// 下	
	attackBoard[hx][hy - 1] = '*';		// 左
	attackBoard[hx][hy + 1] = '*';		//右
	attackBoard[hx - 1][hy + 1] = '*';			//右上
	attackBoard[hx - 1][hy - 1] = '*';			//左上
	attackBoard[hx + 1][hy + 1] = '*';			//右下
	attackBoard[hx + 1][hy - 1] = '*';			//左下
	// 清除版面
	system("CLS");
	printText();

	for (int i = 0; i < GHEIGHT; i++) {
		for (int j = 0; j < GWIDTH; j++) {
			if ((abs(hx - i) + abs(hy - j) <= 2) && (i != hx && j != hy))
				cout << "\033[32m" << attackBoard[i][j] << "\033[0m";
			else
				cout << attackBoard[i][j];
		}
		cout << endl;
	}
	this_thread::sleep_for(0.1s);			// 讓攻擊範圍停留0.1S
	system("CLS");
	printText();
	printoutBoard();

	if (sqrt(pow(abs(posH.x - posC.x), 2) + pow(abs(posH.y - posC.y), 2)) <= sqrt(2)) {					//生物在Hero的攻擊範圍內
		gCreature_obj.hp --;
	}
}

bool checaakValid(int x, int y) {
	if (x <= 0 || x >= 9 || y <= 0 || y >= 9) {
		return false;
	}
	return true;
}

void updataCreature() {
	if (gfindHero) {
		Position posC = gCreature_obj.getPos();
		if (checkValid(posC.x + gcDirection.x, posC.y + gcDirection.y))
			gCreature_obj.setPosition(posC.x + gcDirection.x, posC.y + gcDirection.y);
	}
}



void attackHero() {
	Position posH = gHero_obj.getPos();
	Position posC = gCreature_obj.getPos();
	if (gfindHero) {
		if (sqrt(pow(abs(posH.x - posC.x), 2) + pow(abs(posH.y - posC.y), 2)) <= sqrt(2)) {
			gnumOffindHero++;
			if (gnumOffindHero >= 2) {
				gHero_obj.hp--;
				
			}
		}
	}
	else {
		gnumOffindHero = 0;
	}

}


void creatureDetectHero() {
	Position posC = gCreature_obj.getPos();
	Position posH = gHero_obj.getPos();
	int xc = posC.x;
	int yc = posC.y;
	int xh = posH.x;
	int yh = posH.y;
	if (xc == xh && yc == yh) {		// hero 走到 creature上
		gHero_obj.hp--;					// game over
	}
	else if (xc == xh && yc != yh) {		// 左右
		gfindHero = true;
		if (yc > yh)
			gcDirection.x = 0, gcDirection.y = -1;
		else
			gcDirection.x = 0, gcDirection.y = 1;

	}
	else if (xc != xh && yc == yh) {		//上下
		gfindHero = true;
		if (xc > xh)
			gcDirection.x = -1, gcDirection.y = 0;
		else
			gcDirection.x = 1, gcDirection.y = 0;

	}
	else if (double(abs(xc - xh)) / double(abs(yc - yh)) == 1.0) {			//斜向
		gfindHero = true;
		if (xc > xh && yc > yh)
			gcDirection.x = 0, gcDirection.y = -1;
		else if (xc < xh && yc < yh)
			gcDirection.x = 0, gcDirection.y = 1;
		else if (xc > xh && yc < yh)
			gcDirection.x = 0, gcDirection.y = 1;
		else if (xc < xh && yc > yh)
			gcDirection.x = 0, gcDirection.y = -1;
	}
	else {
		gfindHero = false;     // 沒發現
		gcDirection.x = 0; gcDirection.y = 0;
	}
}

bool checkValid(int x, int y) {
	if (x <= 0 || x >= 9 || y <= 0 || y >= 9) {
		return false;
	}
	return true;
}