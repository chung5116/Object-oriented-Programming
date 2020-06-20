#include"Monster.h"

//Intent : ��info�̪�string�x�s�U��
SingleMonster::SingleMonster(vector<string>info) {
	this->info.name = info[0];
	this->info.normalHp = stoi(info[1]);
	this->info.normalDmg = stoi(info[2]);
	this->info.normalRange = stoi(info[3]);
	this->info.eliteHp = stoi(info[4]);
	this->info.eliteDmg = stoi(info[5]);
	this->info.eliteRange = stoi(info[6]);
}


//Intent :����C�^�X������
void SingleMonster::resetQuality() {
	this->finalInfo.eachTurnQuality.attack = this->finalInfo.dmg;
	this->finalInfo.eachTurnQuality.heal = 0;
	this->finalInfo.eachTurnQuality.shield = 0;
	
}