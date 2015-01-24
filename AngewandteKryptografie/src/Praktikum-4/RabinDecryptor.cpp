/*
 * RabinDecryptor.cpp
 */

#include <vector>
#include "RabinDecryptor.h"
#include "PublicKeyAlgorithmBox.h"

RabinDecryptor::RabinDecryptor(const Integer& p, const Integer& q,
		const Integer& padding) {
	this->p = p;
	this->q = q;
	this->padding = padding;
}

// #compute()
bool RabinDecryptor::compute(const Integer& y, vector<Integer>& xv) {
	PublicKeyAlgorithmBox toolBox = PublicKeyAlgorithmBox();
	Integer n = p * q, m_p, m_q;
	if (!(toolBox.multInverse(p, q, m_q) && toolBox.multInverse(q, p, m_p))) {
		return false;
	}
	vector<Integer> tempV;
	if (!(toolBox.modPrimeSqrt(y, p, tempV) && toolBox.modPrimeSqrt(y, q, tempV))) {
		return false;
	}

	xv.push_back((tempV[0] * q * m_p + tempV[2] * p * m_q) % n);
	xv.push_back((tempV[1] * q * m_p + tempV[2] * p * m_q) % n);
	xv.push_back((tempV[0] * q * m_p + tempV[3] * p * m_q) % n);
	xv.push_back((tempV[1] * q * m_p + tempV[3] * p * m_q) % n);
	return true;
}

bool RabinDecryptor::compute(const Integer& y, Integer& x) {
	return false;
}

// #compute2()
bool RabinDecryptor::compute2(const Integer& y, Integer& x) {
	return false;
}

RabinDecryptor::~RabinDecryptor() {
}

