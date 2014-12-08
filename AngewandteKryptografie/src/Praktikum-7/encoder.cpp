/*
 * encoder.cpp
 */
#include <iostream>
#include "MessageEncoder.h"
#include <integer.h>

using namespace std;
using namespace CryptoPP;

void encoderTest() {
	cout << "MessageEncoderTest" << endl <<
			"==================" << endl;

	MessageEncoder me;
	me.append(Integer("10892"));
	me.append("Hallo Welt!");
	me.append(Integer("459111231"));

	Integer i = me.getInteger(0);
	string s = me.getString(1);
	Integer j = me.getInteger(2);

	cout << "2b) encodeTest:" << i << " : " << s << " : " << j << endl;
	me.clear();

	me.append(Integer("98921323668113423232"));
	me.append("Kryptografie macht Spass!");
	me.append("Crypto++ ist eine Kryptografie-Bibliothek");
	me.append(Integer("456291260721096"));

	Integer b1 = me.getInteger(0);
	string b2 = me.getString(1);
	string b3 = me.getString(2);
	Integer b4 = me.getInteger(3);

	cout << "2d) encodeTest2:" << endl << b1 << endl << b2 << endl << b3 << endl << b4 << endl;

	me.clear();
	me.decode("6DB03BF70E#4963682062696E2065696E65205A65696368656E666F6C67652C20646965#207369636820617573207A776569205465696C656E207A7573616D6D656E7365747A74");

	 b1 = me.getInteger(0);
	 b2 = me.getString(1);
	 b3 = me.getString(2);

	cout << "2e) encodeTest3:" << endl << b1 << endl << b2 << endl << b3 << endl;
	string key = "ahVoh4naghie";
	string mac = "937A6984EE71C06E808AB996BF76C246AC29E198B6637B02C37ABDE92D6A46C8";
	cout << "2f) verify:" << me.verify(key,mac) << endl;;
}


int main(int argc, char **argv) {
	encoderTest();
	return 0;
}
