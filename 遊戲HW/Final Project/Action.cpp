#include"Action.h"

//Intent: �̷ӽs���վ㶶��  for character�A���ӥi��g��template
bool sortByCode(const cSkill& a, const cSkill& b) {
	return a.code < b.code;
}

//Intent: �̷ӽs���վ㶶��	for monster
bool sortByCode2(const mSkill& a, const mSkill& b) {
	return a.code < b.code;
}


Actions::Actions(vector<SingleCharacter>* tmpplayerVector, vector<SingleMonster>* tmpmonsterVector){
	playerVector = tmpplayerVector;
	monsterVector = tmpmonsterVector;
}

//Intent: �̷Ӷ������ޯ� �y�{4-3
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


//Intent:����Ǫ��ޯ�
void Actions::monsterSkills(commandResult command, CharacterData& characterData_obj, MonsterData& monsterData_obj, MapData& map_obj, vector<commandResult>sortCommand) {
	int roleIndex = command.index;
	if ((*monsterVector)[roleIndex].finalInfo.exist == false) {			// ���ˬd�Ǫ��O�_�s�b
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
		if (monsterSkill.reShuffle == 1) {		//���~
			for (int i = 0; i < (*monsterVector)[roleIndex].discardCardsVector.size(); i++) {		//���P�ﭫ�s�[�i��P
				mSkill discardToHand = (*monsterVector)[roleIndex].discardCardsVector[i];
				(*monsterVector)[roleIndex].cardVector.push_back(discardToHand);
			}
			(*monsterVector)[roleIndex].discardCardsVector.clear();			//�M�ű�P��
		}
		else {
			int discardIndex = 0;		//�Y�N�n�Q��󪺤�ƪ�index
			while (1) {		//��XdiscardIndex
				if (command.card1 == (*monsterVector)[roleIndex].cardVector[discardIndex].code) {
					break;
				}
				discardIndex++;
			}
			//���i��ư�
			(*monsterVector)[roleIndex].discardCardsVector.push_back((*monsterVector)[roleIndex].cardVector[discardIndex]);
			//�ӱƻP��Ƴ̫�@�iswap��Apop back
			swap((*monsterVector)[roleIndex].cardVector[discardIndex], (*monsterVector)[roleIndex].cardVector[(*monsterVector)[roleIndex].cardVector.size() - 1]);
			(*monsterVector)[roleIndex].cardVector.pop_back();
			//��z��ư�&��ư�
			sort((*monsterVector)[roleIndex].cardVector.begin(), (*monsterVector)[roleIndex].cardVector.end(), sortByCode2);
			sort((*monsterVector)[roleIndex].discardCardsVector.begin(), (*monsterVector)[roleIndex].discardCardsVector.end(), sortByCode2);

		}
		sort((*monsterVector)[roleIndex].cardVector.begin(), (*monsterVector)[roleIndex].cardVector.end(), sortByCode2);
	}
	else {
		cout << "monsterSkill error occur\n";
	}
}


//Intent: �@�ҫ���ܥ��^�X����(��: ���@�ҭȬ��ޯ�ԭz�W���ƭ�, �D���^�X�w��o�@�Ҫ��`�ƭ�)
void Actions::monsterShield(commandResult command, vector<string>oneSkill) {
	int roleIndex = command.index;
	char icon = command.icon;
	int shieldValue = stoi(oneSkill[1]);
	(*monsterVector)[roleIndex].finalInfo.eachTurnQuality.shield += shieldValue;
	cout << icon << " shield " << shieldValue << " this turn\n";
	
}

//Intent: ��X�^�_�q�M�^�_���q�A��q���|�W�L�̤j��q ex: a heal 2, now hp is 10
void Actions::monsterHeal(commandResult command, vector<string>oneSkill) {
	int roleIndex = command.index;
	char icon = command.icon;
	int healValue = stoi(oneSkill[1]);
	// ���W�L�̤j��q
	if ((*monsterVector)[roleIndex].finalInfo.hp + healValue > (*monsterVector)[roleIndex].finalInfo.maxHp) {
		(*monsterVector)[roleIndex].finalInfo.hp = (*monsterVector)[roleIndex].finalInfo.maxHp;
	}
	else {
		(*monsterVector)[roleIndex].finalInfo.hp += healValue;
	}
	int nowHp = (*monsterVector)[roleIndex].finalInfo.hp;
	cout << icon << " heal " << healValue << ", now hp is " << nowHp << endl;
}

//Intent: �u��X�̲ײ��ʦ�m, ���ΨC�@�B����X�@���a��, �Y�ϲ��ʧ����b��a�]�n��s�a��
void Actions::monsterMove(commandResult command, vector<string>oneSkill, MapData& map_obj) {
	int roleIndex = command.index;
	string moves = oneSkill[1];    // eg. wwa , wdsd
	map_obj.roleMove("m", roleIndex, moves);
	map_obj.printMap();			//�L�X��s��a��
}



