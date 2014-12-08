#include "ClassicCipher.h"

// #readStream()
int ClassicCipher::readStream
(
 istream& strm, 
 vector<byte>& out_text, 
 int block_len,
 unsigned char blender) {
  unsigned char c;

  out_text.clear();
  strm >> c;
  while (strm.eof()==false) {
    // cout << c;
    if (isalpha(c)!=0) {
      out_text.push_back(tolower(c)-'a');
    } // if
    strm >> c;
  } // while

  while ((out_text.size()%block_len)!=0) {
    out_text.push_back(blender-'a');
  } // while

  return out_text.size();
  
} // readStream()


// #writeStream()
int ClassicCipher::writeStream
(
 ostream& strm, 
 const vector<byte>& in_text, 
 unsigned char c_shift,
 int columns
) 
{
  int i, j;
  int out_len;

  j=0; out_len=0;
  for (i=0; i<in_text.size(); i++) {
    strm << (unsigned char)(in_text[i]+c_shift);
    out_len++;
    j++;
    if (j >= columns) {
      strm << endl;
      j=0;
    } // if
  } // for
  if (j!=0) {
    strm << endl;
  } // if

  return out_len;
  
} // writeStream()
 
