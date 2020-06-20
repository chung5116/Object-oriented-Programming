#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include"CharacterData.h"
#include"MonsterData.h"
#include"Gloomhaven.h"
#include"MapData.h"
using namespace std;

int gCharacterNumber;  //�X������ƶq

// split args to get filename
vector<string> parsing(char* args[]);
// �}�l�C��?
void playGame();
// �M�w�W������P�ޯ�d
void inputCharacterAndCard(GloomHaven& gloomHaven_obj, CharacterData& characterData_obj);
// split string
vector<string>splitString(string s, char c);
// �⨤��name��s��a�ϤW
void fetchCharacterNameIntoMap(MapData& map_obj, GloomHaven& gloomHaven_obj);
// ��̫�Q�D�諸�Ǫ���s��gloomHaven class�� monsterVector 
void fetchMonsterIntoGloomHaven(MapData& map_obj, GloomHaven& gloomHaven_obj, MonsterData& monsterData_obj);




int main(int argc, char* argv[]) {
	
	while (true) {
		system("CLS");
		vector<string>token = parsing(argv);
		CharacterData characterData_obj(token[0]);
		MonsterData monsterData_obj(token[1]);
		playGame();
		GloomHaven gloomHaven_obj(gCharacterNumber);
		inputCharacterAndCard(gloomHaven_obj, characterData_obj);

		string mapFile;
		cout << "�п�J�a�ϦW��\n";
		cin >> mapFile;
		//mapFile = "map1.txt";
		//gCharacterNumber = 2;						//for test
		MapData map_obj(mapFile, gCharacterNumber);
		system("CLS");
		map_obj.printMap();

		fetchCharacterNameIntoMap(map_obj, gloomHaven_obj);
		fetchMonsterIntoGloomHaven(map_obj, gloomHaven_obj, monsterData_obj);

		// �y�{4-1 �}�l
		gloomHaven_obj.startGame(characterData_obj, monsterData_obj, map_obj);
	}
}

//Intent : ��@�}�l��args�নstring
//Post: return vector<string>�A�U�������T�ɦW�A�Ǫ���T�ɦW
vector<string> parsing(char* args[]) {
	vector<string>res;

	string s(args[1]);
	res.push_back(s);
	string ss(args[2]);
	res.push_back(ss);

	return res;
}


//Intent : �߰ݬO�_�}�l�C���A�ç�player����ƶq�x�s�bgCharacterNumber
void playGame() {
	string s;
	cout << "�}�l�C��?\n";
	cin >> s;
	//s = "play";						/* ------for debug---------*/
	if (s == "play") {
		int num;
		system("CLS");
		cout << "���a��J����ƶq(�Ʀr2 - 4)\n";		
		cin >> num;     /* ------for debug---------*/
		//num = 3;
		if (num > 4 || num < 2)
			exit(1);
		gCharacterNumber = num;
	}
	else {
		exit(1);
	}
}

//Intent : ��string �̷�c����
//Pre: string ,char ���i��0
//Post: return ���Ϋᵲ�G
vector<string>splitString(string s, char c) {
	istringstream ss(s);
	string token;
	vector<string>res;
	while (getline(ss, token, c)) {
		res.push_back(token);
	}
	return res;
}


//Intent : call gloomHaven_obj.inputCharacterAndCard �}�l��JPlayer����P�d�P
void inputCharacterAndCard(GloomHaven& gloomHaven_obj, CharacterData& characterData_obj) {
	gloomHaven_obj.inputCharacterAndCard(characterData_obj);
}

//Intent : �⨤��name��s��a�ϤW
void fetchCharacterNameIntoMap(MapData& map_obj, GloomHaven& gloomHaven_obj) {
	for (int i = 0; i < gCharacterNumber; i++) {
		map_obj.characterData[i].name = gloomHaven_obj.playerVector[i].info.name;
	}
}



// Intent :��̫�Q�D�諸�Ǫ���s��gloomHaven class�� monsterVector 
void fetchMonsterIntoGloomHaven(MapData& map_obj, GloomHaven& gloomHaven_obj, MonsterData& monsterData_obj) {
	for (int i = 0; i < map_obj.monsterNum; i++) {
		string monsterName = map_obj.enemyData[i].name;
		for (int j = 0; j < monsterData_obj.monsterVector.size(); j++) {
			if (monsterName == monsterData_obj.monsterVector[j].info.name) {
				if (map_obj.enemyData[i].kindOfEnemy == 1) {			//���q
					monsterData_obj.monsterVector[j].finalInfo.name = monsterData_obj.monsterVector[j].info.name;
					monsterData_obj.monsterVector[j].finalInfo.hp = monsterData_obj.monsterVector[j].info.normalHp;
					monsterData_obj.monsterVector[j].finalInfo.dmg = monsterData_obj.monsterVector[j].info.normalDmg;
					monsterData_obj.monsterVector[j].finalInfo.range = monsterData_obj.monsterVector[j].info.normalRange;
					monsterData_obj.monsterVector[j].finalInfo.exist = map_obj.enemyData[i].exist;  //***�o�̧�i
					monsterData_obj.monsterVector[j].finalInfo.index = i;
					monsterData_obj.monsterVector[j].finalInfo.maxHp = monsterData_obj.monsterVector[j].finalInfo.hp;
				}
				else if (map_obj.enemyData[i].kindOfEnemy == 2) {			//�׭^
					monsterData_obj.monsterVector[j].finalInfo.name = monsterData_obj.monsterVector[j].info.name;
					monsterData_obj.monsterVector[j].finalInfo.hp = monsterData_obj.monsterVector[j].info.eliteHp;
					monsterData_obj.monsterVector[j].finalInfo.dmg = monsterData_obj.monsterVector[j].info.eliteDmg;
					monsterData_obj.monsterVector[j].finalInfo.range = monsterData_obj.monsterVector[j].info.eliteRange;
					monsterData_obj.monsterVector[j].finalInfo.exist = map_obj.enemyData[i].exist;		//**�o�̧�i
					monsterData_obj.monsterVector[j].finalInfo.index = i;
					monsterData_obj.monsterVector[j].finalInfo.maxHp = monsterData_obj.monsterVector[j].finalInfo.hp;
				}
				gloomHaven_obj.monsterVector.push_back(monsterData_obj.monsterVector[j]);
			}
		}
	}
}