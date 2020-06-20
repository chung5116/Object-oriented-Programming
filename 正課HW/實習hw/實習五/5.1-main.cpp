// Name: Yung-Cheng Chang B10706009
// Date: 2020.04.09
// Last Update: 2020.04.09
// Problem statement:Input_Output3
#include <iostream>
#include<string>
#include<math.h>
#include <iomanip>
using namespace std;

int main() {
	double x;
	int m; 
	int n;
	char c;
	while (cin >> x >> m >> n >> c) {
		double tmpx = abs(x);
		int count1 = 0;  //幾位數
		int count2 = 0;  // if negative
		int numOfChar = 0;
		while (tmpx >= pow(10, count1)) {
			count1++;
		}
		if (x > 0)count2 = count1;
		else count2 = (count1+1);

		if (n > 0)numOfChar = m - n - count2 - 1;
		else numOfChar = m - count2;     //沒有小數點

		for (int i = 0; i < numOfChar; i++) {
			cout << c;
		}

		if (n > 0) {
			cout << fixed << setprecision(n) << x - 0.0000000009 << endl;
			cout.unsetf(ios::fixed);
		}
		else {				//沒小數點
			int num = (int)x;
			if(x>0){
				cout << setprecision(n) << num << endl;
			}
			else {
				cout << setprecision(n-1) << num << endl;		//有負號
			}
		}
		//x - 0.0000000009
		

		cout.unsetf(ios::fixed);
	}
    return 0;
}