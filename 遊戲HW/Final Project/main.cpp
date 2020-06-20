#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include"CharacterData.h"
#include"MonsterData.h"
#include"Gloomhaven.h"
#include"MapData.h"
using namespace std;

int gCharacterNumber;  //出場角色數量

// split args to get filename
vector<string> parsing(char* args[]);
// 開始遊戲?
void playGame();
// 決定上場角色與技能卡
void inputCharacterAndCard(GloomHaven& gloomHaven_obj, CharacterData& characterData_obj);
// split string
vector<string>splitString(string s, char c);
// 把角色name更新到地圖上
void fetchCharacterNameIntoMap(MapData& map_obj, GloomHaven& gloomHaven_obj);
// 把最後被挑選的怪物更新到gloomHaven class的 monsterVector 
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
		cout << "請輸入地圖名稱\n";
		cin >> mapFile;
		//mapFile = "map1.txt";
		//gCharacterNumber = 2;						//for test
		MapData map_obj(mapFile, gCharacterNumber);
		system("CLS");
		map_obj.printMap();

		fetchCharacterNameIntoMap(map_obj, gloomHaven_obj);
		fetchMonsterIntoGloomHaven(map_obj, gloomHaven_obj, monsterData_obj);

		// 流程4-1 開始
		gloomHaven_obj.startGame(characterData_obj, monsterData_obj, map_obj);
	}
}

//Intent : 把一開始的args轉成string
//Post: return vector<string>，各為角色資訊檔名，怪物資訊檔名
vector<string> parsing(char* args[]) {
	vector<string>res;

	string s(args[1]);
	res.push_back(s);
	string ss(args[2]);
	res.push_back(ss);

	return res;
}


//Intent : 詢問是否開始遊戲，並把player角色數量儲存在gCharacterNumber
void playGame() {
	string s;
	cout << "開始遊戲?\n";
	cin >> s;
	//s = "play";						/* ------for debug---------*/
	if (s == "play") {
		int num;
		system("CLS");
		cout << "玩家輸入角色數量(數字2 - 4)\n";		
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

//Intent : 把string 依照c切割
//Pre: string ,char 不可為0
//Post: return 分割後結果
vector<string>splitString(string s, char c) {
	istringstream ss(s);
	string token;
	vector<string>res;
	while (getline(ss, token, c)) {
		res.push_back(token);
	}
	return res;
}


//Intent : call gloomHaven_obj.inputCharacterAndCard 開始輸入Player角色與卡牌
void inputCharacterAndCard(GloomHaven& gloomHaven_obj, CharacterData& characterData_obj) {
	gloomHaven_obj.inputCharacterAndCard(characterData_obj);
}

//Intent : 把角色name更新到地圖上
void fetchCharacterNameIntoMap(MapData& map_obj, GloomHaven& gloomHaven_obj) {
	for (int i = 0; i < gCharacterNumber; i++) {
		map_obj.characterData[i].name = gloomHaven_obj.playerVector[i].info.name;
	}
}



// Intent :把最後被挑選的怪物更新到gloomHaven class的 monsterVector 
void fetchMonsterIntoGloomHaven(MapData& map_obj, GloomHaven& gloomHaven_obj, MonsterData& monsterData_obj) {
	for (int i = 0; i < map_obj.monsterNum; i++) {
		string monsterName = map_obj.enemyData[i].name;
		for (int j = 0; j < monsterData_obj.monsterVector.size(); j++) {
			if (monsterName == monsterData_obj.monsterVector[j].info.name) {
				if (map_obj.enemyData[i].kindOfEnemy == 1) {			//普通
					monsterData_obj.monsterVector[j].finalInfo.name = monsterData_obj.monsterVector[j].info.name;
					monsterData_obj.monsterVector[j].finalInfo.hp = monsterData_obj.monsterVector[j].info.normalHp;
					monsterData_obj.monsterVector[j].finalInfo.dmg = monsterData_obj.monsterVector[j].info.normalDmg;
					monsterData_obj.monsterVector[j].finalInfo.range = monsterData_obj.monsterVector[j].info.normalRange;
					monsterData_obj.monsterVector[j].finalInfo.exist = map_obj.enemyData[i].exist;  //***這裡改i
					monsterData_obj.monsterVector[j].finalInfo.index = i;
					monsterData_obj.monsterVector[j].finalInfo.maxHp = monsterData_obj.monsterVector[j].finalInfo.hp;
				}
				else if (map_obj.enemyData[i].kindOfEnemy == 2) {			//菁英
					monsterData_obj.monsterVector[j].finalInfo.name = monsterData_obj.monsterVector[j].info.name;
					monsterData_obj.monsterVector[j].finalInfo.hp = monsterData_obj.monsterVector[j].info.eliteHp;
					monsterData_obj.monsterVector[j].finalInfo.dmg = monsterData_obj.monsterVector[j].info.eliteDmg;
					monsterData_obj.monsterVector[j].finalInfo.range = monsterData_obj.monsterVector[j].info.eliteRange;
					monsterData_obj.monsterVector[j].finalInfo.exist = map_obj.enemyData[i].exist;		//**這裡改i
					monsterData_obj.monsterVector[j].finalInfo.index = i;
					monsterData_obj.monsterVector[j].finalInfo.maxHp = monsterData_obj.monsterVector[j].finalInfo.hp;
				}
				gloomHaven_obj.monsterVector.push_back(monsterData_obj.monsterVector[j]);
			}
		}
	}
}