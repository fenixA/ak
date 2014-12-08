#include <cassert>
#include <ctype.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include "VigenereCipher.h"

using namespace std;

// #main()
int main(int argc, char **argv) {
  VigenereCipher cipher;
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
   * Retrieving key.
   */
  for (i=0; i<strlen(argv[2]); i++) {
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
    c_shift = 'a';
  } // if
  else {
    cipher.encrypt(in_text, key, out_text);
    c_shift = 'A';
  } // else

  /*
   * Output result
   */
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
