#ifndef CHARACTER_H
#define CHARACTER_H
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

struct cEachTurnQualityS {
	int heal = 0;			//��^�X�^�_��q
	int shield = 0;			//��^�X���m�O
	int attack = 0;		//��^�X�����O
};


struct cSkill {
	int agi;    //�ӱ���
	int code; //�s��
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

class SingleCharacter {			// ��@�}��information
public:
	characterInfoS info;
	vector<cSkill>cardVector;				//�������P��player��ܭn����
	vector<cSkill>handCardsVector;    // player ����P
	//vector<cSkill>cardToPlay;     // �q��P��X����i�P�A�C�^�Xclear�@��
	vector<cSkill>discardCardsVector;    // player ����P��
	SingleCharacter(vector<string>info,int totalCard);
	SingleCharacter(SingleCharacter sC,vector<string>cardsIndex);    // bulid the character that player choose
	void resetQuality(); //����C�^�X������
};


#endif // !CHARACTER_H
