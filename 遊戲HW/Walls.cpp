#include<iostream>
#include<windows.h>
#include<conio.h>
using namespace std;

int main() {
	char wall = 'x';
	char space = '0';
	char map[10][20] = { 0 };
	int row = -1;
	int col = -1;
	char change = 0;
	char contin = 0;
	cout << "Enter the char for wall in map." << endl;
	cin >> wall;
	cout << "Enter the char for empty space in map." << endl;
	cin >> space;
	cout << "\n\n\n";
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 20; j++) {
			if (i == 0 || i == 9 || j == 0 || j == 19)
				map[i][j] = wall;
			else
				map[i][j] = space;
			cout << map[i][j];
		}
		cout << endl;
	}
	cout << "\n\n\n";

	
	while (1){
		cout << "繼續輸入座標及圖案? : y/n \n";
		cin >> contin;

		// If enter "n" break the while loop
		if (contin == 'n' || contin == 'N') {
			break;
		}
		else if(contin == 'y' || contin == 'Y'){
			cout << "輸入座標及圖案\n座標圖按輸入範例Ex : 5 3 &" << endl;
			cin >> row;
			cin >> col;
			cin >> change;
			cout << "\n\n\n";
			if (row >= 0 && row < 10 && col >= 0 && col < 20) {
				map[row][col] = change;
				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 20; j++) {
						if (i == row && j == col) {
							cout << "\033[32m" << map[i][j] << "\033[0m";
						}
						else
							cout << map[i][j];
					}
					cout << endl;
				}
				cout << "\n\n\n";
			}
			else {
				cout << "輸入錯誤" << endl;
			}
		}
	}
	system("PAUSE");
	return 0;
}