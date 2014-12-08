#ifndef _DESCipher_h_
#define _DESCipher_h_

#include "BlockCipher.h"

class DESCipher : public BlockCipher {
private:
  /** Initial permutation IP. */
  static byte ip[64];

  /** Final permutation IP^{-1}. */
  static byte fp[64];

  /** Expansion vector. */
  static byte ev[48];

  /** Permuted choice 1. */
  static byte pc1[];

  /** Permuted choice 2. */
  static byte pc2[];

  /** S-Boxes 1-8. */
  static byte sbox[8][64];

  /** Permutation p. */
  static byte pp[32];

  /** Total rotations in key schedule. */
  static byte total_rot[16];

  /** Key schedule. */
  byte key_schedule[16][6];

public: 

  /**
   * Konstruktur.
   */
  DESCipher();

  /**
   * Destruktur.
   */
  ~DESCipher();

  /**
   * Compute the key schedule.
   *
   * @param encmode true => key schedule for encryption.
   */
  void computeKeySchedule(const byte *key, bool encmode=true);

  /**
   * Compute S-Box substitution.
   *
   * @param id number of S-Box
   * @param line line in S-Box
   * @param col column in S-Box
   *
   * @return S-Box value
   */
  byte computeSBox(byte id, byte line, byte col);

  /**
   * Decrypt a cipher text.
   *
   * @param cipher_text array to store cipher text
   * @param cipher_len length of the cipher text array
   * @param key key
   * @param key_len key length
   * @param plain_text plain text to be decrypted
   * @param plain_len length of the plain text
   *
   * @return number of decrypted bytes
   */
  virtual int decrypt(const byte* cipher_text, int cipher_len, 
                      const byte* key, int key_len,
                      byte* plain_text, int plain_len);

   /**
   * Encrypt a plain text.
   *
   * @param plain_text plein text to be encrypted
   * @param plain_len length of the plain text
   * @param key key
   * @param key_len key length
   * @param cipher_text array to store cipher text
   * @param cipher_len length of the cipher text array
   *
   * @return number of encrypted bytes
   */
  virtual int encrypt(const byte* plain_text, int plain_len, 
                      const byte* key, int key_len,
                      byte* cipher_text, int cipher_len);

  /**
   * Process a block.
   *
   * @param in_block input block
   * @param out_block output block
   */
  void processBlock(const byte* in_block, byte* out_block);

  /**
   * Feistel chiffre as used in the DES. 
   *
   * @param l_in left input (4 byte)
   * @param r_in right input (4 byte)
   * @param key round key (6 byte)
   * @param l_out left output (4 byte)
   * @param r_out right output (4 byte)
   * @param rnd round of DES (for debug output)
   */
  void feistel(const byte* l_in, 
               const byte* r_in, 
               const byte* key, 
               byte* l_out, 
               byte* r_out,
               int rnd=0);

  /**
   * Function f of the DES. 
   *
   * @param r_in right input (4 byte)
   * @param key round key (6 byte)
   * @param r_out right output (4 byte)
   * @param rnd round of DES (for debug output)
   */
  void functionF(const byte* r_in, 
                 const byte* key, 
                 byte* r_out,
                 int rnd=0);

  /**
   * Get the i-th bit of a byte array.
   *
   * @param array pointer to the byte array
   * @param array_len length of the array
   * @param position of the requested bit
   *
   * @return value of the bit at position pos
   */
  bool getBit(const byte* array, int array_len, int pos) const;

  /**
   * Compute a bit permutation of a byte array.
   *
   * @param p permutation to use
   * @param p_len length of the permutation
   * @param in_array input byte array
   * @param in_len length of the input byte array
   * @param out_array output byte array
   * @param out_len length of the output byte array
   * 
   */
  void permutate(const byte* p, int p_len, 
                 const byte* in_array, int in_len, 
                 byte* out_array, int out_len) const;

  /**
   * Print a byte field as bit array on the screen.
   *
   * @param bytefield
   * @param len length of the bytefield
   * @param block_len length of one bit block
   */
  void printBitField(const byte* bytefield, int len, int block_len=8) const;

  /**
   * Set the i-th bit of a byte array.
   *
   * @param array pointer to the byte array
   * @param array_len length of the array
   * @param pos position of the bit to be set
   * @param value 
   */
  void setBit(byte* array, int array_len, int pos, bool value) const;

}; // class DESCipher

#endif
