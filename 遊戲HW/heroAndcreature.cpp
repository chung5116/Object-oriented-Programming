// Name: 張永承	
// Date: 2020.03.18
// Last Update: 2020.03.20
// Problem statement: Creature Class
#include<iostream>
#include<windows.h>
#include<conio.h>
#include<vector>
#include<thread>
using namespace std;

/*--------------------------------------Variable-------------------------------*/
// Constent variable
const int GWIDTH = 10;
const int GHEIGHT = 10;
const char GWALL = 'O';
const char GSPACE = ' ';
const char GFIND = '!';


//char gBoard[GHEIGHT][GWIDTH];
vector<vector<char>>gBoard;
vector<vector<char>>gtmpBoard;  //暫時儲存
//char gtmpBoard[GHEIGHT][GWIDTH];
bool gfindHero = false;
bool ginvalidDirection = false;    // 防止跑出地圖外
int gnumOffindHero = 0;
/*--------------------------------------------Function---------------------------*/
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
// 更新board
void updateBoard(void);
// 更新creature，如果有發現則移動
void updataCreature(void);
// 生物偵查Hero
void creatureDetectHero(void);
// 生物攻擊hero
bool attackHero(void);
/*----------------------------------------------Class--------------------------*/
struct Position {
	int x; // X, y Coordinate
	int y;
};

struct cDirection{
	int x;
	int y;
};



// Hero class
class Hero {
private:
	Position posHero;

	char icon = 'H';
public:
	int hp = 1;
	Hero(void) { this->posHero.x = 2, this->posHero.y = 3; }
	Position getPos(void) { return this->posHero; }
	char getIcon(void) { return this->icon; }
	void setPosition(int x, int y) { this->posHero.x = x; this->posHero.y = y; }
};


// Creature class
class Creature {
private:
	Position posCreature;
	char icon = 'C';
public:
	int hp = 1;
	Creature(void) { this->posCreature.x = 7, this->posCreature.y = 7; }
	Position getPos(void) { return this->posCreature; }
	char getIcon(void) { return this->icon; }
	void setPosition(int x, int y) { this->posCreature.x = x; this->posCreature.y = y; }
};

Hero gHero_obj;
Creature gCreature_obj;
cDirection gcDirection;			// 生物要移動的方向
/*--------------------------------------------------------------main ----------------------------*/

int main() {
	initializeBoard();

	bool inputState[5];
	// 直接一方獲勝
	while (gHero_obj.hp != 0 && gCreature_obj.hp != 0) {
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
		if (attackHero()) {				// hero 移動完後若還在生物攻擊範圍內則死亡
			system("CLS");
			printText();
			printoutBoard();
			break;
		}
		updateBoard();

	}

	system("PAUSE");
	return 0;
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


bool attackHero() {
	Position posH = gHero_obj.getPos();
	Position posC = gCreature_obj.getPos();
	if (gfindHero) {
		if (sqrt(pow(abs(posH.x - posC.x), 2) + pow(abs(posH.y - posC.y), 2)) <= sqrt(2)) {
			gnumOffindHero++;
			if (gnumOffindHero >= 2) {
				gHero_obj.hp = 0;
				return true;
			}
		}
	}
	else {
		gnumOffindHero = 0;
	}
	
	return false;
}

void creatureDetectHero() {
	Position posC = gCreature_obj.getPos();
	Position posH = gHero_obj.getPos();
	int xc = posC.x; 
	int yc = posC.y;
	int xh = posH.x;
	int yh = posH.y;
	if (xc == xh && yc == yh) {		// hero 走到 creature上
		gHero_obj.hp = 0;					// game over
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

void updataCreature() {
	if (gfindHero) {
		Position posC = gCreature_obj.getPos();
		if(checkValid(posC.x + gcDirection.x, posC.y + gcDirection.y))
			gCreature_obj.setPosition(posC.x + gcDirection.x, posC.y + gcDirection.y);
	}
}


bool getInputCommand(bool(&inputState)[5]) {
	/*system("CLS");
	printText();*/
	//printoutBoard();

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
	}
	// 清除版面
	//system("CLS");
}


void printText() {
	cout << "Use wasd to control Hero, press \"k\" to attack " << endl;
	cout << "Press ESC to end the game\n\n" << endl;
	cout << "Hero's HP: " << gHero_obj.hp << endl;
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
	gtmpBoard[posH.x][posH.y] = gHero_obj.getIcon();
	if (gfindHero) {
		gtmpBoard[posC.x][posC.y] = GFIND;
	}
	else {
		gtmpBoard[posC.x][posC.y] = gCreature_obj.getIcon();
	}
	for (int i = 0; i < GHEIGHT; i++) {
		for (int j = 0; j < GWIDTH; j++) {
			cout << gtmpBoard[i][j];
		}
		cout << endl;
	}
	if (gHero_obj.hp == 0) {
		cout << "\n You Lose\n";
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
		gCreature_obj.hp = 0;
		cout << "\n You WIN\n";
	}
	

}

bool checkValid(int x, int y) {
	if (x <= 0 || x >= 9 || y <= 0 || y >= 9) {
		/*system("CLS");
		printText();
		printoutBoard();*/
		//cout << "Invalid direction" << endl;
		return false;
	}
	return true;
}

void updateBoard() {
	//system("CLS");
	//printText();
	//printoutBoard();
}