//Name: b10706009 ±i¥Ã©Ó
//data: 2020/06/04
//last update: 2020/06/04
//problem subject: STL
#include <iostream>
#include<vector>
#include<map>
#include<fstream>
#include<set>
#include<string>
using namespace std;

int main() {
	fstream file;
	file.open("name.txt", ios::in);
	vector<string>res;		//result
	set<string>m;	//prevent duplicate data
	while (!file.eof()) {
		string buffer;
		getline(file, buffer);
		m.insert(buffer);
	}
	for (auto s : m) {
		cout << s << endl;
	}
    return 0;
}