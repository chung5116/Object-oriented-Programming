// Name: 張永承 B10706009
// Date: 2020.03.20
// Last Update: 2020.03.20
// Problem statement: Fraction

#include<iostream>
#include<string>
using namespace std;

class Fraction
{
public:
	void setNumerator(double num) { this->numerator = num; 
	//cout << "numerator" << numerator << endl; 
	}
	void setDenominator(double num) { this->denominator = num;
	//cout << "denominator" << denominator << endl;
	}
	void getDouble();
	void outputReducedFraction();
private:
	double numerator = 0;
	double denominator = 0;
};


void Fraction::getDouble() {
	double res= numerator / denominator;
	if (res == (int)res) {
		res = (int)res;
		int ans = res;
		cout << ans << endl;
	}
	else {
		string ans = to_string(res);

		cout << ans << endl;
		///printf("%f\n", res);
	}
}

void Fraction::outputReducedFraction() {
	int xtmp = this->numerator;   // 分子
	int  ytmp = this->denominator;  //分母
	int divisor = 0;		//
	if (xtmp == 0) {
		cout << xtmp << endl;
	}
	else {
		for (int i = 1; i <= numerator; i++) {
			if (xtmp % i == 0 && ytmp % i == 0) {
				if (i > divisor)
					divisor = i;
			}
		}
		xtmp /= divisor;
		ytmp /= divisor;

	 if (ytmp == 1) {
	cout << xtmp << endl;
	}
	else
	cout << xtmp << "/" << ytmp << endl;
	}
}

