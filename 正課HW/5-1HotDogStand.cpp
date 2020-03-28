// Name: ±i¥Ã©Ó	
// Date: 2020.03.26
// Last Update: 2020.03.27
// Problem statement: Hot dog stand
#include "HotDogStand.h"
#include<iostream>

int HotDogStand::totalSellAmount = 0;
HotDogStand::HotDogStand(){
}

HotDogStand::HotDogStand(string id){
	standId = id;
	hotDogSellAmount = 0;
}

HotDogStand::HotDogStand(string id, int amount){
	standId = id;
	hotDogSellAmount = amount;
	totalSellAmount += amount;
}


void HotDogStand::justSold(){
	hotDogSellAmount++;
	totalSellAmount++;

}

void HotDogStand::print(){
	std::cout << standId << " " << hotDogSellAmount <<std::endl;
}

int HotDogStand::thisStandSoldAmount(){
	return hotDogSellAmount;
}

int HotDogStand::allStandSoldAmount(){
	return totalSellAmount;
}
