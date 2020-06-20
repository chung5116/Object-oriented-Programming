#ifndef CHARACTER_H
#define CHARACTER_H
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

struct cEachTurnQualityS {
	int heal = 0;			//當回合回復血量
	int shield = 0;			//當回合防禦力
	int attack = 0;		//當回合攻擊力
};


struct cSkill {
	int agi;    //敏捷值
	int code; //編號
	vector<string>topSkill;
	vector<string>bottomSkill;
};

struct characterInfoS{			// "S" means struct
	string name;
	int hp;
	int maxHp;
	//int tmpAgi = -1;
	int numOfHandCard;  
	int totalCard;
	bool exist = true;
	cEachTurnQualityS eachTurnQuality;
};

class SingleCharacter {			// 單一腳色information
public:
	characterInfoS info;
	vector<cSkill>cardVector;				//全部的牌給player選擇要那些
	vector<cSkill>handCardsVector;    // player 的手牌
	//vector<cSkill>cardToPlay;     // 從手牌選出的兩張牌，每回合clear一次
	vector<cSkill>discardCardsVector;    // player 的氣牌堆
	SingleCharacter(vector<string>info,int totalCard);
	SingleCharacter(SingleCharacter sC,vector<string>cardsIndex);    // bulid the character that player choose
	void resetQuality(); //重整每回合的素質
};


#endif // !CHARACTER_H
