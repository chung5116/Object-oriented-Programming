#include<iostream>
#include<vector>
#include<math.h>
#include<cmath>
using namespace std;


int main() {
	int num_input = 0;
	while (cin >> num_input) {
		float tmp_int = 0;
		vector<float>val;
		float average = 0;
		float standard_deviation = 0;

		for (int i = 0; i < num_input; i++) {
			cin >> tmp_int;
			val.push_back(tmp_int);
			average += tmp_int;
		}
		average /= num_input;

		for (int i = 0; i < val.size(); i++) {
			standard_deviation += (average - val[i])* (average - val[i]);
		}
		standard_deviation = standard_deviation / (float)num_input;
		standard_deviation = sqrt(standard_deviation);
		cout << "Average:" << average << "	" << "Standard deviation:" << standard_deviation << endl;
	}
	return 0;
}