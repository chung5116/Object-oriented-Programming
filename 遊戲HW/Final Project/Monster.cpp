#include"Monster.h"

//Intent : 把info裡的string儲存下來
SingleMonster::SingleMonster(vector<string>info) {
	this->info.name = info[0];
	this->info.normalHp = stoi(info[1]);
	this->info.normalDmg = stoi(info[2]);
	this->info.normalRange = stoi(info[3]);
	this->info.eliteHp = stoi(info[4]);
	this->info.eliteDmg = stoi(info[5]);
	this->info.eliteRange = stoi(info[6]);
}


//Intent :重整每回合的素質
void SingleMonster::resetQuality() {
	this->finalInfo.eachTurnQuality.attack = this->finalInfo.dmg;
	this->finalInfo.eachTurnQuality.heal = 0;
	this->finalInfo.eachTurnQuality.shield = 0;
	
}