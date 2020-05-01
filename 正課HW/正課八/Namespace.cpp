// Name: ±i¥Ã©Ó	
// Date: 2020.04.22
// Last Update:2020.04.23
// Problem statement:  Namespace

#include <iostream>
#include"Password.h"
#include"User.h"
using namespace std;
using namespace Authenticate;

int main() {
	inputUserName();
	inputPassword();
	cout << "Your username is " << getUserName() <<" and your password is: ";
	cout<<getPassword() << endl;

    return 0;
}