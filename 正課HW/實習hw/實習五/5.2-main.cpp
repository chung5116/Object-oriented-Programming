// Name: Yung-Cheng Chang B10706009
// Date: 2020.04.09
// Last Update: 2020.04.11
// Problem statement:CPU bit growth
#include <iostream>
#include<math.h>
#define maxint 99999999
using namespace std;


int main() {

	int year = 0;
	while (cin >> year) {
		int gap = (year - 1900) / 10;
		int bit = 4;
		for (int i = 0; i < gap; i++)
			bit *= 2;
		double totalBit = bit * log(2);
		double res = 0;
		int i = 1;
		for (; i < maxint; i++) {
			res += log(i);
			if (res > totalBit)
				break;
		}
		cout << i-1 << endl;
	}
    return 0;
}
