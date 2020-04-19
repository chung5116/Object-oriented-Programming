// Name: ±i¥Ã©Ó	
// Date: 2020.04.01
// Last Update: 2020.04.03
// Problem statement: Operator overloading
#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include<math.h>
using namespace std;

class Complex
{
public:
	double realValue, imaginaryValue;

	Complex() {
		this->realValue = 0;
		this->imaginaryValue = 0;
	}
	//~Complex();
	Complex(double r) {
		this->realValue = r;
		this->imaginaryValue = 0;
	}
	//~Complex(double r);
	Complex(double r, double i) {
		this->realValue = r;
		this->imaginaryValue = i;
	}
	//~Complex(double r, double i);
	double real() {
		return this->realValue;
	}
	double imag() {
		return this->imaginaryValue;
	}
	double norm() {
		return sqrt(realValue * realValue + imaginaryValue * imaginaryValue);
	}
	friend double real(Complex c) {
		return c.realValue;
	}
	friend double imag(Complex c) {
		return c.imaginaryValue;
	}
	friend double norm(Complex c) {
		return sqrt(c.realValue * c.realValue + c.imaginaryValue * c.imaginaryValue);
	}
	Complex operator+(Complex c) {
		Complex res;
		res.realValue = this->realValue + c.realValue;
		res.imaginaryValue = this->imaginaryValue + c.imaginaryValue;
		return res;
	}
	Complex operator-(Complex c) {
		Complex res;
		res.realValue = this->realValue - c.realValue;
		res.imaginaryValue = this->imaginaryValue - c.imaginaryValue;
		return res;
	}
	Complex operator*(Complex c) {
		Complex res;
		res.realValue = (this->realValue * c.realValue) - (this->imaginaryValue * c.imaginaryValue);
		res.imaginaryValue = (this->realValue * c.imaginaryValue) + (this->imaginaryValue * c.realValue);
		return   res;
	}
	Complex operator/(Complex c) {
		Complex tmp = c;
		tmp.imaginaryValue *= -1;
		Complex numerator = (*this) * tmp;
		double denominator = (c.realValue * c.realValue) + (c.imaginaryValue * c.imaginaryValue);
		numerator.realValue /= denominator;
		numerator.imaginaryValue /= denominator;
		return numerator;
	}
	friend	Complex operator+(double d, Complex c) {
		Complex res = c;
		res.realValue = c.realValue + d;
		return   res;
	}
	friend Complex operator-(double d, Complex c) {
		Complex res = c;
		res.realValue = c.realValue - d;
		return   res;
	}
	friend Complex operator*(double d, Complex c) {
		Complex res = c;
		res.realValue = c.realValue * d;
		res.imaginaryValue = c.imaginaryValue * d;
		return   res;
	}
	friend Complex operator/(double d, Complex c) {

		Complex numerator = d * c;
		numerator.imaginaryValue *= -1;
		double denominator = c.realValue * c.realValue + c.imaginaryValue * c.imaginaryValue;
		numerator.realValue = numerator.realValue / denominator;
		numerator.imaginaryValue = numerator.imaginaryValue / denominator;
		return  numerator;
	}
	friend bool operator==(Complex c1, Complex c2) {
		if (c1.realValue == c2.realValue && c1.imaginaryValue == c2.imaginaryValue)
			return true;
		return false;
	}
	friend ostream& operator<<(ostream &strm, const Complex &c) {
		strm << c.realValue << " + " << c.imaginaryValue << "*i" << endl;
		return strm;
	}
	friend istream& operator>>(istream &strm,Complex &c) {
		double x, y;
		strm >> x >> y;
		c.realValue = x;
		c.imaginaryValue = y;
		return strm;
	}
};
/*----------------------------------------*/

/*Complex::Complex() {
	this->realValue = 0;
	this->imaginaryValue = 0;
}

Complex::Complex(double r) {
	this->realValue = r;
	this->imaginaryValue = 0;
}

Complex::Complex(double r, double i) {
	this->realValue = r;
	this->imaginaryValue = i;
}

double Complex::real() {
	return this->realValue;
}
double Complex::imag() {
	return this->imaginaryValue;
}
double Complex::norm() {
	return sqrt(realValue * realValue + imaginaryValue * imaginaryValue);
}

double real(Complex c) {
	return c.realValue;
}
double imag(Complex c) {
	return c.imaginaryValue;
}
double norm(Complex c) {
	return sqrt(c.realValue * c.realValue + c.imaginaryValue * c.imaginaryValue);
}

Complex Complex::operator+(Complex c) {
	Complex res;
	res.realValue = this->realValue + c.realValue;
	res.imaginaryValue = this->imaginaryValue + c.imaginaryValue;
	return res;
}
Complex Complex::operator-(Complex c) {
	Complex res;
	res.realValue = this->realValue - c.realValue;
	res.imaginaryValue = this->imaginaryValue - c.imaginaryValue;
	return res;
}
Complex Complex::operator*(Complex c) {
	Complex res;
	res.realValue = (this->realValue * c.realValue) - (this->imaginaryValue * c.imaginaryValue);
	res.imaginaryValue = (this->realValue * c.imaginaryValue) + (this->imaginaryValue * c.realValue);
	return   res;
}
Complex Complex::operator/(Complex c) {
	Complex tmp = c;
	tmp.imaginaryValue *= -1;
	Complex numerator = (*this) * tmp;
	double denominator = (c.realValue * c.realValue) + (c.imaginaryValue * c.imaginaryValue);
	numerator.realValue /= denominator;
	numerator.imaginaryValue /= denominator;
	return numerator;
}

Complex operator+(double d, Complex c) {
	Complex res = c;
	res.realValue = c.realValue + d;
	return   res;
}
Complex operator-(double d, Complex c) {
	Complex res = c;
	res.realValue = c.realValue - d;
	return   res;
}
Complex operator*(double d, Complex c) {
	Complex res = c;
	res.realValue = c.realValue * d;
	res.imaginaryValue = c.imaginaryValue * d;
	return   res;
}
Complex operator/(double d, Complex c) {

	Complex numerator = d * c;
	numerator.imaginaryValue *= -1;
	double denominator = c.realValue * c.realValue + c.imaginaryValue * c.imaginaryValue;
	numerator.realValue = numerator.realValue / denominator;
	numerator.imaginaryValue = numerator.imaginaryValue / denominator;
	return  numerator;
}

bool operator==(Complex c1, Complex c2) {
	if (c1.realValue == c2.realValue && c1.imaginaryValue == c2.imaginaryValue)
		return true;
	return false;
}


ostream& operator<<(ostream& strm, const Complex& c) {
	strm << c.realValue << " + " << c.imaginaryValue << "*i" << endl;
	return strm;
}
istream& operator>>(istream& strm, Complex& c) {
	double x, y;
	strm >> x >> y;
	c.realValue = x;
	c.imaginaryValue = y;
	return strm;
}*/
#endif // !COMPLEX_H