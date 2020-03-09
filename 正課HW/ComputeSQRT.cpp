#include<iostream>
#include<iomanip>
using namespace std;


int main() {
	double n;
	while (cin >> n) {
		double guess = n / 2;
		double r = 0;
		double previos = 0;
		while (abs(previos - guess) > 0.01) {
			previos = guess;
			r = n / guess;
			guess = (guess + r) / 2;
		}
		cout << fixed << setprecision(2) << guess << endl;
	}
	return 0;
}