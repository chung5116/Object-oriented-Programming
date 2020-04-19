// Name: ±i¥Ã©Ó	
// Date: 2020.04.16
// Last Update:2020.04.17
// Problem statement:  Design Polynomial Class
//#include"Polynomial.h"
//Polynomial::Polynomial() {
//	double d = 0;
//	this->degree = 0;
//	this->coef = new double[1];
//	this->coef[0] = d;
//}
//Polynomial::Polynomial(double* param, int size) {
//	degree = size - 1;
//	coef = new double[size];
//	for (int i = 0; i < size; i++)
//		coef[i] = param[i];
//}
//int Polynomial::mySize() {
//	return degree + 1;
//}
//double evaluate(const Polynomial& poly, const double& var) {
//	double val = 0;
//	double pow = 1;
//	for (int i = 0; i < poly.degree + 1; i++) {
//		val += pow * poly.coef[i];
//		pow *= var;
//	}
//	return val;
//}
//
//Polynomial& Polynomial::operator=(const Polynomial& p) {
//	this->degree = p.degree;
//	this->coef = new double[degree + 1];
//	for (int i = 0; i < degree + 1; i++) {
//		coef[i] = p.coef[i];
//	}
//	return (*this);
//}
//
//double& Polynomial::operator[](const size_t index){
//	return coef[index];
//}
//
//Polynomial Polynomial::operator+(const Polynomial& p) {
//	Polynomial res;
//	int maxdegree =  this->degree > p.degree ? this->degree : p.degree;
//	res.degree = maxdegree;
//	res.coef = new double[res.degree + 1];
//	for (int i = 0; i < res.degree+1; i++) {
//		res.coef[i] = 0;
//		if (i < this->degree + 1) {
//			res.coef[i] += this->coef[i];
//		}
//		if (i < p.degree + 1) {
//			res.coef[i] += p.coef[i];
//		}
//	}
//	return res;
//}
//Polynomial Polynomial::operator-(const Polynomial& p) {
//	Polynomial res;
//	int maxdegree = this->degree > p.degree ? this->degree : p.degree;
//	res.degree = maxdegree;
//	res.coef = new double[res.degree + 1];
//	for (int i = 0; i < res.degree + 1; i++) {
//		res.coef[i] = 0;
//		if (i < this->degree + 1) {
//			res.coef[i] += this->coef[i];
//		}
//		if (i < p.degree + 1) {
//			res.coef[i] -= p.coef[i];
//		}
//	}
//	return res;
//}
//Polynomial Polynomial::operator*(const Polynomial& p) {
//	Polynomial res;
//	res.degree = this->degree + p.degree;
//	res.coef = new double[res.degree + 1];
//	res.initializeCoef();
//	for (int i = 0; i < this->degree + 1; i++) {
//		for (int j = 0; j < p.degree + 1; j++) {
//			double tmpd = this->coef[i] * p.coef[j];
//			res.coef[i + j] += tmpd;
//		}
//	}
//	return res;
//}
//
//
//
//void Polynomial::initializeCoef() {
//	for (int i = 0; i < this->degree + 1; i++)
//		this->coef[i] = 0;
//}
//
//Polynomial operator+(const Polynomial& p, double d) {
//	Polynomial res;
//	res.degree = p.degree;
//	res.coef = new double[res.degree+1];
//	for (int i = 0; i < res.degree + 1; i++) {
//		res.coef[i] = p.coef[i];
//	}
//	res.coef[0] += d;
//	return res;
//}
//
//Polynomial operator-(const Polynomial& p, double d) {
//	Polynomial res;
//	res.degree = p.degree;
//	res.coef = new double[res.degree+1];
//	for (int i = 0; i < res.degree + 1; i++) {
//		res.coef[i] = p.coef[i];
//	}
//	res.coef[0] -= d;
//	return res;
// }
//
//Polynomial operator*(const Polynomial& p, double d) {
//	Polynomial res;
//	res.degree = p.degree;
//	res.coef = new double[res.degree + 1];
//	for (int i = 0; i < res.degree + 1; i++) {
//		res.coef[i] = p.coef[i];
//		res.coef[i] *= d;
//	}
//	return res;
// }
