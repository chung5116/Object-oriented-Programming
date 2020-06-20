#include"Gloomhaven.h"




//Intent:�⪱�a�A�Ǫ���ܪ��P �ھڱӱ��ȱƧ�
//Pre: �Y����true�N����set agi�F�A�]���e���w�g���]�w�F�A �Y�S����h�ھڥd�����s���h���������agi
//Post : return �ƧǦn���}��/�Ǫ�  �������ޯ�N�ϥγo�Ӷ���
vector<commandResult>GloomHaven::sortCommandByAgi(vector<commandResult>cCommand, vector<commandResult>mCommand) {
	vector<commandResult>res;
	for (int i = 0; i < cCommand.size(); i++) {  // �Ĥ@���d���@��agi
		if (cCommand[i].takeBreak == false) {		//�S������
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

//Intent:��ܩҦ�����P�Ǫ�����ʥ��ᶶ��  *�y�{4-2
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
			// �L�X�Ǫ��ޯ�
			for (int j = 0; j < monsterVector[sortCommand[i].index].cardVector[cardindex].skillVector.size(); j++) {
				cout << monsterVector[sortCommand[i].index].cardVector[cardindex].skillVector[j] << " ";
			}
		}
		cout << endl;
	}
}

/*
//Intent: �������  �^�_���I��B��agi = 99�A�ݱq��P���˱�@�i�ñN�Ѿl�d�P�[�^��P
void GloomHaven::commandBreak(int index) {
	if (playerVector[index].info.hp + 20 > playerVector[index].info.maxHp) {
		playerVector[index].info.hp = playerVector[index].info.maxHp;
	}
	else {
		playerVector[index].info.hp += 20;
	}

	commandCheck(index);
	cout << "��ܤ@�i�P���\n";
	int discardIndex;
	while (1) {
		cin >> discardIndex;
		bool invaild = true;   // check ���d�s���s�b
		for (int i = 0; i < playerVector[index].discardCardsVector.size(); i++) {
			if (discardIndex == playerVector[index].discardCardsVector[i].code) {
				playerVector[index].discardCardsVector.erase(playerVector[index].discardCardsVector.begin() + i);    // ���ӥd��
				invaild = false;
			}
		}
		if (invaild == false)
			break;
	}
	// �N�Ѿl�d�P�[�^��P
	for (int i = 0; i < playerVector[index].discardCardsVector.size(); i++) {
		playerVector[index].handCardsVector.push_back(playerVector[index].discardCardsVector[i]);
	}
	playerVector[index].discardCardsVector.clear();
	
	/*sort(playerVector[index].handCardsVector.begin(), playerVector[index].handCardsVector.end(),
		[](const cSkill& a, const cSkill& b)
		{return a.code < b.code; });
	// �̷ӽs���վ㶶��
	sort(playerVector[index].handCardsVector.begin(), playerVector[index].handCardsVector.end(), sortByCode);
}*/



//Intent: ���⥴�P
void GloomHaven::commandPlay(int index, int card1, int card2) {
	int index1, index2;
	// ����Xindex ��������K
	for (int i = 0; i < playerVector[index].handCardsVector.size(); i++) {
		if (playerVector[index].handCardsVector[i].code == card1)
			index1 = i;
		if (playerVector[index].handCardsVector[i].code == card2)
			index2 = i;
	}
	// set agi
	//playerVector[index].info.tmpAgi = playerVector[index].handCardsVector[index1].agi;


}

//Intent: ��� �X�P
commandResult::commandResult(int mindex, int mcard1, int mcard2, string type) {
	index = mindex;
	card1 = mcard1;
	card2 = mcard2;
	takeBreak = false;
	this->type = type;
};

//Intent: ��ܪ���
commandResult::commandResult(int mindex, bool mtakebreak, string type) {
	index = mindex;
	card1 = -1;
	card2 = -1;
	takeBreak = mtakebreak;
	agi = 99;
	this->type = type;
};


//Intent: �Ǫ��ǳƶ��q
vector<commandResult>GloomHaven::monsterInputCommand(MapData& map_obj) {
	vector<commandResult>monsterCommandVector;   // �Ψ��x�s monster��J���O �]�t���� �d�P ����
	for (int i = 0; i < monsterVector.size(); i++) {
		if (monsterVector[i].finalInfo.exist == false)			//�p�G�w����
			continue;
		int tmpIndex = monsterVector[i].finalInfo.index;
		int cardCode = monsterVector[i].cardVector[0].code;		//  �Τ@�ϥΩǪ���P���Ĥ@�i
		commandResult tmpMonsterCommand(tmpIndex, cardCode, -1, "m");
		tmpMonsterCommand.name = map_obj.enemyData[tmpIndex].name;
		tmpMonsterCommand.icon = map_obj.enemyData[tmpIndex].icon;
		monsterCommandVector.push_back(tmpMonsterCommand);
	}
	return monsterCommandVector;
}



// Intent: �Q�Υd���s���M��d���b��role��handCardsVector��index
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
//Intent: �̷ӽs���վ㶶��
bool sortByCode(const cSkill& a, const cSkill& b) {
	return a.code < b.code;
}*/

// Intent: �̷ӱӱ��Ƚվ㶶��
// Post:  1.����=�Ǫ� �A����� 2. ����= ����A����t�@�i �A�Y�٬O�ۦP �h�Ѧr��   3.�Ǫ��W�l�M�w
bool sortByAgi(const commandResult& a, const commandResult& b) {
	if (a.agi != b.agi) {       //agi ���P
		return a.agi < b.agi;
	}
	//����=�Ǫ� �A�����
	else if (a.type != b.type && a.agi == b.agi) {
		if (a.type == "c") {
			return a.agi <= b.agi;
		}
		else if (a.type == "m") {
			return b.agi <= a.agi;
		}
	}
	//���� = ����A����t�@�i�A�Y�٬O�ۦP �h�Ѧr��
	else if (a.type == b.type && a.type == "c" && a.agi == b.agi) {
		if (a.agi2 != b.agi2) {
			return a.agi2 < b.agi2;
		}
		else {
			return a.index < b.index;
		}
	}
	//�Ǫ�  = �Ǫ� �A�Ǫ��W�l�M�w
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