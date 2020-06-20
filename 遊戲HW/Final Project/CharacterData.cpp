#include"CharacterData.h"

//Intent : 讀取角色檔案，eg.名稱，血量，起始手牌數量，可選牌資訊
//Pre: 讀取檔案要存在同個資料夾
CharacterData::CharacterData(string s) {
	// 開始讀取檔案
	fstream file;
	file.open(s, ios::in);
	string buffer;
	if (file.is_open()) {
		getline(file, buffer);			// M隻腳色
		this->numOfCharacter = stoi(buffer);
		for (int i = 0; i < numOfCharacter; i++) {
			getline(file, buffer);  // 名稱 血量 起始手牌數量
			vector<string>info = stringToCharacterInfo(buffer);
			characterDictionary[info[0]] = i;     // record what character we have, and value is the index of that character
			getline(file, buffer); //可選牌數量
			int maxCard = stoi(buffer);
			SingleCharacter sCh(info, maxCard);
			characterVector.push_back(sCh);

			for (int j = 0; j < maxCard; j++) {
				getline(file, buffer);   //skill info
				stringToCardInfo(buffer);
			}
		}

	}
	else {
		cout << "Can't open file\n";
		exit(1);
	}
}

//Intent : 把一排的資訊拆成character info，用vector儲存，方便後續使用
//Pre: string 不能為""
//Post: return vecotr<string> 由各角色資訊組成
vector<string> CharacterData::stringToCharacterInfo(string s) {
	istringstream ss(s);
	string token;
	vector<string>res;
	while (getline(ss, token, ' ')) {
		res.push_back(token);
	}
	return res;
}


//Intent : 把一排的資訊拆成card info，後用 sSkill 儲存，作為單一卡片的資訊
//Pre: string 不能為""
void  CharacterData::stringToCardInfo(string s) {
	int charaIndex = characterVector.size() - 1;
	cSkill card;
	int spaceIndex = s.find(' ',2);
	string front = s.substr(0, spaceIndex);			// index agi
	string back = s.substr(spaceIndex + 1, s.size() - spaceIndex);  //all skill
	// process agi
	string sagi = front.substr(front.size() - 2, 2);
	front = front.substr(0, front.size() - 2);		//卡片編號
	card.code = stoi(front);		//
	card.agi = stoi(sagi);
	// process skill
	spaceIndex = back.find('-');
	string topSkill = back.substr(0, spaceIndex);
	string bottomSkill = back.substr(spaceIndex + 2, back.size() - spaceIndex);
	bottomSkill += " ";
	//top
	int current = 0;  int previos = -1;
	current = topSkill.find(' ', current);   //  ex : attack 4  第一個空格
	current = topSkill.find(' ', current + 1);	// attact 4第二格空格
	while (current != topSkill.npos) {
		string tmp = topSkill.substr(previos+1, current - previos-1);
		//**確認前面是不是攻擊，如果是攻擊，tmp又是range的話，把tmp連在前一個string 後面
		int skillSize = card.topSkill.size();
		if (tmp.substr(0, 5) == "range" && skillSize > 0 && card.topSkill[skillSize - 1].substr(0, 6) == "attack") {
			card.topSkill[skillSize - 1] = card.topSkill[skillSize - 1] + " " + tmp;
		}
		else {
			card.topSkill.push_back(tmp);
		}
		previos = current;
		current = topSkill.find(' ', current+1);   //  ex : attack 4  第一個空格
		if (current < 0)break;
		current = topSkill.find(' ', current + 1);	// attact 4第二格空格
	}
	//bottom
	current = 0;previos = -1;
	current = bottomSkill.find(' ', current);   //  ex : attack 4  第一個空格
	current = bottomSkill.find(' ', current + 1);	// attact 4第二格空格
	while (current != bottomSkill.npos) {
		string tmp = bottomSkill.substr(previos+1, current - previos-1);
		//**確認前面是不是攻擊，如果是攻擊，tmp又是range的話，把tmp連在前一個string 後面
		int skillSize = card.topSkill.size();
		if (tmp.substr(0, 5) == "range" && skillSize > 0 && card.topSkill[skillSize - 1].substr(0, 6) == "attack") {
			card.topSkill[skillSize - 1] = card.topSkill[skillSize - 1] + " " + tmp;
		}
		else {
			card.bottomSkill.push_back(tmp);
		}
		previos = current;
		current = bottomSkill.find(' ', current+1);   //  ex : attack 4  第一個空格
		if (current < 0)break;
		current = bottomSkill.find(' ', current + 1);	// attact 4第二格空格
	}
	this->characterVector[charaIndex].cardVector.push_back(card);  //push new card
}

//Intent : 拿取指定character info
//Pre: index要< character number
characterInfoS CharacterData::getCharacterInfo(int index) {
	if (index < characterVector.size()) {
		return characterVector[index].info;
	}
	else {
		cout << "error occur\n";
	}
}

//Intent : 拿取指定character 
//Pre: index要< character number
SingleCharacter CharacterData::getCharacter(int index) {
	if (index < characterVector.size()) {
	return characterVector[index];
	}
	else {
		cout << "error occur\n";
	}
}
