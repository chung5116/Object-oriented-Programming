#include <iostream>
#include<vector>
using namespace std;

int main() {
	int rowA, colA, rowB, colB;
	cin >> rowA >> colA >> rowB >> colB;
	vector<vector<int>>mA(rowA, vector<int>(colA, 0));
	vector<vector<int >>mB(rowB, vector<int>(colB, 0));
	vector<vector<int >>mC(rowA, vector<int>(colB, 0));
	int tmp;
	for (int i = 0; i < rowA; i++) {
		for (int j = 0; j < colA; j++) {
			cin >> tmp;
			mA[i][j] = tmp;
		}
	}

	for (int i = 0; i < rowB; i++) {
		for (int j = 0; j < colB; j++) {
			cin >> tmp;
			mB[i][j] = tmp;
		}
	}
	if (colA != rowB) {
		cout << "Matrix multiplication failed.\n";

	}
	else {
		for (int k = 0; k < rowA; k++) {
			for (int i = 0; i < colB; i++) {
				int res = 0;
				for (int j = 0; j < rowB; j++) {
					res += mA[k][j] * mB[j][i];
				}
				mC[k][i] = res;
			}
		}
		for (int i = 0; i < mC.size(); i++) {
			for (int j = 0; j < mC[0].size(); j++) {
				cout << mC[i][j] << " ";
			}
			cout << endl;
		}
	}

    return 0;
}