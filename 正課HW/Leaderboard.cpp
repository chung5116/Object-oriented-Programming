#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<algorithm>
#include<functional>
using namespace std;

void getHighScores(vector<int>score_vector, vector<string>name_vector, map<int, string>m) {
	sort(score_vector.begin(), score_vector.end(), greater<int>());
	for (int i = 0; i < 3; i++) {
		cout << m[score_vector[i]] << endl;
		cout << score_vector[i] << endl;
	}
	//map<int, string, greater<int>>::iterator itr;

}


int main() {

	string name;
	int scores;
	vector<int>score_vector;
	vector<string>name_vector;
	map<int, string>m;
	while (cin >> name,cin>>scores) {
		score_vector.push_back(scores);
		name_vector.push_back(name);
		m[scores] = name;
	}
	getHighScores(score_vector, name_vector, m);
	return 0;
}