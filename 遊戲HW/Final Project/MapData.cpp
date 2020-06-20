#include"MapData.h"

//Intent : 讀取地圖檔案，包括地圖、腳色起始可選位置、怪物資訊
//Pre: 讀取檔案要存在同個資料夾
MapData::MapData(string s, int characterNum) {
	// 開始讀取檔案
	fstream file;
	file.open(s, ios::in);
	if (file.is_open()) {
		int row, column;
		file >> row >> column;
		this->characterNum = characterNum;
		mapRow = row;
		mapColumn = column;
		vector<string> mapRow(row);
		tempMap = mapRow;
		for (int i = 0; i < row; i++) {		//地圖原型
			string a;	//用來讀取地圖，一次一行
			file >> a;
			tempMap[i] = a;
		}
		for (int i = 0; i < row; i++) {	//找出全部有幾個門
			for (int j = 0; j < column; j++) {
				if (tempMap[i][j] == '3') {
					doorNum++;
				}
			}
		}
		for (int i = 0; i < row; i++) {		//把ValidPos全部設為-1
			for (int j = 0; j < column; j++) {
				validPos[i][j] = -1;
			}
		}
		map = tempMap;		//map -> 原始地圖
		int x[4], y[4], temp[4];
		for (int i = 0; i < 4; i++) {		//加入腳色起始位置
			file >> x[i] >> y[i];
			temp[i] = y[i] * 100 + x[i];
			tempMap[y[i]][x[i]] = '_';
		}
		int min = temp[0];
		for (int i = 1; i < 4; i++) {		//加入*號
			if (min > temp[i]) {
				min = temp[i];
			}
			if (i == 3) {
				tempMap[y[i]][x[i]] = '*';
				defaultY = y[i];
				defaultX = x[i];
			}
		}
		int mosnterNum, check = 0;
		file >> mosnterNum;
		for (int i = 0; i < mosnterNum; i++) {		//加入怪物位置資訊
			string monsterName;
			int monster_X, monster_Y, two_Role, three_Role, four_Role;		//兩隻腳色~四隻腳色對應的怪物類型
			file >> monsterName >> monster_X >> monster_Y >> two_Role >> three_Role >> four_Role;
			if (characterNum == 2) {
				if (two_Role != 0) {	// 0 表示沒有怪物
					enemyData[this->monsterNum].name = monsterName;
					enemyData[this->monsterNum].pos.x = monster_X;
					enemyData[this->monsterNum].pos.y = monster_Y;
					enemyData[this->monsterNum].kindOfEnemy = two_Role;
					enemyData[this->monsterNum].exist = true;
					tempMap[monster_Y][monster_X] = 'a' + i;
					enemyData[this->monsterNum].icon = 'a' + i;
					this->monsterNum++;			//怪物總量+1
				}
			}
			else if (characterNum == 3) {
				if (three_Role != 0) {	// 0 表示沒有怪物
					enemyData[this->monsterNum].name = monsterName;
					enemyData[this->monsterNum].pos.x = monster_X;
					enemyData[this->monsterNum].pos.y = monster_Y;
					enemyData[this->monsterNum].kindOfEnemy = three_Role;
					enemyData[this->monsterNum].exist = true;
					tempMap[monster_Y][monster_X] = 'a' + i;
					enemyData[this->monsterNum].icon = 'a' + i;
					this->monsterNum++;
				}
			}
			else if (characterNum == 4) {
				if (four_Role != 0) {	// 0 表示沒有怪物				
					enemyData[this->monsterNum].name = monsterName;
					enemyData[this->monsterNum].pos.x = monster_X;
					enemyData[this->monsterNum].pos.y = monster_Y;
					enemyData[this->monsterNum].kindOfEnemy = four_Role;
					enemyData[this->monsterNum].exist = true;
					tempMap[monster_Y][monster_X] = 'a' + i;
					enemyData[this->monsterNum].icon = 'a' + i;
					this->monsterNum++;
				}
			}
		}
		findValidPos(defaultX, defaultY);
		for (int i = 0; i < this->monsterNum; i++) {	//把視野外的怪物設成false
			if (validPos[enemyData[i].pos.y][enemyData[i].pos.x] == -1) {
				enemyData[i].exist = false;
			}
		}

	}
	else {
		cout << "Can't open file\n";
		exit(1);
	}
	tempPrintMap();		//印地圖
	decideInitialPos();		//決定腳色起始位置
}

