#include "BlumBlumShubGenerator.h"

BlumBlumShubGenerator::BlumBlumShubGenerator(const Integer& n, const Integer& seed) {
	this->n = n;
	this->s = (seed*seed) % n;
}

bool BlumBlumShubGenerator::getBit() {
	this->s = (this->s * this->s) % this->n;
	return this->s % 2;
}

