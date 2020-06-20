#ifndef MONSTER_H
#define MONSTER_H
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

struct mSkill{
	int agi;    //�ӱ���
	int code;  //�d���s��
	vector<string>skillVector;
	int reShuffle = 0;   //  1:r  0:d
};

struct mEachTurnQualityS {
	int heal = 0;			//��^�X�^�_��q
	int shield = 0;			//��^�X���m�O
	int attack = 0;		//��^�X�����O
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

struct monsterFinalInfoS {				// ��w�׭^�δ��q��ϥΡAtmp�O���ޯ�d���Ӧ^�X����¦�t��v�T
	string name;
	int hp;
	int dmg;
	int range;
	int index;	// �bmap�̪� enemyData��index
	int maxHp;
	bool exist = true;
	mEachTurnQualityS eachTurnQuality;
};

class SingleMonster {
public:
	monsterInfoS info;
	monsterFinalInfoS finalInfo;
	vector<mSkill>cardVector;
	vector<mSkill>discardCardsVector;    // monster ����P��
	SingleMonster(vector<string>info);
	void resetQuality();				//����C�^�X������
};

#endif // !MONSTER_H
