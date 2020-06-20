#ifndef  NUMBERGAME_H
#define NUMBERGAME_H
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
using namespace std;


class NumberGame {
private:
	vector<int>base;
	string filename;
	vector<int>listNum;
	int input;
public:
	NumberGame() {};
	void SetInput(int);
	void ProcessInput();
	void SetFileName(string name) { this->filename = name; }
	void LoadNumberList();
	void PrintAllValid();
	void Reset();
};



void NumberGame::SetInput(int input) {
	this->input = input;
}
void NumberGame::ProcessInput() {
	cout << "success process\n";
	while (this->input > 0) {
		base.push_back(input % 10);
		input /= 10;
	}
}
void NumberGame::LoadNumberList(){
	cout << "success load\n";
	fstream file;
	file.open(filename, ios::in);
	if (file.is_open()) {
		string buffer;
		while (!file.eof()) {
			getline(file, buffer);
			if (buffer != "") {
				listNum.push_back(stoi(buffer));
			}
		}
	}
	else {
		cout << "file isn't open.\n";
	}
}
void NumberGame::PrintAllValid() {
	cout << "success print\n";
	for (auto s : listNum) {
		int tmp = s;
		for (int i = 0; i < base.size(); i++) {
			int divide = base[i];
			while (tmp > 1 && tmp % divide == 0 && divide>1) {
				tmp /= divide;
			}
		}
		if (tmp == 1) {
			cout << s << endl;
		}
	}
}
void NumberGame::Reset() {
	base.clear();
	listNum.clear();
	filename = "";
}




#endif // ! NUMBERGAME_H