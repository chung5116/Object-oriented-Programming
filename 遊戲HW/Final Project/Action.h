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
bool sortByCode(const cSkill& a, const cSkill& b); // 依照編號調整順序
bool sortByCode2(const mSkill& a, const mSkill& b); // 依照編號調整順序

struct commandResult {         //用來儲存player輸入的指令 與 怪物抽牌的結果
	string type;       //character or monster			"c"  or "m"
	string name;    //**因為怪物可能需要用name來比較順序
	char icon;      // 之後顯示需要icon
	int index;			// 角色/怪物在vector的index
	int card1;			//選擇卡片1的"編號"
	int card2;			//選擇卡片2的"編號"
	bool takeBreak;	// 選擇長休
	int agi = 0;				//敏捷值
	int agi2 = -1;      //**給角色的第二張卡片
	commandResult(int mindex, int mcard1, int mcard2, string type);			// 選擇 出牌
	commandResult(int mindex, bool mtakebreak, string type);		//選擇長休
};


class Actions{
private:
	vector<SingleCharacter>* playerVector;
	vector<SingleMonster>*monsterVector;
public:
	Actions(vector<SingleCharacter>* playerVector,vector<SingleMonster>* monsterVector);
	// 依照順續執行技能 流程4-3，並把角色與怪物進行分流
	void executiveSkills(vector<commandResult>sortCommand, CharacterData& characterData_obj, MonsterData& monsterData_obj, MapData& map_obj);
	//執行怪物技能
	void monsterSkills(commandResult command	,CharacterData& characterData_obj,MonsterData& monsterData_obj	,MapData& map_obj, vector<commandResult>sortCommand);
	void monsterShield(commandResult command, vector<string>oneSkill);   //怪物護甲
	void monsterHeal(commandResult command, vector<string>oneSkill);  //怪物回復hp
	void monsterMove(commandResult command, vector<string>oneSkill, MapData& map_obj);  //怪物移動位置
	void monsterAttack(commandResult command, vector<string>oneSkill, MapData& map_obj, vector<commandResult>sortCommand);  //怪物攻擊角色
	void closeAttack(commandResult command, vector<string>oneSkill, MapData& map_obj, vector<commandResult>sortCommand); //怪物近戰攻擊
	void rangedAttack(commandResult command, vector<string>oneSkill, MapData& map_obj,int attackRange, vector<commandResult>sortCommand); //怪物遠程攻擊


	//執行角色技能
	void characterSkills(commandResult command, CharacterData& characterData_obj, MonsterData& monsterData_obj, MapData& map_obj);
	void characterShield(commandResult command, vector<string>oneSkill);   //腳色護甲
	void characterHeal(commandResult command, vector<string>oneSkill);  //腳色回復hp
	void characterMove(commandResult command, vector<string>oneSkill, MapData& map_obj);  //腳色移動位置
	void characterAttack(commandResult command, vector<string>oneSkill, int range, MapData& map_obj);	//腳色攻擊
	void commandBreak(int index, MapData& map_obj);  //角色長休  回復兩點血且該agi = 99，需從棄牌推捨棄一張並將剩餘卡牌加回手牌
	
};

#endif // !ACTION_H
