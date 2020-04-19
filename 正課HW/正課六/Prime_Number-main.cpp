
#include"6.2-Prime_Number.h"
#include <iostream>

using namespace std;

int main()
{	
	int x = 3;
	int y = ++x;
	x = 3;
	int z = x++;
	PrimeNumber p1, p2(13);	
	PrimeNumber a = ++p1;
	PrimeNumber b = p2 ++;
	cout << a.get() << endl;
	cout << p1.get() << endl;
	cout << b.get() << endl;
	cout << p2.get() << endl;
	system("pause");
	return 0;
}
