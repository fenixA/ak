#include <iostream>
#include <set>
#include "osrng.h"
#include "PublicKeyAlgorithmBox.h"

using namespace std;

void integerExercise() {
	/*********************************************************************
	 * Aufgabe 2.
	 *********************************************************************/
	Integer a = Integer(23975);
	Integer b = Integer("12345678900987654321");
	Integer c = Integer::Power2(10);

	cout << "Aufgabe 2: " << (a + c) * b % 50001 << endl << endl;
}

void eeaExercise() {
	/*********************************************************************
	 * Aufgabe 3.
	 *********************************************************************/
	cout << "Aufgabe 3" << endl << endl;
	PublicKeyAlgorithmBox toolBox = PublicKeyAlgorithmBox();
	Integer a, b, d, x, y;

	a = 2987;
	b = 1279865;
	toolBox.EEA(a, b, d, x, y);
	cout << "a)\t" << d << "\t" << x << "\t" << y << endl;

	a = 78845945;
	b = 2503417846;
	toolBox.EEA(a, b, d, x, y);
	cout << "b)\t" << d << "\t" << x << "\t" << y << endl;

	a = 57913313;
	b = 173739939;
	toolBox.EEA(a, b, d, x, y);
	cout << "c)\t" << d << "\t" << x << "\t" << y << endl;
}

void invExercise() {
	/*********************************************************************
	 * Aufgabe 4.
	 *********************************************************************/
	cout << "Aufgabe 4" << endl << endl;
	PublicKeyAlgorithmBox toolBox = PublicKeyAlgorithmBox();
	Integer a, n, inv;

	a = 10353;
	n = 820343;
	if (toolBox.multInverse(a, n, inv)) {
		cout << "a)\t" << inv << endl;
	} else {
		cout << "a)\tNo inverse!" << endl;
	}

	a = 10353;
	n = 820344;
	if (toolBox.multInverse(a, n, inv)) {
		cout << "b)\t" << inv << endl;
	} else {
		cout << "b)\tNo inverse!" << endl;
	}

	a = 562312;
	n = 57913313;
	if (toolBox.multInverse(a, n, inv)) {
		cout << "c)\t" << inv << endl;
	} else {
		cout << "c)\tNo inverse!" << endl;
	}

}

void modexpExercise() {
	/*********************************************************************
	 * Aufgabe 5.
	 *********************************************************************/
	cout << "Aufgabe 5" << endl << endl;
	PublicKeyAlgorithmBox toolBox = PublicKeyAlgorithmBox();
	Integer base, exp, n;

	base = 2;
	exp = 100000;
	n = 23;
	cout << "a)\t" << toolBox.modularExponentation(base, exp, n) << endl;

	base = 2343947997;
	exp = 765;
	n = 111;
	cout << "b)\t" << toolBox.modularExponentation(base, exp, n) << endl;
}

void randExercise() {
	/*********************************************************************
	 * Aufgabe 6.
	 *********************************************************************/
	cout << "Aufgabe 6" << endl << endl;
	Integer x;
	NonblockingRng rng = NonblockingRng();
	x.Randomize(rng, 128);
	cout << "128:\t" << x << endl;
	x.Randomize(rng, 1024);
	cout << "1024:\t" << x << endl;

}

void millerRabinExercise() {
	/*********************************************************************
	 * Aufgabe 7.
	 *********************************************************************/
	Integer a = Integer("279226292160650115722581212551219487007");
	Integer b = Integer("247278711133334795867191516244139839983");
	Integer c = Integer("192172622525902080249109244057747132167");
	Integer d = Integer("177387942943728133030691912202779547031");

	cout << "Aufgabe 7" << endl << endl;
	PublicKeyAlgorithmBox toolBox = PublicKeyAlgorithmBox();
	cout << "a:\t" << toolBox.millerRabinTest(a, 100) << endl;
	cout << "b:\t" << toolBox.millerRabinTest(b, 100) << endl;
	cout << "c:\t" << toolBox.millerRabinTest(c, 100) << endl;
	cout << "d:\t" << toolBox.millerRabinTest(d, 100) << endl;
}

int main(int argc, char** argv) {

	integerExercise();
	eeaExercise();
	invExercise();
	modexpExercise();
	randExercise();
	millerRabinExercise();

	return 0;

}
