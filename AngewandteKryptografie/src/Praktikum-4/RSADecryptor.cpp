/*
 * RSADecryptor.cpp
 */

#include "PublicKeyAlgorithmBox.h"
#include "RSADecryptor.h"

#include <iostream>

using namespace std;

RSADecryptor::RSADecryptor(const Integer& p, const Integer& q,
		const Integer& d) {
	this->d = d;
	this->p = p;
	this->q = q;
	this->n = p * q;
}

RSADecryptor::~RSADecryptor() {
}

// #compute()
bool RSADecryptor::compute(const Integer& y, Integer& x) const {
	if (y >= n) {
		return false;
	}
	PublicKeyAlgorithmBox toolBox = PublicKeyAlgorithmBox();
	x = toolBox.modularExponentation(y, this->d, this->n);
	return true;
}

// #crt()
bool RSADecryptor::crt(const Integer& y, Integer& x) const {
	if (y >= n) {
		return false;
	}
	PublicKeyAlgorithmBox toolBox = PublicKeyAlgorithmBox();
	Integer dp = this->d % (this->p - 1);
	Integer dq = this->d % (this->q - 1);
	Integer q_inv;
	toolBox.multInverse(q, p, q_inv);
	Integer m1 = toolBox.modularExponentation(y, dp, p);
	Integer m2 = toolBox.modularExponentation(y, dq, q);
	x = (q_inv * (m1 - m2) % p) * q + m2;

	return true;
}

// #garner()
bool RSADecryptor::garner(const Integer& y, Integer& x) const {
	if (y >= n) {
			return false;
		}

	Integer q_inv;

	PublicKeyAlgorithmBox toolBox = PublicKeyAlgorithmBox();
	Integer a = toolBox.modularExponentation(y, d, p);
	Integer b = toolBox.modularExponentation(y, d, q);
	toolBox.multInverse(q, p, q_inv);
	x = (((a - b) * q_inv) % p) * q + b;

	return true;
}
