// Name: ±i¥Ã©Ó	
// Date: 2020.05.13
// Last Update:2020.05.14
// Problem statement: Memory_Simulator
#include <iostream>
#include<string>
#include<vector>
#include<sstream>
#include<algorithm>
#define CHAR 1
#define SHORT 2
#define INT 4

using namespace std;

vector<string>splitString(string buffer);
string toHex(unsigned int num);			// give a num and return hex string
char decToHex(unsigned int n);		//dec to hex return char
void writeInMem(vector<string>tmp, vector<string>& mem);   // write in memory
void getMem(vector<string>tmp, vector<string>& mem);   //get content from memory
void hexToDexS(string s);
void hexToDecI(string s);
unsigned int stringToInt(string s);

	
int main() {

	int sizeOfMem;
	int numOfCommands;
	cin >> sizeOfMem;
	cin >> numOfCommands;
	string buffer;
	vector<string>mem(sizeOfMem,"00");     //initialize memory
	cin.ignore();
	for (int i = 0; i < numOfCommands; i++) {
		getline(cin, buffer);
		vector<string>tmp = splitString(buffer);

		if (tmp[0] == "Set") {
			writeInMem(tmp, mem);
		}
		else if (tmp[0] == "Get") {
			getMem(tmp, mem);
		}
	}
    return 0;
}


void getMem(vector<string>tmp, vector<string>& mem) {
	tmp.erase(tmp.begin());   // erase the first command
	int index = stoi(tmp[0]);
	if (index <0 || index>mem.size()) {		// check illegal position
		cout << "Violation Access.\n";
		return;
	}
	string type = tmp[1];
	if (type == "String") {
		string buffer;
		while (index < mem.size() &&mem[index] != "00" ) {		//until 00 or overflow
			buffer = buffer + mem[index];	
			index++;
		}
		hexToDexS(buffer);
	}
	else if (type == "char") {
		if (index + CHAR > mem.size()) {
			cout << "Violation Access.\n";
		}
		else {
			hexToDexS(mem[index]);
		}
	}
	else if (type == "int") {
		if (index + INT > mem.size()) {			// if over the range,return
			cout << "Violation Access.\n";
		}
		else {
			string buffer;
			for (int i = 0; i < 4; i++) {
				if (index < mem.size()) {
					buffer = buffer + mem[index];
					index++;
				}
			}
			hexToDecI(buffer);
		}
	}
	else if (type == "short") {		
		if (index +SHORT > mem.size()) {		// if over the range,return
			cout << "Violation Access.\n";
		}
		else {
			string buffer;
			for (int i = 0; i < 2; i++) {
				if (index < mem.size()) {
					buffer = buffer + mem[index];
					index++;
				}
			}
			hexToDecI(buffer);
		}
	}
}


void hexToDecI(string s) {
	int res = 0;
	int base = 1;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] >= '0' && s[i] <= '9') {
			res += (s[i] - 48) * base;
			base *= 16;
		}
		else if (s[i] >= 'A' && s[i] <= 'F') {
			res += (s[i] - 55) * base;
			base *= 16;
		}
	}
	cout << res << endl;
}


void writeInMem(vector<string>tmp, vector<string>& mem) {
	tmp.erase(tmp.begin());   // erase the first command
	int index = stoi(tmp[0]);	
	if (index <0 || index>mem.size()) {   // check illegal position
		cout << "Violation Access.\n";
		return;
	}

	string convert = tmp[2];
	if (tmp[1] == "char") {
		mem[index] = toHex(stringToInt(convert));
	}

	else if (tmp[1] == "int") {
		if (index + INT > mem.size()) {
			cout << "Violation Access.\n";
		}
		string res = toHex(stringToInt(convert));
		if (res.size() > 8) {				// if exceed the size of type
			reverse(res.begin(), res.end());
			while (res.size() > 8)
				res.pop_back();
			reverse(res.begin(), res.end());
		}
		for (int i = res.size()-2; i >=0; i -= 2) {
			if (index < mem.size()) {
				mem[index] = res.substr(i, 2);
				index++;
			}
		}
	}

	else if (tmp[1] == "short") {
		if (index + SHORT > mem.size()) {
			cout << "Violation Access.\n";
		}
		string res = toHex(stringToInt(convert));
		if (res.size() > 4) {				// if exceed the size of type
			reverse(res.begin(), res.end());
			while (res.size() > 4)
				res.pop_back();
			reverse(res.begin(), res.end());
		}
		for (int i = res.size() - 2; i >= 0; i -= 2) {
			if (index < mem.size()) {
				mem[index] = res.substr(i, 2);
				index++;
			}
		}
	}
	else if (tmp[1] == "String") {
		if (index + convert.size() > mem.size()) {
			cout << "Violation Access.\n";
		}
			for (int i = 0; i < convert.size(); i++) {
				if (index < mem.size()) {						//if exceed the size of type
					mem[index] = toHex((int)convert[i]);
					index++;
				}
			}
		
	}
}


void hexToDexS(string s) {
	string result;
	for (int i = s.size()-1; i >= 0; i -= 2) {
		int res = 0;
		int pow = 1;
		if (s[i] >= '0' && s[i] <= '9') {
			res += (s[i] - 48) * pow;
			pow *= 16;
		}
		else if (s[i] >= 'A' && s[i] <= 'F') {
			res += (s[i] - 55) * pow;
			pow *= 16;
		}
		if (s[i-1] >= '0' && s[i-1] <= '9') {
			res += (s[i-1] - 48) * pow;
			pow *= 16;
		}
		else if (s[i-1] >= 'A' && s[i-1] <= 'F') {
			res += (s[i-1] - 55) * pow;
			pow *= 16;
		}

		if (res > 127 || res < 32) {				//   out of range use int
			result = to_string(res) + result;
		}
		else if (res >= 32 && res <= 127) {			//32~127 use char
			result = char(res) + result;
		}
	}
	cout << result << endl;
}


vector<string>splitString(string buffer) {
	istringstream ss(buffer);
	string token;
	vector<string>res;
	while (getline(ss, token, ' ')) {
		res.push_back(token);
	}
	return res;
}


string toHex(unsigned int num) {
	unsigned int unNum = (int)num;
	string res;
	while (unNum > 0) {
		res = decToHex(unNum % 16) + res;
		unNum /= 16;
	}
	return res;
}

char decToHex(unsigned int n) {
	char hex[] = { '0', '1', '2', '3','4','5'
				 ,'6','7','8','9','A','B','C'
				 ,'D','E','F' };
	return hex[n];
}

unsigned int stringToInt(string s) {
	unsigned int res = 0;
	unsigned int base = 1;
	for (int i=s.size()-1 ; i >=0; i--) {
		int tmp = s[i] - '0';
		res += tmp * base;
		base *= 10;
	}
	return res;
}