//Intent: 尋找可看見區域
void MapData::findValidPos(int x, int y) {
	if (x >= mapColumn || y >= mapRow) {
		return;
	}
	if (validPos[y][x] != -1) {	//表示已檢查過
		return;
	}
	if (map[y][x] == '0') {
		validPos[y][x] = 0;
		return;
	}
	else if (map[y][x] == '1') {
		validPos[y][x] = 1;
	}
	else if (map[y][x] == '2') {
		validPos[y][x] = 2;
	}
	else if (map[y][x] == '3') {
		validPos[y][x] = 3;
		return;
	}
	findValidPos(x + 1, y);
	findValidPos(x - 1, y);
	findValidPos(x, y + 1);
	findValidPos(x, y - 1);
}

//Intent : 印出map (選擇完腳色初始位置前的印地圖方式)
void MapData::tempPrintMap() {
	for (int i = 0; i < mapRow; i++) {		//把ValidPos全部設為-1(初始化)
		for (int j = 0; j < mapColumn; j++) {
			validPos[i][j] = -1;
		}
	}
	findValidPos(defaultX, defaultY);
	for (int i = 0; i < mapRow; i++) {
		for (int j = 0; j < mapColumn; j++) {
			if (validPos[i][j] <= 0) {
				cout << " ";
			}
			else {
				cout << tempMap[i][j];
			}
		}
		cout << "\n";
	}
}

//Intent: 印出回合數
void MapData::printRound() {
	cout << "round " << this->round_int << ": \n\n";
}

//Intent : 印出map
void MapData::printMap() {
	tempMap = map;		//地圖初始化
	for (int i = 0; i < mapRow; i++) {		//把ValidPos全部設為-1(初始化)
		for (int j = 0; j < mapColumn; j++) {
			validPos[i][j] = -1;
		}
	}
	findValidPos(defaultX, defaultY);
	for (int i = 0; i < characterNum; i++) {
		if (characterData[i].exist == true) {		//腳色存活的話，加到地圖上
			tempMap[characterData[i].pos.y][characterData[i].pos.x] = characterData[i].icon;
		}
	}
	for (int i = 0; i < monsterNum; i++) {
		if (enemyData[i].exist == true) {			//怪物存活的話，加到地圖上
			tempMap[enemyData[i].pos.y][enemyData[i].pos.x] = enemyData[i].icon;
		}
	}
	for (int i = 0; i < mapRow; i++) {
		for (int j = 0; j < mapColumn; j++) {
			if (validPos[i][j] <= 0) {
				cout << " ";
			}
			else {
				cout << tempMap[i][j];
			}
		}
		cout << "\n";
	}
}

//Intent : 決定腳色起始位置
void MapData::decideInitialPos() {
	for (int i = 0; i < characterNum; i++) {
		string command;
		cin >> command;
		if (command == "e") {	//原地不動

			characterData[i].pos.x = defaultX;
			characterData[i].pos.y = defaultY;
			characterData[i].icon = 'A' + i;
			characterData[i].exist = true;
			tempMap[defaultY][defaultX] = 'A' + i;

			int check = 0;
			for (int j = defaultY; j < mapRow; j++) {	//尋找預設位置
				for (int k = 0; k < mapColumn; k++) {
					if (i == characterNum - 1 && tempMap[j][k] == '_') {	//最後一個腳色時，把'_'換成'1'
						tempMap[j][k] = '1';
					}
					else if (tempMap[j][k] == '_') {
						tempMap[j][k] = '*';
						defaultY = j;
						defaultX = k;
						check = 1;
						break;
					}
				}
				if (check == 1) {
					break;
				}
			}
			tempPrintMap();	//印地圖
		}
		else {
			int check = 0;
			int nowPos_x = defaultX, nowPos_y = defaultY;
			for (int j = 0; j < command.size(); j++) {
				switch (command[j]) {
				case 'w':
					if (tempMap[nowPos_y - 1][nowPos_x] == '_') {
						nowPos_y -= 1;
					}
					break;
				case 'a':
					if (tempMap[nowPos_y][nowPos_x - 1] == '_') {
						nowPos_x -= 1;
					}
					break;
				case 's':
					if (tempMap[nowPos_y + 1][nowPos_x] == '_') {
						nowPos_y += 1;
					}
					break;
				case 'd':
					if (tempMap[nowPos_y][nowPos_x + 1] == '_') {
						nowPos_x += 1;
					}
					break;
				default:
					break;
				}
			}
			if (tempMap[nowPos_y][nowPos_x] == '*') {
				characterData[i].pos.x = nowPos_x;
				characterData[i].pos.y = nowPos_y;
				characterData[i].icon = 'A' + i;
				characterData[i].exist = true;

				tempMap[defaultY][defaultX] = 'A' + i;
				for (int j = defaultY; j < mapRow; j++) {	//尋找預設位置
					for (int k = 0; k < mapColumn; k++) {
						if (i == characterNum - 1 && tempMap[j][k] == '_') {	//最後一個腳色時，把'_'換成'1'
							tempMap[j][k] = '1';
						}
						else if (map[j][k] == '_') {
							tempMap[j][k] = '*';
							defaultY = j;
							defaultX = k;
							check = 1;
							break;
						}
					}
					if (check == 1) {
						break;
					}
				}
				tempPrintMap();	//印地圖
			}
			else {
				if (i == characterNum - 1) {
					for (int j = defaultY; j < mapRow; j++) {	//最後一個腳色時，把'_'和'*'換成'1'
						for (int k = 0; k < mapColumn; k++) {
							if (tempMap[j][k] == '_' || tempMap[j][k] == '*') {
								tempMap[j][k] = '1';
							}

						}
					}
				}
				tempMap[nowPos_y][nowPos_x] = 'A' + i;
				characterData[i].pos.x = nowPos_x;
				characterData[i].pos.y = nowPos_y;
				characterData[i].icon = 'A' + i;
				characterData[i].exist = true;
				tempPrintMap();	//印地圖
			}
		}
	}
}

