#include"Character.h"


//Intent : ��info�H�Υ����d���`���x�s�U�ӡA
SingleCharacter::SingleCharacter(vector<string>info, int totalCard) {
	this->info.name = info[0];
	this->info.hp = stoi(info[1]);
	this->info.maxHp = this->info.hp;
	this->info.numOfHandCard = stoi(info[2]);
	this->info.totalCard = totalCard;
}


//Intent : �Ψӫإ�player��ܪ��}��A�Ƕi����Ҫ�&player��ܪ��d��index
//���ܪ��d���x�s�bhandCardsVector
SingleCharacter::SingleCharacter(SingleCharacter sC, vector<string>cardsIndex) {
	this->info = sC.info;
	for (int i = 1; i < cardsIndex.size(); i++) {				// put the choosen cards into "handCards" vector
		int index = stoi(cardsIndex[i]);
		this->handCardsVector.push_back(sC.cardVector[index]);
	}
}


//Intent :����C�^�X������
void SingleCharacter::resetQuality() {
	this->info.eachTurnQuality.attack = 0;
	this->info.eachTurnQuality.heal = 0;
	this->info.eachTurnQuality.shield = 0;
}