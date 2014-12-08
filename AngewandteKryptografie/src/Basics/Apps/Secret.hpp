/*
 * Secret.hpp
 *
 *  Created on: Apr 6, 2014
 *      Author: g77
 */

#ifndef SECRET_HPP_
#define SECRET_HPP_

#include <vector>

using namespace std;

class Secret {

private:
	vector<char> secret;

public:
	Secret();
	void decrypt();

};

#endif /* SECRET_HPP_ */
