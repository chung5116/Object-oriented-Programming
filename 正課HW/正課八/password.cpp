#include"Password.h"


string passWord;
void Authenticate::inputPassword() {
	while (1) {
		string tmp;
		int check = 0;
		cout << "Enter your password (at least 8 characters and at least one non-letter)\n";
		cin >> tmp;
		if (tmp.size() >= 8) {
			for (int i = 0; i < tmp.size(); i++) {
				if (tmp[i] < 'a' || tmp[i]>'z') {
					check = 1;
				}
			}
			if (check == 1) {
				passWord = tmp;
				break;
			}
		}
	}
}

string  Authenticate::getPassword() {
	return passWord;
}