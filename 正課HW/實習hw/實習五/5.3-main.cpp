// Name: Yung-Cheng Chang B10706009
// Date: 2020.04.09
// Last Update: 2020.04.10
// Problem statement:Simple Drawing Program
#include <iostream>
#include<vector>
using namespace std;

bool check(vector<vector<char>>&board,int x,int y);
bool square(vector<vector<char>>& board);
bool  trianle(vector<vector<char>>& board);
bool line(vector<vector<char>>& board);
void print(vector<vector<char>>& board);

int main() {
	int m; int n;
	//m = 5; n = 6;
	while (cin >> m >> n) {
		vector<vector<char>>board(n, vector<char>(m, '*'));
		string command;
		while (cin >> command) {
			if (command == "exit") {
				exit(1);
			}
			else if (command == "S") {
				if (square(board))
					print(board);
			}
			else if (command == "T") {
				if(trianle(board))
					print(board);
			}
			else if (command == "L") {
				if(line( board))
					print(board);
			}
		}
	}
    return 0;
}


bool check(vector<vector<char>>& board, int x, int y) {
	if (y >= board.size() || y < 0)			//rol
		return false;
	if (x < 0 || x >= board[y].size())				//col
		return false;
	return true;
}

bool square(vector<vector<char>>& board) {
	int w; int x; int y;
	vector<vector<char>>tmpboard = board;
	cin >> w >> x >> y;
	//w = 2; x = 100; y = 100;
	if (w == 1) {
		if (check(board, x, y)) {
			tmpboard[y][x] = 'X';
		}
		else {
			cout << "Out of range.\n\n";
			return false;
		}
	}
	else if (w > 1) {
		for (int i = 0; i < w; i++) {
			for (int j = 0; j < w; j++) {
				if (check(board,x + j, y + i)) {
					tmpboard[y+i][x + j] = 'X';
				}
				else {
					cout << "Out of range.\n\n";
					return false;
				}
			}
		}
	}
	else {
		cout << "Out of range.\n\n";
		return false;
	}
	board = tmpboard;
	return true;
}

bool line(vector<vector<char>>& board) {
	int x1; int y1; int x2; int y2;
	int dirx = 0;
	int diry = 0;
	vector<vector<char>>tmpboard = board;
	cin>>x1>>y1>>x2>>y2;
	//x1 = 0; y1 = 4; x2 = 4; y2 = 4;
	if (x1 < x2) {
		dirx = 1;
	}
	else if (x2 > x1) {
		dirx = -1;
	}
	if (y1 < y2)diry = 1;
	else if (y1 > y2)diry = -1;

	while (!(x1 == x2 && y1 == y2)) {
		if(check(board, x1, y1)) {
			tmpboard[y1][x1] = 'X';
		}
		else {
			cout << "Out of range.\n\n";
			return false;
		}
		x1 += dirx;
		y1 += diry;
	}
	if (check(board, x1, y1)) {
		tmpboard[y1][x1] = 'X';
	}
	else {
		cout << "Out of range.\n\n";
		return false;
	}
	board = tmpboard;
	return true;
}

bool  trianle(vector<vector<char>>& board) {
	vector<vector<char>>tmpboard = board;
	int w; int x; int y; string type;
	cin >> w >> x >> y >> type;

	if (type[1] == 'U') {
		for (int i = 0; i < w; i++) {
			if (check(board, x , y-i)) {
				tmpboard[y-i ][x] = 'X';
			}
			else {
				cout << "Out of range.\n\n";
				return false;
			}
		}

		if (type[0] == 'L') {
			for (int i = 0; i < w; i++) {		//rol
				if (check(board, x-i, y)) {
					tmpboard[y][x-i] = 'X';
				}
				else {
					cout << "Out of range.\n\n";
					return false;
				}
			}

			// 그쪿 ㈈ⅹ짾
			int y1 = y - w + 1; int x1 = x;
			for (int i = 0; i < w; i++) {
				if (check(board, x1-i, y1+i)) {
					tmpboard[y1+i][x1-i] = 'X';
				}
				else {
					cout << "Out of range.\n\n";
					return false;
				}
			}

		}
		else if (type[0] == 'R') {
			for (int i = 0; i < w; i++) {			//rol
				if (check(board, x+i, y)) {
					tmpboard[y][x+i] = 'X';
				}
				else {
					cout << "Out of range.\n\n";
					return false;
				}
			}
			// 그쪿 ㈈쩵짾
			int y1 = y - w + 1; int x1 = x;
			for (int i = 0; i < w; i++) {
				if (check(board, x1 + i, y1 + i)) {
					tmpboard[y1 + i][x1 + i] = 'X';
				}
				else {
					cout << "Out of range.\n\n";
					return false;
				}
			}
		}
	}


	else if (type[1] == 'D') {
		for (int i = 0; i < w; i++) {
			if (check(board, x, y +i)) {
				tmpboard[y+i][x] = 'X';
			}
			else {
				cout << "Out of range.\n\n";
				return false;
			}
		}
		if (type[0] == 'L') {
			for (int i = 0; i < w; i++) {		//rol
				if (check(board, x-i, y)) {
					tmpboard[y ][x-i] = 'X';
				}
				else {
					cout << "Out of range.\n\n";
					return false;
				}
			}
			// 그쪿 ㈈쩵짾
			int y1 = y; int x1 = x-w+1;
			for (int i = 0; i < w; i++) {
				if (check(board, x1 + i, y1 + i)) {
					tmpboard[y1 + i][x1 + i] = 'X';
				}
				else {
					cout << "Out of range.\n\n";
					return false;
				}
			}
		}
		else if (type[0] == 'R') {
			for (int i = 0; i < w; i++) {			//rol
				if (check(board, x+i, y)) {
					tmpboard[y][x+i] = 'X';
				}
				else {
					cout << "Out of range.\n\n";
					return false;
				}
			}

			// 그쪿 ㈈ⅹ짾
			int y1 = y; int x1 = x+w-1;
			for (int i = 0; i < w; i++) {
				if (check(board, x1 - i, y1 + i)) {
					tmpboard[y1 + i][x1 - i] = 'X';
				}
				else {
					cout << "Out of range.\n\n";
					return false;
				}
			}
		}

	}
	board = tmpboard;
	return true;
}

void print(vector<vector<char>>& board) {
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			cout << board[i][j];
		}
		cout << endl;
	}
	cout << endl;
}