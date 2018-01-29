/* myclient.cc: sample client program */
#include "connection.h"
#include "connectionclosedexception.h"
#include "clientcommandhandler.h"


#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]) {
	if (argc != 3) {
		cerr << "Usage: myclient host-name port-number" << endl;
		exit(1);
	}


	int port = -1;
	try {
		port = stoi(argv[2]);
	} catch (exception& e) {
		cerr << "Wrong port number. " << e.what() << endl;
		exit(1);
	}
	
	shared_ptr<Connection> conn = make_shared<Connection>(argv[1], port);

	if (!conn->isConnected()) {
		cerr << "Connection attempt failed" << endl;
		exit(1);
	}
	ClientCommandHandler clientHandler(conn);
	cout << "Waiting for input. Type help for manual" << endl;
	string sel;
	while (getline(cin, sel)) {
		try {
			if(sel == "help") {
				cout << "------------------------" << endl;
				cout << "(1) - Create a newsgroup" << endl;
				cout << "(2) - List all newsgroups" << endl;
				cout << "(3) - Delete a newsgroup" << endl;
				cout << "(4) - Create an article" << endl; 
				cout << "(5) - List articles in a newsgroup" << endl;
				cout << "(6) - Delete an article" << endl;
				cout << "(7) - Get an article" << endl;
				cout << "------------------------" << endl;
			} else if (sel == "1") {
				cout << "Name of the newsgroup: ";
				string name;
				getline(cin, name);
				clientHandler.reqCreateNewsgroup(name);
			} else if (sel == "2") {
				clientHandler.reqListNewsgroups();	
			} else if (sel == "3") {
				cout << "ID of the newsgroup to delete: ";
				string idString;
				getline(cin, idString);
				int id = atoi(idString.c_str());
				clientHandler.reqDeleteNewsgroup(id);
			} else if (sel == "4") {
				cout << "ID of the newsgroup: ";
				string idString;
				getline(cin, idString);
				int id = atoi(idString.c_str());
				cout << "converted id: " << id << endl;
				cout << "Article title: ";
				string title;
				getline(cin, title);
				cout << "Article author: ";
				string author;
				getline(cin, author);
				cout << "Article text: ";
				string text;
				getline(cin, text);
				clientHandler.reqCreateArticle(id, title, author, text);	
			} else if (sel == "5") {
				cout << "ID of the newsgroup: ";
				string idString;
				getline(cin, idString);
				int id = atoi(idString.c_str());
				clientHandler.reqListArticles(id);	
			} else if (sel == "6") {
				cout << "ID of the newsgroup: ";
				string idNString;
				getline(cin, idNString);
				int idN = atoi(idNString.c_str());
				cout << "ID of the article: ";
				string idAString;
				getline(cin, idAString);
				int idA = atoi(idAString.c_str());
				clientHandler.reqDeleteArticle(idN, idA);	
			} else if (sel == "7") {
				cout << "ID of the newsgroup: ";
				string idNString;
				getline(cin, idNString);
				int idN = atoi(idNString.c_str());
				cout << "ID of the article: ";
				string idAString;
				getline(cin, idAString);
				int idA = atoi(idAString.c_str());
				clientHandler.reqGetArticle(idN, idA);		
			}

			cout << "Waiting for input..." << endl;
		} catch (ConnectionClosedException&) {
			cout << " no reply from server. Exiting." << endl;
			exit(1);
		} catch (NAKException&) {
			cout << "Waiting for input. Type help for manual" << endl;
		}

	}
}

