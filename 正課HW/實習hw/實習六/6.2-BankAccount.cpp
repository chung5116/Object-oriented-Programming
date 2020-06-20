// Name: ±i¥Ã©Ó	B10706009
// Date: 2020.04.16
// Last Update: 2020.04.16
// Problem statement:  Bank Account
#include"BankAccount.h"

int BankAccount::total = 0;
BankAccount::BankAccount() {
	this->balance = 0;
}
BankAccount::BankAccount(int input) {
	this->balance = 0;
	this->balance += input;
	total += input;
}
void BankAccount::withdraw(int output) {
	this->balance -= output;
	total -= output;
}
void BankAccount::save(int input) {
	this->balance += input;
	total += input;
}
int BankAccount::getBalance() {
	return this->balance;
}
int BankAccount::getAllMoneyInBank() {
	return total;
}