#include"CharacterData.h"

//Intent : Ū�������ɮסAeg.�W�١A��q�A�_�l��P�ƶq�A�i��P��T
//Pre: Ū���ɮ׭n�s�b�P�Ӹ�Ƨ�
CharacterData::CharacterData(string s) {
	// �}�lŪ���ɮ�
	fstream file;
	file.open(s, ios::in);
	string buffer;
	if (file.is_open()) {
		getline(file, buffer);			// M���}��
		this->numOfCharacter = stoi(buffer);
		for (int i = 0; i < numOfCharacter; i++) {
			getline(file, buffer);  // �W�� ��q �_�l��P�ƶq
			vector<string>info = stringToCharacterInfo(buffer);
			characterDictionary[info[0]] = i;     // record what character we have, and value is the index of that character
			getline(file, buffer); //�i��P�ƶq
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

//Intent : ��@�ƪ���T�character info�A��vector�x�s�A��K����ϥ�
//Pre: string ���ର""
//Post: return vecotr<string> �ѦU�����T�զ�
vector<string> CharacterData::stringToCharacterInfo(string s) {
	istringstream ss(s);
	string token;
	vector<string>res;
	while (getline(ss, token, ' ')) {
		res.push_back(token);
	}
	return res;
}


//Intent : ��@�ƪ���T�card info�A��� sSkill �x�s�A�@����@�d������T
//Pre: string ���ର""
void  CharacterData::stringToCardInfo(string s) {
	int charaIndex = characterVector.size() - 1;
	cSkill card;
	int spaceIndex = s.find(' ',2);
	string front = s.substr(0, spaceIndex);			// index agi
	string back = s.substr(spaceIndex + 1, s.size() - spaceIndex);  //all skill
	// process agi
	string sagi = front.substr(front.size() - 2, 2);
	front = front.substr(0, front.size() - 2);		//�d���s��
	card.code = stoi(front);		//
	card.agi = stoi(sagi);
	// process skill
	spaceIndex = back.find('-');
	string topSkill = back.substr(0, spaceIndex);
	string bottomSkill = back.substr(spaceIndex + 2, back.size() - spaceIndex);
	bottomSkill += " ";
	//top
	int current = 0;  int previos = -1;
	current = topSkill.find(' ', current);   //  ex : attack 4  �Ĥ@�ӪŮ�
	current = topSkill.find(' ', current + 1);	// attact 4�ĤG��Ů�
	while (current != topSkill.npos) {
		string tmp = topSkill.substr(previos+1, current - previos-1);
		//**�T�{�e���O���O�����A�p�G�O�����Atmp�S�Orange���ܡA��tmp�s�b�e�@��string �᭱
		int skillSize = card.topSkill.size();
		if (tmp.substr(0, 5) == "range" && skillSize > 0 && card.topSkill[skillSize - 1].substr(0, 6) == "attack") {
			card.topSkill[skillSize - 1] = card.topSkill[skillSize - 1] + " " + tmp;
		}
		else {
			card.topSkill.push_back(tmp);
		}
		previos = current;
		current = topSkill.find(' ', current+1);   //  ex : attack 4  �Ĥ@�ӪŮ�
		if (current < 0)break;
		current = topSkill.find(' ', current + 1);	// attact 4�ĤG��Ů�
	}
	//bottom
	current = 0;previos = -1;
	current = bottomSkill.find(' ', current);   //  ex : attack 4  �Ĥ@�ӪŮ�
	current = bottomSkill.find(' ', current + 1);	// attact 4�ĤG��Ů�
	while (current != bottomSkill.npos) {
		string tmp = bottomSkill.substr(previos+1, current - previos-1);
		//**�T�{�e���O���O�����A�p�G�O�����Atmp�S�Orange���ܡA��tmp�s�b�e�@��string �᭱
		int skillSize = card.topSkill.size();
		if (tmp.substr(0, 5) == "range" && skillSize > 0 && card.topSkill[skillSize - 1].substr(0, 6) == "attack") {
			card.topSkill[skillSize - 1] = card.topSkill[skillSize - 1] + " " + tmp;
		}
		else {
			card.bottomSkill.push_back(tmp);
		}
		previos = current;
		current = bottomSkill.find(' ', current+1);   //  ex : attack 4  �Ĥ@�ӪŮ�
		if (current < 0)break;
		current = bottomSkill.find(' ', current + 1);	// attact 4�ĤG��Ů�
	}
	this->characterVector[charaIndex].cardVector.push_back(card);  //push new card
}

//Intent : �������wcharacter info
//Pre: index�n< character number
characterInfoS CharacterData::getCharacterInfo(int index) {
	if (index < characterVector.size()) {
		return characterVector[index].info;
	}
	else {
		cout << "error occur\n";
	}
}

//Intent : �������wcharacter 
//Pre: index�n< character number
SingleCharacter CharacterData::getCharacter(int index) {
	if (index < characterVector.size()) {
	return characterVector[index];
	}
	else {
		cout << "error occur\n";
	}
}
