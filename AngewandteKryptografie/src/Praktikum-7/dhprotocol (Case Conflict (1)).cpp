/*
 * DHProtocol.cpp
 */
#include <cassert>
#include <fstream>
#include <socketft.h>
#include "FortunaGenerator.h"
#include "MessageEncoder.h"
#include "DHProtocol.h"

using namespace std;
using namespace CryptoPP;

#define BUFFERSIZE 20000
#define PKSIZE 10

DHProtocol::DHProtocol(const string& param_file) {
	ifstream file;
	string data;
	MessageEncoder encoder;

	file.open(param_file.c_str());
	if (file.is_open() == false) {
		cout << "Could not open file: " << param_file << endl;
		assert(false);
	}

	file >> data;
	file.close();

	if (encoder.decode(data) == false) {
		cout << "Could not decode DH parameters." << endl;
		assert(false);
	}

	if (encoder.size() != 3) {
		cout << "Wrong number of DH parameters." << endl;
		assert(false);
	}

	q = encoder.getInteger(0);
	p = encoder.getInteger(1);
	alpha = encoder.getInteger(2);

	/*
	 cout << "q = " << q << endl;
	 cout << "p = " << p << endl;
	 cout << "alpha = " << alpha << endl;
	*/

}


void DHProtocol::alice(const string& host, unsigned int port) {

	// Socket for connecting the server Bob
	Socket client;

	int len;
	byte* buffer = new byte[BUFFERSIZE];
	string data;



	cout << "Acting as Alice." << endl;

		try {
			// Creating a socket ...
			client.Create();
			// ... and connecting to the server
			client.Connect(host.c_str(), port);

			/*
			 *  Note: if no connection can be established, an
			 *  exception is thrown. Otherwise, the socket is ready
			 *  to use.
			 */
			FortunaGenerator *gen = new FortunaGenerator;
			MessageEncoder me;




			// Receive r1 form the server
			len = client.Receive(buffer, BUFFERSIZE);
			data.assign((char*) buffer, len);
			me.decode(data);
			Integer r1 = me.getInteger(0);
			cout << "1. A empfangen von B: "<< r1 << endl;

			me.clear();
			//private key generate
			Integer pkey = gen->getInteger(PKSIZE);
			Integer modEx = modExp(alpha, pkey, p);

			// send
			me.append(modEx);
			string r2 = me.encode();
			client.Send((byte*)r2.c_str(), r2.length());
			cout << "2. A gesendet an B:   " << modEx << endl;

			// common key
			Integer r3 = modExp(r1, pkey, p);
			cout << "3. Gemeinsamer Key:" << r3 << endl;





		}
		catch (Socket::Err& err) {
			// Dump the error message, of an exception is thrown
			cout << "Error: " << err.GetWhat() << endl;
		}

		delete buffer;

}

void DHProtocol::bob(unsigned int port) {
	cout << "Acting as Bob." << endl;

	Socket server, client;
	int len;

	server.Create();
	server.Bind(port);
	server.Listen();

	while (true) {
		try {

			if (server.Accept(client) == true) {
				serverBob(client);
			}
		} catch (Socket::Err& err) {
			cout << "Fehler: " << err.GetWhat() << endl;
		}
	}
	server.CloseSocket();
}

bool DHProtocol::serverBob(Socket client) {

	int len;
	byte* buffer = new byte[BUFFERSIZE];
	string data;



	try {
			cout << "Accepting incoming connection..." << endl;

			FortunaGenerator *gen = new FortunaGenerator;
			MessageEncoder me;


			//private key generate
			Integer pkey = gen->getInteger(PKSIZE);
			Integer modEx = modExp(alpha, pkey, p);

			// send r1
			me.append(modEx);
			string r1 = me.encode();
			client.Send((byte*)r1.c_str(), r1.length());
			cout << "1. B gesendet an A:   " << modEx << endl;

			// Receive r2 form the server
			len = client.Receive(buffer, BUFFERSIZE);
			data.assign((char*) buffer, len);
			me.decode(data);
			Integer r2 = me.getInteger(0);
			cout << "2. B empfangen von A: "<< r2 << endl;

			//common key
			Integer r3 = modExp(r2, pkey, p);
			cout << "3. Gemeinsamer Key:" << r3 << endl;




				} catch (Socket::Err& err) {
			cout << "Error: " << err.GetWhat() << endl;
		}


	delete buffer;

}

void DHProtocol::oscar(unsigned int inport, const string& host, unsigned int port) {
	cout << "Acting as Oscar." << endl;

	Socket server, client;
	int len;

	server.Create();
	server.Bind(inport);
	server.Listen();

	while (true) {
		try {

			if (server.Accept(client) == true) {
				serverOscar(client, host, port);
			}
		} catch (Socket::Err& err) {
			cout << "Error: " << err.GetWhat() << endl;
		}
	}
	server.CloseSocket();
}

bool DHProtocol::serverOscar(Socket alice, const string& host, unsigned int port) {
	int len;
	byte* buffer = new byte[BUFFERSIZE];
	string data;
	Socket bob;

	try {

		// Creating a socket ...
		bob.Create();
		// ... and connecting to the server
		bob.Connect(host.c_str(), port);
			/*
			 *  Note: if no connection can be established, an
			 *  exception is thrown. Otherwise, the socket is ready
			 *  to use.
			 */
		cout << "Oscar Accepting incoming connection..." << endl;

		FortunaGenerator *gen = new FortunaGenerator;
		MessageEncoder me;

		//private key generate
		Integer pkey = gen->getInteger(PKSIZE);
		Integer modEx = modExp(alpha, pkey, p);

	//BOB
		// Receive r1 from bob
		len = bob.Receive(buffer, BUFFERSIZE);
		data.assign((char*) buffer, len);
		me.decode(data);
		Integer bob1 = me.getInteger(0);
		cout << "1. O empfangen von B: "<< bob1 << endl;

		me.clear();

		// send r2 to bob
		me.append(modEx);
		string bob2 = me.encode();
		bob.Send((byte*)bob2.c_str(), bob2.length());
		cout << "1. O gesendet an B:   " << modEx << endl;

		//common key
		Integer bob3 = modExp(bob1, pkey, p);


		me.clear();
	//ALICE

		// send r1
		me.append(modEx);
		string alice1 = me.encode();
		alice.Send((byte*)alice1.c_str(), alice1.length());
		cout << "1. O gesendet an A:   " << modEx << endl;

		// Receive r2 form the server
		len = alice.Receive(buffer, BUFFERSIZE);
		data.assign((char*) buffer, len);
		me.decode(data);
		Integer alice2 = me.getInteger(0);
		cout << "2. O empfangen von A: "<< alice2 << endl;

		//common key
		Integer alice3 = modExp(alice2, pkey, p);


		cout << "-------------------------------------------------------" << endl;
		cout << "3. Alice Key:" << alice3 << endl;
		cout << "3. Bob Key:  " << bob3 << endl;
		cout << "-------------------------------------------------------" << endl;

	} catch (Socket::Err& err) {
		cout << "Error: " << err.GetWhat() << endl;
	}


	delete buffer;


}


Integer DHProtocol::modExp(const Integer& a, const Integer& b,
		const Integer& n) const {
	Integer c = 0;
	Integer d = 1;
	int i = 0;
	int k = b.BitCount() - 1;

	while (i < b.BitCount()) {
		d = (d * d) % n;
		if (b.GetBit(k - i) == 1) {
			d = (d * a) % n;
		}
		i++;
	}
	return d;
}
