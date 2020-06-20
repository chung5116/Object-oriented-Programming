// Name: ±i¥Ã©Ó	B10706009
// Date: 2020.04.16
// Last Update: 2020.04.16
// Problem statement:  Student Identify System
#include <iostream>
#include<string>
#include<vector>
using namespace std;

vector<vector<string>>stList;
void check(string id, string symptom, string history) {
	vector<string>tmp;
	tmp.push_back(id); tmp.push_back(symptom); tmp.push_back(history);
	if (symptom == "Fever" || symptom == "Dry cough" || symptom == "Fatigue" ||
		symptom == "Shortness of breath" || symptom == "Chills" || symptom == "Dry cough") {
		cout << id << "\t" << "Access" << "\t" << "denied.\n";
		tmp.push_back("Denied");
		stList.push_back(tmp);
		return;
	}
	if (history == "China" || history == "USA" || history == "Italy" || history == "Spain" || history == "Germany"
		|| history == "Iran" || history == "France" || history == "UK" || history == "Switzerland") {
		cout << id << "\t" << "Access" << "\t" << "denied.\n";
		tmp.push_back("Denied");
		stList.push_back(tmp);
		return;
	}
	cout << id << "\t" << "Access" << "\t" << "allowed.\n";
	tmp.push_back("Allowed");
	stList.push_back(tmp);
}

int main() {
	string access;
	string id;
	string symptom;
	string history;
	while (cin >> access) {
		if (access == "List") {
			for (int i = 0; i < stList.size(); i++) {
				for (int j = 0; j < stList[i].size(); j++) {
					cout << stList[i][j] << "\t";
				}
				cout << endl;
			}
		}
		else {
			cin >> id;
			getline(cin, symptom,' ');
			getline(cin, symptom);
			int spaceindex = 0;
			for (int i = symptom.length() - 1; i >= 0; i--) {
				if (symptom[i] == ' ') {
					spaceindex = i;
					break;
				}
			}
			history = symptom.substr(spaceindex+1, symptom.length() - spaceindex);
			symptom = symptom.substr(0, spaceindex);
			check(id, symptom, history);
		}
	}
    return 0;
}