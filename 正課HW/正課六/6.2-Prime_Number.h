// Name: ±i¥Ã©Ó	
// Date: 2020.04.01
// Last Update: 2020.04.01
// Problem statement: Class Design
class PrimeNumber {
public:
	int value;
	int get();
	PrimeNumber();
	PrimeNumber(int _value);
	PrimeNumber & operator++();
	PrimeNumber operator++(int);
	PrimeNumber & operator--();
	PrimeNumber operator--(int);
	int larger(int value);
	int smaller(int value);
};