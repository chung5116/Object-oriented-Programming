#include"Action.h"

//Intent: 依照編號調整順序  for character，未來可改寫成template
bool sortByCode(const cSkill& a, const cSkill& b) {
	return a.code < b.code;
}

//Intent: 依照編號調整順序	for monster
bool sortByCode2(const mSkill& a, const mSkill& b) {
	return a.code < b.code;
}


Actions::Actions(vector<SingleCharacter>* tmpplayerVector, vector<SingleMonster>* tmpmonsterVector){
	playerVector = tmpplayerVector;
	monsterVector = tmpmonsterVector;
}

//Intent: 依照順續執行技能 流程4-3
void  Actions::executiveSkills(vector<commandResult>sortCommand, CharacterData& characterData_obj, MonsterData& monsterData_obj, MapData& map_obj) {
	for (int i = 0; i < (*playerVector).size(); i++) {
		(*playerVector)[i].resetQuality();
	}
	for (int i = 0; i < (*monsterVector).size(); i++) {
		(*monsterVector)[i].resetQuality();
	}
	for (int i = 0; i < sortCommand.size(); i++) {
		if (sortCommand[i].type == "c") {		//character 
			characterSkills(sortCommand[i], characterData_obj, monsterData_obj, map_obj);
		}
		else if (sortCommand[i].type == "m") {		//monster
			monsterSkills(sortCommand[i], characterData_obj, monsterData_obj, map_obj, sortCommand);
		}
	}
}


//Intent:執行怪物技能
void Actions::monsterSkills(commandResult command, CharacterData& characterData_obj, MonsterData& monsterData_obj, MapData& map_obj, vector<commandResult>sortCommand) {
	int roleIndex = command.index;
	if ((*monsterVector)[roleIndex].finalInfo.exist == false) {			// 先檢查怪物是否存在
		return;
	}
	int mIndex;
	for (int i = 0; i < monsterData_obj.monsterVector.size(); i++) {
		if (command.name == monsterData_obj.monsterVector[i].finalInfo.name)
			mIndex = i;
	}
	int cardIndex = monsterData_obj.getTheMonsterCardIndex(mIndex, command.card1);
	if (cardIndex != -1) {
		mSkill monsterSkill = monsterData_obj.monsterVector[mIndex].cardVector[cardIndex];
		monsterData_obj.monsterVector[mIndex].resetQuality();
		monsterData_obj.monsterVector[mIndex].finalInfo.eachTurnQuality.attack = monsterData_obj.monsterVector[mIndex].finalInfo.dmg;
		for (int i = 0; i < monsterSkill.skillVector.size(); i++) {
			vector<string>oneSkill = splitString(monsterSkill.skillVector[i], ' ');
			if (oneSkill[0] == "move") {
				monsterMove(command, oneSkill,map_obj);
			}
			else if (oneSkill[0] == "shield") {
				monsterShield(command, oneSkill);
			}
			else if (oneSkill[0] == "heal") {
				monsterHeal(command, oneSkill);
			}
			else if (oneSkill[0] == "attack") {				//eg. attack -1 , attack 1 range 0
				monsterAttack(command, oneSkill, map_obj,sortCommand);
			}
		}
		if (monsterSkill.reShuffle == 1) {		//重洗
			for (int i = 0; i < (*monsterVector)[roleIndex].discardCardsVector.size(); i++) {		//把棄牌堆重新加進手牌
				mSkill discardToHand = (*monsterVector)[roleIndex].discardCardsVector[i];
				(*monsterVector)[roleIndex].cardVector.push_back(discardToHand);
			}
			(*monsterVector)[roleIndex].discardCardsVector.clear();			//清空棄牌堆
		}
		else {
			int discardIndex = 0;		//即將要被丟棄的手排的index
			while (1) {		//找出discardIndex
				if (command.card1 == (*monsterVector)[roleIndex].cardVector[discardIndex].code) {
					break;
				}
				discardIndex++;
			}
			//推進棄排堆
			(*monsterVector)[roleIndex].discardCardsVector.push_back((*monsterVector)[roleIndex].cardVector[discardIndex]);
			//該排與手排最後一張swap後，pop back
			swap((*monsterVector)[roleIndex].cardVector[discardIndex], (*monsterVector)[roleIndex].cardVector[(*monsterVector)[roleIndex].cardVector.size() - 1]);
			(*monsterVector)[roleIndex].cardVector.pop_back();
			//整理手排堆&棄排堆
			sort((*monsterVector)[roleIndex].cardVector.begin(), (*monsterVector)[roleIndex].cardVector.end(), sortByCode2);
			sort((*monsterVector)[roleIndex].discardCardsVector.begin(), (*monsterVector)[roleIndex].discardCardsVector.end(), sortByCode2);

		}
		sort((*monsterVector)[roleIndex].cardVector.begin(), (*monsterVector)[roleIndex].cardVector.end(), sortByCode2);
	}
	else {
		cout << "monsterSkill error occur\n";
	}
}


