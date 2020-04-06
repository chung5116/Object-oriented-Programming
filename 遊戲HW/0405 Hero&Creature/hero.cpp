// Name: 張永承	
// Date: 2020.03.31
// Last Update: 2020.03.27
// Problem statement: Hero & Creature
using namespace std;
#include"herocreature.h"



Hero::Hero(Board& bd) {
	system("CLS");
	char icon;
	int x, y;
	cout << "Enter Hero's icon\n";
	cin >> icon;
	//icon = '@';
	this->icon = icon;
	cout << "Enter valid X,Y postion of Hero\n";
	cin >> x >> y;
	//x = 5; y = 5;
	while (!bd.checkValid(x, y)) {
		system("CLS");
		cout << "Enter valid X,Y postion of Hero again\n";
		cin >> x >> y;
	}
	this->posHero.x = x;
	this->posHero.y = y;
	bd.setBoard(x, y, icon);

}

void Hero::carryoutCommand(bool(&inputState)[7], Creature* gCreature[3]) {
	int tmpx = posHero.x;
	int tmpy = posHero.y;
	if (inputState[4]) {			//attack
		invalidDirection = false;
		drawAttckRange(gCreature);
	}
	else {
		if (inputState[0]) {		// w
			if (gBoard_obj.checkValid(tmpx - 1, tmpy)) {
				posHero.x = tmpx - 1;
				posHero.y = tmpy;
				invalidDirection = false;
			}
			else {
				invalidDirection = true;
			}
		}
		else if (inputState[1]) {			// a 
			if (gBoard_obj.checkValid(tmpx, tmpy - 1)) {
				posHero.x = tmpx;
				posHero.y = tmpy - 1;
				invalidDirection = false;
			}
			else {
				invalidDirection = true;
			}
		}
		else if (inputState[2]) {			// s 
			if (gBoard_obj.checkValid(tmpx + 1, tmpy)) {
				posHero.x = tmpx + 1;
				posHero.y = tmpy;
				invalidDirection = false;
			}
			else {
				invalidDirection = true;
			}
		}
		else if (inputState[3]) {			// d 
			if (gBoard_obj.checkValid(tmpx, tmpy + 1)) {
				posHero.x = tmpx;
				posHero.y = tmpy + 1;
				invalidDirection = false;
			}
			else {
				invalidDirection = true;
			}
		}
		else if (inputState[5]) {	// add creature		l 
			if (Creature::numofC <= 3) {
				for (int i = 0; i < 3; i++) {
					if (gCreature[i]->exist == false) {
						Creature::numofC++;
						gCreature[i]->exist = true;
						// input x,y
						gCreature[i]->posCreature = gCreature[i]->generateRandomXY(gBoard_obj);
						// set x,y;
						break;
					}
				}
			}
		}
		else if (inputState[6]) {	//add trigger			j
			if (Trigger::numofT <= 3) {
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
			}
		}
		//
	}
}

void Hero::drawAttckRange(Creature* gCreature[3]) {
	int hx = posHero.x;
	int hy = posHero.y;
	vector<vector<char>>attackBoard = gBoard_obj.getBoard();
	if (gBoard_obj.checkValid(hx - 1, hy)) {
		attackBoard[hx - 1][hy] = '*';		// 上
	}
	if (gBoard_obj.checkValid(hx + 1, hy)) {
		attackBoard[hx + 1][hy] = '*';		// 下
	}

	if (gBoard_obj.checkValid(hx, hy - 1)) {
		attackBoard[hx][hy - 1] = '*';		// 左
	}
	if (gBoard_obj.checkValid(hx, hy + 1)) {
		attackBoard[hx][hy + 1] = '*';		//右
	}
	if (gBoard_obj.checkValid(hx - 1, hy + 1)) {
		attackBoard[hx - 1][hy + 1] = '*';			//右上
	}
	if (gBoard_obj.checkValid(hx - 1, hy - 1)) {
		attackBoard[hx - 1][hy - 1] = '*';			//左上
	}
	if (gBoard_obj.checkValid(hx + 1, hy + 1)) {
		attackBoard[hx + 1][hy + 1] = '*';			//右下
	}
	if (gBoard_obj.checkValid(hx + 1, hy - 1)) {
		attackBoard[hx + 1][hy - 1] = '*';			//左下
	}
	// 清除版面
	system("CLS");
	printoutText();

	for (int i = 0; i < attackBoard.size(); i++) {
		for (int j = 0; j < attackBoard[i].size(); j++) {
			if ((abs(hx - i) + abs(hy - j) <= 2) && (i != hx && j != hy))
				cout << "\033[32m" << attackBoard[i][j] << "\033[0m";
			else
				cout << attackBoard[i][j];
		}
		cout << endl;
	}
	this_thread::sleep_for(0.1s);
	system("CLS");
	printoutText();
	printBoard();
	for (int i = 0; i < 3; i++) {
		if (gCreature[i]->exist == true) {
			//生物在Hero的攻擊範圍內
			if (sqrt(pow(abs(posHero.x - gCreature[i]->posCreature.x), 2) + pow(abs(posHero.y - gCreature[i]->posCreature.y), 2)) <= sqrt(2)) {
				gCreature[i]->hp--;
			}
			if (gCreature[i]->hp == 0) {
				gCreature[i]->exist = false;
				Creature::numofC--;
			}
		}
	}
}

void Hero::heroPassTrigger(Trigger* gTrigger[3]) {
	for (int i = 0; i < 3; i++) {
		if (gTrigger[i]->exist) {
			Position posT = gTrigger[i]->getPos();
			if (this->posHero.x == posT.x && this->posHero.y == posT.y) {
				//升級音效
				this->hp = this->hp + 20;
				this->level++;
				Position newT = gTrigger[i]->generateRandomXY(gBoard_obj);
				gTrigger[i]->setPosition(newT.x, newT.y);
				// 音效
				PlaySound(L"levelup.wav", NULL, SND_FILENAME | SND_ASYNC);

			}
		}
	}
}
