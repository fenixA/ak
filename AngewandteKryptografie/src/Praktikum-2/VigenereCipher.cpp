#include <cassert>
#include "VigenereCipher.h"

// #decrypt()
int VigenereCipher::decrypt(const vector<byte>& cipher_text,
		const vector<byte>& key, vector<byte>& plain_text) {
	int plain_len = 0, result = 0, key_cnt = 0;
	vector<byte>::const_iterator ct_it;
	vector<byte>::const_iterator key_it;

	key_it = key.begin();
	ct_it = cipher_text.begin();

	while (ct_it != cipher_text.end()) {

		result = (*ct_it - *key_it) % 26;

		while(result < 0) {
			result += 26;
		}

		plain_text.push_back(result);
		ct_it++;
		key_it++;
		plain_len++;
		key_cnt++;

		if (key_cnt == key.size()) {
			key_it = key.begin();
			key_cnt = 0;
		}
	}

	return plain_len;

} // decrypt()

// #encrypt()
int VigenereCipher::encrypt(const vector<byte>& plain_text,
		const vector<byte>& key, vector<byte>& cipher_text) {
	int cipher_len = 0, result = 0, key_cnt = 0;
	vector<byte>::const_iterator pl_it;
	vector<byte>::const_iterator key_it;

	key_it = key.begin();
	pl_it = plain_text.begin();

	while (pl_it != plain_text.end()) {

		result = (*pl_it + *key_it) % 26;
		cipher_text.push_back(result);
		pl_it++;
		key_it++;
		cipher_len++;
		key_cnt++;

		if (key_cnt == key.size()) {
			key_it = key.begin();
			key_cnt = 0;
		}
	}



	return cipher_len;

} // encrypt()

