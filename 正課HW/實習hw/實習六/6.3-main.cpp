// Name: 張永承	B10706009
// Date: 2020.04.16
// Last Update: 2020.04.119
// Problem statement:  Student Score System
#include <iostream>
#include<string>
#include<vector>
using namespace std;




class st {
private:
	vector<vector<string>>schedule;
public:
	st(string name);
	string stName;
	void addCourse();
	void delCourse();
	void printStCourse(string course);
	void printall();
};

void addst();
void addco();
void delst();
void delco();
void print();
vector<string>split(const string& str, const string& delim);

vector<st>st_arr;
int main() {
	string cmd;
	while (cin >> cmd) {
		if (cmd == "AddStudent") {
			addst();
		}
		else if (cmd == "AddCourse") {
			addco();
		}
		else if (cmd == "DelStudent") {
			delst();
		}
		else if (cmd == "DelCourse") {
			delco();
		}
		else if (cmd == "Print") {
			print();
		}
	}
    return 0;
}

void addst() {
	string name;
	cin >> name;
	for (int i = 0; i < st_arr.size(); i++) {
		if (st_arr[i].stName == name) {
			cout << "The student's name is duplicate.\n";
			return;
		}
	}
	st newSt(name);
	st_arr.push_back(newSt);
}
void addco() {
	string name;
	cin >> name;
	for (int i = 0; i < st_arr.size(); i++) {
		if (st_arr[i].stName == name) {
			st_arr[i].addCourse();
			return;
		}
	}
	cout << "The student's name does not exist.\n";
}
void delst() {
	string name;
	cin >> name;
	vector<st>::iterator it;
	it = st_arr.begin();
	for (int i = 0; i < st_arr.size(); i++) {
		if (st_arr[i].stName == name) {
			st_arr.erase(it+i);
			return;
		}
	}
	cout << "The student's name does not exist.\n";
}
void delco() {
	string name;
	cin >> name;
	for (int i = 0; i < st_arr.size(); i++) {
		if (st_arr[i].stName == name) {
			st_arr[i].delCourse();
			return;
		}
	}
	string course;
	cin >> course;
	cout << "The student's name does not exist.\n";
}
void print() {
	string st;
	getline(cin, st);
	st.erase(0,1);	
	if (st[st.length() - 1] == ' ') {		//後面會抓到'  '
		st.erase(st.length() - 1, 1);	
	}
	if (st == "StudentList") {
		if (st_arr.size() > 0) {
			for (int i = 0; i < st_arr.size(); i++) {
				cout << st_arr[i].stName << endl;
			}
		}
		else {
			cout << "The Students list is empty.\n";
		}
	}
	else {
		for (int i = 0; i < st.length(); i++) {
			if (st[i] == ' ') {
				string name = st.substr(0, i);
				string course = st.substr(i + 1, course.length() - i);
				for (int i = 0; i < st_arr.size(); i++) {
					if (st_arr[i].stName == name) {
						st_arr[i].printStCourse(course);
					}
				}
				return;
			}
		}

		for (int i = 0; i < st_arr.size(); i++) {
			if (st_arr[i].stName == st) {
				st_arr[i].printall();
				return;
			}
		}
		cout << "The student's name does not exist.\n";
	}
}

vector<string>split(const string& str, const string& delim) {
	vector<string> res;
	string strs = str + delim;
	size_t pos;
	size_t size = strs.size();

	for (int i = 0; i < size; ++i) {
		pos = strs.find(delim, i); 
		if (pos < size) {
			string s = strs.substr(i, pos - i);
			res.push_back(s);
			i = pos + delim.size() - 1;
		}

	}
	return res;
}
st::st(string name) {
	schedule.resize(5);
	for (int i = 0; i < schedule.size(); i++) {
		schedule[i].resize(10,"");
	}
	this->stName = name;
}


void st::addCourse() {
	string courseName;
	string time;
	vector<string>vtime;
	cin >> courseName;	
	getline(cin, time);
	string::iterator it;
	it = time.begin();
	time.erase(0,1);
	vtime = split(time, " ");
	
	for (int i = 0; i < vtime.size(); i++) {
		char day = vtime[i][0];
		string::iterator it;
		it = vtime[i].begin();
		string snum = vtime[i];
		snum = snum.erase(0,1);
		int num = stoi(snum);
		int rol = 0;
		num--;
		if (day == 'M') {
			rol = 0;
		}
		else if(day == 'T') {
			rol = 1;
		}
		else if (day == 'W') {
			rol = 2;
		}
		else if (day == 'R') {
			rol = 3;
		}
		else if (day == 'F') {
			rol = 4;
		}
		if (schedule[rol][num] != "") {
			cout << "Course conflict.\n";
			return;
		}
	}
	for (int i = 0; i < vtime.size(); i++) {
		char day = vtime[i][0];
		int num = stoi(vtime[i].erase(0,1));
		int rol = 0;
		num--;
		if (day == 'M') {
			rol = 0;
		}
		else if (day == 'T') {
			rol = 1;
		}
		else if (day == 'W') {
			rol = 2;
		}
		else if (day == 'R') {
			rol = 3;
		}
		else if (day == 'F') {
			rol = 4;
		}
		if (schedule[rol][num] == "") {
			schedule[rol][num] = courseName;
		}
		else {
			cout << "conflit error\n";
		}
	}
}

void st::delCourse() {
	string courseName;
	cin >> courseName;
	bool exist = false;
	for (int i = 0; i < schedule.size(); i++) {
		for (int j = 0; j < schedule[i].size(); j++) {
			if (schedule[i][j] == courseName) {
				schedule[i][j] = "";
				exist = true;
			}
		}
	}
	if (!exist) {
		cout << "The course does not exist.\n";
	}
}

void st::printStCourse(string course) {
	bool exist = false;
	for (int i = 0; i < schedule.size(); i++) {
		for (int j = 0; j < schedule[i].size(); j++) {
			if (schedule[i][j] == course) {
				exist = true;
			}
		}
	}
	if (!exist) {
		cout << "The course does not exist.";
	}
	else {
		cout << course << " ";
		for (int i = 0; i < schedule.size(); i++) {
			for (int j = 0; j < schedule[i].size(); j++) {
				if (schedule[i][j] == course) {
					if (i == 0) {
						cout << "M";
					}
					else if (i == 1) {
						cout << "T";
					}
					else if (i == 2) {
						cout << "W";
					}
					else if (i == 3) {
						cout << "R";
					}
					else if (i == 4) {
						cout << "F";
					}
					cout << j + 1 << " ";
				}
			}
		}
	}
	cout << endl;
}

void st::printall() {
	for (int i = 0; i < schedule.size(); i++) {
		if (i == 0) {
			cout << "M: ";
		}
		else if (i == 1) {
			cout << "T: ";
		}
		else if (i == 2) {
			cout << "W: ";
		}
		else if (i ==3) {
			cout << "R: ";
		}
		else if (i == 4) {
			cout << "F: ";
		}
		for (int j = 0; j < schedule[i].size(); j++) {
			if (schedule[i][j] != "") {
				cout << j + 1 << ":" << schedule[i][j] << " ";
			}
		}
		cout << endl;
	}
}