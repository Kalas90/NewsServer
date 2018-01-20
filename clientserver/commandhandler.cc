#include "commandhandler.h"

using namespace std;

CommandHandler::CommandHandler(const shared_ptr<Connection>& connection, DatabaseHandler& dbHandler) : conn(connection), messageHandler(connection), databaseHandler(dbHandler) {}

void CommandHandler::ansListNewsgroups(){
	confirmEnd();
	vector<Newsgroup> newsgroups = databaseHandler.listNewsgroups();
	int quantity = newsgroups.size(); 
	cout << "quantity: " << quantity << endl;

	messageHandler.sendCode(Protocol::ANS_LIST_NG);	
	messageHandler.sendIntParameter(quantity);
	for_each(newsgroups.begin(), newsgroups.end(), [&](const Newsgroup& ng) 
			{
				messageHandler.sendIntParameter(ng.id);
				messageHandler.sendStringParameter(ng.name);
			});
	messageHandler.sendCode(Protocol::ANS_END);	
}

void CommandHandler::ansCreateNewsgroup(){
	string name = messageHandler.recvStringParameter();
	confirmEnd();	
	
	bool success = databaseHandler.createNewsgroup(name);
	messageHandler.sendCode(Protocol::ANS_CREATE_NG);
	if (success) {
		messageHandler.sendCode(Protocol::ANS_ACK);
	} else {
		messageHandler.sendCode(Protocol::ANS_NAK);
		messageHandler.sendCode(Protocol::ERR_NG_ALREADY_EXISTS);
	}
	messageHandler.sendCode(Protocol::ANS_END);
}

void CommandHandler::ansDeleteNewsgroup(){
	int id = messageHandler.recvIntParameter();
	confirmEnd();
	

	bool success = databaseHandler.deleteNewsgroup(id);
	messageHandler.sendCode(Protocol::ANS_DELETE_NG);
	if (success) {
		messageHandler.sendCode(Protocol::ANS_ACK);
	} else {
		messageHandler.sendCode(Protocol::ANS_NAK);
		messageHandler.sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);
	}
	messageHandler.sendCode(Protocol::ANS_END);
}

void CommandHandler::ansListArticles(){
	int id = messageHandler.recvIntParameter();
	confirmEnd();
	//Get articles
	
	bool success;
	messageHandler.sendCode(Protocol::ANS_LIST_ART);
	if (success) {
		//List articles
	} else {
		messageHandler.sendCode(Protocol::ANS_NAK);
		messageHandler.sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);
	}
	messageHandler.sendCode(Protocol::ANS_END);	
}

void CommandHandler::ansCreateArticle(){
	int id = messageHandler.recvIntParameter();
	string title = messageHandler.recvStringParameter();
	string author = messageHandler.recvStringParameter();
	string text = messageHandler.recvStringParameter();
	confirmEnd();
	// Create article
	
	bool success;
	messageHandler.sendCode(Protocol::ANS_CREATE_ART);
	if (success) {
		messageHandler.sendCode(Protocol::ANS_ACK);
	} else {
		messageHandler.sendCode(Protocol::ANS_NAK);
		messageHandler.sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);
	}
	messageHandler.sendCode(Protocol::ANS_END);	
}

void CommandHandler::ansDeleteArticle(){
	int idN = messageHandler.recvIntParameter();
	int idA = messageHandler.recvIntParameter();
	confirmEnd();
	// Delete Article
	
	bool success;
	messageHandler.sendCode(Protocol::ANS_DELETE_ART);
	if (success) {
		messageHandler.sendCode(Protocol::ANS_ACK);
	} else {
		messageHandler.sendCode(Protocol::ANS_NAK);
		//if(art or newsg)
		messageHandler.sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);
	}
	messageHandler.sendCode(Protocol::ANS_END);	
}

void CommandHandler::ansGetArticle(){
	int idN = messageHandler.recvIntParameter();
	int idA = messageHandler.recvIntParameter();
	confirmEnd();
	//get article
	
	bool success;
	messageHandler.sendCode(Protocol::ANS_GET_ART);
	if (success) {
		messageHandler.sendCode(Protocol::ANS_ACK);
		//send title, author, test
	} else {
		messageHandler.sendCode(Protocol::ANS_NAK);
		//if(art or newsg)
		messageHandler.sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);
	}
	messageHandler.sendCode(Protocol::ANS_END);	
}


int CommandHandler::recvCode() {
	return messageHandler.recvCode();
}

bool CommandHandler::confirmEnd() {
	if(recvCode() == Protocol::COM_END){
		return true;
	} else {
		cerr << "Protocol Violation. Did not receive COM_END." << endl;
		throw ConnectionClosedException();
		return false;	
	}
}

shared_ptr<Connection> CommandHandler::getConnection(){
	return conn;
}

