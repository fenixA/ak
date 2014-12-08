/*
 * Secet.cpp
 *
 *  Created on: Apr 6, 2014
 *      Author: g77
 */

#include <iostream>
#include <iomanip>
#include <string>
#include "Secret.hpp"


using namespace std;

Secret::Secret() {


	secret.push_back(67);
	secret.push_back(111);
	secret.push_back(110);
	secret.push_back(103);
	secret.push_back(114);
	secret.push_back(97);
	secret.push_back(116);
	secret.push_back(117);
	secret.push_back(108);
	secret.push_back(97);
	secret.push_back(116);
	secret.push_back(105);
	secret.push_back(111);
	secret.push_back(110);
	secret.push_back(115);
	secret.push_back(33);
	secret.push_back(32);
	secret.push_back(89);
	secret.push_back(111);
	secret.push_back(117);
	secret.push_back(32);
	secret.push_back(102);
	secret.push_back(105);
	secret.push_back(110);
	secret.push_back(105);
	secret.push_back(115);
	secret.push_back(104);
	secret.push_back(101);
	secret.push_back(100);
	secret.push_back(32);
	secret.push_back(116);
	secret.push_back(104);
	secret.push_back(101);
	secret.push_back(32);
	secret.push_back(66);
	secret.push_back(97);
	secret.push_back(115);
	secret.push_back(105);
	secret.push_back(99);
	secret.push_back(115);
	secret.push_back(32);
	secret.push_back(101);
	secret.push_back(120);
	secret.push_back(101);
	secret.push_back(114);
	secret.push_back(99);
	secret.push_back(105);
	secret.push_back(115);
	secret.push_back(101);
	secret.push_back(33);
	secret.push_back(33);

}

void Secret::decrypt() {

	for	(int i = 0;	i< secret.size(); i++) {
		cout << secret[i];

	}

	cout<< endl << endl	;
}
