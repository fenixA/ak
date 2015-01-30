/*
 * RSAAttack.cpp
 */

#include <vector>
#include "PublicKeyAlgorithmBox.h"
#include "RSAAttack.h"

using namespace std;

RSAAttack::RSAAttack() {
}

RSAAttack::~RSAAttack() {
}

// #factorizeN()
bool RSAAttack::factorizeN(const Integer& n, const Integer& phi_n, Integer& p,
		Integer& q) const {
	PublicKeyAlgorithmBox toolBox = PublicKeyAlgorithmBox();

	Integer b = phi_n - n - 1;

	Integer res = (b * b) - 4 * n;
	if (res < 0) {
		return false;
	}
	Integer sqrt;
	if (!toolBox.sqrt(res, sqrt))
		return false;
	Integer p_tmp = (-b + sqrt) / 2;
	Integer q_tmp = (-b - sqrt) / 2;
	if (p_tmp * q_tmp == n) {
		p = p_tmp;
		q = q_tmp;
		return true;
	}
	return false;
}

// #wienerAttack()
bool RSAAttack::wienerAttack(const Integer& n, const Integer& e, Integer& p,
		Integer& q) const {

	PublicKeyAlgorithmBox toolBox = PublicKeyAlgorithmBox();
	vector<Integer> c = vector<Integer>();
	vector<Integer> d = vector<Integer>();
	Integer phi_n;
	toolBox.computeConvergents(e, n, d, c);

	for (int i = 1; i < c.size(); i++) {
		if ((e * d[i] - 1) % c[i] == 0) {
			phi_n = (e * d[i] - 1) / c[i];
			if (factorizeN(n, phi_n, p, q)) {
				return true;
			}
		}
	}
	return false;
}

// #halfAttack()
Integer RSAAttack::halfAttack(const Integer& n, const Integer& e,
		const Integer& y, RSAOracle& rsa_oracle) const {
	PublicKeyAlgorithmBox box = PublicKeyAlgorithmBox();
	Integer l = n.BitCount();
	Integer lo;
	Integer hi;
	Integer mid;
	Integer tmp_y = y;
	vector<bool> h = vector<bool>();
	h.clear();
	Integer ctr = l * 10;
	for (int i = 0; i <= l; i++) {
		h.push_back(rsa_oracle.half(tmp_y));
		tmp_y = (tmp_y * box.modularExponentation(2, e, n)) % n;
	}
	lo = 0;
	hi = n * ctr;
	for (int i = 0; i < l; i++) {
		mid = (hi + lo) / 2;
		if (h[i]) {
			lo = mid;
		} else {
			hi = mid;
		}
	}

	return hi / ctr;

	/*
	 PublicKeyAlgorithmBox toolBox = PublicKeyAlgorithmBox();
	 Integer l = n.BitCount();
	 Integer lo;
	 Integer high;
	 Integer mid;
	 Integer tmp = y;
	 vector<bool> h =vector<bool>();
	 Integer mod = toolBox.modularExponentation(2,e,n);
	 for(int i = 0 ; i < l; i++){
	 h.push_back(rsa_oracle.half(tmp));
	 tmp = (tmp * mod )%n;

	 }
	 lo = 0;
	 high = n;
	 for(int i = 0 ; i < l; i++){
	 mid = (high+lo)/2;
	 if(h[i]){
	 lo = mid;
	 }
	 else{
	 high = mid;
	 }
	 }

	 return high;
	 */
}
