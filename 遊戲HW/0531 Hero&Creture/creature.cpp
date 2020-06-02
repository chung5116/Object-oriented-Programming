// Name: Yung-Cheng Chang
// Date: 2020.04.09
// Last Update: 2020.04.11
// Problem statement: Hero & Creature
#include"herocreature.h"
using namespace std;

int Creature::numofC = 0;

Creature::Creature(Board& bd) {
	this->boardHeight = bd.height;
	system("CLS");
	char icon;
	cout << "Enter Creature's icon\n";
	cin >> icon;
	//icon = 'C';
	this->icon = icon;
	this->exist = false;
	this->posCreature = generateRandomXY(bd);
	//bd.setBoard(posCreature.x, posCreature.y, this->icon);
	//gBoard_obj.setBoard(posCreature.x, posCreature.y, this->icon);
}

Creature::Creature(Board& bd, char icon) {
	this->boardHeight = bd.height;
	this->icon = icon;
	this->exist = false;
	this->posCreature = generateRandomXY(bd);
}


Position Creature::generateRandomXY(Board& bd) {
	vector<vector<char>>* localBoard = bd.getTmpboard();
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

void Creature::creatureDetectHero(Hero& gHero_obj) {
	Position posH = gHero_obj.getPos();
	int xc = posCreature.x;
	int yc = posCreature.y;
	int xh = posH.x;
	int yh = posH.y;

	if (xc == xh && yc == yh) {		// hero ���� creature�W
		gHero_obj.hp -= 20;
	}
	else if (xc == xh && yc != yh) {		// ���k
		this->findHero = true;
		if (yc > yh)
			this->cDirection.x = 0, this->cDirection.y = -1;
		else
			this->cDirection.x = 0, this->cDirection.y = 1;
	}
	else if (xc != xh && yc == yh) {		//�W�U
		this->findHero = true;
		if (xc > xh)
			this->cDirection.x = -1, this->cDirection.y = 0;
		else
			this->cDirection.x = 1, this->cDirection.y = 0;

	}
	/*else if (double(abs(xc - xh)) / double(abs(yc - yh)) == 1.0) {			//�צV
		this->findHero = true;
		if (xc > xh && yc > yh)
			this->cDirection.x = 0, this->cDirection.y = -1;
		else if (xc < xh && yc < yh)
			this->cDirection.x = 0, this->cDirection.y = 1;
		else if (xc > xh && yc < yh)
			this->cDirection.x = 0, this->cDirection.y = 1;
		else if (xc < xh && yc > yh)
			this->cDirection.x = 0, this->cDirection.y = -1;
	}*/
	else {
		this->findHero = false;     // �S�o�{
		this->cDirection.x = 0; this->cDirection.y = 0;
	}

}

void  Creature::attackHero(Hero& gHero_obj) {
	Position posH = gHero_obj.getPos();
	if (this->findHero) {
		if (sqrt(pow(abs(posH.x - posCreature.x), 2) + pow(abs(posH.y - posCreature.y), 2)) <= sqrt(2)) {
			this->numOffindHero++;
			if (this->numOffindHero >= 3) {
				gHero_obj.hp = gHero_obj.hp - 10;
			}
		}
	}
	else {
		this->numOffindHero = 0;
	}
}

void Creature::walkAround() {
	while (1) {
		int dir = rand() % 4;
		Position newDir;
		switch (dir) {
		case 0:
			newDir.x = 0; newDir.y = 1;
			break;
		case 1:
			newDir.x = 0; newDir.y = -1;
			break;
		case 2:
			newDir.x = 1; newDir.y = 0;
			break;
		case 3:
			newDir.x = -1; newDir.y = 0;
			break;
		}
		Position newPos = posCreature + newDir;
		if (gBoard_obj.checkValid(newPos.x, newPos.y)) {
			posCreature = newPos;
			break;
		}
	}
}