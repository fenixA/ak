#ifndef _AffineBreaker_h_
#define _AffineBreaker_h_

#include <map>
#include "AffineCipher.h"
#include "byte.h"

using namespace std;

/**
 * @class A class for breaking the affine cipher.
 * @author Christoph Karg
 *
 * A class for breaking the affine cipher.
 */
class AffineBreaker: public AffineCipher {
protected:
	/**
	 * Table to store character frequency.
	 */
	multimap<float, byte> frequency_table;

	/**
	 * Compute the character frequency of a given cipher text.
	 * @param cipher_text byte vector containing the cipher text
	 */
	void computeFrequency(vector<byte>& cipher_text);

	/**
	 * Break the given cipher text under the assumption that the
	 * characters "e" and "t" are encrypted as ce and ct, respectively.
	 * @param ce encryption of the character "e"
	 * @param ct encryption of the character "t"
	 * @param cipher_text cipher text to break
	 */
	void breakCipher(byte ce, byte ct, const vector<byte>& cipher_text);

public:

	virtual ~AffineBreaker() {
	}
	/**
	 * Analyse a given cipher text.
	 @param cipher_text cipher text to be analysed
	 @param nr_chars use nr_chars most frequent chars
	 */
	void analyse(vector<byte>& cipher_text, int nr_chars = 5);

};

#endif
