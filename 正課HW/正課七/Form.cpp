// Name: Yung-Cheng Chang
// Date: 2020.04.09
// Last Update: 2020.03.27
// Problem statement:Form Word
#include"Form.h"

void Form::ProcessInputWord() {
	for (int i = 0; i < this->inputWord.length(); i++) {
		char tmp = inputWord[i];
		inputChar[tmp]++;
		if (tmp >= 65 && tmp <= 90) {		//uppercase to lower
			tmp = tmp + 32;
			inputChar[tmp]++;
		}
		else if (tmp >= 97 && tmp <= 122) {		//lowercase to upper
			tmp = tmp - 32;
			inputChar[tmp]++;
		}
	}
}

void Form::Load_CompareWord() {
	fstream file;
	file.open(fileName,ios::in);
	if (file.is_open()) {
		int k = 0;
		while (!file.eof()) {
			char buffer[200];
			file.getline(buffer, sizeof(buffer));
			k++;
			CompareWord(buffer,k);
		}
		file.close();
	}
	else {
		cout << "Can't open file\n";
	}
}


void Form::PrintFoundWords() {
	for (int i = 0; i < outputString.size(); i++) {
		cout << this->outputString[i] << endl;
	}
}

void  Form::CompareWord(char buffer[],int k) {
	string tmpWord = "";

	for (int i = 0; buffer[i] != '\0' && buffer[i]!='\n';i++) {
		tmpWord += buffer[i];
	}
	tmpWord.pop_back();  //這邊popback() 因為不知道何會一直抓到換行符號
	map<char, int>tmpMap = this->inputChar;
	for (int i = 0; i < tmpWord.length(); i++) {			// if there are any invalid char ,then return
		if (tmpMap.find(tmpWord[i]) == tmpMap.end()  || tmpMap[tmpWord[i]]==0) {
			return;
		}
		else {
			tmpMap[tmpWord[i]]--;
		}
	}
	this->outputString.push_back(tmpWord);
}