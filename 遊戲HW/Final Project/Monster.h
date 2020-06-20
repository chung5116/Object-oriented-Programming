#ifndef MONSTER_H
#define MONSTER_H
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

struct mSkill{
	int agi;    //敏捷值
	int code;  //卡片編號
	vector<string>skillVector;
	int reShuffle = 0;   //  1:r  0:d
};

struct mEachTurnQualityS {
	int heal = 0;			//當回合回復血量
	int shield = 0;			//當回合防禦力
	int attack = 0;		//當回合攻擊力
};

struct monsterInfoS{
	string name;
	int normalHp;
	int normalDmg;
	int normalRange;
	int eliteHp;
	int eliteDmg;
	int eliteRange;

};

struct monsterFinalInfoS {				// 選定菁英或普通後使用，tmp是給技能卡對於該回合的基礎速質影響
	string name;
	int hp;
	int dmg;
	int range;
	int index;	// 在map裡的 enemyData的index
	int maxHp;
	bool exist = true;
	mEachTurnQualityS eachTurnQuality;
};

class SingleMonster {
public:
	monsterInfoS info;
	monsterFinalInfoS finalInfo;
	vector<mSkill>cardVector;
	vector<mSkill>discardCardsVector;    // monster 的氣牌堆
	SingleMonster(vector<string>info);
	void resetQuality();				//重整每回合的素質
};

#endif // !MONSTER_H
