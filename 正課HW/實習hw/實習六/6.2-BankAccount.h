// Name: ±i¥Ã©Ó	B10706009
// Date: 2020.04.16
// Last Update: 2020.04.16
// Problem statement:  Bank Account
class BankAccount {
private:
	static int total;
	int balance;
public:
	BankAccount();
	BankAccount(int input);
	void withdraw(int output);
	void save(int input);
	int getBalance();
	int static getAllMoneyInBank();
};