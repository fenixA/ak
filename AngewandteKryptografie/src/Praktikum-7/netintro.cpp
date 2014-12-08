#include <iostream>
#include <socketft.h>
#include "MessageEncoder.h"

using namespace std;
using namespace CryptoPP;

// Maximum size of the receive buffer
#define MAXSIZE 100000

void alice(string host, unsigned int port) {
	// Socket for connecting the server Bob
	Socket client;
	// Buffer for reading data from the socket
	byte* buffer = new byte[MAXSIZE];
	byte* buffer2 = new byte[MAXSIZE];
	byte* buffer3 = new byte[MAXSIZE];
	// length of the received data
	int len=0;
	// helper string
	string data;
	// The message which Alice want to send to Bob
	string msg("Hello Bob! How are you?");

	string data_int;
	MessageEncoder me;
	int len_int=0;

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

		// Send message to the server
		client.Send((byte*)msg.c_str(), msg.length());

		// Receive data form the server
		len = client.Receive(buffer, MAXSIZE);
		data.assign((char*) buffer, len);
		cout << data << endl;

		cout << "Zahlen" <<endl;


		me.append(Integer("10232"));
		me.append(Integer("8934"));
		string msg_int = me.encode();

		client.Send((byte*)msg_int.c_str(), msg_int.length());
		len_int = client.Receive(buffer2, MAXSIZE);
		data_int.assign((char*) buffer2 , len_int);

		//sum empfangen
		me.clear();
		me.decode(data_int);
		Integer i = me.getInteger(0);
		cout << "Ergebnis: " << i << endl;

	}
	catch (Socket::Err& err) {
		// Dump the error message, of an exception is thrown
		cout << "Error: " << err.GetWhat() << endl;
	}

	// Don't forget to release the allocated memory
	delete buffer3;
	delete buffer2;
	delete buffer;

}

bool bob(Socket alice) {
	byte* buffer = new byte[MAXSIZE];
	byte* buffer2 = new byte[MAXSIZE];

	int len;
	string msg="Hi Alice. I am fine!";
	string data;
	string data_int;
	int len_int;

	try {
		cout << "Accepting incoming connection..." << endl;

		len = alice.Receive(buffer, MAXSIZE);
		data.assign((char*) buffer, len);
		cout << data << endl;

		alice.Send((byte*) msg.c_str(), msg.length());





		MessageEncoder me;
		len_int = alice.Receive(buffer2, MAXSIZE);
		data_int.assign((char*) buffer2, len_int);

		me.decode(data_int);

		Integer i = me.getInteger(0);
		Integer j = me.getInteger(1);
		Integer sum = i + j;

		//ergebnis zurücksenden
		me.clear();
		me.append(sum);
		string msg_int = me.encode();
		alice.Send((byte*)msg_int.c_str(), msg_int.length());
		cout << "gesendet: " << sum << endl;

	} catch (Socket::Err& err) {
		cout << "Error: " << err.GetWhat() << endl;
	}
	delete buffer2;
	delete buffer;

	return true;
}

void serverBob(int port) {
	// Socket for the server
	Socket server;
	// Socket for the connection client
	Socket client;

	cout << "Acting as Bob." << endl;

	// Create the server socket
	server.Create();
	// Bind to the given port
	server.Bind(port);
	// Listen on the port and wait for an incoming connection
	server.Listen();

	/*
	 * The server does not stop. This is, after the communication
	 * with Alice is finished, the server resets its data and waits
	 * for another connection.
	 */
	while (true) {

		try {
			/*
			 * On a connection, the client socket is initialized
			 * and given the function which performs the data exchange
			 */
			if (server.Accept(client) == true) {
				bob(client);
			}

		} catch (Socket::Err& err) {
			cout << "Error: " << err.GetWhat() << endl;
		}
	}

	// Close the socket (actually this will never happen!
	server.CloseSocket();
}

void help(string name) {
	cout << "Usage: " << name << " <mode>" << endl << endl;
	cout << "Modes:" << endl;
	cout << "  Alice <hostname> <port>" << endl;
	cout << "  Bob <port>" << endl;
}

int main(int argc, char **argv) {
	/*
	 * Depending on the command line arguments, the program
	 * acts as Alice or Bob
	 */
	if (argc < 2) {
		help(argv[0]);
		return 1;
	}

	string mode = argv[1];

	/*
	 * Act as Alice.
	 */
	if (mode == "Alice") {
		if (argc<3) {
			help(argv[0]);
			return 1;
		} else {
			string host(argv[2]);
			int port = atoi(argv[3]);
			alice(host, port);
			return 0;
		}
	}

	/*
	 * Act as Bob.
	 */
	if (mode == "Bob") {
		if (argc<2) {
			help(argv[0]);
			return 1;
		} else {
			int port = atoi(argv[2]);
			serverBob(port);
			return 0;
		}
	}

	help(argv[0]);
	return 0;
}
