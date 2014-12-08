#ifndef _AffineCipher_h_
#define _AffineCipher_h_

#include "ClassicCipher.h"

/**
 * @class A class for the affine cipher.
 * @author Christoph Karg
 *
 * A class for the affine cipher.
 */
class AffineCipher : public ClassicCipher {
private:
  /**
   * Table containing the multiplicative inverses in Z_26.
   *
   * If the table entry equals 0, then the number is not invertable.
   */
  const static byte inverse_table[26];

public:
  /**
   * Decrypt a cipher text.
   *
   * @param cipher_text to be decrypted
   * @param key key
   * @param plain_text vector to store the resulting plain text
   *
   * @return number of decrypted bytes
   */
  virtual int decrypt(const vector<byte>& cipher_text, 
                      const vector<byte>&  key,
                      vector<byte>& plain_text);

   /**
   * Encrypt a plain text.
   *
   * @param plain_text plain text to be encrypted
   * @param plain_len length of the plain text
   * @param key key
   * @param key_len key length
   * @param cipher_text array to store cipher text
   * @param cipher_len length of the cipher text array
   *
   * @return number of encrypted bytes
   */
   int encrypt(const vector<byte>& plain_text,
                      const vector<byte>& key, 
                      vector<byte>& cipher_text);


  /**
   * Return the multiplicative inverse of a number in Z_26.
   *
   * @param a number to invert
   *
   * @return inverse of the number, if the number has such an inverse, 0,
   * otherwise.
   */
  int multInverse(byte a) const;

}; // AffineCipher

#endif
