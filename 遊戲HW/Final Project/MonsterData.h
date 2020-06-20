#ifndef MONSTERDATA_H
#define MONSTERDATA_H
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include"Monster.h"

class MonsterData {
private:
	int numOfMonster; //total number of character
	
public:
	MonsterData(string s);
	vector<SingleMonster>monsterVector;
	vector<string> stringToMonsterInfo(string s);	//Intent : 把一排的資訊拆成monster info，用vector儲存，方便後續使用
	void stringToCardInfo(string s);	//Intent : 把一排的資訊拆成card info，後用 mSkill 儲存，作為單一卡片的資訊
	int getTheMonsterCardIndex(int mIndex, int cardCode);	//傳進該怪物的index與欲尋找卡片的編號，回傳該卡片在該vector的index
	
};

#endif // !MONSTERDATA_H
