#include <cassert>
#include <cstring>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include "AffineCipher.h"

// Maximum length of plain/cipher text
#define MAX_LEN 4096

using namespace std;

int main(int argc, char **argv) {
  AffineCipher cipher;
  ifstream in_file;
  ofstream out_file;
  vector<byte> key, in_text, out_text;
  int i, j;
  unsigned char c, c_shift;

  /*
   * Check whether at least three arguments are given.
   */
  if (argc<4) {
    cerr << "Usage: " << argv[0] 
         << " [d|e] <key> <in_file> [<out_file>]"
         << endl;
    return 1;
  } // if

  /*
   * Check correctness of the key: it must be a lowercase string 
   * of length 2
   */
  if (strlen(argv[2])<2) {
    cerr << "Key length is not equal to 2" << endl; 
    return 1;
  } // if
 
  for (i=0; i<2; i++) {
    if (islower(argv[2][i])==0) {
      cerr << "key must be a lower case character." << endl;
      return 1;
    } // if
    else {
      key.push_back(argv[2][i]-'a');
    } // else
  } // for
  
  /* 
   * Read input file.
   */
  in_file.open(argv[3]);
  if (in_file==0) {
    cerr << "Could not open file >" << argv[3] << "<" << endl;
    return 1;
  } // if
  else {
    cipher.readStream(in_file, in_text);
    in_file.close();
  } // else

  /*
   * Encrypt/decrypt the input text.
   */
  if (strcmp(argv[1], "d")==0) {
    cipher.decrypt(in_text, key, out_text);
    c_shift='a';
  } // if
  else {
    cipher.encrypt(in_text, key, out_text);
    c_shift='A';
  } // else

  if (argc==5) {
    out_file.open(argv[4]);
    if (out_file==0) {
      cerr << "Could not open output file >" << argv[4] << "<" << endl;
      return 1;
    } // if
    else {
      cipher.writeStream(out_file, out_text, c_shift);
      out_file.close();
    } // else
  } // if
  else {
    cipher.writeStream(cout, out_text, c_shift);
  } // else


  return 0; 

} // main()