//Intent: 根據moveCommand 做出該role的移動 eg:  "c" , 0 ,wwa
//Pre: index要存在  
void MapData::roleMove(string type, int index, string moveCommand) {
	/*用vector把所要經過所有pos都存下來在一步一步檢查，若可以則往前若不行則停留
	1.最後一部在怪物身上那麼就要回去上一部，若上一部還是怪物身上，在回上一部，以此類推
	2.可以穿越怪物但不能穿越角色
	*/

	vector<Postion> pos;
	vector<validPosS> validPos;
	if (type == "m")
		pos.push_back(enemyData[index].pos);
	else if (type == "c")
		pos.push_back(characterData[index].pos);

	//先把後面的可能位置存下來
	for (int i = 0; i < moveCommand.size(); i++) {
		char dir = moveCommand[i];			//方向
		Postion posTmp = pos[i];
		switch (dir) {
		case 'w':
			posTmp.y -= 1;
			break;
		case 'a':
			posTmp.x -= 1;
			break;
		case 's':
			posTmp.y += 1;
			break;
		case 'd':
			posTmp.x += 1;
			break;
		default:
			break;
		}
		pos.push_back(posTmp);
	}

	validPos.resize(pos.size());
	int i;
	for (i = 1; i < pos.size(); i++) {
		if (!checkPosValid(pos[i], type, validPos[i])) {
			//i--;
			break;
		}
	}
	// 檢查是否停留在role上
	i--;
	for (; i > 0; i--) {
		if (validPos[i].passSameRole == true)	//if true代表這格是在role上，要後退到上一格
			continue;
		else
			break;
	}
	if (type == "m")
		enemyData[index].pos = pos[i];
}

//Intent: check 欲移動位置是否可以  
//Pre: 對怪物來說門是障礙物，所以須傳進type
//Post:  retrun 1 可以 ; 0 不行
bool MapData::checkPosValid(Postion nextPost, string type, validPosS& validPos) {
	if (type == "m") {
		if (nextPost.y < 0 || nextPost.y >= map.size()) {
			validPos.passSameRole = false;
			validPos.validPos = false;
			return false;
		}
		else if (nextPost.x < 0 || nextPost.x >= map[nextPost.y].size()) {
			validPos.passSameRole = false;
			validPos.validPos = false;
			return false;
		}

		if (tempMap[nextPost.y][nextPost.x] == '1') {  //地板
			validPos.passSameRole = false;
			validPos.validPos = true;
			return true;
		}
		else if (tempMap[nextPost.y][nextPost.x] >= 'a' && tempMap[nextPost.y][nextPost.x] <= 'z') {		//怪物
			validPos.passSameRole = true;
			validPos.validPos = true;
			return true;
		}
		//角色 障礙物 牆壁
		else {
			validPos.passSameRole = false;
			validPos.validPos = false;
			return false;
		}
	}
	/*else if (type == "c") {
		// character 移動要考慮這個空間，最多移動到門，門後的空間不能過去
	}*/
	return  false;
}

