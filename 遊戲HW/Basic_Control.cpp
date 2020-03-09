#include<iostream>
#include<conio.h>
#include<ctime>
#include<thread>
#include<chrono>
using namespace std;

int main() {
	clock_t start, stop;
	start = clock();
	stop = start;
	double time_counter = 0;
	for (int i = 0; i < 15; i++) {
		std::this_thread::sleep_for(1s);
		start = clock();
		time_counter += (double)(start - stop);
		stop = start;
		cout << "total time " << i << " at " << time_counter / CLOCKS_PER_SEC << endl;
	}
	char in = 0;
	while (1) {
		//cout << _getch() << endl;
		in = _getch();
		switch (in - 'A') {
		case 22:
			cout << "Key W is pressed" << endl;
			break;
		case 0:
			cout << "Key A is pressed" << endl;
			break;
		case 18:
			cout << "Key S is pressed" << endl;
			break;
		case 3:
			cout << "Key D is pressed" << endl;
			break;
		}
		if (in == 27)
			break;
	}

	system("PAUSE");
	return 0;
}