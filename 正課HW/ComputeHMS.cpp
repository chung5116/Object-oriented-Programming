#include<iostream>
using namespace std;


int main() {
	unsigned long long int hours = 0;
	unsigned long long int min = 0;
	unsigned long long int sec = 0;
	unsigned long long int input = 0;
	input = 9223372036854775808;
	while (cin >> input) {
		hours = input / 3600;
		input -= 3600 * hours;
		min = input / 60;
		input -= 60 * min;
		sec = input;
		cout << hours << " hours " << min << " minutes and " << sec << " seconds" << endl;
	}


	return 0;
}