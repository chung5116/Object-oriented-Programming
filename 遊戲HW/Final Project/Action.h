#ifndef ACTION_H
#define ACTION
using namespace std;
#include<iostream>
#include"CharacterData.h"
#include"Character.h"
#include"Monster.h"
#include"MonsterData.h"
#include"MapData.h"
#include<vector>
#include<algorithm>

extern vector<string>splitString(string s, char c);
bool sortByCode(const cSkill& a, const cSkill& b); // �̷ӽs���վ㶶��
bool sortByCode2(const mSkill& a, const mSkill& b); // �̷ӽs���վ㶶��

struct commandResult {         //�Ψ��x�splayer��J�����O �P �Ǫ���P�����G
	string type;       //character or monster			"c"  or "m"
	string name;    //**�]���Ǫ��i��ݭn��name�Ӥ������
	char icon;      // ������ܻݭnicon
	int index;			// ����/�Ǫ��bvector��index
	int card1;			//��ܥd��1��"�s��"
	int card2;			//��ܥd��2��"�s��"
	bool takeBreak;	// ��ܪ���
	int agi = 0;				//�ӱ���
	int agi2 = -1;      //**�����⪺�ĤG�i�d��
	commandResult(int mindex, int mcard1, int mcard2, string type);			// ��� �X�P
	commandResult(int mindex, bool mtakebreak, string type);		//��ܪ���
};


class Actions{
private:
	vector<SingleCharacter>* playerVector;
	vector<SingleMonster>*monsterVector;
public:
	Actions(vector<SingleCharacter>* playerVector,vector<SingleMonster>* monsterVector);
	// �̷Ӷ������ޯ� �y�{4-3�A�ç⨤��P�Ǫ��i����y
	void executiveSkills(vector<commandResult>sortCommand, CharacterData& characterData_obj, MonsterData& monsterData_obj, MapData& map_obj);
	//����Ǫ��ޯ�
	void monsterSkills(commandResult command	,CharacterData& characterData_obj,MonsterData& monsterData_obj	,MapData& map_obj, vector<commandResult>sortCommand);
	void monsterShield(commandResult command, vector<string>oneSkill);   //�Ǫ��@��
	void monsterHeal(commandResult command, vector<string>oneSkill);  //�Ǫ��^�_hp
	void monsterMove(commandResult command, vector<string>oneSkill, MapData& map_obj);  //�Ǫ����ʦ�m
	void monsterAttack(commandResult command, vector<string>oneSkill, MapData& map_obj, vector<commandResult>sortCommand);  //�Ǫ���������
	void closeAttack(commandResult command, vector<string>oneSkill, MapData& map_obj, vector<commandResult>sortCommand); //�Ǫ���ԧ���
	void rangedAttack(commandResult command, vector<string>oneSkill, MapData& map_obj,int attackRange, vector<commandResult>sortCommand); //�Ǫ����{����


	//���樤��ޯ�
	void characterSkills(commandResult command, CharacterData& characterData_obj, MonsterData& monsterData_obj, MapData& map_obj);
	void characterShield(commandResult command, vector<string>oneSkill);   //�}���@��
	void characterHeal(commandResult command, vector<string>oneSkill);  //�}��^�_hp
	void characterMove(commandResult command, vector<string>oneSkill, MapData& map_obj);  //�}�Ⲿ�ʦ�m
	void characterAttack(commandResult command, vector<string>oneSkill, int range, MapData& map_obj);	//�}�����
	void commandBreak(int index, MapData& map_obj);  //�������  �^�_���I��B��agi = 99�A�ݱq��P���˱�@�i�ñN�Ѿl�d�P�[�^��P
	
};

#endif // !ACTION_H
