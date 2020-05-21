// Name: ±i¥Ã©Ó	
// Date: 2020.05.21
// Last Update:2020.05.21
// Problem statement: AbsoluteValue
#ifndef TEMPLATE_H
#define TEMPLATE_H




template<class  T>
float absoluteValue(T a, T b) {
	float res;
	if (a > b) {
		 res = (float)a - b;
	}
	else {
		 res = (float)b-a;
	}
	return res;
}


#endif // !TEMPLATE_H