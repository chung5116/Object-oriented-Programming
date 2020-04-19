// Name: 張永承	
// Date: 2020.03.26
// Last Update: 2020.03.26
// Problem statement: Design Month Class
#include "Month.h"
#include<iostream>
#include<string>
using namespace std;

// 選擇月份回傳，若沒有則回傳1
int selectMonth(char first, char second, char third) {
	string tmpmonth = "   ";
		tmpmonth[0] = first;
		tmpmonth[1] = second;
		tmpmonth[2] = third;

	if (tmpmonth == "Jan") {
		return 1;
	}
	else if (tmpmonth == "Feb") {
		return 2;
	}
	else if (tmpmonth == "Mar") {
		return 3;
	}
	else if (tmpmonth == "Apr") {
		return 4;
	}
	else if (tmpmonth == "May") {
		return 5;
	}
	else if (tmpmonth == "Jun") {
		return 6;
	}
	else if (tmpmonth == "Jul") {
		return 7;
	}
	else if (tmpmonth == "Aug") {
		return 8;
	}
	else if (tmpmonth == "Sep") {
		return 9;
	}
	else if (tmpmonth == "Oct") {
		return 10;
	}
	else if (tmpmonth == "Nov") {
		return 11;
	}
	else if (tmpmonth == "Dec") {
		return 12;
	}
	else
		return 1;
}


Month::Month(){
	this->month = 1;
}

Month::Month(char first, char second, char third){
	this->month = selectMonth(first, second, third);
}

Month::Month(int monthInt){
	if (1 <= monthInt && monthInt <= 12)
		this->month = monthInt;
	else
		this->month = 1;
}


Month::~Month()
{
}

void Month::inputInt(){
	int monthInput = 0;
	std::cin >> monthInput;
	if (1 <= monthInput && monthInput <= 12)
		this->month = monthInput;
	else
		this->month = 1;
}

void Month::inputStr(){
	char first; char second; char third;
	cin >> first >> second >> third;
	this->month = selectMonth(first, second, third);
}

void Month::outputInt(){
	std::cout << this->month;
}

void Month::outputStr(){
	int x = this->month;
	if (x == 1) {
		cout << "Jan";
	}
	else if (x == 2) {
		cout << "Feb";
	}
	else if (x == 3) {
		cout << "Mar";
	}
	else if (x == 4) {
		cout << "Apr";
	}
	else if (x == 5) {
		cout << "May";
	}
	else if (x == 6) {
		cout << "Jun";
	}
	else if (x == 7) {
		cout << "Jul";
	}
	else if (x == 8) {
		cout << "Aug";
	}
	else if (x == 9) {
		cout << "Sep";
	}
	else if (x == 10) {
		cout << "Oct";
	}
	else if (x ==11) {
		cout << "Nov";
	}
	else if (x == 12) {
		cout << "Dec";
	}


}

Month Month::nextMonth(){
	return Month(this->month + 1);
}
