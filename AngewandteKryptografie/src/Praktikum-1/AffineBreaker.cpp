#include <algorithm>
#include "AffineBreaker.h"
#include <stdio.h>

using namespace std;

// #analyse()
void AffineBreaker::analyse(vector<byte>& cipher_text, int nr_chars) {

	computeFrequency(cipher_text);
	multimap<float, byte>::reverse_iterator frequency_table_1;
	multimap<float, byte>::reverse_iterator frequency_table_2;

	byte ce, ct;

	frequency_table_1 = frequency_table.rbegin();
	frequency_table_2 = frequency_table.rbegin();
	for (int i = 0; i < nr_chars; i++) {
		ce = frequency_table_1->second;

		frequency_table_2 = frequency_table_1;
		frequency_table_2++;
		for (int j = i + 1; j < nr_chars; j++) {
			ct = frequency_table_2->second;
			breakCipher(ce, ct, cipher_text);
			frequency_table_2++;
		}
		frequency_table_1++;
	}
}  // analyse()

// #breakCipher()
void AffineBreaker::breakCipher(byte ce, byte ct,
		const vector<byte>& cipher_text) {

//4*a + b =  ce % 26
//19*a + b = ct % 26

//19*a + ce - 4*a = ct
//15*a + ce = ct
	int a = (ct - ce) * 7;

	while (a < 0) {
		a += 26;
	}

	int b = ce - 4 * a;

	while (b < 0) {
		b += 26;
	}

	b = b % 26;
	a = a % 26;

	cout << endl << "Cipher: " << (char) (ce + 'a') << " | "
			<< (char) (ct + 'a') << endl << (char) (a + 'a') << "(" << a << ")" << "|"
			<< (char) (b + 'a') << "(" << b << ")" << endl;
	int e = a;
	int c;
	int d = 26;
	while (e != 0) {
		c = e;
		e = d % e;
		d = c;

	}

	if (d != 1) {
		return;
	}

	vector<byte> key;
	vector<byte> plain_text;
	key.push_back(a);
	key.push_back(b);
	int plain_len = decrypt(cipher_text, key, plain_text);

	ostream& os = cout;
	if (plain_len > 50) {
		writeStream(os, plain_text, 'a', 50);
	} else {
		writeStream(os, plain_text, 'a', plain_len);
	}

	/*vector<byte>::iterator plain_text_it;

	 plain_text_it = plain_text.begin();
	 while (plain_text_it!=plain_text.end())
	 {
	 cout << *plain_text_it << " ";
	 plain_text_it++;
	 }
	 cout << endl;
	 */

} // breakCipher()
/*
 // #computeFrequency()
 void AffineBreaker::computeFrequency(vector<byte>& cipher_text) {

 map<byte, int> mha;
 map<byte, int>::iterator mha_it;

 multimap<float, byte>::reverse_iterator frequency_table_it;
 vector<byte>::const_iterator ct_it;

 ct_it = cipher_text.begin();
 while (ct_it != cipher_text.end()) {
 if (mha.count(*ct_it)) {
 mha[*ct_it]++;
 }
 if (!mha.count(*ct_it)) {
 mha.insert(pair<char, int>(*ct_it, 1));
 }
 ct_it++;
 }
 cout << endl;

 //map into multimap => gets sorted
 mha_it = mha.begin();
 while (mha_it != mha.end()) {
 frequency_table.insert(
 pair<float, byte>((*mha_it).second, (*mha_it).first));
 mha_it++;
 }

 //multimap sorted output
 frequency_table_it = frequency_table.rbegin();
 while (frequency_table_it != frequency_table.rend()) {
 cout << (char)(*frequency_table_it).second  << " | "
 << (*frequency_table_it).first  << endl;
 frequency_table_it++;
 }
 cout << endl;

 } // computeFrequency()
 */
void AffineBreaker::computeFrequency(vector<byte>& cipher_text) {
	map<byte, int> m;
	vector<byte>::iterator v_it;
	multimap<float, byte>::reverse_iterator frequency_table_it;
	v_it = cipher_text.begin();
	while (v_it != cipher_text.end()) {
		if (m.count(*v_it) > 0) {
			m[*v_it] = m[*v_it] + 1;
		} else {
			m.insert(pair<byte, int>(*v_it, 1));
		}
		v_it++;
	}
	map<byte, int>::iterator m_it;
	m_it = m.begin();
	while (m_it != m.end()) {
		frequency_table.insert(
				pair<float, byte>(
						(float) m_it->second / (float) cipher_text.size(),
						m_it->first));
		m_it++;
	}

//multimap sorted output
	frequency_table_it = frequency_table.rbegin();
	while (frequency_table_it != frequency_table.rend()) {
		cout << (char) (frequency_table_it->second + 'a') << " | "
				<< frequency_table_it->first << endl;
		frequency_table_it++;
	}
	cout << endl;
} // computeFrequency()
