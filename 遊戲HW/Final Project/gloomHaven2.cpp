#include"Gloomhaven.h"




//Intent:把玩家，怪物選擇的牌 根據敏捷值排序
//Pre: 若長休為true就不用set agi了，因為前面已經有設定了， 若沒長休則根據卡片的編號去抓取對應的agi
//Post : return 排序好的腳色/怪物  之後執行技能就使用這個順序
vector<commandResult>GloomHaven::sortCommandByAgi(vector<commandResult>cCommand, vector<commandResult>mCommand) {
	vector<commandResult>res;
	for (int i = 0; i < cCommand.size(); i++) {  // 第一章卡片作為agi
		if (cCommand[i].takeBreak == false) {		//沒有長休
			// card1 's agi
			int index= findCardIndexFromCode(cCommand[i].card1, cCommand[i].index,"c");
			if (index != -1) {
				cCommand[i].agi = playerVector[cCommand[i].index].handCardsVector[index].agi;
			}
			else {
				cout << "sortCommandByAgi error\n";
			}
			// card2's agi
			int index2 = findCardIndexFromCode(cCommand[i].card2, cCommand[i].index, "c");
			if (index2 != -1) {
				cCommand[i].agi2 = playerVector[cCommand[i].index].handCardsVector[index2].agi;
			}
			else {
				cout << "sortCommandByAgi error\n";
			}
		}
		else {
			cCommand[i].agi = 99;
		}
		res.push_back(cCommand[i]);
	}

	for (int i = 0; i < mCommand.size(); i++) {
		int index = findCardIndexFromCode(mCommand[i].card1, mCommand[i].index, "m");
		if (index != -1) {
			//mCommand[i].agi = agi;
			mCommand[i].agi = monsterVector[mCommand[i].index].cardVector[index].agi;
		}
		else {
			cout << "sortCommandByAgi error\n";
		}
		res.push_back(mCommand[i]);
	}
	std::sort(res.begin(), res.end(), sortByAgi);
	return res;
}

//Intent:顯示所有角色與怪物的行動先後順序  *流程4-2
void GloomHaven::showRoleStep(vector<commandResult>sortCommand) {
	cout << "\n\n";
	for (int i = 0; i < sortCommand.size(); i++) {
		if (sortCommand[i].type == "c") {
			if (sortCommand[i].agi == 99) {
				cout << sortCommand[i].icon << " " << sortCommand[i].agi << " -1";
			}
			else {
				cout << sortCommand[i].icon << " " << sortCommand[i].agi << " " << sortCommand[i].card1 << " " << sortCommand[i].card2;
			}
		}
		else if(sortCommand[i].type == "m"){
			int cardindex = findCardIndexFromCode(sortCommand[i].card1, sortCommand[i].index, "m");

			cout << sortCommand[i].name << " " << sortCommand[i].agi << " ";
			// 印出怪物技能
			for (int j = 0; j < monsterVector[sortCommand[i].index].cardVector[cardindex].skillVector.size(); j++) {
				cout << monsterVector[sortCommand[i].index].cardVector[cardindex].skillVector[j] << " ";
			}
		}
		cout << endl;
	}
}

/*
//Intent: 角色長休  回復兩點血且該agi = 99，需從棄牌推捨棄一張並將剩餘卡牌加回手牌
void GloomHaven::commandBreak(int index) {
	if (playerVector[index].info.hp + 20 > playerVector[index].info.maxHp) {
		playerVector[index].info.hp = playerVector[index].info.maxHp;
	}
	else {
		playerVector[index].info.hp += 20;
	}

	commandCheck(index);
	cout << "選擇一張牌丟棄\n";
	int discardIndex;
	while (1) {
		cin >> discardIndex;
		bool invaild = true;   // check 丟棄卡編號存在
		for (int i = 0; i < playerVector[index].discardCardsVector.size(); i++) {
			if (discardIndex == playerVector[index].discardCardsVector[i].code) {
				playerVector[index].discardCardsVector.erase(playerVector[index].discardCardsVector.begin() + i);    // 丟棄該卡片
				invaild = false;
			}
		}
		if (invaild == false)
			break;
	}
	// 將剩餘卡牌加回手牌
	for (int i = 0; i < playerVector[index].discardCardsVector.size(); i++) {
		playerVector[index].handCardsVector.push_back(playerVector[index].discardCardsVector[i]);
	}
	playerVector[index].discardCardsVector.clear();
	
	/*sort(playerVector[index].handCardsVector.begin(), playerVector[index].handCardsVector.end(),
		[](const cSkill& a, const cSkill& b)
		{return a.code < b.code; });
	// 依照編號調整順序
	sort(playerVector[index].handCardsVector.begin(), playerVector[index].handCardsVector.end(), sortByCode);
}*/