//Intent: 護甲持續至本回合結束(註: 此護甲值為技能敘述上的數值, 非本回合已獲得護甲的總數值)
void Actions::monsterShield(commandResult command, vector<string>oneSkill) {
	int roleIndex = command.index;
	char icon = command.icon;
	int shieldValue = stoi(oneSkill[1]);
	(*monsterVector)[roleIndex].finalInfo.eachTurnQuality.shield += shieldValue;
	cout << icon << " shield " << shieldValue << " this turn\n";
	
}

//Intent: 輸出回復量和回復後血量，血量不會超過最大血量 ex: a heal 2, now hp is 10
void Actions::monsterHeal(commandResult command, vector<string>oneSkill) {
	int roleIndex = command.index;
	char icon = command.icon;
	int healValue = stoi(oneSkill[1]);
	// 不超過最大血量
	if ((*monsterVector)[roleIndex].finalInfo.hp + healValue > (*monsterVector)[roleIndex].finalInfo.maxHp) {
		(*monsterVector)[roleIndex].finalInfo.hp = (*monsterVector)[roleIndex].finalInfo.maxHp;
	}
	else {
		(*monsterVector)[roleIndex].finalInfo.hp += healValue;
	}
	int nowHp = (*monsterVector)[roleIndex].finalInfo.hp;
	cout << icon << " heal " << healValue << ", now hp is " << nowHp << endl;
}

//Intent: 只輸出最終移動位置, 不用每一步都輸出一次地圖, 即使移動完停在原地也要更新地圖
void Actions::monsterMove(commandResult command, vector<string>oneSkill, MapData& map_obj) {
	int roleIndex = command.index;
	string moves = oneSkill[1];    // eg. wwa , wdsd
	map_obj.roleMove("m", roleIndex, moves);
	map_obj.printMap();			//印出更新後地圖
}



//Intent: 怪物攻擊角色 a lock A in distance 3，如果沒目標"no one lock"
//a attack A 3 damage, A shield 1, A remain 12 hp
void Actions::monsterAttack(commandResult command, vector<string>oneSkill, MapData& map_obj, vector<commandResult>sortCommand) {
	//判斷 進站 OR 遠程
	// 先把怪物的座標拉出來，在把各角色的座標拉出來先做近戰攻擊準備  然後才是視野，遠程
	int dRange;	//範圍變化值
	int dAttack = stoi(oneSkill[1]);  //攻擊力變化值
	int roleIndex = command.index;	   //monster 在  (*monsterVector)的index
	if (oneSkill.size() == 2) {		// attack 1
		dRange = 0;
	}
	else if (oneSkill.size() == 4) {		//attack 0 range 1
		dRange = stoi(oneSkill[3]);
	}
	int attackRange = (*monsterVector)[roleIndex].finalInfo.range + dRange;
	(*monsterVector)[roleIndex].finalInfo.eachTurnQuality.attack += dAttack;


	if (attackRange == 0) {		//近戰攻擊
		closeAttack(command, oneSkill, map_obj, sortCommand);
	}
	else if (attackRange > 0) {		//遠程
		rangedAttack(command, oneSkill, map_obj, attackRange, sortCommand);
	}
}


