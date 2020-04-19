// Name: ±i¥Ã©Ó	
// Date: 2020.03.26
// Last Update: 2020.03.27
// Problem statement:Hot dog stand
#pragma once
#include<iostream>
#include<string>
using namespace std;


class HotDogStand
{
public:
	HotDogStand();
	HotDogStand(string id);
	HotDogStand(string id, int amount);
	void justSold();
	void print();
	int thisStandSoldAmount();
	static int allStandSoldAmount();

private:
	string standId;
	int hotDogSellAmount;
	static int totalSellAmount;
};

