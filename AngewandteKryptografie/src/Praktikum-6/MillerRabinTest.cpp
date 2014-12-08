
#include <iostream>
#include <cassert>
#include <cmath>
#include "MillerRabinTest.h"
#include "integer.h"

using namespace std;

Integer MillerRabinTest::boundedExponentation(const Integer& b,
		const Integer& e, const Integer& bound) const {
	Integer c = 0;
	Integer d = 1;
	int i = 0;
	int k = e.BitCount() - 1;

	while (i < e.BitCount())
	{
		d = (d * d);
		if (e.GetBit(k - i) == 1)
		{
			d = (d * b);
		}
		if (d > bound)
		{
			return bound + 1;
		}
		i++;
	}
	return d;

}

bool MillerRabinTest::isPerfectPower(const Integer& n, Integer& b,
		Integer& e) const {
	//e = 2;
	bool found = false;
	while (e < (n + 1).BitCount() && !found)
	{
		b = searchBase(n, e);
		if (b > 0)
		{
			found = true;
		} else {
			e++;
		}
	}
	return found;

}

Integer MillerRabinTest::modularExponentation(const Integer& a,
		const Integer& b, const Integer& n) const {
	Integer c = 0;
	Integer d = 1;
	int i = 0;
	int k = b.BitCount() - 1;

	while (i < b.BitCount())
	{
		d = (d * d) % n;
		if (b.GetBit(k - i) == 1)
		{
			d = (d * a) % n;
		}
		i++;
	}
	return d;
}

bool MillerRabinTest::witness(const Integer& a, const Integer& n) const {
	// Eingabebedingungen pruefen
	if (n <= 2 || !((n % 2) == 1) || a < 1 || a > (n - 1))
	{
		cout << endl << "Fehlerhafte Eingabe!" << endl;
		return false;
	}
	Integer u = n-1, r = 0, d = 0, x = 0;

	while((u % 2) == 0)
	{
		u = (u/2);
		r++;
	}

	d = modularExponentation(a, u, n);

	for (int i = 0; i <= r; i++)
	{
		x = d;
		d = (d * d) % n;

		if (d == 1 && x != 1 && x != (n - 1))
		{
			return true;
		}
	}
	if (d != 1)
	{
		return true;
	}
	return false;

}

bool MillerRabinTest::isPrime(PRNG* rng, const Integer& n,
		unsigned int s) const {
	if (n <= 2)
	{
		cout << "Fehlerhafte Eingabe!";
		return false;
	}
	if (n % 2 == 0)
	{
		return false;
	}

	Integer rand, test, b;
	for (int i = 0; i < s; i++)
	{
		rand = 1;
		while (rand < 2)
		{
			rand = rng->getInteger(n - 1);
		}

		if (Integer::Gcd(rand, n) > 1)
		{
			return false;
		}
		if (witness(rand, n))
		{
			return false;
		}

		if (isPerfectPower(n, rand, b))
		{
			return false;
		}
	}
	return true;
}

Integer MillerRabinTest::searchBase(const Integer& n, const Integer& e) const {

	Integer left = 2, right = n, b, x;
	do {
		b = left + (right - left) / 2;
		x = boundedExponentation(b, e, n);

		if (x > n)
		{
			right = b;
		} else {
			left = b;
		}
	} while ((x != n) && ((right - left) / 2 > 0));

	if (x == n)
	{
		return b;
	} else {
		return 0;
	}
}
