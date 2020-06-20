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
	vector<string> stringToMonsterInfo(string s);	//Intent : ��@�ƪ���T�monster info�A��vector�x�s�A��K����ϥ�
	void stringToCardInfo(string s);	//Intent : ��@�ƪ���T�card info�A��� mSkill �x�s�A�@����@�d������T
	int getTheMonsterCardIndex(int mIndex, int cardCode);	//�Ƕi�өǪ���index�P���M��d�����s���A�^�Ǹӥd���b��vector��index
	
};

#endif // !MONSTERDATA_H
