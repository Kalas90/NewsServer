/* myserver.cc: sample server program */
#include "server.h"
#include "connection.h"
#include "commandhandler.h"
#include "databasehandler.h"
#include "connectionclosedexception.h"
#include "protocol.h"

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
	DatabaseHandler dbHandler;
	
	while (true) {
		shared_ptr<Connection> conn = server.waitForActivity();
		if (conn == nullptr){
			conn = make_shared<Connection>();
			server.registerConnection(conn);
			cout << "registered connection" << endl;
		}
		CommandHandler handler(conn, dbHandler);
		try {
			int code = handler.recvCode();
			switch(code) {
				case Protocol::COM_LIST_NG:
					handler.ansListNewsgroups();
					break;
				case Protocol::COM_CREATE_NG:
					handler.ansCreateNewsgroup();
					break;
				case Protocol::COM_DELETE_NG:
					handler.ansDeleteNewsgroup();
					break;
				case Protocol::COM_LIST_ART:
					handler.ansListArticles();
					break;
				case Protocol::COM_CREATE_ART:
					handler.ansCreateArticle();
					break;
				case Protocol::COM_DELETE_ART:
					handler.ansDeleteArticle();
					break;
				case Protocol::COM_GET_ART:
					handler.ansGetArticle();
					break;
				default:
					throw ConnectionClosedException();
					break;
			}

		} catch (ConnectionClosedException&) {
				server.deregisterConnection(handler.getConnection());
				cout << "Connection closed" << endl;
			
		}
	}
}
