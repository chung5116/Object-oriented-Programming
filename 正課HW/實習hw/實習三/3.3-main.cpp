// Name: �i�é�	
// Date: 2020.03.26
// Last Update: 2020.03.27
// Problem statement: Playfair Cipher
#include <iostream>
#include<map>
#include<vector>
#include<string>
using namespace std;


// ��r����iboard		return ������index
int fillBoard(vector<vector<char>>& board, map<char,int>& keyMap,string inputString);
// �Ѿl���r����J
void fillRestofalphabet(int index, vector<vector<char>>& board, map<char, int>& keyMap);
// string break into pair , and insert 'x' if needed
void breakMessage(string&inputString);
// �[�K�ഫ
void encryptPlaintext(vector<vector<char>>& board, string& inputString);



int main() {
	string inputStringplain;
	string inputStringboard;

	while (cin >> inputStringplain) {
		cin >> inputStringboard;
		vector<vector<char>>board;		// ����j�p�B�z�n
		board.resize(5);
		map<char, int>keyMap;
		for (int i = 0; i < 5; i++)
			board[i].resize(5);
		int endindex = fillBoard(board, keyMap, inputStringboard);
		fillRestofalphabet(endindex, board, keyMap);
		breakMessage(inputStringplain);
		encryptPlaintext(board, inputStringplain);
	}
    return 0;
}


int fillBoard(vector<vector<char>>& board, map<char, int>& keyMap, string inputString) {
	int currentIndex = 0;
	int i = 0;			//rol	
	int j = 0;			// co;
	for (auto&in : inputString) {
		if (keyMap.find(in) == keyMap.end()) {		//�p�G�r��������
			i = currentIndex / 5;
			j = currentIndex % 5;
			if (in == 'i' || in == 'j') {
				keyMap['i'] = 1;
				keyMap['j'] = 1;
				board[i][j] = ('i');
				//board[i][j].push_back('j');
			}
			else if (in == 'j') {
				keyMap['j'] = 1;
				continue;
			}
			else {
				keyMap[in] = 1;
				board[i][j] = in;
			}
			currentIndex++;
		}
	}
	return currentIndex;
}

void fillRestofalphabet(int index, vector<vector<char>>& board, map<char, int>& keyMap) {
	for (int i = (int)('a'); i <= (int)('z'); i++) {
		char alph = char(i);
		int rol = index / 5;
		int col = index % 5;
		if (keyMap.find(alph) == keyMap.end()) {
			if (alph == 'i' || alph == 'j') {
				keyMap['i'] = 1;
				keyMap['j'] = 1;
				board[rol][col] = 'i';
				++index;
				continue;
			}
			keyMap[alph] = 1;
			board[rol][col] = alph;
			++index;
		}
	}
}

void breakMessage(string &inputString) {
	for (int i = 0; i < inputString.size(); i++) {
		if (i + 1 >= inputString.size())		// �B�z�̫�@�ӳ�ơA�H�K�y���W�L���ת�error
			inputString.push_back('x');
		else {
			if (inputString[i] == inputString[i + 1]) {
				inputString.insert(i + 1, "x");
			}
		}
		i++;
	}
}
void encryptPlaintext(vector<vector<char>>& board, string& inputString) {
	for (int k = 0; k < inputString.length(); k++) {
		if (inputString[k] == 'j')
			inputString[k] = 'i';
	}
	for (int k = 0; k < inputString.length(); k+=2) {
		int x1 = 0;
		int y1 = 0;
		int x2 = 0;
		int y2 = 0;
		for (int i = 0; i < board.size(); i++) {
			for (int j = 0; j < board[0].size(); j++) {
				if (board[i][j] == inputString[k]) {
					x1 = i; y1 = j;
				}
				else if (board[i][j] ==inputString[k + 1]) {
					x2 = i; y2 = j;
				}
			}
		}
		// if same rol 
		if (x1 == x2) {
			if (y1 + 1 >= 5)
				y1 = -1;
			if (y2 + 1 >= 5)
				y2 = -1;
			inputString[k] = board[x1][++y1];
			inputString[k + 1] = board[x2][++y2];
		}
		// if same col
		else if (y1 == y2) {
			if (x1 + 1 >= 5)
				x1 = -1;
			if (x2 + 1 >= 5)
				x2 = -1;
			inputString[k] = board[++x1][y1];
			inputString[k + 1] = board[++x2][y2];
		}
		// rectangle
		else {
			inputString[k] = board[x1][y2];
			inputString[k + 1] = board[x2][y1];
		}
	}
	cout << inputString << endl;
}