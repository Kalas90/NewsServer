/* myserver.cc: sample server program */
#include "server.h"
#include "connection.h"
#include "messagehandler.h"
#include "connectionclosedexception.h"

#include <memory>
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]){
	if (argc != 2) {
		cerr << "Usage: myserver port-number" << endl;
		exit(1);
	}
	
	int port = -2;
	try {
		port = stoi(argv[1]);
	} catch (exception& e) {
		cerr << "Wrong port number. " << e.what() << endl;
		exit(1);
	}
	
	Server server(port);
	if (!server.isReady()) {
		cerr << "Server initialization error." << endl;
		exit(1);
	}

	cout << "init succesfull" << endl;
	
	while (true) {
		MessageHandler handler(server); 
		try {
			int code = handler.recvCode();
			if(code > 0) {
				cout << "received code" << endl;
			}

		} catch (ConnectionClosedException&) {
				server.deregisterConnection(handler.getConnection());
				cout << "Client closed connection" << endl;
			
		}
	}
}
