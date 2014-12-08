#include <cassert>
#include <cstdlib>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include "VigenereBreaker.h"

using namespace std;

int main(int argc, char **argv) {
  VigenereBreaker vbreaker;
  ifstream in_file;
  vector<byte> key;
  vector<byte> cipher_text;
  int ngram_len;

  /*
   * Check whether at least one argument is given.
   */
  if (argc<=1) {
    cerr << "Usage: " << argv[0] 
         << " <in_file> [n-gram length]"
         << endl;
    exit(1);
  } // if

  /*
   * Read n-gram length 
   */
  ngram_len=0;
  if (argc>=3) {
    ngram_len=atoi(argv[2]);
  }
  if (ngram_len<=3) {
    ngram_len=3;
  }

  /* 
   * Read input file.
   */
  in_file.open(argv[1]);
  if (in_file==0) {
    cerr << "Could not open file >" << argv[1] << "<" << endl;
    exit(1);
  } // if
  else {
    vbreaker.readStream(in_file, cipher_text);
    in_file.close();
  } // else

  // Analyse the cipher text
  vbreaker.kasiskiTest(cipher_text, ngram_len);
  
  return 0; 

} // main()
