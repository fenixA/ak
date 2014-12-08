
/*
 * FortunaGenerator.cpp
 *
 *  Created on: 20.04.2011
 *      Author: chkarg
 */

#include <iostream>
#include <fstream>
#include "filters.h"
#include "sha.h"
#include "aes.h"
#include "modes.h"
#include "hex.h"
#include "files.h"
#include "FortunaGenerator.h"

using namespace std;

FortunaGenerator::FortunaGenerator() {
	for (int i = 0; i < sizeof(key); i++) {
		key[i] = 0;
	}

	for (int i = 0; i < sizeof(cntr); i++) {
		cntr[i] = 0;
	}

	seeded = false;
	last_reseed = 0;
}

bool FortunaGenerator::incCntr() {
 /*	bool done = false;
	int i = 0;
	byte check = 0;
	while (!done) {
		check = cntr[i];
		cntr[i]++;
		if (cntr[i] < check) {
			i++;
		} else {
			done = true;
		}
		if (i == sizeof(cntr)) {
			return false;
		}
	}
	return true;
	*/

	Integer counter;
	for(int i = 0; i < sizeof(cntr); i++)
	{
		counter = counter + (cntr[i] * Integer::Power2(8*i));
	}
	counter += 1;
	for(int i = 0; i < sizeof(cntr); i++)
	{
		cntr[i] = counter.GetByte(i);
	}
	if(sizeof(cntr) < 16)
	{
		return true;
	}
	else{
		return false;
	}

}

void FortunaGenerator::reseed(byte* seed, unsigned int size) {
	byte data[sizeof(key) + size];

	for (int i = 0; i < sizeof(key); i++)
	{
		data[i] = key[i];
	}
	for (int j = 0; j < size; j++)
	{
		data[j+sizeof(key)] = seed[j];
	}

	SHA256 hash;
	ArraySource(data, sizeof(data), true,
			new HashFilter(hash, new ArraySink(key, sizeof(key))));

	incCntr();
	seeded = true;
	last_reseed = getTimeStamp();
}

bool FortunaGenerator::getBit() {

	byte b = getByte();
	return b % 2;
	/*byte gen[16];

	this->generateBlocks(gen, (unsigned int) 1);

	// Key erneuern
	byte nKey[32];
	this->generateBlocks(nKey, 2);
	for (int i = 0; i < sizeof(key); i++)
	{
		key[i] = nKey[i];
	}

	// Speicher leeren
	for (int i = 0; i < sizeof(gen); i++)
	{
		gen[i] = 0;
	}
	for(int j = 0; j < sizeof(nKey); j++)
	{
		nKey[j] = 0;
	}

	return ((gen[0] >> 7) & 1);
	*/
}

byte FortunaGenerator::getByte() {
	byte rand[1];
	rand[0] = 0;
	getBlock(rand,1);
	return rand[0];

	/*
	byte gen[16];

	this->generateBlocks(gen, (unsigned int) 1);

	// Key erneuern
	byte nKey[32];
	this->generateBlocks(nKey, 2);
	for (int i = 0; i < sizeof(key); i++)
	{
		key[i] = nKey[i];
	}

	// Speicher leeren
	for (int i = 0; i < sizeof(gen); i++)
	{
		gen[i] = 0;
	}
	for(int j = 0; j < sizeof(nKey); j++)
	{
		nKey[j] = 0;
	}
	*/
}

void FortunaGenerator::generateBlocks(byte* buffer, unsigned int n) {

	if ((getTimeStamp() - last_reseed) > 500 || !seeded) {
		byte seed[32];
		FILE *urandom;
		urandom = fopen("/dev/urandom", "r");
		for (int i = 0; i < sizeof(seed); i++)
		{
			seed[i] = fgetc(urandom);
		}
		fclose(urandom);

		reseed(seed, sizeof(seed));
	}

	// cntr pruefen
	unsigned int check = 0;
	for (int i = 0; i < sizeof(cntr); i++)
	{
		if ((unsigned int) cntr[i] == 0)
		{
			check++;
		}
	}

	if (check == 16)
	{
		cout << "Fehler in der Initialisierung des Generators";
		return;
	}

	//Puffer leeren
	for (int i = 0; i < sizeof(buffer); i++)
	{
		buffer[i] = 0;
	}

	// Bloecke generieren, in Puffer schreiben
	byte data[16];
	ECB_Mode<AES>::Encryption aes;
	aes.SetKey(key, sizeof(key));
	for (int i = 0; i < n; i++)
	{
		ArraySource(cntr, sizeof(cntr), true,
				new StreamTransformationFilter(aes,
						new ArraySink(data, sizeof(data))));

		for (int j = 0; j < sizeof(data); j++)
		{
			buffer[(i * sizeof(data)) + j] = data[j];
		}

		incCntr();
	}
}

void FortunaGenerator::getBlock(byte* buffer, unsigned int n) {

	// Fehlerhafte Werte abfangen
	if(n < 0 || n > 1048576)
	{
		cout << "Inkorrekte Länge!";
		return;
	}

	// Blockanzahl und Arraygroesse
	unsigned int blocks = 0, count = 0;

	while (blocks < n)
	{
		blocks += 16;
		count++;
	}

	//Bloecke generieren, in Puffer schreiben
	byte gen[blocks];

	this->generateBlocks(gen, (unsigned int) count);

	for (int i = 0; i < n; i++)
	{
		buffer[i] = gen[i];
	}

	// Key erneuern
	byte nKey[32];
	this->generateBlocks(nKey, 2);
	for (int i = 0; i < sizeof(key); i++)
	{
		key[i] = nKey[i];
	}

	// Speicher leeren
	for (int i = 0; i < (sizeof(gen) || i < sizeof(nKey)); i++)
	{
		gen[i] = 0;
		nKey[i] = 0;
	}

}

uint32_t FortunaGenerator::getTimeStamp() const {
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

