#include<iostream>
#include<math.h>
using namespace std;

int main() {
	string in;
	while (cin >> in) {
		int size = in.length();
		int row = sqrt(size);
		int col = row;
		if (size != row*row)
			row++;
		for (int i = 0; i < row; i++) {
			int j = i;
			while (j < size) {
				cout << in[j];
				j += row;
			}
			cout << endl;
		}

	}

	
	return 0;
}