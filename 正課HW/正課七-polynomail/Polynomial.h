// Name: ±i¥Ã©Ó	
// Date: 2020.04.16
// Last Update:2020.04.18
// Problem statement:  Design Polynomial Class
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include<iostream>
#include<vector>
using namespace std;

class Polynomial {
private:
	int degree;
	vector<double>coef;
public:
	Polynomial();
	Polynomial(double* param, int size);
	int mySize();
	friend double evaluate(const Polynomial& poly, const double& var);
	//Polynomial& operator=(const Polynomial& p);
	void operator=(const Polynomial& p);
	double& operator[](const size_t index);
	Polynomial operator+(const Polynomial& p);
	Polynomial operator-(const Polynomial& p);
	Polynomial operator*(const Polynomial& p);
	Polynomial operator+(const double d);
	Polynomial operator-(const double d);
	Polynomial operator*(const double d);
	friend Polynomial operator+(const Polynomial& p, double d);
	friend Polynomial operator-(const Polynomial& p, double d);
	friend Polynomial operator*(const Polynomial& p, double d);
	void initializeCoef();
};

Polynomial::Polynomial() {
	double d = 0;
	this->degree = 0;
	coef.push_back(0);
}
Polynomial::Polynomial(double* param, int size) {
	degree = size - 1;
	for (int i = 0; i < size; i++)
		coef.push_back(param[i]);
}
int Polynomial::mySize() {
	return degree + 1;
}
double evaluate(const Polynomial& poly, const double& var) {

	double val = 0;
	double pow = 1;
	for (int i = 0; i < poly.degree + 1; i++) {
		val += pow * poly.coef[i];
		pow *= var;
	}
	return val;
}

void Polynomial::operator=(const Polynomial& p) {
	this->degree = p.degree;
	coef.resize(p.degree + 1, 0);
	for (int i = 0; i < degree + 1; i++) {
		coef[i] = (p.coef[i]);
	}
}

double& Polynomial::operator[](const size_t index) {
	return coef[index];
}

Polynomial Polynomial::operator+(const Polynomial& p) {
	Polynomial res;
	int maxdegree = this->degree > p.degree ? this->degree : p.degree;
	res.degree = maxdegree;
	res.coef.resize(res.degree + 1, 0);
	for (int i = 0; i < res.degree + 1; i++) {
		if (i < this->degree + 1) {
			double d = this->coef[i];
			res.coef[i] += d;
		}
		if (i < p.degree + 1) {
			double d = p.coef[i];
			res.coef[i] += d;
		}
	}
	return res;
}
Polynomial Polynomial::operator-(const Polynomial& p) {
	Polynomial res;
	int maxdegree = this->degree > p.degree ? this->degree : p.degree;
	res.degree = maxdegree;
	res.coef.resize(res.degree + 1, 0);
	for (int i = 0; i < res.degree + 1; i++) {
		if (i < this->degree + 1) {
			double d = this->coef[i];
			res.coef[i] += d;
		}
		if (i < p.degree + 1) {
			double d = p.coef[i];
			res.coef[i] -= d;
		}
	}

	return res;
}
Polynomial Polynomial::operator*(const Polynomial& p) {
	Polynomial res;
	res.degree = this->degree + p.degree;
	res.coef.resize(res.degree + 1, 0);
	for (int i = 0; i < this->degree + 1; i++) {
		for (int j = 0; j < p.degree + 1; j++) {
			double tmpd = this->coef[i] * p.coef[j];
			res.coef[i + j] += tmpd;
		}
	}
	return res;
}

Polynomial Polynomial::operator+(const double d) {
	Polynomial res;
	res.degree = this->degree;
	res.coef.resize(res.degree + 1, 0);
	for (int i = 0; i < degree + 1; i++)
		res.coef[i] = (this->coef[i]);
	res.coef[0] += d;
	return res;
}
Polynomial Polynomial::operator-(const double d) {
	Polynomial res;
	res.degree = this->degree;
	res.coef.resize(res.degree + 1, 0);
	for (int i = 0; i < degree + 1; i++)
		res.coef[i]  =(this->coef[i]);
	res.coef[0] -= d;
	return res;
}
Polynomial Polynomial::operator*(const double d) {
	Polynomial res;
	res.degree = this->degree;
	res.coef.resize(res.degree + 1, 0);
	for (int i = 0; i < degree + 1; i++) {
		res.coef[i] = (this->coef[i]);
		res.coef[i] *= d;
	}
	return res;
}


void Polynomial::initializeCoef() {
	for (int i = 0; i < this->degree + 1; i++)
		this->coef[i] = 0;
}

Polynomial operator+(const Polynomial& p, double d) {
	Polynomial res;
	res.degree = p.degree;
	res.coef.resize(p.degree + 1, 0);

	for (int i = 0; i < res.degree + 1; i++) {
		double tmpd = p.coef[i];
		res.coef[i] = tmpd;
	}
	res.coef[0] += d;
	return res;
}

Polynomial operator-(const Polynomial& p, double d) {
	Polynomial res;
	res.degree = p.degree;
	res.coef.resize(res.degree + 1, 0);
	for (int i = 0; i < res.degree + 1; i++) {
		double tmpd = p.coef[i];
		res.coef[i] = tmpd;
	}
	res.coef[0] -= d;
	return res;
}

Polynomial operator*(const Polynomial& p, double d) {
	Polynomial res;
	res.degree = p.degree;
	res.coef.resize(res.degree + 1, 0);
	for (int i = 0; i < res.degree + 1; i++) {
		double tmpd = p.coef[i];
		res.coef[i] = tmpd;
		res.coef[i] *= d;
	}
	return res;
}

#endif // !POLYNOMIAL_H