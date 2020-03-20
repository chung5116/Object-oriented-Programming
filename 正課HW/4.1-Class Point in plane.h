// Name: ±i¥Ã©Ó B10706009
// Date: 2020.03.20
// Last Update: 2020.03.20
// Problem statement: Class Point in plane
#include<iostream>
using namespace std;

class  Point
{
public:
	void Set(int x, int y) { this->num1 = x; this->num2 = y; }
	void Move(int x, int y) { this->num1 += x; this->num2 += y; }
	int  RetrieveVertical() { return this->num1; }
	int RetrieveHorizontal() { return this->num2; }
	void Rotate();
private:
	int num1;
	int num2;
};

void Point::Rotate() {
	int tmp1 = this->num1;
	int tmp2 = this->num2;
	this->num2 = -tmp1;
	this->num1 = tmp2;
}