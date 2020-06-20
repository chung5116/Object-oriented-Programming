#include"Gloomhaven.h"


//Intent : �x�splayer��J������ƶq
GloomHaven::GloomHaven(int characterNumber){
	
	this->numOfCharacter = characterNumber;
	this->surviveCharacter = this->numOfCharacter;
}

//Intent : �ǶicharacterData�A��player��J����W�P�ޯ�d�A�g�L�ˬd�S���D���x�s�bplayerVector
void GloomHaven::inputCharacterAndCard(CharacterData& characterData_obj) {
	cout << "��ܥX������(�W��)�P�ޯ�d(�Ʀr)�A�C��u��J�@�䨤��\n";
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

				// �o�̬O�n bulid ����obj �F�A�ھ�name ��card number�� �M�wproperties
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


//Intent: �C���y�{���D�nfunction�A��@�\��call others functions
void GloomHaven::startGame(CharacterData& characterData_obj, MonsterData& monsterData_obj, MapData& map_obj) {
	while (1) {			//  ����έ�fucntion�ˬd�C������

		map_obj.round_int++;
		//system("CLS");
		map_obj.printRound();
		map_obj.printMap();
		vector<commandResult>playerCommandVector = playerInputCommand(map_obj);
		vector<commandResult>monsterCommandVector = monsterInputCommand(map_obj);
		vector<commandResult>sortCommand = sortCommandByAgi(playerCommandVector, monsterCommandVector);
		showRoleStep(sortCommand);   
		Actions actions(&playerVector, &monsterVector);			// ��o���vector�Ƕi�h�A�]�����h�ɤ��ब��include

		actions.executiveSkills(sortCommand, characterData_obj, monsterData_obj, map_obj);
		if (endOfEveryTurn(map_obj)) {
			return;
		}
	}
}


//Intent: ���a�ǳƶ��q
//*** �o��S�� �P�@��}��X�P�⦸�����b
vector<commandResult>GloomHaven::playerInputCommand(MapData& map_obj) {
	vector<commandResult>playerCommandVector;   // �Ψ��x�s Player��J���O �]�t���� �d�P ����
	cin.ignore();
	for (int i = 0; i < numOfCharacter; i++) {
		if (playerVector[i].info.exist == false)			//�ˬd�O�_���`
			continue;
		//print the map
		if (!checkCharacterCanContinue(i, map_obj)) {
			continue;
		}
		string buffer;
		getline(cin, buffer);
		vector<string>command = splitString(buffer, ' ');
		int index = command[0][0] - 'A';      //��N���নint ��K�ާ@
		
		// �ˬd����O�_�s�b
		bool invalid = false;
		if (index<0 || index > numOfCharacter) {		//��J�D���⪺icon
			invalid = true;
		}
		else if (playerVector[index].info.exist == false) {		//��J������w���`
			invalid = true;
		}

		if (invalid == true) {
			i--;
			cout << "input again\n";
			continue;
		}
		//�ˬd�d���s���O�_�����T
		if (command.size() == 3) {			//���`�X�P
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
			//commandPlay(index, card1, card2);     //  ���`�X�P 
		}
		else if (command.size() == 2 && command[1] == "-1") {	//  ����
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
		else {        //�����O�H�W�B�J
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

//Intent:�ˬd����i���i�H����Υ��P�A�Y������h���`
//Post : return true if ����i�H�ʧ@ , return false if ���⦺�`
bool GloomHaven::checkCharacterCanContinue(int index, MapData& map_obj) {
	if (playerVector[index].handCardsVector.size() < 2
		&& playerVector[index].discardCardsVector.size() < 2) {
		cout << 'A' + index << " is killed!!\n";
		map_obj.characterData[index].exist = false;		//�q���a�Ϩ���o������w�g���`
		playerVector[index].info.exist = false;

		return false;
	}
	return true;
}



//Intent: �d��[index]���Ө��⪺ ��P�P��P
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



//Intent:�C�^�X�����p��
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



//Intent: �ˬd�O�_�������ⳣ���`
//Post: return true if all character dead, otherwise return false
bool GloomHaven::allCharacterDead() {
	for (int i = 0; i < playerVector.size(); i++) {
		if (playerVector[i].info.exist == true)
			return false;
	}
	return true;
}



//Intent:�ˬd�O�_�����Ǫ����H���`
//Post: return true if all monster dead, otherwise return false
bool GloomHaven::allMonsterDead() {
	for (int i = 0; i < monsterVector.size(); i++) {
		if (monsterVector[i].finalInfo.exist == true)
			return false;
	}
	return true;
}