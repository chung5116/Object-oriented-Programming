#include"MonsterData.h"	

//Intent : Ū���Ǫ��ɮסAeg.�W�١A(��q�A�����O�A�d��)���q/�׭^�A�H�αi�Ǫ��d������T
//Pre: Ū���ɮ׭n�s�b�P�Ӹ�Ƨ�
MonsterData::MonsterData(string s) {
	// �}�lŪ���ɮ�
	fstream file;
	file.open(s, ios::in);
	string buffer;
	if (file.is_open()) {
		getline(file, buffer);			// M���Ǫ�
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


//Intent : ��@�ƪ���T�monster info�A��vector�x�s�A��K����ϥ�
//Pre: string ���ର""
//Post: return vecotr<string> �ѦU�Ǫ���T�զ�
vector<string> MonsterData::stringToMonsterInfo(string s) {
	vector<string>res;
	istringstream ss(s);
	string token;
	while (getline(ss, token, ' ')) {
		res.push_back(token);
	}
	return res;
}

//Intent : ��@�ƪ���T�card info�A��� mSkill �x�s�A�@����@�d������T
//Pre: string ���ର""
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
	s2 = s2.substr(0, s2.size() - 2);			//�d���s��
	card.code = stoi(s2);			//�d���s��
	card.agi = stoi(sagi);
	//process skill
	if (s[s.size() - 1] == 'r')card.reShuffle = 1;
	
	
	int current = 0;  int previos = -1;
	current = s.find(' ', current);   //  ex : attack 4  �Ĥ@�ӪŮ�
	current = s.find(' ', current + 1);	// attact 4�ĤG��Ů�
	while (current != s.npos) {
		string tmp = s.substr(previos + 1, current - previos - 1);
		//**�T�{�e���O���O�����A�p�G�O�����Atmp�S�Orange���ܡA��tmp�s�b�e�@��string �᭱
		int skillSize = card.skillVector.size();
		if (tmp.substr(0, 5) == "range" && skillSize > 0 && card.skillVector[skillSize - 1].substr(0, 6) == "attack") {
			card.skillVector[skillSize - 1] = card.skillVector[skillSize - 1] + " " + tmp;
		}
		else {
			card.skillVector.push_back(tmp);
		}
		previos = current;
		current = s.find(' ', current + 1);   //  ex : attack 4  �Ĥ@�ӪŮ�
		if (current < 0)break;
		current = s.find(' ', current + 1);	// attact 4�ĤG��Ů�
	}
	this->monsterVector[monsterIndex].cardVector.push_back(card);
}


//Intent : �Ƕi�өǪ���index�P���M��d�����s��
//Post: mindex�����n�O<�Ǫ��ƶq�AcardCode�����s�b
//Pre: return �ӥd���b"cardVector"��index, return -1 if the card didn't exist
int MonsterData::getTheMonsterCardIndex(int mIndex, int cardCode) {

	int size;
	try{ 
		size = monsterVector[mIndex].cardVector.size();			//��mindex���bvector��
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