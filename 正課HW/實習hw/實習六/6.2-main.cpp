// Name: ±i¥Ã©Ó	B10706009
// Date: 2020.04.16
// Last Update: 2020.04.16
// Problem statement:  Student Info System
#include <iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

vector<vector<string>>stLib;
void add();
void edit();
void del();
void find();
void list();

int main() {
	string cmd;
	stLib.clear();
	while (cin >> cmd) {
		if (cmd == "Add") {
			add();
		}
		else if (cmd == "Edit") {
			edit();
		}
		else if (cmd == "Del") {
			del();
		}
		else if (cmd == "Find") {
			find();
		}
		else if (cmd == "List") {
			list();
		}
	}
	return 0;

}


void add(){
	string id; string name; string gender; string weight; string height;
	cin >> id >> name >> gender >> height>>weight ;
	for (int i = 0; i < stLib.size(); i++) {
		if (stLib[i][0] == id) {
			cout << "The student's ID is duplicate.\n";
			return;
		}
	}
	vector<string>tmp;
	tmp.push_back(id); tmp.push_back(name); tmp.push_back(gender); tmp.push_back(height); tmp.push_back(weight);
	stLib.push_back(tmp);

}

void edit(){
	string id; string type; string value;
	cin >> id >> type >> value;
	for (int i = 0; i < stLib.size(); i++) {
		if (stLib[i][0] == id) {
			if (type == "Name") {
				stLib[i][1] = value;
			}
			if (type == "Gender") {
				stLib[i][2] = value;
			}
			if (type == "Height") {
				stLib[i][3] = value;
			}
			if (type == "Weight") {
				stLib[i][4] = value;
			}
			return;
		}
	}
	cout << "Student Not Found.\n";
}
void del(){
	string id;
	cin >> id;
	vector<vector<string>>::iterator it;
	it = stLib.begin();
	for (int i = 0; i < stLib.size(); i++) {
		if (stLib[i][0] == id) {
			stLib.erase(it+i);
			return;
		}
	}
	cout << "Student Not Found.\n";
}
void find(){
	string id;
	cin >> id;
	vector<vector<string>>::iterator it;
	for (int i = 0; i < stLib.size(); i++) {
		if (stLib[i][0] == id) {
			for (int j = 0; j < stLib[i].size(); j++) {
				cout << stLib[i][j] << "\t";
			}
			cout << endl;
			return;
		}
	}
	cout << "Student Not Found.\n";
}
void list() {
	vector<int>id_int;
	vector<int>M_id;
	for (int i = 0; i < stLib.size(); i++) {
		string id_str = stLib[i][0];
		if (id_str[0] == 'M') {
			id_str.erase(id_str.begin());
			int id = stoi(id_str);
			M_id.push_back(id);
		}
		else if (id_str[0] == 'B') {
			id_str.erase(id_str.begin());
			int id = stoi(id_str);
			id_int.push_back(id);
		}
	}
	sort(id_int.begin(), id_int.end());
	sort(M_id.begin(), M_id.end());
	for (int i = 0; i < id_int.size(); i++) {
		int id = id_int[i];
		for (int j = 0; j < stLib.size(); j++) {
			string id_str = stLib[j][0];
			id_str.erase(id_str.begin());
			int idst = stoi(id_str);
			if (idst == id) {
				for (int k = 0; k < stLib[j].size(); k++) {
					cout << stLib[j][k] << "\t";
				}
			}
		}
		cout << endl;
	}

	for (int i = 0; i < M_id.size(); i++) {
		int id = M_id[i];
		for (int j = 0; j < stLib.size(); j++) {
			string id_str = stLib[j][0];
			id_str.erase(id_str.begin());
			int idst = stoi(id_str);
			if (idst == id) {
				for (int k = 0; k < stLib[j].size(); k++) {
					cout << stLib[j][k] << "\t";
				}
			}
		}
		cout << endl;
	}
	
}