#include <iostream>
#include<fstream>
#include<vector>
#include<map>
using namespace std;

int main() {
	vector<int>num_data;
	int temp;
	map<int, int, greater<int>>m;

	while (cin >> temp) {
		m[temp]++;
	}
	cout << "N	count" << endl;
	for (map<int, int, greater<int>>::iterator it = m.begin();
		it != m.end(); it++) {
		cout << (*it).first << "	" << (*it).second << endl;
	}

    return 0;
}