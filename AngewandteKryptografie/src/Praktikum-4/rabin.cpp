/*
 * rabin.cpp
 */

#include <iostream>
#include <vector>
#include "osrng.h"
#include "PublicKeyAlgorithmBox.h"
#include "RabinDecryptor.h"
#include "RabinEncryptor.h"
#include "RabinAttack.h"
#include <vector>

using namespace std;

// #rabinParameters()
void rabinParameters() {
	/*********************************************************************
	 * Aufgabe 9.
	 *********************************************************************/

	cout << endl << "Aufgabe 9" << endl << endl;
	PublicKeyAlgorithmBox toolBox = PublicKeyAlgorithmBox();
	Integer p;

	toolBox.randomRabinPrime(p, 256, 50);
	cout << "p:\t" << p << endl;
	toolBox.randomRabinPrime(p, 256, 50);
	cout << "q:\t" << p << endl;

}

// #sqrtModPrimeExercise()
void sqrtModPrimeExercise() {
	/*********************************************************************
	 * Aufgabe 10.
	 *********************************************************************/
	cout << endl << "Aufgabe 10" << endl << endl;
	Integer y, p;
	vector<Integer> v;

	PublicKeyAlgorithmBox toolBox = PublicKeyAlgorithmBox();

	y = 400040001;
	p = 884249923643;
	if (toolBox.modPrimeSqrt(y, p, v)) {
		cout << "a)\tv0 = " << v[0] << "\tv1 = " << v[1] << endl;
	}

	y = 644640535034;
	p = 868380007367;
	if (toolBox.modPrimeSqrt(y, p, v)) {
		cout << "b)\tv0 = " << v[2] << "\tv1 = " << v[3] << endl;
	}
}

// #rabinDemo()
void rabinDemo() {
	/*********************************************************************
	 * Aufgaben 11 und 12.
	 *********************************************************************/
	cout << endl << "Aufgabe 11 f)" << endl << endl;
	RabinEncryptor re = RabinEncryptor(
			Integer("728768879148869666628372866383")
					* Integer("1178365175275537416785439551531"), 1234);
	Integer x = Integer("234131892323212"), y, x2;
	vector<Integer> v;
	re.compute(x, y);
	cout << "y:\t" << y << endl;

	RabinDecryptor rd = RabinDecryptor(
			Integer("728768879148869666628372866383"),
			Integer("1178365175275537416785439551531"), 1234);

	rd.compute(y, v);
	cout << "v0:\t" << v[0] << endl;
	cout << "v1:\t" << v[1] << endl;
	cout << "v2:\t" << v[2] << endl;
	cout << "v3:\t" << v[3] << endl;

	cout << endl << "Aufgabe 12 c)" << endl << endl;
	v.clear();
	re.compute2(x, y);
	cout << "y:\t" << y << endl;

	if (rd.compute2(y, x2)) {
		cout << "x:\t" << x2 << endl;
	}
}

// #rabinAttack()
void rabinAttack() {
	/*********************************************************************
	 * Aufgabe 13.
	 *********************************************************************/
	cout << endl << "Aufgabe 13 b)" << endl << endl;
	RabinDecryptor rd = RabinDecryptor(
			Integer("728768879148869666628372866383"),
			Integer("1178365175275537416785439551531"), 1234);
	Integer f, n = Integer("728768879148869666628372866383")
			* Integer("1178365175275537416785439551531");
	RabinAttack ra = RabinAttack();
	int tries = ra.factorize(n, f, 1000, rd);
	if (tries == (-1)) {
		cout << "No factor found!";
	} else {
		cout << "f:\t" << f << "\tNoOfTries:\t" << tries << endl;
	}

}

// #main()
int main() {

	rabinParameters();
	sqrtModPrimeExercise();
	rabinDemo();
	rabinAttack();

	return 0;
}
