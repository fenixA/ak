/*
 * RabinAttack.cpp
 */

#include "PublicKeyAlgorithmBox.h"
#include "RabinDecryptor.h"
#include "RabinAttack.h"
#include "osrng.h"
#include <iostream>

using namespace std;

RabinAttack::RabinAttack() {
}

RabinAttack::~RabinAttack() {
}

int RabinAttack::factorize(const Integer& n, Integer& f, int max_tries,
		RabinDecryptor& rabin_dec) {
	PublicKeyAlgorithmBox toolBox = PublicKeyAlgorithmBox();
	Integer r, y, x, eea_x, eea_y;
	NonblockingRng rng = NonblockingRng();
	for (int i = 0; i < max_tries; i++) {
		r.Randomize(rng, 1, n - 1);
		y = toolBox.modularExponentation(r, 2, n);
		if (!rabin_dec.compute(y, x)) {
			continue;
		} else if ((x % n) == (r % n)) {
			continue;
		} else {
			toolBox.EEA((x - r), n, f, eea_x, eea_y);
			return i + 1;
		}
	}
	return -1;
}
