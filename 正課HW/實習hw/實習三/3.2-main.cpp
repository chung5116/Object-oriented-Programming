// Name: 張永承	
// Date: 2020.03.26
// Last Update: 2020.03.26
// Problem statement: Row Transposition Cipher
#include <iostream>
#include<string>
#include<vector>
#include<sstream>
using namespace std;

int main() {
	string plaintext;
	while (getline(cin, plaintext)) {
		vector<vector<char>>data;		//儲存分組後的字元
		vector<int>rol;
		int maxnum = 0;
		int numOfrol = 0;    //總共幾列
		string snum;

		getline(cin, snum);
		istringstream in (snum);
		string t;
		while (in >> t) {			// split string into index
			rol.push_back(stoi(t));
		}

		numOfrol = rol.size() ;
		data.resize(numOfrol);
		for (int i = 0; i < plaintext.length(); i++) {
			int index = i % (numOfrol);
			if (plaintext[i] == ' ') {
				data[index].push_back('_');
			}
			else
				data[index].push_back(plaintext[i]);
		}

		for (int i = 0; i < rol.size(); i++) {
			for (int j = 0; j < data[rol[i]].size(); j++) {
				cout << data[rol[i]][j];
			}
		}
		cout << endl;
	}

    return 0;
}