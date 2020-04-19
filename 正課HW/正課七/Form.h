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

	void SetInputWord(string inputWord) {	//�]�wInput
		this->inputWord = inputWord;
	}
	void ProcessInputWord();//�B�z Input ����T
	void SetFileName(string fileName) {	//�]�w�ɮצW��  
		this->fileName = fileName;
	}
	void Load_CompareWord();//Ū�ɨåB���
	void CompareWord(char buffer[],int k);
	void PrintFoundWords();//�L�X�ŦX���r
};