// Intent : 怪物近戰攻擊
void Actions::closeAttack(commandResult command, vector<string>oneSkill, MapData& map_obj, vector<commandResult>sortCommand) {
	int charaMinIndex;       // 後面使用給拿取角色icon使用
	int roleIndex = command.index;
	Postion posM = map_obj.enemyData[roleIndex].pos;   //怪物pos
	vector<int>indexOfCharacterInRange;   // 符合範圍的角色index of "playerVector"，因為若有多的敵人，則須從agi最小的

	for (int i = 0; i < (*playerVector).size(); i++) {
		if ((*playerVector)[i].info.exist == false)		// 如果角色已死亡則continue
			continue;

		Postion posC = map_obj.characterData[i].pos;

		int totalRange = abs(posC.x - posM.x) + abs(posC.y - posM.y);
		if (totalRange == 1)
			indexOfCharacterInRange.push_back(i);
	}
	

	if (indexOfCharacterInRange.empty()) {		// 沒有角色在近戰攻擊範圍內
		cout << "no one lock\n";
	}
	else {
		int minAgi = 101;     // 在符合範圍的角色裡 agi最小的index
		int minIndex = 0;
		for (int i = 0; i < indexOfCharacterInRange.size(); i++) {
			string name = (*playerVector)[indexOfCharacterInRange[i]].info.name;
			for (int j = 0; j < sortCommand.size(); j++) {			// use name to find it's agi
				if (name == sortCommand[j].name) {
					if (sortCommand[j].agi < minAgi) {
						minIndex = i;
						minAgi = sortCommand[j].agi;
						charaMinIndex = j;
					}
				}
			}
		}
		// minIndex 就是要攻擊的目標了
		
		minIndex = indexOfCharacterInRange[minIndex];
		int damage = (*monsterVector)[roleIndex].finalInfo.eachTurnQuality.attack;
		int shield = (*playerVector)[minIndex].info.eachTurnQuality.shield;
		int hurt = damage - shield;
		if (hurt < 0)		// if shield > damage
			hurt = 0;
		(*playerVector)[minIndex].info.hp -= hurt;
		//eg. a lock A in distance 3
		cout << command.icon << " lock " << sortCommand[charaMinIndex].icon << " in distance 1\n";
		// eg. a attack A 10 damage, A shield 1, A remain 20 hp
		cout << command.icon << " attack " << sortCommand[charaMinIndex].icon << " " <<
			damage << " damage, " << sortCommand[charaMinIndex].icon << " shield " << shield <<
			", " << sortCommand[charaMinIndex].icon<<" remain " << (*playerVector)[minIndex].info.hp << " hp.\n";

		// 如果角色被攻擊後死亡
		if ((*playerVector)[minIndex].info.hp <= 0) {			
			(*playerVector)[minIndex].info.exist = false;
			cout << sortCommand[charaMinIndex].icon << " is killed !!\n";
			//通知map那邊 此角色已死亡
			map_obj.characterData[minIndex].exist = false;
			map_obj.printMap();
		}
	}

}


//Intent : 怪物遠程攻擊
void Actions::rangedAttack(commandResult command, vector<string>oneSkill, MapData& map_obj, int attackRange, vector<commandResult>sortCommand) {
	int roleIndex = command.index;
	Postion posM = map_obj.enemyData[roleIndex].pos;   //怪物pos
	bool lock = false;

	// 因要取距離最近的，故距離1放在[1]，距離2放在[2]
	vector<vector<int>>indexOfCharacterInRange(attackRange+1);   // 符合範圍的角色index of "playerVector"，因為若有多的敵人，則須從agi最小的
	for (int i = 0; i < (*playerVector).size(); i++) {
		if ((*playerVector)[i].info.exist == false)		// 如果角色已死亡則continue
			continue;

		Postion posC = map_obj.characterData[i].pos;

		int totalRange = abs(posC.x - posM.x) + abs(posC.y - posM.y);
		if (totalRange <= attackRange) {
			indexOfCharacterInRange[totalRange].push_back(i);		// push在range內的腳色在"playerVector"的index
			lock = true;
		}
	}
	if (lock == false) {			//沒角色在範圍內
		cout << "no one lock\n";
		return;
	}
	lock = false;   // 可能在範圍內的都沒有視野

	//**從距離近的開始判斷有沒有視野然後就完成攻擊
	for (int i = 1; i < indexOfCharacterInRange.size(); i++) {
		for (int j = 0; j < indexOfCharacterInRange[i].size();j++) {
			int pIndex = indexOfCharacterInRange[i][j];   //在range內的腳色在"playerVector"的index
			int range = i;
			Postion posC = map_obj.characterData[pIndex].pos;
			if (map_obj.sight(posC, posM)) {
				lock = true;
				int damage = (*monsterVector)[roleIndex].finalInfo.eachTurnQuality.attack;
				int shield = (*playerVector)[pIndex].info.eachTurnQuality.shield;
				int hurt = damage - shield;
				if (hurt < 0)		// if shield > damage
					hurt = 0;

				(*playerVector)[pIndex].info.hp -= hurt;
				int charaMinIndex;

				// 因為需要使用角色icon 所以使用尋找該角色在"sortCommand"的index : k
				for (int k = 0; k < sortCommand.size(); k++) {
					if (sortCommand[k].index == pIndex && (*playerVector)[pIndex].info.name == sortCommand[k].name)
						charaMinIndex = k;
				}
				//eg. a lock A in distance 3
				cout << command.icon << " lock " << sortCommand[charaMinIndex].icon << " in distance " << i << endl;;
				// eg. a attack A 10 damage, A shield 1, A remain 20 hp
				cout << command.icon << " attack " << sortCommand[charaMinIndex].icon << " " <<
					damage << " damage, " << sortCommand[charaMinIndex].icon << " shield " << shield <<
					", " << sortCommand[charaMinIndex].icon << " remain " << (*playerVector)[pIndex].info.hp << "hp.\n";


				// 如果角色被攻擊後死亡
				if ((*playerVector)[pIndex].info.hp <= 0) {
					(*playerVector)[pIndex].info.exist = false;
					cout << sortCommand[charaMinIndex].icon << " is killed !!\n";
					//通知map那邊 此角色已死亡
					map_obj.characterData[pIndex].exist = false;
					map_obj.printMap();
				}
				return;
			}
		}
	}

	if (lock == false) {			//在範圍的角色裡都沒有視野
		cout << "no one lock\n";
		return;
	}
}


