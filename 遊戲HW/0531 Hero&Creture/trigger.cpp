// Name: Yung-Cheng Chang B10706009
// Date: 2020.04.09
// Last Update: 2020.04.11
// Problem statement: Hero & Creature
//#include"trigger.h"
#include"otherItems.h"
using namespace std;

int Trigger::numofT = 1;
Trigger::Trigger(Board& bd, Position pos):Item(pos){
	this->boardHeight = bd.height;
	system("CLS");
	//cout << "Enter Trigger's icon\n";
	//cin >> icon;
	icon = 'T';

	//bd.setBoard(posTrigger.x, posTrigger.y, this->icon);
}

/*Trigger::Trigger(Board& bd,char icon) {
	this->boardHeight = bd.height;
	this->icon = icon;
	this->exist = false;

	//bd.setBoard(posTrigger.x, posTrigger.y, this->icon);
}*/


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


 void Trigger::triggered(Hero& h) {
	 Position pos = h.getPos();
	 if (pos.x == posItem.x && pos.y == posItem.y) {
		 h.hp -= 10;
		 update();
	 }
}


 void Trigger::update() {
	 exist = false;
}