//門開啟未完成
//Intent: 根據moveCommand 做出該character的移動 eg:  "c" , 0 ,wwa
//Pre: index要存在
int MapData::characterMove(int index, int numOfMove) {
	while (1) {
		bool inValid = false;
		string moveCommand;
		Postion pos = characterData[index].pos;
		cin >> moveCommand;
		int validNum = 0;
		if (moveCommand == "e") {
			return 0;
		}
		for (int i = 0; i < moveCommand.size(); i++) {
			if (moveCommand[i] == 'w' || moveCommand[i] == 'a' || moveCommand[i] == 's' || moveCommand[i] == 'd') {
				validNum++;
			}
		}
		if (validNum > numOfMove) {
			cout << "error move!!!\n";
			continue;
		}
		for (int i = 0; i < moveCommand.size(); i++) {
			char dir = moveCommand[i];			//方向
			switch (dir) {
			case 'w':
				pos.y -= 1;
				break;
			case 'a':
				pos.x -= 1;
				break;
			case 's':
				pos.y += 1;
				break;
			case 'd':
				pos.x += 1;
				break;
			default:
				break;
			}
			if (tempMap[pos.y][pos.x] == '0' || tempMap[pos.y][pos.x] == '2') {		// 碰到牆壁或障礙物 ;
				cout << "error move!!!\n";
				inValid = true;
				break;
			}
			if (tempMap[pos.y][pos.x] <= 'z' && tempMap[pos.y][pos.x] >= 'a') {		// 碰到敵人 ;
				cout << "error move!!!\n";
				inValid = true;
				break;
			}
		}
		if (inValid == true) {
			continue;
		}
		bool checkMonsterExist = false;
		if (tempMap[pos.y][pos.x] == '3') {
			for (int i = 0; i < this->monsterNum; i++) {
				if (validPos[enemyData[i].pos.y][enemyData[i].pos.x] == 1 && enemyData[i].exist == true) {
					checkMonsterExist = true;
				}
			}
			if (checkMonsterExist == false) {
				characterData[index].pos.x = pos.x;
				characterData[index].pos.y = pos.y;
				printMap();
				map[pos.y][pos.x] = '1';
				doorNum -= 1;
				for (int i = 0; i < mapRow; i++) {		//把ValidPos全部設為-1(初始化)
					for (int j = 0; j < mapColumn; j++) {
						validPos[i][j] = -1;
					}
				}
				findValidPos(defaultX, defaultY);
				return 2;
			}
		}
		if (tempMap[pos.y][pos.x] == '1' || tempMap[pos.y][pos.x] == '3') {
			characterData[index].pos.x = pos.x;
			characterData[index].pos.y = pos.y;
			printMap();
			return 0;
		}
		else {
			cout << "error move!!!\n";
		}
	}
}

//Intent: 判斷有沒有視野 true: 有，false: 沒有
//Post: 傳進兩個role的position
bool MapData::sight(Postion posC, Postion posM) {
	Postion left, right;			//方便做運算
	if (posC.x == posM.x) {		//斜率不存在
		Postion top,down;			//方便做運算
		if (posC.y > posM.y) {
			top = posM;
			down = posC;
		}
		else {
			top = posC;
			down = posM;
		}

		for (int i = top.y + 1; i < down.y; i++) {
			if (tempMap[i][posC.x] == '0')
				return false;
		}
		return true;
	}


	if (posC.x < posM.x) {
		left = posC;
		right = posM;
	}
	else {
		left = posM;
		right = posC;
	}
	double slope = right.y - left.y / right.x - left.x;		//斜率

	for (int i = left.x + 1; i <= right.x - 1; i++) {				//role所在的那格要特別處理，所以先看中間的部分
		for (int j = 1; j <= 10; j++) {			//每個再切10份
			double tmpx = i + j * 0.049;
			double tmpy = (tmpx - left.x) * slope + left.y;	//x的變化量*斜率 + Y
			tmpx = round(tmpx);			//四捨五入因為格子的一半為0.5
			tmpy = round(tmpy);
			int x = (int)tmpx;
			int y = (int)tmpy;
			if (tempMap[y][x] == '0')
				return false;
		}
	}

	//左邊右半格
	for (int j = 1; j <= 10; j++) {
		double tmpx = left.x + j * 0.049;
		double tmpy = left.y + j * 0.049 * slope;
		tmpx = round(tmpx);			//四捨五入因為格子的一半為0.5
		tmpy = round(tmpy);
		int x = (int)tmpx;
		int y = (int)tmpy;
		if (tempMap[y][x] == '0')
			return false;
	}
	//右邊左半格
	for (int j = 1; j <= 10; j++) {
		double tmpx = right.x - j * 0.049;
		double tmpy = left.y - j * 0.049 * slope;
		tmpx = round(tmpx);			//四捨五入因為格子的一半為0.5
		tmpy = round(tmpy);
		int x = (int)tmpx;
		int y = (int)tmpy;
		if (tempMap[y][x] == '0')
			return false;
	}

	return true;
}