//--------------------------------------------------------------------------------------


//Intent:執行腳色技能
void Actions::characterSkills(commandResult command, CharacterData& characterData_obj, MonsterData& monsterData_obj, MapData& map_obj) {

	if (command.takeBreak) {
		cout << command.icon << "'s turn: card - 1\n";
		commandBreak(command.index, map_obj);

	}
	else {
		string  upOrDown;
		vector<string>  skill;
		cout << command.icon << "'s turn: card " << command.card1 << " " << command.card2 << "\n";
		while (1) {
			cin >> upOrDown;
			if (upOrDown == "check") {
				for (int i = 0; i < (*playerVector).size(); i++) {
					if ((*playerVector)[i].info.exist == true) {
						cout << map_obj.characterData[i].icon << "-hp: " << (*playerVector)[i].info.hp << ", shield: " << (*playerVector)[i].info.eachTurnQuality.shield << "\n";
					}
				}
				for (int i = 0; i < (*monsterVector).size(); i++) {
					if (map_obj.enemyData[i].exist == true) {
						cout << map_obj.enemyData[i].icon << "-hp: " << (*monsterVector)[i].finalInfo.hp << ", shield: " << (*monsterVector)[i].finalInfo.eachTurnQuality.shield << "\n";
					}
				}
			}
			else {
				int tempCardNum = upOrDown[0] - '0';
				if (tempCardNum == command.card1) {
					int cardNum = 0;
					while (1) {
						if (command.card1 == (*playerVector)[command.index].handCardsVector[cardNum].code) {
							break;
						}
						cardNum++;
					}
					if (upOrDown[1] == 'u') {
						skill = (*playerVector)[command.index].handCardsVector[cardNum].topSkill;
						for (int i = 0; i < skill.size(); i++) {
							vector<string>oneSkill = splitString(skill[i], ' ');
							if (oneSkill[0] == "move") {
								characterMove(command, oneSkill, map_obj);
							}
							else if (oneSkill[0] == "shield") {
								characterShield(command, oneSkill);
							}
							else if (oneSkill[0] == "heal") {
								characterHeal(command, oneSkill);
							}
							else if (oneSkill[0] == "attack" && oneSkill.size() == 4) {
								int range = stoi(oneSkill[3]);
								characterAttack(command, oneSkill, range, map_obj);
							}
							else if (oneSkill[0] == "attack") {
								int range = 1;
								characterAttack(command, oneSkill, range, map_obj);
							}
						}
						(*playerVector)[command.index].discardCardsVector.push_back((*playerVector)[command.index].handCardsVector[cardNum]);
						swap((*playerVector)[command.index].handCardsVector[cardNum], (*playerVector)[command.index].handCardsVector[(*playerVector)[command.index].handCardsVector.size() - 1]);
						(*playerVector)[command.index].handCardsVector.pop_back();
						sort((*playerVector)[command.index].handCardsVector.begin(), (*playerVector)[command.index].handCardsVector.end(), sortByCode);
						sort((*playerVector)[command.index].discardCardsVector.begin(), (*playerVector)[command.index].discardCardsVector.end(), sortByCode);
						int cardNum2 = 0;
						while (1) {
							if (command.card2 == (*playerVector)[command.index].handCardsVector[cardNum2].code) {
								break;
							}
							cardNum2++;
						}
						skill = (*playerVector)[command.index].handCardsVector[cardNum2].bottomSkill;
						for (int i = 0; i < skill.size(); i++) {
							vector<string>oneSkill = splitString(skill[i], ' ');
							if (oneSkill[0] == "move") {
								characterMove(command, oneSkill, map_obj);
							}
							else if (oneSkill[0] == "shield") {
								characterShield(command, oneSkill);
							}
							else if (oneSkill[0] == "heal") {
								characterHeal(command, oneSkill);
							}
							else if (oneSkill[0] == "attack" && oneSkill.size() == 4) {
								int range = stoi(oneSkill[3]);
								characterAttack(command, oneSkill, range, map_obj);
							}
							else if (oneSkill[0] == "attack") {
								int range = 1;
								characterAttack(command, oneSkill, range, map_obj);
							}
						}
						(*playerVector)[command.index].discardCardsVector.push_back((*playerVector)[command.index].handCardsVector[cardNum2]);
						swap((*playerVector)[command.index].handCardsVector[cardNum2], (*playerVector)[command.index].handCardsVector[(*playerVector)[command.index].handCardsVector.size() - 1]);
						(*playerVector)[command.index].handCardsVector.pop_back();
						sort((*playerVector)[command.index].handCardsVector.begin(), (*playerVector)[command.index].handCardsVector.end(), sortByCode);
						sort((*playerVector)[command.index].discardCardsVector.begin(), (*playerVector)[command.index].discardCardsVector.end(), sortByCode);
					}
					else if (upOrDown[1] == 'd') {
						skill = (*playerVector)[command.index].handCardsVector[cardNum].bottomSkill;
						for (int i = 0; i < skill.size(); i++) {
							vector<string>oneSkill = splitString(skill[i], ' ');
							if (oneSkill[0] == "move") {
								characterMove(command, oneSkill, map_obj);
							}
							else if (oneSkill[0] == "shield") {
								characterShield(command, oneSkill);
							}
							else if (oneSkill[0] == "heal") {
								characterHeal(command, oneSkill);
							}
							else if (oneSkill[0] == "attack" && oneSkill.size() == 4) {
								int range = stoi(oneSkill[3]);
								characterAttack(command, oneSkill, range, map_obj);
							}
							else if (oneSkill[0] == "attack") {
								int range = 1;
								characterAttack(command, oneSkill, range, map_obj);
							}
						}
						(*playerVector)[command.index].discardCardsVector.push_back((*playerVector)[command.index].handCardsVector[cardNum]);
						swap((*playerVector)[command.index].handCardsVector[cardNum], (*playerVector)[command.index].handCardsVector[(*playerVector)[command.index].handCardsVector.size() - 1]);
						(*playerVector)[command.index].handCardsVector.pop_back();
						sort((*playerVector)[command.index].handCardsVector.begin(), (*playerVector)[command.index].handCardsVector.end(), sortByCode);
						sort((*playerVector)[command.index].discardCardsVector.begin(), (*playerVector)[command.index].discardCardsVector.end(), sortByCode);
						int cardNum2 = 0;
						while (1) {
							if (command.card2 == (*playerVector)[command.index].handCardsVector[cardNum2].code) {
								break;
							}
							cardNum2++;
						}
						skill = (*playerVector)[command.index].handCardsVector[cardNum2].topSkill;
						for (int i = 0; i < skill.size(); i++) {
							vector<string>oneSkill = splitString(skill[i], ' ');
							if (oneSkill[0] == "move") {
								characterMove(command, oneSkill, map_obj);
							}
							else if (oneSkill[0] == "shield") {
								characterShield(command, oneSkill);
							}
							else if (oneSkill[0] == "heal") {
								characterHeal(command, oneSkill);
							}
							else if (oneSkill[0] == "attack" && oneSkill.size() == 4) {
								int range = stoi(oneSkill[3]);
								characterAttack(command, oneSkill, range, map_obj);
							}
							else if (oneSkill[0] == "attack") {
								int range = 1;
								characterAttack(command, oneSkill, range, map_obj);
							}
						}
						(*playerVector)[command.index].discardCardsVector.push_back((*playerVector)[command.index].handCardsVector[cardNum2]);
						swap((*playerVector)[command.index].handCardsVector[cardNum2], (*playerVector)[command.index].handCardsVector[(*playerVector)[command.index].handCardsVector.size() - 1]);
						(*playerVector)[command.index].handCardsVector.pop_back();
						sort((*playerVector)[command.index].handCardsVector.begin(), (*playerVector)[command.index].handCardsVector.end(), sortByCode);
						sort((*playerVector)[command.index].discardCardsVector.begin(), (*playerVector)[command.index].discardCardsVector.end(), sortByCode);
					}
					break;
				}
				if (tempCardNum == command.card2) {
					int cardNum = 0;
					while (1) {
						if (command.card2 == (*playerVector)[command.index].handCardsVector[cardNum].code) {
							break;
						}
						cardNum++;
					}
					if (upOrDown[1] == 'u') {
						skill = (*playerVector)[command.index].handCardsVector[cardNum].topSkill;
						for (int i = 0; i < skill.size(); i++) {
							vector<string>oneSkill = splitString(skill[i], ' ');
							if (oneSkill[0] == "move") {
								characterMove(command, oneSkill, map_obj);
							}
							else if (oneSkill[0] == "shield") {
								characterShield(command, oneSkill);
							}
							else if (oneSkill[0] == "heal") {
								characterHeal(command, oneSkill);
							}
							else if (oneSkill[0] == "attack" && oneSkill.size() == 4) {
								int range = stoi(oneSkill[3]);
								characterAttack(command, oneSkill, range, map_obj);
							}
							else if (oneSkill[0] == "attack") {
								int range = 1;
								characterAttack(command, oneSkill, range, map_obj);
							}
						}
						(*playerVector)[command.index].discardCardsVector.push_back((*playerVector)[command.index].handCardsVector[cardNum]);
						swap((*playerVector)[command.index].handCardsVector[cardNum], (*playerVector)[command.index].handCardsVector[(*playerVector)[command.index].handCardsVector.size() - 1]);
						(*playerVector)[command.index].handCardsVector.pop_back();
						sort((*playerVector)[command.index].handCardsVector.begin(), (*playerVector)[command.index].handCardsVector.end(), sortByCode);
						sort((*playerVector)[command.index].discardCardsVector.begin(), (*playerVector)[command.index].discardCardsVector.end(), sortByCode);
						int cardNum2 = 0;
						while (1) {
							if (command.card1 == (*playerVector)[command.index].handCardsVector[cardNum2].code) {
								break;
							}
							cardNum2++;
						}
						skill = (*playerVector)[command.index].handCardsVector[cardNum2].bottomSkill;
						for (int i = 0; i < skill.size(); i++) {
							vector<string>oneSkill = splitString(skill[i], ' ');
							if (oneSkill[0] == "move") {
								characterMove(command, oneSkill, map_obj);
							}
							else if (oneSkill[0] == "shield") {
								characterShield(command, oneSkill);
							}
							else if (oneSkill[0] == "heal") {
								characterHeal(command, oneSkill);
							}
							else if (oneSkill[0] == "attack" && oneSkill.size() == 4) {
								int range = stoi(oneSkill[3]);
								characterAttack(command, oneSkill, range, map_obj);
							}
							else if (oneSkill[0] == "attack") {
								int range = 1;
								characterAttack(command, oneSkill, range, map_obj);
							}
						}
						(*playerVector)[command.index].discardCardsVector.push_back((*playerVector)[command.index].handCardsVector[cardNum2]);
						swap((*playerVector)[command.index].handCardsVector[cardNum2], (*playerVector)[command.index].handCardsVector[(*playerVector)[command.index].handCardsVector.size() - 1]);
						(*playerVector)[command.index].handCardsVector.pop_back();
						sort((*playerVector)[command.index].handCardsVector.begin(), (*playerVector)[command.index].handCardsVector.end(), sortByCode);
						sort((*playerVector)[command.index].discardCardsVector.begin(), (*playerVector)[command.index].discardCardsVector.end(), sortByCode);
					}
					else if (upOrDown[1] == 'd') {
						skill = (*playerVector)[command.index].handCardsVector[cardNum].bottomSkill;
						for (int i = 0; i < skill.size(); i++) {
							vector<string>oneSkill = splitString(skill[i], ' ');
							if (oneSkill[0] == "move") {
								characterMove(command, oneSkill, map_obj);
							}
							else if (oneSkill[0] == "shield") {
								characterShield(command, oneSkill);
							}
							else if (oneSkill[0] == "heal") {
								characterHeal(command, oneSkill);
							}
							else if (oneSkill[0] == "attack" && oneSkill.size() == 4) {
								int range = stoi(oneSkill[3]);
								characterAttack(command, oneSkill, range, map_obj);
							}
							else if (oneSkill[0] == "attack") {
								int range = 1;
								characterAttack(command, oneSkill, range, map_obj);
							}
						}
						(*playerVector)[command.index].discardCardsVector.push_back((*playerVector)[command.index].handCardsVector[cardNum]);
						swap((*playerVector)[command.index].handCardsVector[cardNum], (*playerVector)[command.index].handCardsVector[(*playerVector)[command.index].handCardsVector.size() - 1]);
						(*playerVector)[command.index].handCardsVector.pop_back();
						sort((*playerVector)[command.index].handCardsVector.begin(), (*playerVector)[command.index].handCardsVector.end(), sortByCode);
						sort((*playerVector)[command.index].discardCardsVector.begin(), (*playerVector)[command.index].discardCardsVector.end(), sortByCode);
						int cardNum2 = 0;
						while (1) {
							if (command.card1 == (*playerVector)[command.index].handCardsVector[cardNum2].code) {
								break;
							}
							cardNum2++;
						}
						skill = (*playerVector)[command.index].handCardsVector[cardNum2].topSkill;
						for (int i = 0; i < skill.size(); i++) {
							vector<string>oneSkill = splitString(skill[i], ' ');
							if (oneSkill[0] == "move") {
								characterMove(command, oneSkill, map_obj);
							}
							else if (oneSkill[0] == "shield") {
								characterShield(command, oneSkill);
							}
							else if (oneSkill[0] == "heal") {
								characterHeal(command, oneSkill);
							}
							else if (oneSkill[0] == "attack" && oneSkill.size() == 4) {
								int range = stoi(oneSkill[3]);
								characterAttack(command, oneSkill, range, map_obj);
							}
							else if (oneSkill[0] == "attack") {
								int range = 1;
								characterAttack(command, oneSkill, range, map_obj);
							}
						}
						(*playerVector)[command.index].discardCardsVector.push_back((*playerVector)[command.index].handCardsVector[cardNum2]);
						swap((*playerVector)[command.index].handCardsVector[cardNum2], (*playerVector)[command.index].handCardsVector[(*playerVector)[command.index].handCardsVector.size() - 1]);
						(*playerVector)[command.index].handCardsVector.pop_back();
						sort((*playerVector)[command.index].handCardsVector.begin(), (*playerVector)[command.index].handCardsVector.end(), sortByCode);
						sort((*playerVector)[command.index].discardCardsVector.begin(), (*playerVector)[command.index].discardCardsVector.end(), sortByCode);
					}
					break;
				}
				cout << "input again\n";
			}
		}
	}
}

