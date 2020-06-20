#include"MonsterData.h"	

//Intent : 讀取怪物檔案，eg.名稱，(血量，攻擊力，範圍)普通/菁英，以及張怪物卡片的資訊
//Pre: 讀取檔案要存在同個資料夾
MonsterData::MonsterData(string s) {
	// 開始讀取檔案
	fstream file;
	file.open(s, ios::in);
	string buffer;
	if (file.is_open()) {
		getline(file, buffer);			// M隻怪物
		this->numOfMonster = stoi(buffer);

		for (int i = 0; i < numOfMonster; i++) {
			getline(file, buffer);
			vector<string>info = stringToMonsterInfo(buffer);
			SingleMonster sMon(info);
			monsterVector.push_back(sMon);
			for (int j = 0; j < 6; j++) {
				getline(file, buffer);
				stringToCardInfo(buffer);
			}
		}
	}
	else {
		cout << "can't open file\n";
		exit(1);
	}
}


//Intent : 把一排的資訊拆成monster info，用vector儲存，方便後續使用
//Pre: string 不能為""
//Post: return vecotr<string> 由各怪物資訊組成
vector<string> MonsterData::stringToMonsterInfo(string s) {
	vector<string>res;
	istringstream ss(s);
	string token;
	while (getline(ss, token, ' ')) {
		res.push_back(token);
	}
	return res;
}

//Intent : 把一排的資訊拆成card info，後用 mSkill 儲存，作為單一卡片的資訊
//Pre: string 不能為""
void MonsterData::stringToCardInfo(string s) {
	int monsterIndex = monsterVector.size() - 1;
	int nameLength = monsterVector[monsterIndex].info.name.size();
	mSkill card;
	//delete name
	s = s.substr(nameLength + 1, s.size() - nameLength - 1);
	//split index, agi  &  card information
	int spaceIndex = s.find(' ', 2);
	string s2 = s.substr(0, spaceIndex);
	s = s.substr(spaceIndex + 1, s.size() - spaceIndex);	
	//process agi
	string sagi = s2.substr(s2.size() - 2, 2);
	s2 = s2.substr(0, s2.size() - 2);			//卡片編號
	card.code = stoi(s2);			//卡片編號
	card.agi = stoi(sagi);
	//process skill
	if (s[s.size() - 1] == 'r')card.reShuffle = 1;
	
	
	int current = 0;  int previos = -1;
	current = s.find(' ', current);   //  ex : attack 4  第一個空格
	current = s.find(' ', current + 1);	// attact 4第二格空格
	while (current != s.npos) {
		string tmp = s.substr(previos + 1, current - previos - 1);
		//**確認前面是不是攻擊，如果是攻擊，tmp又是range的話，把tmp連在前一個string 後面
		int skillSize = card.skillVector.size();
		if (tmp.substr(0, 5) == "range" && skillSize > 0 && card.skillVector[skillSize - 1].substr(0, 6) == "attack") {
			card.skillVector[skillSize - 1] = card.skillVector[skillSize - 1] + " " + tmp;
		}
		else {
			card.skillVector.push_back(tmp);
		}
		previos = current;
		current = s.find(' ', current + 1);   //  ex : attack 4  第一個空格
		if (current < 0)break;
		current = s.find(' ', current + 1);	// attact 4第二格空格
	}
	this->monsterVector[monsterIndex].cardVector.push_back(card);
}


//Intent : 傳進該怪物的index與欲尋找卡片的編號
//Post: mindex必須要是<怪物數量，cardCode必須存在
//Pre: return 該卡片在"cardVector"的index, return -1 if the card didn't exist
int MonsterData::getTheMonsterCardIndex(int mIndex, int cardCode) {

	int size;
	try{ 
		size = monsterVector[mIndex].cardVector.size();			//怕mindex不在vector裡
	}
	catch(char const* error){
		cout << error << endl;    
	}

	for (int i = 0; i < size; i++) {
		if (cardCode == monsterVector[mIndex].cardVector[i].code)
			return i;
	}
	return -1;
}