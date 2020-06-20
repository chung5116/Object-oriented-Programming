#include"Gloomhaven.h"


//Intent : 儲存player輸入的角色數量
GloomHaven::GloomHaven(int characterNumber){
	
	this->numOfCharacter = characterNumber;
	this->surviveCharacter = this->numOfCharacter;
}

//Intent : 傳進characterData，請player輸入角色名與技能卡，經過檢查沒問題後儲存在playerVector
void GloomHaven::inputCharacterAndCard(CharacterData& characterData_obj) {
	cout << "選擇出場角色(名稱)與技能卡(數字)，每行只輸入一支角色\n";
	int i = 0;
	cin.ignore();   /* ------for debug---------*/
	//string forDug[3] = { "brute 0 1 2 3 4 5",   /* ------for debug---------*/
	//			"brute 0 1 2 3 4 5",
	//			"brute 0 1 2 3 4 5"
	//};
	for (int i = 0; i < numOfCharacter; i++) {
		bool invalidInput = false;
		string buffer;
		getline(cin, buffer);
		//buffer = forDug[i];        /* ------for debug---------*/
		vector<string>player = splitString(buffer, ' ');

		// check is it a invalid input    eg.character didn't exist , number of card is wrong
		if (characterData_obj.characterDictionary.find(player[0]) != characterData_obj.characterDictionary.end()) {
			int chIndex = characterData_obj.characterDictionary[player[0]];
			characterInfoS infotmp = characterData_obj.getCharacterInfo(chIndex);
			if (player.size() == infotmp.numOfHandCard + 1) {

				// 這裡是要 bulid 角色obj 了，根據name 跟card number來 決定properties
				SingleCharacter sCtmp(characterData_obj.getCharacter(chIndex),player);
				playerVector.push_back(sCtmp);
			}
			else {
				invalidInput = true;
			}
		}
		else {
			invalidInput = true;
		}
		if (invalidInput == true) {
			cout << "Invalid input, please input again\n";
			i--;
		}
	}
}


//Intent: 遊戲流程的主要function，實作功能call others functions
void GloomHaven::startGame(CharacterData& characterData_obj, MonsterData& monsterData_obj, MapData& map_obj) {
	while (1) {			//  之後用個fucntion檢查遊戲結束

		map_obj.round_int++;
		//system("CLS");
		map_obj.printRound();
		map_obj.printMap();
		vector<commandResult>playerCommandVector = playerInputCommand(map_obj);
		vector<commandResult>monsterCommandVector = monsterInputCommand(map_obj);
		vector<commandResult>sortCommand = sortCommandByAgi(playerCommandVector, monsterCommandVector);
		showRoleStep(sortCommand);   
		Actions actions(&playerVector, &monsterVector);			// 把這兩個vector傳進去，因為兩個h檔不能互相include

		actions.executiveSkills(sortCommand, characterData_obj, monsterData_obj, map_obj);
		if (endOfEveryTurn(map_obj)) {
			return;
		}
	}
}


