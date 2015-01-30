/*
 * rsa.cpp
 */

#include <iostream>
#include "PublicKeyAlgorithmBox.h"
#include "RSAEncryptor.h"
#include "RSADecryptor.h"
#include "RSAAttack.h"
#include "RSAOracle.h"

using namespace std;

// #rsaParameters()
void rsaParameters() {
	/*********************************************************************
	 * Aufgabe 15.
	 *********************************************************************/
	//cout << endl << "Aufgabe 15" << endl << endl;
	PublicKeyAlgorithmBox toolBox = PublicKeyAlgorithmBox();
	Integer p, q, e, d;
	toolBox.generateRSAParams(p, q, e, d);

}

// #rsaDemo()
void rsaDemo() {
	/*********************************************************************
	 * Aufgabe 16.
	 *********************************************************************/
	Integer p = Integer("15192846618168946907");
	Integer q = Integer("10041530829891794273");
	Integer e = Integer("141290156426204318982571851806193576543");
	Integer d = Integer("73707354481439936713886319521045114527");
	Integer x = Integer("79372353861768787619084471254314002875");
	Integer y = Integer("47915958473033255778832465116435774510");

	cout << endl << "Aufgabe 16" << endl << endl;
	RSAEncryptor enc = RSAEncryptor(p * q, e);
	Integer res;
	enc.compute(x, res);
	cout << "enc:\t\t" << res << endl;

	RSADecryptor dec = RSADecryptor(p, q, d);
	Integer res2;
	dec.compute(res, res2);
	cout << "dec:\t\t" << res2 << endl;
	res2 = 0;
	dec.garner(res, res2);
	cout << "dec garner:\t" << res2 << endl;
	res2 = 0;
	dec.crt(res, res2);
	cout << "dec crt:\t" << res2 << endl;
}

//#sqrtExercise()
void sqrtExercise() {
	/*********************************************************************
	 * Aufgabe 17.
	 *********************************************************************/
	cout << endl << "Aufgabe 17" << endl << endl;
	Integer y1 = Integer("3157242151326374471752634944");
	PublicKeyAlgorithmBox toolBox = PublicKeyAlgorithmBox();
	Integer s;
	toolBox.sqrt(y1, s);
	cout << "s:\t" << s << endl;

	Integer y2 = Integer("11175843681943819792704729");
	Integer y3 = Integer("3343229819990029117723");
	s = 0;
	toolBox.sqrt(y2, s);
	cout << "s:\t" << s << endl;
	s = 0;
	toolBox.sqrt(y3, s);
	cout << "s:\t" << s << endl;

}

// #factorizingAttack()
void factorizingAttack() {
	/*********************************************************************
	 * Aufgabe 18.
	 *********************************************************************/
	cout << endl << "Aufgabe 18" << endl << endl;
	PublicKeyAlgorithmBox toolBox = PublicKeyAlgorithmBox();

	Integer n = Integer("127869459623070904125109742803085324131");
	Integer phi_n = Integer("127869459623070904102412837477002840200");
	RSAAttack attack = RSAAttack();
	Integer p, q;
	attack.factorizeN(n, phi_n, p, q);
	cout << "p:\t" << p << endl;
	cout << "q:\t" << q << endl;
	cout << "p*q:\t" << p * q << endl;
}

// #euklidExercise()
void euklidExercise() {
	/*********************************************************************
	 * Aufgabe 19.
	 *********************************************************************/
	cout << endl << "Aufgabe 19" << endl << endl;
	Integer a = Integer("39");
	Integer b = Integer("112");
	PublicKeyAlgorithmBox toolBox = PublicKeyAlgorithmBox();
	vector<Integer> v = vector<Integer>();
	Integer d = toolBox.euklid(a, b, v);
	vector<Integer>::iterator v_it;
	v_it = v.begin();
	cout << "d: " << d << endl;
	cout << "{ ";
	while (v_it != v.end()) {
		cout << *v_it << " ";
		v_it++;
	}
	cout << "}" << endl;

}
// #convergentsExercise()
void convergentsExercise() {
	/*********************************************************************
	 * Aufgabe 20.
	 *********************************************************************/

	cout << endl << "Aufgabe 20" << endl << endl;
	PublicKeyAlgorithmBox toolBox = PublicKeyAlgorithmBox();
	vector<Integer> c = vector<Integer>();
	vector<Integer> d = vector<Integer>();
	Integer a = Integer("39");
	Integer b = Integer("112");
	toolBox.computeConvergents(a, b, c, d);
	vector<Integer>::iterator v_it;

	v_it = c.begin();
	cout << "c = { ";
	while (v_it != c.end()) {
		cout << *v_it << " ";
		v_it++;
	}

	cout << "}" << endl;

	v_it = d.begin();
	cout << "d = { ";
	while (v_it != d.end()) {
		cout << *v_it << " ";
		v_it++;
	}

	cout << "}" << endl;

}

// #wienerAttack()
void wienerAttack() {
	/*********************************************************************
	 * Aufgabe 21.
	 *********************************************************************/

	cout << endl << "Aufgabe 21" << endl << endl;

	Integer n = Integer("224497286580947090363360894377508023561");
	Integer e = Integer("163745652718951887142293581189022709093");

	RSAAttack attack = RSAAttack();
	Integer p, q;
	attack.wienerAttack(n, e, p, q);
	cout << "p: " << p << endl;
	cout << "q: " << q << endl;
}

// #oracleExercise()
void oracleExercise() {
	/*********************************************************************
	 * Aufgabe 22.
	 *********************************************************************/
	cout << endl << "Aufgabe 22" << endl << endl;
	Integer p = Integer("16015510136412338011");
	Integer q = Integer("12177032305856164321");
	Integer d = Integer("946975621");
	Integer y1 = Integer("116415012259126332853105614449093205668");
	Integer y2 = Integer("74304303162215663057995326922844871006");
	Integer y3 = Integer("102949691974634609941445904667722882083");
	Integer y4 = Integer("42549620926959222864355800078420537413");
	RSAOracle ora = RSAOracle(p, q, d);
	cout << ora.half(y1);
	cout << ora.half(y2);
	cout << ora.half(y3);
	cout << ora.half(y4);
	cout << endl;
}

// #halfAttack()
void halfAttack() {
	/*********************************************************************
	 * Aufgabe 23.
	 *********************************************************************/
	cout << endl << "Aufgabe 23" << endl << endl;

	Integer p = Integer("12889769717276679053"), q = Integer(
			"17322528238664264177"), d = Integer(
			"149154082258429024247010774747829057473"), e = Integer(
			"55051594731967684255289987977028610689"), x = Integer(
			"167092961114842952923160287194683529938"), y;

	RSAAttack attacker = RSAAttack();
	RSAOracle oracle = RSAOracle(p, q, d);
	RSAEncryptor rsa = RSAEncryptor(p * q, e);

	rsa.compute(x, y);
	cout << "enc:\t\t" << y << endl;
	Integer res = attacker.halfAttack(p * q, e, y, oracle);
	cout << "dec halfAttack:\t" << res << endl << endl;
}

// #main()
int main() {
	rsaParameters();
	rsaDemo();
	sqrtExercise();
	factorizingAttack();
	euklidExercise();
	convergentsExercise();
	wienerAttack();
	oracleExercise();
	halfAttack();
	return 0;
}

