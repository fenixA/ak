#include <cassert>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include "AffineBreaker.h"

using namespace std;

int main(int argc, char **argv) {
  AffineBreaker abreaker;
  ifstream in_file;
  ofstream out_file;
  vector<byte> key;
  vector<byte> cipher_text;
  int i, j;
  unsigned char c, c_shift;

  /*
   * Check whether at least one argument is given.
   */
  if (argc<=1) {
    cerr << "Usage: " << argv[0] 
         << " <in_file>"
         << endl;
    return 1;
  } // if

  /* 
   * Read input file.
   */
  in_file.open(argv[1]);
  if (in_file==0) {
    cerr << "Could not open file >" << argv[1] << "<" << endl;
    return 1;
  } // if
  else {
    abreaker.readStream(in_file, cipher_text);
    in_file.close();
  } // else

  // Analyse the cipher text
  abreaker.analyse(cipher_text);


  return 0; 

} // main()
