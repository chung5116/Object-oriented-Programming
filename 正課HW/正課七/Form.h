// Name: Yung-Cheng Chang
// Date: 2020.04.09
// Last Update: 2020.04.10
// Problem statement:Form Word
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
using namespace std;
class Form
{
private:
	string inputWord;
	string fileName;
	vector<string>outputString;
	map<char, int>inputChar;		// store char
public:

	void SetInputWord(string inputWord) {	//設定Input
		this->inputWord = inputWord;
	}
	void ProcessInputWord();//處理 Input 的資訊
	void SetFileName(string fileName) {	//設定檔案名稱  
		this->fileName = fileName;
	}
	void Load_CompareWord();//讀檔並且比較
	void CompareWord(char buffer[],int k);
	void PrintFoundWords();//印出符合的字
};

