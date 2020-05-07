// Name: �i�é�	
// Date: 2020.04.30
// Last Update:2020.04.30
// Problem statement: Word game
#include <iostream>
#include<fstream>
#include<vector>
#include<map>
//�C�Ӧr�����n�۾F �]�i�H�﨤�u �ت����X�׽u�Z��

using namespace std;
vector<vector<char>>grid(4);			// �D�ص���
vector<int >gletter(26,0);
map<char, int>letterMap;
void check(string s);
void adjoining(vector<vector<int>>& tmpGrid, string s);
bool checkAdjoining(int x, int y, vector<vector<int>>& tmpGrid);					// return true : ����1     false : ����S1
bool checkAdjoining(int x, int y, char target);					// return true : ����1     false : ����S1
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

			for (int j = 0; j < 4; j++) {			//�����r��
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
	vector<vector<int>>tmpGrid(4, vector<int>(4, 0)); //����1 �ˬd�C��1���񦳨S��1�A�Y�S�h�Ono
	vector<int >letter = gletter;
	for (int i = 0; i < s.length(); i++) {			// check if reused 
		if (letterMap.find(s[i]) != letterMap.end()) {			// �p�Ggrid���o�Ӧr���~�~��
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
		�o��n�ˬd �O�_���e�@�Ӫ��F�~�A�B�ˬd���P�e�@�ӳ������n�O�bgrid�W��
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