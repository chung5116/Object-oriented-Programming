#include"User.h"

string userName;

void Authenticate::inputUserName() {
	while (1) {
		int check = 0;
		string tmp;
		cout << "Enter your username (8 letters only)\n";
		cin >> tmp;
		if (tmp.size() == 8) {
			for (int i = 0; i < tmp.size(); i++) {
				if (tmp[i] < 'a' || tmp[i]>'z') {
					check = 1;
				}
			}
			if (check == 0) {
				userName = tmp;
				break;
			}
		}
	}
}

string Authenticate::getUserName() {
	return userName;
}