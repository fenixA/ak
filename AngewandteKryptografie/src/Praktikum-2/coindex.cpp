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
  vector<byte> cipher_text;
  int i, max_cols;
  float threshold=0.065;

  /*
   * Check whether at least one argument is given.
   */
  if (argc<3) {
    cerr << "Usage: " << argv[0] 
         << " <in_file> <max_cols> [threshold]"
         << endl;
    exit(1);
  } // if

  /*
   * Read maximum number oc columns to be analysed
   */
  max_cols=0;
  max_cols=atoi(argv[2]);
  if (max_cols<=0) {
    max_cols=5;
  }

  /*
   * Read threshold value 
   */
  if (argc>=4) {
    threshold=atof(argv[3]);
  }
  if (threshold<=0.0) {
    threshold=0.065;
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
  for (i=1; i<=max_cols; i++) {
    vbreaker.coincidenceTest(cipher_text, i, threshold);
  }
  
  return 0; 

} // main()
