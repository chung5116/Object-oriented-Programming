#ifndef  CHARACTERDATA_H
#define CHARACTERDATA_H
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<map>
#include"Character.h"
using namespace std;



class CharacterData{
private:
	int numOfCharacter; //total number of character
	vector<SingleCharacter>characterVector;
	
public:
	CharacterData(string s);
	map<string, int>characterDictionary;   // for  convenience search
	vector<string> stringToCharacterInfo(string s);
	void stringToCardInfo(string s);
	characterInfoS getCharacterInfo(int index);
	SingleCharacter getCharacter(int index);
};


#endif // ! CHARACTERDATA_H