//Intent: 護甲持續至本回合結束(註: 此護甲值為技能敘述上的數值, 非本回合已獲得護甲的總數值)
void Actions::characterShield(commandResult command, vector<string>oneSkill) {   //腳色護甲
	int roleIndex = command.index;
	char icon = command.icon;
	int shieldValue = stoi(oneSkill[1]);
	(*playerVector)[roleIndex].info.eachTurnQuality.shield += shieldValue;
	cout << icon << " shield " << shieldValue << " this turn\n";
}

//Intent: 輸出回復量和回復後血量，血量不會超過最大血量 ex: A heal 2, now hp is 10
void Actions::characterHeal(commandResult command, vector<string>oneSkill) {  //腳色回復hp
	int roleIndex = command.index;
	char icon = command.icon;
	int healValue = stoi(oneSkill[1]);
	// 不超過最大血量
	if ((*playerVector)[roleIndex].info.hp + healValue > (*playerVector)[roleIndex].info.maxHp) {
		(*playerVector)[roleIndex].info.hp = (*playerVector)[roleIndex].info.maxHp;
	}
	else {
		(*playerVector)[roleIndex].info.hp += healValue;
	}
	int nowHp = (*playerVector)[roleIndex].info.hp;
	cout << icon << " heal " << healValue << ", now hp is " << nowHp << endl;
}

