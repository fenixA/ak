/*
 * RSAEncryptor.cpp
 */

#include "PublicKeyAlgorithmBox.h"
#include "RSAEncryptor.h"

RSAEncryptor::RSAEncryptor(const Integer& n, const Integer& e) {
	this->n = n;
	this->e = e;
}

RSAEncryptor::~RSAEncryptor() {
}

bool RSAEncryptor::compute(const Integer& x, Integer& y) const {
	if (x >= n) {
		return false;
	}
	PublicKeyAlgorithmBox toolBox = PublicKeyAlgorithmBox();
	y = toolBox.modularExponentation(x, e, n);
	return true;
}
