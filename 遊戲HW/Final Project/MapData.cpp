#include"MapData.h"

//Intent : Ū���a���ɮסA�]�A�a�ϡB�}��_�l�i���m�B�Ǫ���T
//Pre: Ū���ɮ׭n�s�b�P�Ӹ�Ƨ�
MapData::MapData(string s, int characterNum) {
	// �}�lŪ���ɮ�
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
		for (int i = 0; i < row; i++) {		//�a�ϭ쫬
			string a;	//�Ψ�Ū���a�ϡA�@���@��
			file >> a;
			tempMap[i] = a;
		}
		for (int i = 0; i < row; i++) {	//��X�������X�Ӫ�
			for (int j = 0; j < column; j++) {
				if (tempMap[i][j] == '3') {
					doorNum++;
				}
			}
		}
		for (int i = 0; i < row; i++) {		//��ValidPos�����]��-1
			for (int j = 0; j < column; j++) {
				validPos[i][j] = -1;
			}
		}
		map = tempMap;		//map -> ��l�a��
		int x[4], y[4], temp[4];
		for (int i = 0; i < 4; i++) {		//�[�J�}��_�l��m
			file >> x[i] >> y[i];
			temp[i] = y[i] * 100 + x[i];
			tempMap[y[i]][x[i]] = '_';
		}
		int min = temp[0];
		for (int i = 1; i < 4; i++) {		//�[�J*��
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
		for (int i = 0; i < mosnterNum; i++) {		//�[�J�Ǫ���m��T
			string monsterName;
			int monster_X, monster_Y, two_Role, three_Role, four_Role;		//�Ⱖ�}��~�|���}��������Ǫ�����
			file >> monsterName >> monster_X >> monster_Y >> two_Role >> three_Role >> four_Role;
			if (characterNum == 2) {
				if (two_Role != 0) {	// 0 ��ܨS���Ǫ�
					enemyData[this->monsterNum].name = monsterName;
					enemyData[this->monsterNum].pos.x = monster_X;
					enemyData[this->monsterNum].pos.y = monster_Y;
					enemyData[this->monsterNum].kindOfEnemy = two_Role;
					enemyData[this->monsterNum].exist = true;
					tempMap[monster_Y][monster_X] = 'a' + i;
					enemyData[this->monsterNum].icon = 'a' + i;
					this->monsterNum++;			//�Ǫ��`�q+1
				}
			}
			else if (characterNum == 3) {
				if (three_Role != 0) {	// 0 ��ܨS���Ǫ�
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
				if (four_Role != 0) {	// 0 ��ܨS���Ǫ�				
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
		for (int i = 0; i < this->monsterNum; i++) {	//������~���Ǫ��]��false
			if (validPos[enemyData[i].pos.y][enemyData[i].pos.x] == -1) {
				enemyData[i].exist = false;
			}
		}

	}
	else {
		cout << "Can't open file\n";
		exit(1);
	}
	tempPrintMap();		//�L�a��
	decideInitialPos();		//�M�w�}��_�l��m
}

//Intent: �M��i�ݨ��ϰ�
void MapData::findValidPos(int x, int y) {
	if (x >= mapColumn || y >= mapRow) {
		return;
	}
	if (validPos[y][x] != -1) {	//��ܤw�ˬd�L
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

//Intent : �L�Xmap (��ܧ��}���l��m�e���L�a�Ϥ覡)
void MapData::tempPrintMap() {
	for (int i = 0; i < mapRow; i++) {		//��ValidPos�����]��-1(��l��)
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

//Intent: �L�X�^�X��
void MapData::printRound() {
	cout << "round " << this->round_int << ": \n\n";
}

//Intent : �L�Xmap
void MapData::printMap() {
	tempMap = map;		//�a�Ϫ�l��
	for (int i = 0; i < mapRow; i++) {		//��ValidPos�����]��-1(��l��)
		for (int j = 0; j < mapColumn; j++) {
			validPos[i][j] = -1;
		}
	}
	findValidPos(defaultX, defaultY);
	for (int i = 0; i < characterNum; i++) {
		if (characterData[i].exist == true) {		//�}��s�����ܡA�[��a�ϤW
			tempMap[characterData[i].pos.y][characterData[i].pos.x] = characterData[i].icon;
		}
	}
	for (int i = 0; i < monsterNum; i++) {
		if (enemyData[i].exist == true) {			//�Ǫ��s�����ܡA�[��a�ϤW
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

//Intent : �M�w�}��_�l��m
void MapData::decideInitialPos() {
	for (int i = 0; i < characterNum; i++) {
		string command;
		cin >> command;
		if (command == "e") {	//��a����

			characterData[i].pos.x = defaultX;
			characterData[i].pos.y = defaultY;
			characterData[i].icon = 'A' + i;
			characterData[i].exist = true;
			tempMap[defaultY][defaultX] = 'A' + i;

			int check = 0;
			for (int j = defaultY; j < mapRow; j++) {	//�M��w�]��m
				for (int k = 0; k < mapColumn; k++) {
					if (i == characterNum - 1 && tempMap[j][k] == '_') {	//�̫�@�Ӹ}��ɡA��'_'����'1'
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
			tempPrintMap();	//�L�a��
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
				for (int j = defaultY; j < mapRow; j++) {	//�M��w�]��m
					for (int k = 0; k < mapColumn; k++) {
						if (i == characterNum - 1 && tempMap[j][k] == '_') {	//�̫�@�Ӹ}��ɡA��'_'����'1'
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
				tempPrintMap();	//�L�a��
			}
			else {
				if (i == characterNum - 1) {
					for (int j = defaultY; j < mapRow; j++) {	//�̫�@�Ӹ}��ɡA��'_'�M'*'����'1'
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
				tempPrintMap();	//�L�a��
			}
		}
	}
}

//Intent: �ھ�moveCommand ���X��role������ eg:  "c" , 0 ,wwa
//Pre: index�n�s�b  
void MapData::roleMove(string type, int index, string moveCommand) {
	/*��vector��ҭn�g�L�Ҧ�pos���s�U�Ӧb�@�B�@�B�ˬd�A�Y�i�H�h���e�Y����h���d
	1.�̫�@���b�Ǫ����W����N�n�^�h�W�@���A�Y�W�@���٬O�Ǫ����W�A�b�^�W�@���A�H������
	2.�i�H��V�Ǫ��������V����
	*/

	vector<Postion> pos;
	vector<validPosS> validPos;
	if (type == "m")
		pos.push_back(enemyData[index].pos);
	else if (type == "c")
		pos.push_back(characterData[index].pos);

	//����᭱���i���m�s�U��
	for (int i = 0; i < moveCommand.size(); i++) {
		char dir = moveCommand[i];			//��V
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
	// �ˬd�O�_���d�brole�W
	i--;
	for (; i > 0; i--) {
		if (validPos[i].passSameRole == true)	//if true�N��o��O�brole�W�A�n��h��W�@��
			continue;
		else
			break;
	}
	if (type == "m")
		enemyData[index].pos = pos[i];
}

//Intent: check �����ʦ�m�O�_�i�H  
//Pre: ��Ǫ��ӻ����O��ê���A�ҥH���Ƕitype
//Post:  retrun 1 �i�H ; 0 ����
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

		if (tempMap[nextPost.y][nextPost.x] == '1') {  //�a�O
			validPos.passSameRole = false;
			validPos.validPos = true;
			return true;
		}
		else if (tempMap[nextPost.y][nextPost.x] >= 'a' && tempMap[nextPost.y][nextPost.x] <= 'z') {		//�Ǫ�
			validPos.passSameRole = true;
			validPos.validPos = true;
			return true;
		}
		//���� ��ê�� ���
		else {
			validPos.passSameRole = false;
			validPos.validPos = false;
			return false;
		}
	}
	/*else if (type == "c") {
		// character ���ʭn�Ҽ{�o�ӪŶ��A�̦h���ʨ���A���᪺�Ŷ�����L�h
	}*/
	return  false;
}

//���}�ҥ�����
//Intent: �ھ�moveCommand ���X��character������ eg:  "c" , 0 ,wwa
//Pre: index�n�s�b
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
			char dir = moveCommand[i];			//��V
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
			if (tempMap[pos.y][pos.x] == '0' || tempMap[pos.y][pos.x] == '2') {		// �I������λ�ê�� ;
				cout << "error move!!!\n";
				inValid = true;
				break;
			}
			if (tempMap[pos.y][pos.x] <= 'z' && tempMap[pos.y][pos.x] >= 'a') {		// �I��ĤH ;
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
				for (int i = 0; i < mapRow; i++) {		//��ValidPos�����]��-1(��l��)
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

//Intent: �P�_���S������ true: ���Afalse: �S��
//Post: �Ƕi���role��position
bool MapData::sight(Postion posC, Postion posM) {
	Postion left, right;			//��K���B��
	if (posC.x == posM.x) {		//�ײv���s�b
		Postion top,down;			//��K���B��
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
	double slope = right.y - left.y / right.x - left.x;		//�ײv

	for (int i = left.x + 1; i <= right.x - 1; i++) {				//role�Ҧb������n�S�O�B�z�A�ҥH���ݤ���������
		for (int j = 1; j <= 10; j++) {			//�C�ӦA��10��
			double tmpx = i + j * 0.049;
			double tmpy = (tmpx - left.x) * slope + left.y;	//x���ܤƶq*�ײv + Y
			tmpx = round(tmpx);			//�|�ˤ��J�]����l���@�b��0.5
			tmpy = round(tmpy);
			int x = (int)tmpx;
			int y = (int)tmpy;
			if (tempMap[y][x] == '0')
				return false;
		}
	}

	//����k�b��
	for (int j = 1; j <= 10; j++) {
		double tmpx = left.x + j * 0.049;
		double tmpy = left.y + j * 0.049 * slope;
		tmpx = round(tmpx);			//�|�ˤ��J�]����l���@�b��0.5
		tmpy = round(tmpy);
		int x = (int)tmpx;
		int y = (int)tmpy;
		if (tempMap[y][x] == '0')
			return false;
	}
	//�k�䥪�b��
	for (int j = 1; j <= 10; j++) {
		double tmpx = right.x - j * 0.049;
		double tmpy = left.y - j * 0.049 * slope;
		tmpx = round(tmpx);			//�|�ˤ��J�]����l���@�b��0.5
		tmpy = round(tmpy);
		int x = (int)tmpx;
		int y = (int)tmpy;
		if (tempMap[y][x] == '0')
			return false;
	}

	return true;
}


