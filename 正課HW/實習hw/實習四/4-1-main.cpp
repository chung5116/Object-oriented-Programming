// Name: ±i¥Ã©Ó	B10706009
// Date: 2020.04.02
// Last Update: 2020.04.02
// Problem statement:  Collatz Conjecture
#include <iostream>
using namespace std;

int conjecture(int num) {			// calculate cycle
	int cycle = 1;
	while (num != 1) {
		if (num % 2 == 0) {
			num /= 2;
		}
		else {
			num = num * 3 + 1;
		}
		cycle++;
	}
	return	cycle;
}


int main() {
	int num1 = 0;
	int num2 = 0;

	while (cin >> num1 >> num2) {
		int maxcycle = 0;
		if (num2 >= num1) {
			for (int i = num1; i <= num2; i++) {
				int cycle = conjecture(i);
				if (cycle > maxcycle)
					maxcycle = cycle;
			}
		}
		else {
			for (int i = num1; i >= num2; i--) {
				int cycle = conjecture(i);
				if (cycle > maxcycle)
					maxcycle = cycle;
			}
		}
		cout << num1 << " " << num2 << " " << maxcycle << endl;
	}
    return 0;
}