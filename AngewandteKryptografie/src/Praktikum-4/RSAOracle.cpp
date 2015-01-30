/*
 * RSAOracle.cpp
 */

#include <cassert>
#include <iostream>
#include "RSAOracle.h"
#include "PublicKeyAlgorithmBox.h"

using namespace std;

RSAOracle::RSAOracle(Integer& p, Integer& q, Integer& d) {
	this->n = p * q;
	this->d = d;
}

RSAOracle::~RSAOracle() {
}

// #half()
bool RSAOracle::half(const Integer& y) const {
	PublicKeyAlgorithmBox toolBox = PublicKeyAlgorithmBox();

	if (toolBox.modularExponentation(y, d, n) <= n / 2) {
		return false;
	} else {
		return true;
	}
}

// #parity()
bool RSAOracle::parity(const Integer& y) const {
	return false;
}
