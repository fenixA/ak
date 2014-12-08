#include <cassert>
#include <map>
#include <iomanip>
#include <set>
#include <string>
#include <vector>
#include <math.h>
#include "VigenereBreaker.h"
#include "AffineBreaker.h"
#include <algorithm>

#define ALPHABET_LEN 26

// #analyse()
void VigenereBreaker::analyse(const vector<byte>& cipher_text) {
	int kasiski_len;

	// Check length of cipher text
	if (cipher_text.size() == 0)
		return;

	// Perform Kasiski test
	kasiski_len = kasiskiTest(cipher_text);

	cout << "Kasiski test: " << kasiski_len << endl;

} // analyse()

// #gcd()
int VigenereBreaker::gcd(int a, int b) const {
	int r;

	do {
		r = a % b;
		a = b;
		b = r;
	} while (r != 0);

	return a;

} // gcd()

// #gcd()
int VigenereBreaker::gcd(const vector<int>& v) const {
	int r, i;

	assert(v.size() > 0);

	if (v.size() == 1) {
		return v[0];
	} // if
	else {

		r = gcd(v[0], v[1]);
		i = 2;
		while ((r > 1) && (i < v.size())) {
			r = gcd(r, v[i]);
			i++;
		} // while

		return r;

	} // else

} // gcd()

// #kasiski()
int VigenereBreaker::kasiskiTest(const vector<byte>& cipher_text,
		int ngram_len) {
	vector<int>::iterator v_it;
	map<string, vector<int> > m;
	map<string, vector<int> >::iterator m_it;
	vector<byte>::const_iterator s_it;
	string s_cipher;

	s_it = cipher_text.begin();

	while (s_it != cipher_text.end()) {

		s_cipher += (char) (*s_it + 'A');

		s_it++;
	}

	int p = 0, cnt = 0;

	while ((p + ngram_len) < s_cipher.length()) {

		if (!m.count(s_cipher.substr(p, ngram_len))) {
			m.insert(
					pair<string, vector<int> >(s_cipher.substr(p, ngram_len),
							vector<int>()));
		}
		m.find(s_cipher.substr(p, ngram_len))->second.push_back(p);
		p++;
	}
	m_it = m.begin();
	map<int, int> frequencyOfGcd;

	while (m_it != m.end()) {

		if (m_it->second.size() > 2) {

			cout << (m_it->first) << ": ";

			vector<int> foo;

			v_it = m_it->second.begin();
			int bar = *v_it;
			while (v_it != m_it->second.end()) {

				cout << *v_it << " ";

				if (bar != *v_it) {
					foo.push_back(*v_it - bar);
				}
				v_it++;
			}

			cout << " -> " << gcd(foo) << endl;
			if (!frequencyOfGcd.count(gcd(foo))) {
				frequencyOfGcd.insert(pair<int, int>(gcd(foo), 0));
			}
			frequencyOfGcd.find(gcd(foo))->second++;
		}

		m_it++;
	}
	map<int, int>::iterator it = frequencyOfGcd.begin();
	map<int, int>::iterator end = frequencyOfGcd.end();

	int max_value = it->second;
	int devider = it->first;
	for (; it != end; ++it) {
		if (it->second > max_value) {
			max_value = it->second;
			devider = it->first;
		}
	}
	cout << "Devider:\t" << devider << "\tfrequency:\t" << max_value << endl;
	return devider;

} // kasiski()

// #coincidenceIndex()
float VigenereBreaker::coincidenceIndex(const vector<byte>& text) {
	map<byte, int> frequency_table = computeFrequency(text);
	map<byte, int>::iterator it = frequency_table.begin();
	float returnValue = 0;
	while (it != frequency_table.end()) {
		returnValue += (it->second * (it->second - 1));
		it++;
	}
	return (returnValue / (text.size() * (text.size() - 1)));
} // coincidenceIndex()

map<int, vector<byte> > VigenereBreaker::createVectorMap(
		const vector<byte>& cipher_text, int cols) {
	map<int, vector<byte> > text;
	vector<byte>::const_iterator it_c = cipher_text.begin();

	for (int i = 0; i < cols; i++) {
		text.insert(pair<int, vector<byte> >(i, vector<byte>()));
	}

	while (it_c != cipher_text.end()) {
		for (int i = 0; i < cols && (it_c != cipher_text.end()); i++) {
			text.find(i)->second.push_back(*it_c);
			it_c++;
		}
	}
	return text;
}

// #coincidenceTest()
bool VigenereBreaker::coincidenceTest(const vector<byte>& cipher_text, int cols,
		float threshold) {
	map<int, vector<byte> > text = createVectorMap(cipher_text, cols);

	bool flag = true;
	cout << endl << cols << "\t";
	for (int i = 0; i < cols; i++) {
		float tempIndex = coincidenceIndex(text.find(i)->second);
		cout << tempIndex << " ";
		if (!(tempIndex >= threshold)) {
			flag = false;
		}
	}
	if (flag) {
		cout << endl << boolalpha << flag;
	}

	return flag;
} // coincidenceTest()

// #mutualCoinIndex()
int VigenereBreaker::mutualCoinIndex(const vector<byte>& cipher_text, int cols,
		int col_i, int col_j, float threshold) {

	cout << endl
			<< "#---------------------------------------------------------------------------------------------------#"
			<< endl;
	cout << col_i << " : " << col_j << endl << "-------" << endl;

	map<int, vector<byte> > colMap = createVectorMap(cipher_text, cols);
	vector<byte> col_i_v = colMap.find(col_i)->second;
	vector<byte> col_j_v = colMap.find(col_j)->second;

	map<byte, int> frequency_table_i = computeFrequency(col_i_v);
	map<byte, int> frequency_table_j = computeFrequency(col_j_v);

	map<byte, int>::iterator it = frequency_table_i.begin();

	float index = 0;
	int shift = 0;

	for (int g = 0; g < ALPHABET_LEN; g++) {
		it = frequency_table_i.begin();
		float tempIndex = 0;
		while (it != frequency_table_i.end()) {
			if (frequency_table_j.find(((it->first) + g) % ALPHABET_LEN)
					!= frequency_table_j.end()) {
				tempIndex += frequency_table_j.find(
						((it->first) + g) % ALPHABET_LEN)->second
						* (it->second);
			}
			it++;
		}
		tempIndex /= (col_i_v.size() * col_j_v.size());
		if (tempIndex > index) {
			index = tempIndex;
			shift = g;
		}
		if (g % 5 == 0) {
			cout << endl;
		}
		cout << "(" << g << ")" << tempIndex << "\t";
	}
	cout << endl << "Max.: " << index << "\tThresh: " << threshold
			<< "\tShift: " << shift << endl;
	if (index >= threshold) {
		return shift;
	} else {
		return -1;
	}
} // mutualCoinIndex()

map<byte, int> VigenereBreaker::computeFrequency(const vector<byte>& text) {
	map<byte, int> m;
	vector<byte>::const_iterator v_it;
	for (int i = 0; i < ALPHABET_LEN; i++) {
		m.insert(pair<byte, int>((char) i, 0));
	}

	v_it = text.begin();
	while (v_it != text.end()) {
		m[*v_it] += 1;
		v_it++;
	}
	return m;
} // computeFrequency()
