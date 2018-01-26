#include "clientcommandhandler.h"

using namespace std;

ClientCommandHandler::ClientCommandHandler(const shared_ptr<Connection>& connection) : messageHandler(connection) {}

void ClientCommandHandler::reqListNewsgroups(){
	messageHandler.sendCode(Protocol::COM_LIST_NG);
	messageHandler.sendCode(Protocol::COM_END);

	int code = messageHandler.recvCode();
	if(code != Protocol::ANS_LIST_NG) {
		wrongCode();
	}
	cout << "Newsgroup list:" << endl;
	int quantity = messageHandler.recvIntParameter();
	for(int i = 0; i < quantity; ++i) {
		cout << messageHandler.recvIntParameter() << " " 
		     << messageHandler.recvStringParameter() << endl;
	}
	confirmEnd();
}

void ClientCommandHandler::reqCreateNewsgroup(const string& name){
	messageHandler.sendCode(Protocol::COM_CREATE_NG);
	messageHandler.sendStringParameter(name);
	messageHandler.sendCode(Protocol::COM_END);
	
	int code = messageHandler.recvCode();
	if(code != Protocol::ANS_CREATE_NG) {
		wrongCode();
	}
	code = messageHandler.recvCode();
	if(code == Protocol::ANS_ACK) {
		confirmEnd();
	} else if (code == Protocol::ANS_NAK){
		doesNotExist();		
		confirmEnd();
	} else {
		wrongCode();
	}
	cout << "Created new newsgroup: " << name << endl;
}

void ClientCommandHandler::reqDeleteNewsgroup(const int& id){
	messageHandler.sendCode(Protocol::COM_DELETE_NG);
	messageHandler.sendIntParameter(id);
	messageHandler.sendCode(Protocol::COM_END);

	int code = messageHandler.recvCode();
	if(code != Protocol::ANS_DELETE_NG) {
		wrongCode();
	}
	code = messageHandler.recvCode();
	if(code == Protocol::ANS_ACK) {
		confirmEnd();
	} else if (code == Protocol::ANS_NAK) {
		doesNotExist();
		confirmEnd();
	} else {
		wrongCode();
	}	
}

void ClientCommandHandler::reqListArticles(const int& id){
	messageHandler.sendCode(Protocol::COM_LIST_ART);
	messageHandler.sendIntParameter(id);
	messageHandler.sendCode(Protocol::COM_END);

	int code = messageHandler.recvCode();
	if(code != Protocol::ANS_LIST_ART) {
		wrongCode();
	}
	code = messageHandler.recvCode();
	if(code == Protocol::ANS_ACK) {
		cout << "Article List:" << endl;
		int quantity = messageHandler.recvIntParameter();
		for(int i = 0; i < quantity; ++i) {
			cout << messageHandler.recvIntParameter() << " " 
		     	     << messageHandler.recvStringParameter() << endl;
		}
		confirmEnd();
		
	} else if (code == Protocol::ANS_NAK) {
		doesNotExist();
		confirmEnd();
	} else {
		wrongCode();
	}	
}

void ClientCommandHandler::reqCreateArticle(const int& id, const string& title, const string& author, const string& text){
	messageHandler.sendCode(Protocol::COM_CREATE_ART);
	messageHandler.sendIntParameter(id);
	messageHandler.sendStringParameter(title);
	messageHandler.sendStringParameter(author);
	messageHandler.sendStringParameter(text);
	messageHandler.sendCode(Protocol::COM_END);

	int code = messageHandler.recvCode();
	if(code != Protocol::ANS_CREATE_ART) {
		wrongCode();
	}
	code = messageHandler.recvCode();
	if(code == Protocol::ANS_ACK) {
		confirmEnd();
	} else if (code == Protocol::ANS_NAK){
		doesNotExist();		
		confirmEnd();
	} else {
		wrongCode();
	}
	cout << "Created new article: " << title << endl;
}

void ClientCommandHandler::reqDeleteArticle(const int& idN, const int& idA){
	messageHandler.sendCode(Protocol::COM_DELETE_ART);
	messageHandler.sendIntParameter(idN);
	messageHandler.sendIntParameter(idA);
	messageHandler.sendCode(Protocol::COM_END);
	
	int code = messageHandler.recvCode();
	if(code != Protocol::ANS_DELETE_ART) {
		wrongCode();
	}
	code = messageHandler.recvCode();
	if(code == Protocol::ANS_ACK) {
		confirmEnd();
	} else if (code == Protocol::ANS_NAK) {
		doesNotExist();
		confirmEnd();
	} else {
		wrongCode();
	}	
}

void ClientCommandHandler::reqGetArticle(const int& idN, const int& idA){
	messageHandler.sendCode(Protocol::COM_GET_ART);
	messageHandler.sendIntParameter(idN);
	messageHandler.sendIntParameter(idA);
	messageHandler.sendCode(Protocol::COM_END);
	
	int code = messageHandler.recvCode();
	if(code != Protocol::ANS_GET_ART) {
		wrongCode();
	}
	code = messageHandler.recvCode();
	if(code == Protocol::ANS_ACK) {
		cout << "Article title: " << messageHandler.recvStringParameter() << endl 
		     << "Article author: " << messageHandler.recvStringParameter() << endl 
		     << messageHandler.recvStringParameter() << endl;
		confirmEnd();
	} else if (code == Protocol::ANS_NAK) {
		doesNotExist();
		confirmEnd();
	} else {
		wrongCode();
	}	
}

void ClientCommandHandler::confirmEnd() {
	int code = messageHandler.recvCode();
	if(code != Protocol::ANS_END) {
		cerr << "Did not receive End code when expected." << endl;
		throw ConnectionClosedException();
	}
}

void ClientCommandHandler::wrongCode() {
	cerr << "Protocol error: Received wrong code" << endl;		
	throw ConnectionClosedException();
}

void ClientCommandHandler::doesNotExist() {
	int code = messageHandler.recvCode();
	if(code == Protocol::ERR_NG_ALREADY_EXISTS) {
		cerr << "That Newsgroup already exists" << endl;
		throw NAKException();
	} else if(code == Protocol::ERR_NG_DOES_NOT_EXIST) {
		cerr << "That Newsgroup does not exist" << endl;
		throw NAKException();
	} else if(code == Protocol::ERR_ART_DOES_NOT_EXIST) {
		cerr << "That Article does not exist" << endl;
		throw NAKException();
	} else {
		cerr << "Protocol Error: Did not receive expected code." << endl;
		throw ConnectionClosedException();
	}
}

