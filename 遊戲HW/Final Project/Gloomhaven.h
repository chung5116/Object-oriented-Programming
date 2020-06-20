#ifndef GLOOMHAVEN_H
#define GLOOMHAVEN_H
#include"CharacterData.h"
#include"Character.h"
#include"Monster.h"
#include"MonsterData.h"
#include"MapData.h"
#include"Action.h"
#include<algorithm>


extern vector<string>splitString(string s, char c);

//bool sortByCode(const cSkill& a, const cSkill& b); // �̷ӽs���վ㶶��
bool sortByAgi(const commandResult& a, const commandResult& b); // �̷ӱӱ��Ƚվ㶶��


class GloomHaven {
private:
	friend class Actions;
	
	int numOfCharacter;  //player��ܴX������
	int surviveCharacter;  // �ثe�٨S���`������ƶq
	
	//int round = 0; //�^�M��
	//void printRound(); // print round x : 
	vector<commandResult> playerInputCommand(MapData& map_obj);   // 4-1   ���a�ǳƶ��q
	vector<commandResult> monsterInputCommand(MapData& map_obj);   // 4-1   �Ǫ��ǳƶ��q
	// �⪱�a�A�Ǫ���ܪ��P �ھڱӱ��ȱƧ� 
	vector<commandResult> sortCommandByAgi(vector<commandResult>cCommand, vector<commandResult>mCommand);
	void commandCheck(int index);     // print �����P ��P��
	//void commandBreak(int index);		//�������
	void commandPlay(int index,int card1,int card2);		//���⥴�P  card12 �O�d���s�� �ëDindex
	int findCardIndexFromCode(int code,int roleIndex,string type);			// �Q�Υd���s���M��d���b��role��handCardsVector��index
	void showRoleStep(vector<commandResult>sortCommand);   //��ܩҦ�����P�Ǫ�����ʥ��ᶶ��  *�y�{4-2
	bool allCharacterDead();		// �ˬd�O�_�������ⳣ���`
	bool allMonsterDead();			//�ˬd�O�_�����Ǫ����H���`
public:
	GloomHaven(int characterNumber);

	vector<SingleCharacter>playerVector;    // the character and cards that player choose    **�o�̪�index��map�� characterData ��index ��
	vector<SingleMonster>monsterVector;   // ��������ƶq�� ���W���Ǫ�        **�o�̪�index��map�� enemyData ��index ��
	void inputCharacterAndCard(CharacterData& characterData_obj);  //determine which character and cards the player want
	void startGame(CharacterData& characterData_obj, MonsterData& monsterData_obj, MapData& map_obj);   // start game
	bool checkCharacterCanContinue(int index, MapData& map_obj);   //�ˬd�O�_�i�H�X�P�άO���� �Y����h���`
	bool endOfEveryTurn(MapData& map_obj); //�C�^�X�����p��
};



#endif // !GLOOMHAVEN_H
