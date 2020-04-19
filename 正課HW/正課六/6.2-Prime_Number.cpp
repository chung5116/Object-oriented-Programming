// Name: ±i¥Ã©Ó	
// Date: 2020.04.01
// Last Update:2020.04.01
// Problem statement:  Class Design
#include"6.2-Prime_Number.h"

int PrimeNumber::get() {
	return this->value;
}

PrimeNumber::PrimeNumber() {
	value = 1;
}

PrimeNumber::PrimeNumber(int _value) {
	value = _value;
}


PrimeNumber& PrimeNumber::operator++() {     //++p1;
	this->value = larger(this->value);
	return (*this);
}

PrimeNumber PrimeNumber::operator++(int) {			//p2++;
	PrimeNumber p(value);
	this->value = larger(this->value);
	return p;
}

PrimeNumber& PrimeNumber::operator--() {
	if (this->value == 2) {
		this->value = 1;
	}
	else {
		this->value = smaller(this->value);
	}
	return (*this);
}

PrimeNumber PrimeNumber::operator--(int) {
	PrimeNumber p = (value);
	if (value == 2) {
		value = 1;
	}
	else {
		value = smaller(value);
	}

	return p;
}

int PrimeNumber::larger(int value) {
	if (value + 1 == 2)
		return ++value;
	while (1) {
		++value;
		int des = value / 2;
		bool prime = true;
		for (int i = 2; i <= des; i++) {
			if (value % i == 0) {
				prime = false;
				break;
			}
		}
		if (prime)
			return value;
	}
}
int PrimeNumber::smaller(int value) {
	if (value - 1 == 2)
		return --value;
	while (1) {
		--value;
		int des = value / 2;
		bool prime = true;
		for (int i = 2; i <= des; i++) {
			if (value % i == 0) {
				prime = false;
				break;
			}
		}
		if (prime)
			return value;
	}
}