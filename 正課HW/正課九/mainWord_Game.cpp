// Name: 張永承	
// Date: 2020.04.30
// Last Update:2020.04.30
// Problem statement: Word game
#include <iostream>
#include<fstream>
#include<vector>
#include<map>
//每個字母都要相鄰 也可以對角線 建表格後算出斜線距離

using namespace std;
vector<vector<char>>grid(4);			// 題目給的
vector<int >gletter(26,0);
map<char, int>letterMap;
void check(string s);
void adjoining(vector<vector<int>>& tmpGrid, string s);
bool checkAdjoining(int x, int y, vector<vector<int>>& tmpGrid);					// return true : 附近有1     false : 附近沒1
bool checkAdjoining(int x, int y, char target);					// return true : 附近有1     false : 附近沒1
void fill(vector<vector<int>>& tmpGrid, string s);

int main() {

	fstream file;
	file.open("words.txt", ios::in);
	if (!file) {
		cout << "open file failed\n";
	}
	else {
		for (int i = 0; i < 4; i++) {		//input grid
			string tmp;
			cin >> tmp;

			for (int j = 0; j < 4; j++) {			//紀錄字母
				gletter[tmp[j] - 'a']++;
				grid[i].push_back(tmp[j]);
				letterMap[tmp[j]]++;
			}
		}
		char buffer[100];
		while (!file.eof()) {
			file.getline(buffer, 100);
			//cout << buffer << endl;
			string word(buffer);
			check(word);
		}
	}

    return 0;
}

void check(string s) {
	vector<vector<int>>tmpGrid(4, vector<int>(4, 0)); //紀錄1 檢查每個1附近有沒有1，若沒則是no
	vector<int >letter = gletter;
	for (int i = 0; i < s.length(); i++) {			// check if reused 
		if (letterMap.find(s[i]) != letterMap.end()) {			// 如果grid有這個字母才繼續
			letter[s[i] - 'a']--;
			if (letter[s[i] - 'a'] < 0) {
				return;
			}
		}
	}
	fill(tmpGrid, s);
	adjoining(tmpGrid,s);
}

void adjoining(vector<vector<int>>& tmpGrid,string s) {
	int i = s.length() - 1;
	while (i > 0) {
		char c = s[i];
		int j = i - 1;
		/*
		這邊要檢查 是否為前一個的鄰居，且檢查的與前一個都必須要是在grid上的
		*/
	}


	/*for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (tmpGrid[i][j] == 1) {
				if (!checkAdjoining(i, j, tmpGrid)) {
					return;
				}
			}
		}
	}*/
	cout << s << endl;
}

bool checkAdjoining(int x, int y, char target) {
	//top
	if (x - 1 > 0 && grid[x-1][y] == target)
		return true;
	//down
	if (x + 1 < 3 && grid[x+1][y] == target)
		return true;
	//left
	if (y - 1 > 0 && grid[x][y-1] == target)
		return true;
	//right
	if (y + 1 < 3 && grid[x][y+1] == target)
		return true;

	// top right
	if (x - 1 > 0 && y + 1 < 3 && grid[x-1][y+1] == target)
		return true;

	//top left
	if (x - 1 > 0 && y - 1 > 0 && grid[x-1][y-1] == target)
		return true;

	//down left
	if (x + 1 < 3 && y - 1 > 0 && grid[x+1][y-1] == target)
		return true;

	//down right
	if (x + 1 < 3 && y + 1 < 3 && grid[x+1][y+1] == target)
		return true;

	return false;
}

bool checkAdjoining(int x, int y, vector<vector<int>>& tmpGrid) {
	//top
	x = x - 1 < 0 ? 3 : x-1;
	if (tmpGrid[x][y] == 1)
		return true;
	//down
	x = x + 1 > 3 ? 0 : x + 1;
	if (tmpGrid[x][y] == 1)
		return true;
	//left
	y = y - 1 < 0 ? 3 : y - 1;
	if (tmpGrid[x][y] == 1)
		return true;
	//right
	y = y + 1 > 3 ? 0 : y + 1;
	if (tmpGrid[x][y] == 1)
		return true;

	// top right
	x = x - 1 < 0 ? 3 : x - 1;
	y = y + 1 > 3 ? 0 : y + 1;
	if (tmpGrid[x][y] == 1)
		return true;

	//top left
	x = x - 1 < 0 ? 3 : x - 1;
	y = y - 1 < 0 ? 3 : y - 1;
	if (tmpGrid[x][y] == 1)
		return true;

	//down left
	x = x + 1 > 3 ? 0 : x + 1;
	y = y - 1 < 0 ? 3 : y - 1;
	if (tmpGrid[x][y] == 1)
		return true;

	//down right
	x = x + 1 > 3 ? 0 : x + 1;
	y = y + 1 > 3 ? 0 : y + 1;
	if (tmpGrid[x][y] == 1)
		return true;

	return false;
}

void fill(vector<vector<int>>& tmpGrid, string s) {
	vector<vector<char>>localGrid = grid;
	for (int i = 0; i < s.length(); i++) {
		char c = s[i];
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				if (localGrid[j][k] == c) {
					tmpGrid[j][k] = 1;
					localGrid[j][k] = '0';
				}
			}
		}
	}
}