//Intent: 角色移動
void Actions::characterMove(commandResult command, vector<string>oneSkill, MapData& map_obj) {
	int checkOpenDoor = 0;
	int roleIndex = command.index;
	int moves = stoi(oneSkill[1]);
	checkOpenDoor = map_obj.characterMove(roleIndex, moves);
	if (checkOpenDoor == 2) {
		map_obj.findValidPos(map_obj.defaultX, map_obj.defaultY);
		for (int i = 0; i < (*monsterVector).size(); i++) {
			if (map_obj.validPos[map_obj.enemyData[i].pos.y][map_obj.enemyData[i].pos.x] == 1 && (*monsterVector)[i].finalInfo.hp > 0) {
				map_obj.enemyData[i].exist = true;
				(*monsterVector)[i].finalInfo.exist = true;
			}
		}
	}
}

//還沒寫視野問題
//Intent: 角色攻擊
void Actions::characterAttack(commandResult command, vector<string>oneSkill, int range, MapData& map_obj) {
	while (1) {
		char target;
		int check = 0, attackNum, tempAttackNum;
		attackNum = stoi(oneSkill[1]);
		cout << "輸入要攻擊的目標(0:放棄攻擊):";
		cin >> target;
		if (target == '0') {	//放棄攻擊
			return;
		}
		for (int i = 0; i < (*monsterVector).size(); i++) {
			if (map_obj.enemyData[i].icon == target && map_obj.enemyData[i].exist == true) {
				if (abs(map_obj.enemyData[i].pos.x - map_obj.characterData[command.index].pos.x) + abs(map_obj.enemyData[i].pos.y - map_obj.characterData[command.index].pos.y) <= range) {
					tempAttackNum = attackNum - (*monsterVector)[i].finalInfo.eachTurnQuality.shield;  //攻擊力-怪物防禦力
					if (attackNum > 0) {
						(*monsterVector)[i].finalInfo.hp -= tempAttackNum;
					}
					cout << map_obj.characterData[command.index].icon << " attack " << target << " " << attackNum << " damage, " << target << " shield " << (*monsterVector)[i].finalInfo.eachTurnQuality.shield;
					cout << ", " << target << " remain " << (*monsterVector)[i].finalInfo.hp << " hp\n";
					if ((*monsterVector)[i].finalInfo.hp <= 0) {
						cout << target << " is killed!!\n";
						map_obj.enemyData[i].exist = false;
						(*monsterVector)[i].finalInfo.exist = false;
						map_obj.printMap();
					}
					return;
				}
			}
		}
		if (check == 0) {
			cout << "error target!!!\n";
			continue;
		}
	}

}

