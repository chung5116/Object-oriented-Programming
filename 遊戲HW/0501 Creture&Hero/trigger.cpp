// Name: Yung-Cheng Chang B10706009
// Date: 2020.04.09
// Last Update: 2020.04.11
// Problem statement: Hero & Creature
#include"trigger.h"
using namespace std;

int Trigger::numofT = 0;

Trigger::Trigger(Board& bd) {
	this->boardHeight = bd.height;
	system("CLS");
	char icon;
	//cout << "Enter Trigger's icon\n";
	//cin >> icon;
	icon = 'T';
	this->icon = icon;
	this->exist = false;
	this->posTrigger = generateRandomXY(bd);
	
	//bd.setBoard(posTrigger.x, posTrigger.y, this->icon);
}

Trigger::Trigger(Board& bd,char icon) {
	this->boardHeight = bd.height;
	this->icon = icon;
	this->exist = false;
	this->posTrigger = generateRandomXY(bd);

	//bd.setBoard(posTrigger.x, posTrigger.y, this->icon);
}


Position Trigger::generateRandomXY(Board& bd) {
	vector<vector<char>>*localBoard = bd.getTmpboard();
	Position random;
	int min = 1;
	int max = boardHeight - 1;
	int dx = 0;
	int dy = 0;
	while (true) {
		dx = (rand() % (max - min + 1)) + min;
		dy = (rand() % ((*localBoard)[dx].size() - 1 - min + 1)) + min;
		if (bd.checkValid(dx, dy))
			break;
	}
	random.x = dx;
	random.y = dy;
	return random;
}