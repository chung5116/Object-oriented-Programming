#include"Character.h"


//Intent : 把info以及全部卡片總數儲存下來，
SingleCharacter::SingleCharacter(vector<string>info, int totalCard) {
	this->info.name = info[0];
	this->info.hp = stoi(info[1]);
	this->info.maxHp = this->info.hp;
	this->info.numOfHandCard = stoi(info[2]);
	this->info.totalCard = totalCard;
}


//Intent : 用來建立player選擇的腳色，傳進角色模版&player選擇的卡片index
//把選擇的卡片儲存在handCardsVector
SingleCharacter::SingleCharacter(SingleCharacter sC, vector<string>cardsIndex) {
	this->info = sC.info;
	for (int i = 1; i < cardsIndex.size(); i++) {				// put the choosen cards into "handCards" vector
		int index = stoi(cardsIndex[i]);
		this->handCardsVector.push_back(sC.cardVector[index]);
	}
}


//Intent :重整每回合的素質
void SingleCharacter::resetQuality() {
	this->info.eachTurnQuality.attack = 0;
	this->info.eachTurnQuality.heal = 0;
	this->info.eachTurnQuality.shield = 0;
}