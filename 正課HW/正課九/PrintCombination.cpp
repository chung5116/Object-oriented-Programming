// Name: ±i¥Ã©Ó	
// Date: 2020.04.30
// Last Update:2020.04.30
// Problem statement:  Design Polynomial Class
#include"PrintCombination.h"

void PrintCombination(int* ptr, const int& total, const int& choice) {
	vector<int>res{0 };
	combination(res, total, choice);
}


void combination(vector<int>res, int total, int choice) {
	if (res.size()-1 == choice) {
		for (int i = 1; i < res.size(); i++) {
			cout << res[i] << " ";
		}
		cout << endl;
	}
	else {
			for (int i = res.back() + 1; i <= total; i++) {
				res.push_back(i);
				combination(res, total, choice);
				res.pop_back();
			}
	}
}