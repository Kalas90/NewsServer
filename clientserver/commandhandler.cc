#include "commandhandler.h"

using namespace std;

CommandHandler::CommandHandler(const shared_ptr<Connection>& connection, DatabaseHandler& dbHandler) : conn(connection), messageHandler(connection), databaseHandler(dbHandler) {}

void CommandHandler::ansListNewsgroups(){
	confirmEnd();
	vector<Newsgroup> newsgroups = databaseHandler.listNewsgroups();
	int quantity = newsgroups.size(); 

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
	
	pair<bool, vector<Article>> results = databaseHandler.listArticles(id);
	messageHandler.sendCode(Protocol::ANS_LIST_ART);
	if (results.first) {
		vector<Article> articles = results.second;
		messageHandler.sendCode(Protocol::ANS_ACK);
		messageHandler.sendIntParameter(articles.size());
		if(articles.size() > 0) {	
			for_each(articles.begin(), articles.end(), [&](const Article& art)
				{
					messageHandler.sendIntParameter(art.id);
					messageHandler.sendStringParameter(art.title);
				});	
		}
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
		
	bool success = databaseHandler.createArticle(id, title, author, text);;
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
	
	pair<bool, bool> success = databaseHandler.deleteArticle(idN, idA);
	messageHandler.sendCode(Protocol::ANS_DELETE_ART);
	if (success.first && success.second) {
		messageHandler.sendCode(Protocol::ANS_ACK);
	} else {
		messageHandler.sendCode(Protocol::ANS_NAK);
		if(!success.first) {
			messageHandler.sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);
		} else {
			messageHandler.sendCode(Protocol::ERR_ART_DOES_NOT_EXIST);
		}
	}
	messageHandler.sendCode(Protocol::ANS_END);	
}

void CommandHandler::ansGetArticle(){
	int idN = messageHandler.recvIntParameter();
	int idA = messageHandler.recvIntParameter();
	confirmEnd();
	
	pair<unique_ptr<Article>, bool> art = databaseHandler.getArticle(idN, idA);
	messageHandler.sendCode(Protocol::ANS_GET_ART);
	if (art.first && art.second) {
		messageHandler.sendCode(Protocol::ANS_ACK);
		messageHandler.sendStringParameter(art.first->title);
		messageHandler.sendStringParameter(art.first->author);
		messageHandler.sendStringParameter(art.first->text);
	} else {
		messageHandler.sendCode(Protocol::ANS_NAK);
		if(art.second) {
			messageHandler.sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);
		} else {
			messageHandler.sendCode(Protocol::ERR_ART_DOES_NOT_EXIST);
		}
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

