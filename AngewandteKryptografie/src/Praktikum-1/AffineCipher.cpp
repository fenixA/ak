#include <cassert>
#include "AffineCipher.h"

// #decrypt()
int AffineCipher::decrypt
(
 const vector<byte>& cipher_text, 
 const vector<byte>&  key,
 vector<byte>& plain_text)
{
	int plain_len = 0;
	vector<byte>::const_iterator ct_it;
	vector<byte>::const_iterator key_it;

	key_it = key.begin();
	byte key1 = *key_it;
	key_it++;
	byte key2 = *key_it;

	ct_it = cipher_text.begin();
	while (ct_it!=cipher_text.end())
		{

			int result = multInverse(key1) * (*ct_it - key2)%26;
			while(result < 0)
			{
				result += 26;
			}

			plain_text.push_back(result);

			ct_it++;
			plain_len++;

		}


	return plain_len;


} // decrypt()


// #encrypt()
int AffineCipher::encrypt
(
 const vector<byte>& plain_text,
 const vector<byte>& key, 
 vector<byte>& cipher_text
)
{
		int cipher_len = 0;
		vector<byte>::const_iterator pt_it;
		vector<byte>::const_iterator key_it;

		key_it = key.begin();
		byte key1 = *key_it;
		key_it++;
		byte key2 = *key_it;

		pt_it = plain_text.begin();
		while (pt_it!=plain_text.end())
			{

				cipher_text.push_back((key1 * *pt_it + key2)%26);
				pt_it++;
				cipher_len++;
			}



		return cipher_len;
} // encrypt()


// #multInverse()
int AffineCipher::multInverse(byte a) const {
  if (a<26) {
    return inverse_table[a];
  } // if
  else {
    return 0;
  } // else
} // multInverse()


// #inverse_table
const byte AffineCipher::inverse_table[26] = { 
  0,  // 0
  1,  // 1
  0,  // 2
  9,  // 3
  0,  // 4
  21, // 5
  0,  // 6
  15, // 7
  0,  // 8
  3,  // 9
  0,  // 10
  19, // 11
  0,  // 12
  0,  // 13
  0,  // 14
  7,  // 15
  0,  // 16
  23, // 17
  0,  // 18
  11, // 19
  0,  // 20
  5,  // 21
  0,  // 22
  17, // 23
  0,  // 24
  25  // 25
};
