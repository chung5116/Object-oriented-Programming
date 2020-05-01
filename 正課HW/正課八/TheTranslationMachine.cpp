// Name: ±i¥Ã©Ó	
// Date: 2020.04.22
// Last Update:2020.04.23
// Problem statement:  The Translation Machine
#include <iostream>
#include<map>
#include<vector>
using namespace std;

struct pairS{
	char first = ' ';
	char second = ' ';
	pairS(char f, char s) { first = f; second = s; }
};

bool findTrans(map<char, vector<char>>& m, char a, char b) {
	if (a == b) { return true; }
	if (m.empty()) {
		return false;
	}
	if (m.find(a) != m.end()) {
		int size = m[a].size();
		if (m[a].at(size - 1) == b) {
			return true;
		}
		else {
			for (int i = 0; i < size; i++) {
				if (size - 1 < 0) {
					cout << "size < 0";
					continue;
				}
				if (m.find(a) != m.end()) {				// need to check again, because in the recursive , the char might be erased
					char tmp = m[a].at(size - 1);
					m[a].pop_back();
					size--;
					i--;
					if (m[a].empty())
						m.erase(a);
					if (findTrans(m, tmp, b))
						return true;
				}
				else {
					break;
				}
			}
		}
	}
}

int main() {
	int m = 0;		//number of translations of letters
	int n = 0;		//number of word pairs.
	while (cin >> m >> n) {
		if (m == 0 &&n==0)
			break;
		map<char, vector<char>>pairMap;			// cause one char can map to many char , so use vector to store
		for (int i = 0; i < m; i++) {
			char first;
			char second;
			cin >> first >> second;
			pairMap[first].push_back(second);			// push value
		}
		for (int i = 0; i < n; i++) {
			string first;
			string second;
			cin >> first >> second;
			bool yes = true;
			if (first == second) {
				cout << "yes\n";
				continue;
			}
			if (first.length() != second.length()) {
				cout << "no\n";
				yes = false;
				continue;
			}
			for (int i = 0; i < first.length(); i++) {		
				char charFromfirst = first[i];
				char target = second[i];
				map<char, vector<char>>tmpMap = pairMap;
				if (charFromfirst == target) {
					continue;
				}
				if (tmpMap.find(charFromfirst) == tmpMap.end()) {
					cout << "no\n";	
					yes = false;
					break;
				}
				else {
					if (!findTrans(tmpMap, charFromfirst, target)) {
						cout << "no\n";
						yes = false;
						break;
					}
				}
			}
			if (yes)
				cout << "yes\n";
		}
	}
    return 0;
}