#include <iostream>
#include "nbtheory.h"
#include "osrng.h"
#include "PublicKeyAlgorithmBox.h"

using namespace CryptoPP;
using namespace std;

// #EEA()
bool PublicKeyAlgorithmBox::EEA(const Integer& a, const Integer& b, Integer& d,
		Integer& x, Integer& y) {
	if (b == 0) {
		d = a;
		x = 1;
		y = 0;
		if (d == 1) {
			return true;
		} else {
			return false;
		}
	} else {
		EEA(b, a % b, d, x, y);
		Integer x_s = x;
		x = y;
		y = x_s - (a / b) * x;
	}
	if (d == 1) {
		return true;
	} else {
		return false;
	}
} // EEA()

// #modularExponentation()
Integer PublicKeyAlgorithmBox::modularExponentation(const Integer& a,
		const Integer& b, const Integer& n) {
	Integer c = 0;
	Integer d = 1;
	int i = 0;
	int k = b.BitCount() - 1;

	while (i < b.BitCount()) {
		d = (d * d) % n;
		if (b.GetBit(k - i) == 1) {
			d = (d * a) % n;
		}
		i++;
	}
	return d;
} // modularExponentation()

// #multInverse()
bool PublicKeyAlgorithmBox::multInverse(const Integer& a, const Integer& n,
		Integer& a_inv) {
	Integer d, x, y;
	bool gcd = EEA(a, n, d, x, y);
	if (d != 1 || !gcd) {
		return false;
	} else {
		x = x < 0 ? (x + n) % n : x;
		a_inv = x;
		return true;
	}
} // multInverse()

// #witness()
bool PublicKeyAlgorithmBox::witness(const Integer& a, const Integer& n) {
	Integer u = n - 1, r = 0, d = 0, x = 0;
	while ((u % 2) == 0) {
		u = (u / 2);
		r++;
	}
	d = modularExponentation(a, u, n);
	for (int i = 0; i <= r; i++) {
		x = d;
		d = (d * d) % n;

		if (d == 1 && x != 1 && x != (n - 1)) {
			return true;
		}
	}
	if (d != 1) {
		return true;
	}
	return false;
} // witness()

// randomInteger()
Integer PublicKeyAlgorithmBox::randomInteger(const Integer& n) {
	return Integer("1");
}

// #millerRabinTest()
bool PublicKeyAlgorithmBox::millerRabinTest(Integer& n, unsigned int s) {
	NonblockingRng rng = NonblockingRng();
	Integer a;
	for (int i = 0; i < s; i++) {
		a = 1;
		while (a < 2) {
			a.Randomize(rng, (n - 1).BitCount());
		}
		if (witness(a, n)) {
			return false;
		}
	}
	return true;
} // millerRabinTest()

// #randomPrime()
unsigned int PublicKeyAlgorithmBox::randomPrime(Integer &p, unsigned int bitlen,
		unsigned int s) {
	NonblockingRng rng = NonblockingRng();
	int ctr = 0;
	while (true) {
		ctr++;
		p.Randomize(rng, bitlen);
		if (millerRabinTest(p, s)) {
			return ctr;
		}
	}
} // randomPrime()

// #randomPrime()
unsigned int PublicKeyAlgorithmBox::randomRabinPrime(Integer &p,
		unsigned int bitlen, unsigned int s) {
	NonblockingRng rng = NonblockingRng();
	while (true) {
		//bitlen?
		p.Randomize(rng, bitlen);
		if (p % 4 != 3) {
			continue;
		} else if (!millerRabinTest(p, s)) {
			continue;
		} else {
			return 0;
		}
	}
} // randomRabinPrime()

// #modPrimeSqrt()
bool PublicKeyAlgorithmBox::modPrimeSqrt(const Integer& y, const Integer& p,
		vector<Integer>& v) {
	if (p % 4 != 3) {
		return false;
	}
	Integer tmp = modularExponentation(y, (p + 1) / 4, p);
	v.push_back(tmp);
	v.push_back(p - tmp);
	return true;
}

Integer PublicKeyAlgorithmBox::euklid(const Integer& a, const Integer& b,
		vector<Integer>& q) {
	return Integer("1");
}

unsigned int PublicKeyAlgorithmBox::computeConvergents(const Integer& a,
		const Integer& b, vector<Integer>& c, vector<Integer>& d) {
	return 1;
}

// #sqrt()
bool PublicKeyAlgorithmBox::sqrt(const Integer& x, Integer& s) const {
	return false;
}

void PublicKeyAlgorithmBox::generateRSAParams(Integer& p, Integer& q,
		Integer& e, Integer& d, unsigned int bitlen, unsigned int s) {
	randomPrime(p, bitlen, s);
	randomPrime(q, bitlen, s);
	Integer phi_n = (p - 1) * (q - 1);
	NonblockingRng rng = NonblockingRng();
	Integer x, y;
	while (true) {
		e.Randomize(rng, 1, phi_n - 1);
		if(EEA(e, phi_n, d, x, y)){
			if(multInverse(e, phi_n, d)){
				break;
			}
		}
	}
}

int PublicKeyAlgorithmBox::calcDecDigits(const Integer &x) {
	Integer temp = x;
	int ctr = 1;
	while (temp > 10) {
		temp /= 10;
		ctr++;
	}
	return ctr;
}

Integer PublicKeyAlgorithmBox::exp(const Integer &base, Integer exponent) {
	if (exponent == 1) {
		return base;
	} else {
		return base * exp(base, exponent - 1);
	}
}

