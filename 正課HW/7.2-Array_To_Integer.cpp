 Name: Yung-Cheng Chang
 Date: 2020.04.09
 Last Update: 2020.03.27
 Problem statement:Array to integer
#include"Atoi.h"

int Atoi::Length() { 
	if (beTrans[0] == '-') {
		return this->beTrans.length() - 1;
	}
	else
		return this->beTrans.length();
}

bool Atoi::IsDigital() {

	for (int i = 0; i < this->beTrans.length(); i++) {
		if (beTrans[i]>='9'&& beTrans[i]<='0' && (beTrans[i] != '+') && (beTrans[i] != '-'))
			return false;
	}
	return true;
}

int Atoi::StringToInteger() {
	string tmps = this->beTrans;
	if (tmps[0] == '-') {
		tmps.erase(tmps.begin());
	}
	int mul = 0;
	int res = 0;
	for (int i = tmps.length()-1; i>=0; i--) {
		res += (tmps[i] - '0') * (int)pow(10, mul);
		mul++;
	}
	if (beTrans[0] == '-')
		res *= -1;
	return res;
}