//Intent: 玩家準備階段
//*** 這邊沒做 同一支腳色出牌兩次的防呆
vector<commandResult>GloomHaven::playerInputCommand(MapData& map_obj) {
	vector<commandResult>playerCommandVector;   // 用來儲存 Player輸入指令 包含角色 卡牌 長休
	cin.ignore();
	for (int i = 0; i < numOfCharacter; i++) {
		if (playerVector[i].info.exist == false)			//檢查是否死亡
			continue;
		//print the map
		if (!checkCharacterCanContinue(i, map_obj)) {
			continue;
		}
		string buffer;
		getline(cin, buffer);
		vector<string>command = splitString(buffer, ' ');
		int index = command[0][0] - 'A';      //把代號轉成int 方便操作
		
		// 檢查角色是否存在
		bool invalid = false;
		if (index<0 || index > numOfCharacter) {		//輸入非角色的icon
			invalid = true;
		}
		else if (playerVector[index].info.exist == false) {		//輸入的角色已死亡
			invalid = true;
		}

		if (invalid == true) {
			i--;
			cout << "input again\n";
			continue;
		}
		//檢查卡片編號是否都正確
		if (command.size() == 3) {			//正常出牌
			int card1 = stoi(command[1]);
			int card2 = stoi(command[2]);
			bool cardExist = false;
			for (int i = 0; i < playerVector[index].handCardsVector.size(); i++) { //check card1
				if (card1 == playerVector[index].handCardsVector[i].code)
					cardExist = true;
			}
			if (cardExist == false) {
				invalid = true;
			}
			else {
				cardExist = false;
				for (int i = 0; i < playerVector[index].handCardsVector.size(); i++) {			//check card2
					if (card2 == playerVector[index].handCardsVector[i].code)
						cardExist = true;
				}
				if (cardExist == false) {
					invalid = true;
				}
			}
			if (invalid == true) {
				i--;
				cout << "input again\n";
				continue;
			}
			commandResult tmpPlayCommand(index, card1, card2,"c");
			tmpPlayCommand.name = playerVector[index].info.name;
			tmpPlayCommand.icon = map_obj.characterData[index].icon;
			playerCommandVector.push_back(tmpPlayCommand);
			//commandPlay(index, card1, card2);     //  正常出牌 
		}
		else if (command.size() == 2 && command[1] == "-1") {	//  長休
			//playerVector[index].info.tmpAgi = 99;
			commandResult tmpPlayCommand(index,true, "c");
			tmpPlayCommand.name = playerVector[index].info.name;
			tmpPlayCommand.icon = map_obj.characterData[index].icon;
			playerCommandVector.push_back(tmpPlayCommand);
			//commandBreck(index);	
		}
		else if (command.size() == 2 && command[1] == "check") {     //check 
			commandCheck(index);
			i--;
		}
		else {        //都不是以上步驟
			invalid = true;
		}
		if (invalid == true) {
			i--;
			cout << "input again\n";
			continue;
		}
	}
	return playerCommandVector;
}

//Intent:檢查角色可不可以長休或打牌，若都不行則死亡
//Post : return true if 角色可以動作 , return false if 角色死亡
bool GloomHaven::checkCharacterCanContinue(int index, MapData& map_obj) {
	if (playerVector[index].handCardsVector.size() < 2
		&& playerVector[index].discardCardsVector.size() < 2) {
		cout << 'A' + index << " is killed!!\n";
		map_obj.characterData[index].exist = false;		//通知地圖那邊這隻角色已經死亡
		playerVector[index].info.exist = false;

		return false;
	}
	return true;
}



//Intent: 查看[index]之該角色的 手牌與棄牌
void GloomHaven::commandCheck(int index) {
	cout << "hand: ";
	for (int i = 0; i < playerVector[index].handCardsVector.size(); i++) {
		cout << " " << playerVector[index].handCardsVector[i].code << ",";
	}
	cout << " ; discard: ";
	for (int i = 0; i < playerVector[index].discardCardsVector.size(); i++) {
		cout << " " << playerVector[index].discardCardsVector[i].code << ",";
	}
	cout << endl;
}



//Intent:每回合結束計算
bool  GloomHaven::endOfEveryTurn(MapData& map_obj) {
	if (allCharacterDead() ) {		//monster win!!
		cout << "monster win~\n";
		system("pause");
		return true;
	}
	else if (allMonsterDead() && map_obj.doorNum == 0) {		//character win!
		cout << "character win~\n";
		system("pause");
		return true;
	}
	return false;
}



//Intent: 檢查是否全部角色都死亡
//Post: return true if all character dead, otherwise return false
bool GloomHaven::allCharacterDead() {
	for (int i = 0; i < playerVector.size(); i++) {
		if (playerVector[i].info.exist == true)
			return false;
	}
	return true;
}



//Intent:檢查是否全部怪物都以死亡
//Post: return true if all monster dead, otherwise return false
bool GloomHaven::allMonsterDead() {
	for (int i = 0; i < monsterVector.size(); i++) {
		if (monsterVector[i].finalInfo.exist == true)
			return false;
	}
	return true;
}