//Intent: 角色長休  回復兩點血且該agi = 99，需從棄牌推捨棄一張並將剩餘卡牌加回手牌
void Actions::commandBreak(int index, MapData& map_obj) {
	if ((*playerVector)[index].info.hp + 2 > (*playerVector)[index].info.maxHp) {
		(*playerVector)[index].info.hp = (*playerVector)[index].info.maxHp;
	}
	else {
		(*playerVector)[index].info.hp += 2;
	}
	cout << "hand: ";
	for (int i = 0; i < (*playerVector)[index].handCardsVector.size(); i++) {
		cout << " " << (*playerVector)[index].handCardsVector[i].code << ",";
	}
	cout << " ; discard: ";
	for (int i = 0; i < (*playerVector)[index].discardCardsVector.size(); i++) {
		cout << " " << (*playerVector)[index].discardCardsVector[i].code << ",";
	}
	cout << endl;
	int discardIndex;
	while (1) {
		cin >> discardIndex;
		bool invaild = true;   // check 丟棄卡編號存在
		for (int i = 0; i < (*playerVector)[index].discardCardsVector.size(); i++) {
			if (discardIndex == (*playerVector)[index].discardCardsVector[i].code) {
				(*playerVector)[index].discardCardsVector.erase((*playerVector)[index].discardCardsVector.begin() + i);    // 丟棄該卡片
				invaild = false;
			}
		}
		if (invaild == false)
			break;
	}
	// 將剩餘卡牌加回手牌
	for (int i = 0; i < (*playerVector)[index].discardCardsVector.size(); i++) {
		(*playerVector)[index].handCardsVector.push_back((*playerVector)[index].discardCardsVector[i]);
	}
	(*playerVector)[index].discardCardsVector.clear();

	/*sort(playerVector[index].handCardsVector.begin(), playerVector[index].handCardsVector.end(),
		[](const cSkill& a, const cSkill& b)
		{return a.code < b.code; });*/
		// 依照編號調整順序
	sort((*playerVector)[index].handCardsVector.begin(), (*playerVector)[index].handCardsVector.end(), sortByCode);
	cout << map_obj.characterData[index].icon << " heal 2, now hp is " << (*playerVector)[index].info.hp << "\nremove card: " << discardIndex << "\n";
}
