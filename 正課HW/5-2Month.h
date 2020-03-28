// Name: ±i¥Ã©Ó	
// Date: 2020.03.26
// Last Update: 2020.03.26
// Problem statement: Design Month Class
#pragma once
class Month
{
public:
	Month();
	Month(char first, char second, char third);
	Month(int monthInt);
	~Month();
	void inputInt();
	void inputStr();
	void outputInt();
	void outputStr();
	Month nextMonth();
private:
	int month;
};

