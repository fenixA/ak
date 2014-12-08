#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctype.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "VigenereBreaker.h"

using namespace std;

int main(int argc, char **argv) {
  VigenereBreaker vbreaker;
  ifstream in_file;
  vector<byte> plain_text, cipher_text, key;
  int i, j, max_cols, shift, len, line;
  byte keychar;
  float threshold=0.065, ci;
  vector<vector<int> > keyshift;
  bool ok;

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
   * Read maximum number of columns to be analysed
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
  cout << "Threshold: " << threshold << endl;

  /*
   * Create key shift table 
   */
  for (i=0; i<max_cols; i++) {
    keyshift.push_back(vector<int>(max_cols, 0));
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
  for (i=0; i<max_cols; i++) {
    for (j=0; j<max_cols; j++) {
      if (i!=j) {
        shift = vbreaker.mutualCoinIndex(cipher_text,
                                         max_cols, i, j, 
                                         threshold);
        keyshift[i][j] = shift;
      } else {
        keyshift[i][j] = 0;
      }
    }
  }

  // return 0;
  cout << "Key shift table: " << endl << endl;

  cout << "i/j: ";
  for (i=0; i<max_cols; i++) {
    cout << setw(2) << i << "  ";
  }
  cout << endl;

  for (i=0; i<max_cols; i++) {
    cout << setw(2) << i << ": ";
    for (j=0; j<max_cols; j++) {
      cout << "[" << setw(2) << keyshift[i][j] << "]";
    }
    cout << endl;
  }

  for (line=0; line<max_cols; line++) {

    /*
     * Check line for correctness
     */
    ok=true;
    for (i=0; i<max_cols; i++) {
      if (keyshift[i][line]<0) {
        ok=false;
      }
    }

    if (ok==true) {

      cout << endl << "Decrypting with key in line " 
           << line << ":" << endl << endl;
      /*
       * Check the corresponding keys
       */
      for (i=0; i<26; i++) {
        cout << "  ";
        // Construct key 
        key=vector<byte>(max_cols,0);
        // cout << (char)('a'+i);
        for (j=0; j<max_cols; j++) {
          keychar = (i+keyshift[line][j]) % 26;
          key[j]=keychar;
          cout << (char)('a'+keychar);
        }
        cout << ": ";
        
        plain_text.clear();
        vbreaker.decrypt(cipher_text, key, plain_text);
        len = min(50,(int)plain_text.size());
        for (j=0; j<len; j++) {
          cout << (char)('a'+plain_text[j]);
        }
        cout << endl;
      }
    }
  }

  return 0; 

} // main()
