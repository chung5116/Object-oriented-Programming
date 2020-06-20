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

//bool sortByCode(const cSkill& a, const cSkill& b); // 依照編號調整順序
bool sortByAgi(const commandResult& a, const commandResult& b); // 依照敏捷值調整順序


class GloomHaven {
private:
	friend class Actions;
	
	int numOfCharacter;  //player選擇幾隻角色
	int surviveCharacter;  // 目前還沒死亡的角色數量
	
	//int round = 0; //回和數
	//void printRound(); // print round x : 
	vector<commandResult> playerInputCommand(MapData& map_obj);   // 4-1   玩家準備階段
	vector<commandResult> monsterInputCommand(MapData& map_obj);   // 4-1   怪物準備階段
	// 把玩家，怪物選擇的牌 根據敏捷值排序 
	vector<commandResult> sortCommandByAgi(vector<commandResult>cCommand, vector<commandResult>mCommand);
	void commandCheck(int index);     // print 角色手牌 棄牌等
	//void commandBreak(int index);		//角色長休
	void commandPlay(int index,int card1,int card2);		//角色打牌  card12 是卡片編號 並非index
	int findCardIndexFromCode(int code,int roleIndex,string type);			// 利用卡片編號尋找卡片在該role的handCardsVector的index
	void showRoleStep(vector<commandResult>sortCommand);   //顯示所有角色與怪物的行動先後順序  *流程4-2
	bool allCharacterDead();		// 檢查是否全部角色都死亡
	bool allMonsterDead();			//檢查是否全部怪物都以死亡
public:
	GloomHaven(int characterNumber);

	vector<SingleCharacter>playerVector;    // the character and cards that player choose    **這裡的index跟map的 characterData 的index 樣
	vector<SingleMonster>monsterVector;   // 對應角色數量後 場上的怪物        **這裡的index跟map的 enemyData 的index 樣
	void inputCharacterAndCard(CharacterData& characterData_obj);  //determine which character and cards the player want
	void startGame(CharacterData& characterData_obj, MonsterData& monsterData_obj, MapData& map_obj);   // start game
	bool checkCharacterCanContinue(int index, MapData& map_obj);   //檢查是否可以出牌或是長休 若不行則死亡
	bool endOfEveryTurn(MapData& map_obj); //每回合結束計算
};



#endif // !GLOOMHAVEN_H