//Intent: �Ǫ��������� a lock A in distance 3�A�p�G�S�ؼ�"no one lock"
//a attack A 3 damage, A shield 1, A remain 12 hp
void Actions::monsterAttack(commandResult command, vector<string>oneSkill, MapData& map_obj, vector<commandResult>sortCommand) {
	//�P�_ �i�� OR ���{
	// ����Ǫ����y�ЩԥX�ӡA�b��U���⪺�y�ЩԥX�ӥ�����ԧ����ǳ�  �M��~�O�����A���{
	int dRange;	//�d���ܤƭ�
	int dAttack = stoi(oneSkill[1]);  //�����O�ܤƭ�
	int roleIndex = command.index;	   //monster �b  (*monsterVector)��index
	if (oneSkill.size() == 2) {		// attack 1
		dRange = 0;
	}
	else if (oneSkill.size() == 4) {		//attack 0 range 1
		dRange = stoi(oneSkill[3]);
	}
	int attackRange = (*monsterVector)[roleIndex].finalInfo.range + dRange;
	(*monsterVector)[roleIndex].finalInfo.eachTurnQuality.attack += dAttack;


	if (attackRange == 0) {		//��ԧ���
		closeAttack(command, oneSkill, map_obj, sortCommand);
	}
	else if (attackRange > 0) {		//���{
		rangedAttack(command, oneSkill, map_obj, attackRange, sortCommand);
	}
}


// Intent : �Ǫ���ԧ���
void Actions::closeAttack(commandResult command, vector<string>oneSkill, MapData& map_obj, vector<commandResult>sortCommand) {
	int charaMinIndex;       // �᭱�ϥε���������icon�ϥ�
	int roleIndex = command.index;
	Postion posM = map_obj.enemyData[roleIndex].pos;   //�Ǫ�pos
	vector<int>indexOfCharacterInRange;   // �ŦX�d�򪺨���index of "playerVector"�A�]���Y���h���ĤH�A�h���qagi�̤p��

	for (int i = 0; i < (*playerVector).size(); i++) {
		if ((*playerVector)[i].info.exist == false)		// �p�G����w���`�hcontinue
			continue;

		Postion posC = map_obj.characterData[i].pos;

		int totalRange = abs(posC.x - posM.x) + abs(posC.y - posM.y);
		if (totalRange == 1)
			indexOfCharacterInRange.push_back(i);
	}
	

	if (indexOfCharacterInRange.empty()) {		// �S������b��ԧ����d��
		cout << "no one lock\n";
	}
	else {
		int minAgi = 101;     // �b�ŦX�d�򪺨���� agi�̤p��index
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
		// minIndex �N�O�n�������ؼФF
		
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

		// �p�G����Q�����ᦺ�`
		if ((*playerVector)[minIndex].info.hp <= 0) {			
			(*playerVector)[minIndex].info.exist = false;
			cout << sortCommand[charaMinIndex].icon << " is killed !!\n";
			//�q��map���� ������w���`
			map_obj.characterData[minIndex].exist = false;
			map_obj.printMap();
		}
	}

}


//Intent : �Ǫ����{����
void Actions::rangedAttack(commandResult command, vector<string>oneSkill, MapData& map_obj, int attackRange, vector<commandResult>sortCommand) {
	int roleIndex = command.index;
	Postion posM = map_obj.enemyData[roleIndex].pos;   //�Ǫ�pos
	bool lock = false;

	// �]�n���Z���̪񪺡A�G�Z��1��b[1]�A�Z��2��b[2]
	vector<vector<int>>indexOfCharacterInRange(attackRange+1);   // �ŦX�d�򪺨���index of "playerVector"�A�]���Y���h���ĤH�A�h���qagi�̤p��
	for (int i = 0; i < (*playerVector).size(); i++) {
		if ((*playerVector)[i].info.exist == false)		// �p�G����w���`�hcontinue
			continue;

		Postion posC = map_obj.characterData[i].pos;

		int totalRange = abs(posC.x - posM.x) + abs(posC.y - posM.y);
		if (totalRange <= attackRange) {
			indexOfCharacterInRange[totalRange].push_back(i);		// push�brange�����}��b"playerVector"��index
			lock = true;
		}
	}
	if (lock == false) {			//�S����b�d��
		cout << "no one lock\n";
		return;
	}
	lock = false;   // �i��b�d�򤺪����S������

	//**�q�Z���񪺶}�l�P�_���S�������M��N��������
	for (int i = 1; i < indexOfCharacterInRange.size(); i++) {
		for (int j = 0; j < indexOfCharacterInRange[i].size();j++) {
			int pIndex = indexOfCharacterInRange[i][j];   //�brange�����}��b"playerVector"��index
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

				// �]���ݭn�ϥΨ���icon �ҥH�ϥδM��Ө���b"sortCommand"��index : k
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


				// �p�G����Q�����ᦺ�`
				if ((*playerVector)[pIndex].info.hp <= 0) {
					(*playerVector)[pIndex].info.exist = false;
					cout << sortCommand[charaMinIndex].icon << " is killed !!\n";
					//�q��map���� ������w���`
					map_obj.characterData[pIndex].exist = false;
					map_obj.printMap();
				}
				return;
			}
		}
	}

	if (lock == false) {			//�b�d�򪺨���̳��S������
		cout << "no one lock\n";
		return;
	}
}


