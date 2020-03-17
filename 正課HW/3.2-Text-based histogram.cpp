#include <iostream>
#include<map>
using namespace std;

int main() {
	int grade;
	map<int, int, less<int>>m;

	//use map to record the data
	while (cin >> grade) {
		if (grade >= 0 && grade <= 5)
			m[grade]++;
	}

	
	for (int i = 0; i <= 5; i++) {
		if (m.find(i) != m.end()) {
			cout << m[i] << " grade(s) of " << i << endl;
		}
		else {			// If can't find the number in the map
			cout << "0 grade(s) of " << i << endl;
		}
	}
    return 0;
}