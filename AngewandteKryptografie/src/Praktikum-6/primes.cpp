/*
 * primes.cpp
 */

#include <cassert>
#include <cmath>
#include <iostream>
#include <iomanip>
#include "FortunaGenerator.h"
#include "MillerRabinTest.h"
#include "filters.h" // StringSink
#include "hex.h" // HexEncoder
#include <unistd.h>

using namespace std;

void millerRabin() {

	cout << endl << "Miller-Rabin Test" << "=================" << endl;

		MillerRabinTest *mrt = new MillerRabinTest;
		PRNG *gen = new FortunaGenerator;

		string n1 = "249236727971798483921811058804041930204535828339";
		string n2 = "167376539261987877304745111417636335723391598799";
		string n3 = "207241657224647904979925877995751997643166331621";
		string n4 = "203681457354349143050092586190992078578082388049";
		Integer c1(n1.c_str());
		Integer c2(n2.c_str());
		Integer c3(n3.c_str());
		Integer c4(n4.c_str());
		unsigned int s = 50;
		cout << endl << "Aufgabe 4 B:)";
		cout << endl << n1 << " => " <<  mrt->isPrime(gen, c1, s);
		cout << endl << n2 << " => " <<  mrt->isPrime(gen, c2, s);
		cout << endl << n3 << " => " <<  mrt->isPrime(gen, c3, s);
		cout << endl << n4 << " => " <<  mrt->isPrime(gen, c4, s) << endl;

		cout << endl << "Aufgabe 5 B: 2^121)" << endl
				<< mrt->boundedExponentation(7, 43, Integer::Power2(121));
		cout << endl << "Aufgabe 5 B: 2^120)" << endl
				<< mrt->boundedExponentation(7, 43, Integer::Power2(120)) << endl;

		string n5("346158389003024161132823470747012309343112001349179903402673");
		Integer c5(n5.c_str());
		cout << endl;
		cout << "Aufgabe 6 B:" << endl << "Basis: " << mrt->searchBase(c5, 29) << endl;

		string ipp1("2183814375991796599109312252753832343");
		Integer ippn1(ipp1.c_str());
		string ipp2("1329227995784915872903807060280344577");
		Integer ippn2(ipp2.c_str());
		string ipp5 ("346158389003024161132823470747012309343112001349179903402673");
		Integer ippn5(ipp5.c_str());
		Integer ipp3 = 7;
		Integer ipp4 = 43;
		Integer ipp6 = 113;
		Integer ipp7 = 29;
		cout << endl;
		cout << "Aufgabe 7 B:" << endl;
		cout << "isPerfectPower 5 A: " << mrt->isPerfectPower(ippn1, ipp3, ipp4) << endl;
		cout << "isPerfectPower 5 B: " << mrt->isPerfectPower(ippn2, ipp3, ipp4) << endl;
		cout << "isPerfectPower 6  : " << mrt->isPerfectPower(ippn5, ipp6, ipp7)<< endl;

		Integer rn512;
		Integer rn1024;
		Integer rn2048;
		Integer rn4096;

		int counter = 0;
		int counter2 = 0;
		unsigned int quali = 10;
		cout << endl << "Aufgabe 8:" << endl;
		do
		{
			rn512 = gen->getInteger(64);
			counter++;

		} while (!mrt->isPrime(gen, rn512, quali));

		cout << counter <<": Zufallszahl der Laenge 512: " << rn512;
		counter = 0;

		do
		{
			rn1024 = gen->getInteger(128);
			counter++;

		} while (!mrt->isPrime(gen, rn1024, quali));

		cout << endl <<  counter << ": Zufallszahl der Laenge 1024: " << rn1024;
		counter = 0;

		do
		{
			rn2048 = gen->getInteger(256);
			counter++;
		} while (!mrt->isPrime(gen, rn2048, quali));

		cout << endl << counter << ": Zufallszahl der Laenge 2048: " << rn2048;
		counter = 0;

		do
		{
			rn4096 = gen->getInteger(512);
			counter++;
		} while (!mrt->isPrime(gen, rn4096, quali));

		cout << endl << counter << ": Zufallszahl der Laenge 4096: " << rn4096;
		counter = 0;
}

void fortuna() {
	cout << "Fortuna PRNG"
		 << "============"
		 << endl;

	//byte seed[8];
	//string hexSeed = "7ab2af1a4561abf8";
	byte seed[8] = {0x7a, 0xb2, 0xaf, 0x1a, 0x45, 0x61, 0xab, 0xf8};

	 /*StringSource(hexSeed, true,
				new HexDecoder(new ArraySink(seed, sizeof(seed))
								)
		);
		*/

	FortunaGenerator *gen = new FortunaGenerator;

	gen->reseed(seed, sizeof(seed));
	byte buffer[1009];

	for (int i = 0; i < sizeof(buffer); i++)
	{
		buffer[i] = 0;
	}

	gen->getBlock(buffer,1000);
	int ausgabe = 0;
	cout << endl << "Aufgabe 2 F:)" << endl;
	for (int i = 0; i < 1000; i++)
	{
		if( ausgabe == 16)
		{
			cout << endl;
			ausgabe = 0;
		}
		ausgabe ++;
		cout << (unsigned int) buffer[i] << " ";
	}

	sleep(1);
	cout << endl;
	gen->getBlock(buffer, (unsigned int) 1000);
	ausgabe = 0;
	cout << "Aufgabe 2 H:)" << endl;
	for (int i = 0; i < 1000; i++)
	{
		if( ausgabe == 16)
				{
					cout << endl;
					ausgabe = 0;
				}
				ausgabe ++;
		cout << (unsigned int) buffer[i] << " ";
	}
		cout << endl;
}

int main() {
	cout << "Generierung von Primzahlen" << endl
		 << "=========================="
		 << endl;

	fortuna();
	millerRabin();

	return 0;
}
