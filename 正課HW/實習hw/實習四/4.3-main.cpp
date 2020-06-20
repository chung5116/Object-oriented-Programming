// Name: ±i¥Ã©Ó	B10706009
// Date: 2020.04.02
// Last Update: 2020.04.02
// Problem statement:  Student Records
#include <iostream>
#include<vector>
using namespace std;



typedef struct {
	string firstName;
	string lastName;
	string phone;
}StRec;

void print(vector< StRec>& arrSt);
void insert(vector< StRec>& arrSt, string firstName, string lastName, string  phone);
void search(vector< StRec>& arrSt, string firstName, string lastName, string  phone);
void deleteSt(vector< StRec>& arrSt, string firstName, string lastName, string  phone);

int main() {
	string command;
	vector< StRec>arrSt;
	while (cin >> command) {
		if (command == "insert") {
			string firstName;
			string lastName;
			string phone;
			cin >> firstName >> lastName >> phone;
			insert(arrSt, firstName, lastName, phone);
		}

		else if (command == "print") {
			if (arrSt.size() == 0) {
				cout << "Print Error" << endl;
			}
			else {
				print(arrSt);
			}
			//cout << command <<endl;
		}

		else if (command == "delete") {
			
				string firstName;
				string lastName;
				string phone;
				cin >> firstName >> lastName >> phone;
				deleteSt(arrSt, firstName, lastName, phone);
		}

		else if (command == "search") {
			string firstName;
			string lastName;
			string phone;
			cin >> firstName >> lastName >> phone;
			search(arrSt, firstName, lastName, phone);
		}
		else {
			cout << "Input Error" << endl;
		}
	}

	return 0;
}



void print(vector< StRec>& arrSt) {
	for (auto& s : arrSt) {
		cout << s.firstName << " " << s.lastName << " " << s.phone << endl;
	}
}

void insert(vector< StRec>& arrSt, string firstName, string lastName, string  phone) {
	if (firstName.length() > 25 || lastName.length() > 30 || phone.length() > 15) {
		cout << "Input Error" << endl;
		return;
	}
	for (int i = 0; i < phone.length(); i++) {
		if (phone[i] > '9' || phone[i] < '0') {
			cout << "Input Error" << endl;
			return;
		}
	}
	if (arrSt.size() == 10) {
		cout << "Insert Error" << endl;
		return;
	}
	for (auto& s : arrSt) {
		if (s.firstName == firstName 
			&& s.lastName == lastName
			&&s.phone == phone) {
			cout << "Insert Error" << endl;
			return;
		}
	}
	StRec s;
	s.firstName = firstName;
	s.lastName = lastName;
	s.phone = phone;
	arrSt.push_back(s);

}

void search(vector< StRec>& arrSt, string firstName, string lastName, string  phone) {
	if (firstName.length() > 25 || lastName.length() > 30 || phone.length() > 15) {
		cout << "Input Error" << endl;
		return;
	}
	for (int i = 0; i < phone.length(); i++) {
		if (phone[i] > '9' || phone[i] < '0') {
			cout << "Input Error" << endl;
			return;
		}
	}
	for (int i = 0; i < arrSt.size(); i++) {
		if (arrSt[i].firstName == firstName
			&& arrSt[i].lastName == lastName
			&& arrSt[i].phone == phone) {
			cout << i << endl;
			return;
		}
	}
	cout << "Search Error" << endl;
}
void deleteSt(vector< StRec>& arrSt, string firstName, string lastName, string  phone) {
	if (firstName.length() > 25 || lastName.length() > 30 || phone.length() > 15) {
		cout << "Input Error" << endl;
		return;
	}
	for (int i = 0; i < phone.length(); i++) {
		if (phone[i] > '9' || phone[i] < '0') {
			cout << "Input Error" << endl;
			return;
		}
	}
	vector< StRec>::iterator it;
	for (it = arrSt.begin(); it != arrSt.end(); it++) {
		if ((*it).firstName == firstName
			&& (*it).lastName == lastName
			&& (*it).phone == phone) {
			arrSt.erase(it);
			return;
		}
	}
	cout << "Delete Error" << endl;
}