//Intent: 角色打牌
void GloomHaven::commandPlay(int index, int card1, int card2) {
	int index1, index2;
	// 先找出index 之後比較方便
	for (int i = 0; i < playerVector[index].handCardsVector.size(); i++) {
		if (playerVector[index].handCardsVector[i].code == card1)
			index1 = i;
		if (playerVector[index].handCardsVector[i].code == card2)
			index2 = i;
	}
	// set agi
	//playerVector[index].info.tmpAgi = playerVector[index].handCardsVector[index1].agi;


}

//Intent: 選擇 出牌
commandResult::commandResult(int mindex, int mcard1, int mcard2, string type) {
	index = mindex;
	card1 = mcard1;
	card2 = mcard2;
	takeBreak = false;
	this->type = type;
};

//Intent: 選擇長休
commandResult::commandResult(int mindex, bool mtakebreak, string type) {
	index = mindex;
	card1 = -1;
	card2 = -1;
	takeBreak = mtakebreak;
	agi = 99;
	this->type = type;
};


//Intent: 怪物準備階段
vector<commandResult>GloomHaven::monsterInputCommand(MapData& map_obj) {
	vector<commandResult>monsterCommandVector;   // 用來儲存 monster輸入指令 包含角色 卡牌 長休
	for (int i = 0; i < monsterVector.size(); i++) {
		if (monsterVector[i].finalInfo.exist == false)			//如果已消失
			continue;
		int tmpIndex = monsterVector[i].finalInfo.index;
		int cardCode = monsterVector[i].cardVector[0].code;		//  統一使用怪物手牌的第一張
		commandResult tmpMonsterCommand(tmpIndex, cardCode, -1, "m");
		tmpMonsterCommand.name = map_obj.enemyData[tmpIndex].name;
		tmpMonsterCommand.icon = map_obj.enemyData[tmpIndex].icon;
		monsterCommandVector.push_back(tmpMonsterCommand);
	}
	return monsterCommandVector;
}



// Intent: 利用卡片編號尋找卡片在該role的handCardsVector的index
int GloomHaven::findCardIndexFromCode(int code, int roleIndex, string type) {
	if (type == "c") {
		for (int i = 0; i < playerVector[roleIndex].handCardsVector.size(); i++) {
			if (code == playerVector[roleIndex].handCardsVector[i].code)
				return i;
		}
	}
	else if (type == "m") {
		for (int i = 0; i < monsterVector[roleIndex].cardVector.size(); i++) {
			if (code == monsterVector[roleIndex].cardVector[i].code)
				return i;
		}
	}
	return -1;
}

/*
//Intent: 依照編號調整順序
bool sortByCode(const cSkill& a, const cSkill& b) {
	return a.code < b.code;
}*/

// Intent: 依照敏捷值調整順序
// Post:  1.角色=怪物 ，角色先 2. 角色= 角色，比較另一張 ，若還是相同 則由字母   3.怪物名子決定
bool sortByAgi(const commandResult& a, const commandResult& b) {
	if (a.agi != b.agi) {       //agi 不同
		return a.agi < b.agi;
	}
	//角色=怪物 ，角色先
	else if (a.type != b.type && a.agi == b.agi) {
		if (a.type == "c") {
			return a.agi <= b.agi;
		}
		else if (a.type == "m") {
			return b.agi <= a.agi;
		}
	}
	//角色 = 角色，比較另一張，若還是相同 則由字母
	else if (a.type == b.type && a.type == "c" && a.agi == b.agi) {
		if (a.agi2 != b.agi2) {
			return a.agi2 < b.agi2;
		}
		else {
			return a.index < b.index;
		}
	}
	//怪物  = 怪物 ，怪物名子決定
	else if (a.type == b.type && a.type == "m" && a.agi == b.agi) {
		int i = 0;
		while (i < a.name.size() && i < b.name.size()) {
			if (a.name[i] < b.name[i]) {
				return true;
			}
			else if (a.name[i] > b.name[i]) {
				return	 false;
			}
			i++;
		}

		if (a.name == b.name) {
			return a.icon < b.icon;
		}
		else if (a.name.length() < b.name.length()) {
			return true;
		}
		else {
			return false;
		}
	}
}