//--------------------------------------------------------------------------------------


//Intent:����}��ޯ�
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

//Intent: �@�ҫ���ܥ��^�X����(��: ���@�ҭȬ��ޯ�ԭz�W���ƭ�, �D���^�X�w��o�@�Ҫ��`�ƭ�)
void Actions::characterShield(commandResult command, vector<string>oneSkill) {   //�}���@��
	int roleIndex = command.index;
	char icon = command.icon;
	int shieldValue = stoi(oneSkill[1]);
	(*playerVector)[roleIndex].info.eachTurnQuality.shield += shieldValue;
	cout << icon << " shield " << shieldValue << " this turn\n";
}

//Intent: ��X�^�_�q�M�^�_���q�A��q���|�W�L�̤j��q ex: A heal 2, now hp is 10
void Actions::characterHeal(commandResult command, vector<string>oneSkill) {  //�}��^�_hp
	int roleIndex = command.index;
	char icon = command.icon;
	int healValue = stoi(oneSkill[1]);
	// ���W�L�̤j��q
	if ((*playerVector)[roleIndex].info.hp + healValue > (*playerVector)[roleIndex].info.maxHp) {
		(*playerVector)[roleIndex].info.hp = (*playerVector)[roleIndex].info.maxHp;
	}
	else {
		(*playerVector)[roleIndex].info.hp += healValue;
	}
	int nowHp = (*playerVector)[roleIndex].info.hp;
	cout << icon << " heal " << healValue << ", now hp is " << nowHp << endl;
}

//Intent: ���Ⲿ��
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

//�٨S�g�������D
//Intent: �������
void Actions::characterAttack(commandResult command, vector<string>oneSkill, int range, MapData& map_obj) {
	while (1) {
		char target;
		int check = 0, attackNum, tempAttackNum;
		attackNum = stoi(oneSkill[1]);
		cout << "��J�n�������ؼ�(0:������):";
		cin >> target;
		if (target == '0') {	//������
			return;
		}
		for (int i = 0; i < (*monsterVector).size(); i++) {
			if (map_obj.enemyData[i].icon == target && map_obj.enemyData[i].exist == true) {
				if (abs(map_obj.enemyData[i].pos.x - map_obj.characterData[command.index].pos.x) + abs(map_obj.enemyData[i].pos.y - map_obj.characterData[command.index].pos.y) <= range) {
					tempAttackNum = attackNum - (*monsterVector)[i].finalInfo.eachTurnQuality.shield;  //�����O-�Ǫ����m�O
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

//Intent: �������  �^�_���I��B��agi = 99�A�ݱq��P���˱�@�i�ñN�Ѿl�d�P�[�^��P
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
		bool invaild = true;   // check ���d�s���s�b
		for (int i = 0; i < (*playerVector)[index].discardCardsVector.size(); i++) {
			if (discardIndex == (*playerVector)[index].discardCardsVector[i].code) {
				(*playerVector)[index].discardCardsVector.erase((*playerVector)[index].discardCardsVector.begin() + i);    // ���ӥd��
				invaild = false;
			}
		}
		if (invaild == false)
			break;
	}
	// �N�Ѿl�d�P�[�^��P
	for (int i = 0; i < (*playerVector)[index].discardCardsVector.size(); i++) {
		(*playerVector)[index].handCardsVector.push_back((*playerVector)[index].discardCardsVector[i]);
	}
	(*playerVector)[index].discardCardsVector.clear();

	/*sort(playerVector[index].handCardsVector.begin(), playerVector[index].handCardsVector.end(),
		[](const cSkill& a, const cSkill& b)
		{return a.code < b.code; });*/
		// �̷ӽs���վ㶶��
	sort((*playerVector)[index].handCardsVector.begin(), (*playerVector)[index].handCardsVector.end(), sortByCode);
	cout << map_obj.characterData[index].icon << " heal 2, now hp is " << (*playerVector)[index].info.hp << "\nremove card: " << discardIndex << "\n";
}
