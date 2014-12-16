#include <iomanip>
#include <iostream>
#include <fstream>
#include <cstring>
#include "DESCipher.h"

using namespace std;

// #main()
int main(int argc, char **argv) {
	DESCipher des;
	ifstream in_file;
	ofstream out_file;
	byte* in_text, *out_text;
	int in_len, out_len;
	byte key[8];
	int i, j;
	bool encmode;
	if (strcmp(argv[1], "test") == 0) {

		byte a[2] = { 0x2F, 0x6B };
		byte b[2] = { 0xF3, 0xC0 };

		byte p[13] = { 0x01, 0x03, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x06, 0x07,
				0x03, 0x02, 0x01 };
		byte in[] = { 0xD2 };
		byte out[5];

		encmode = true;
		des.computeKeySchedule(a, true);



		//des.permutate(p, 13, in, 1, out, 5);
		//des.printBitField(out, 40, 8);
		//des.printBitField(a, 16, 4);
		//des.printBitField(b, 16, 16);

		//des.setBit(b, 2, 15, true);
		//des.printBitField(b, 16, 16);

		return 0;
	}

	/*
	 * Check whether at least three arguments are given.
	 */
	if (argc < 4) {
		cerr << "Usage: " << argv[0] << " [d|e] <key> <in_file> [<out_file>]"
				<< endl;
		return 1;
	} // if

	/*
	 * Check correctness of the key: it must be a lowercase string
	 * of length 2
	 */
	if (strlen(argv[2]) != 16) {
		cerr << "Key must be an hexadecimal string of length 16." << endl;
		return 1;
	} // if

	j = 0;
	for (i = 0; i < 16; i += 2) {
		if ((isxdigit(argv[2][i]) == 0) || (isxdigit(argv[2][i]) == 0)) {
			cerr << "Invalid key (no hex digit)." << endl;
			return 1;
		} // if
		else {
			key[j] = 16 * des.hexToByte(argv[2][i])
					+ des.hexToByte(argv[2][i + 1]);
			j++;
		} // else
	} // for

	/*
	 *
	 */
	if (strcmp(argv[1], "d") == 0) {
		encmode = false;
	} // if
	else {
		encmode = true;
	} // else

	in_file.open(argv[3]);
	if (in_file == 0) {
		cerr << "Could not open file >" << "<" << endl;
		return 1;
	} // if
	else {
		in_len = des.readStream(in_file, in_text, !encmode);
		in_file.close();
	} // else

	out_text = new byte[in_len];
	if (encmode == true) {
		des.encrypt(in_text, in_len, key, 8, out_text, in_len);
	} // if
	else {
		des.decrypt(in_text, in_len, key, 8, out_text, in_len);
	} // else

	if (argc == 5) {
		out_file.open(argv[4]);
		if (out_file == 0) {
			cerr << "Could not open output file >" << argv[4] << "<" << endl;
			return 1;
		} // if
		else {
			des.writeStream(out_file, out_text, in_len, encmode);
			out_file.close();
		} // else
	} // if
	else {
		des.writeStream(cout, out_text, in_len, encmode);
	} // else
	  //  out_file.open("t.txt");

	delete[] in_text;
	delete[] out_text;

	return 0;

} // main()
