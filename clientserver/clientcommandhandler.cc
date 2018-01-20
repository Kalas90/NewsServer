#include "clientcommandhandler.h"

using namespace std;

ClientCommandHandler::ClientCommandHandler(const shared_ptr<Connection>& connection) : messageHandler(connection) {}

void ClientCommandHandler::reqListNewsgroups(){
	messageHandler.sendCode(Protocol::COM_LIST_NG);
	messageHandler.sendCode(Protocol::COM_END);
}

void ClientCommandHandler::reqCreateNewsgroup(string name){
	messageHandler.sendCode(Protocol::COM_CREATE_NG);
	messageHandler.sendStringParameter(name);
	messageHandler.sendCode(Protocol::COM_END);
}

void ClientCommandHandler::reqDeleteNewsgroup(int id){
	messageHandler.sendCode(Protocol::COM_DELETE_NG);
	messageHandler.sendIntParameter(id);
	messageHandler.sendCode(Protocol::COM_END);
}

void ClientCommandHandler::reqListArticles(int id){
	messageHandler.sendCode(Protocol::COM_LIST_ART);
	messageHandler.sendIntParameter(id);
	messageHandler.sendCode(Protocol::COM_END);
}

void ClientCommandHandler::reqCreateArticle(int id, string title, string author, string text){
	messageHandler.sendCode(Protocol::COM_CREATE_ART);
	messageHandler.sendIntParameter(id);
	messageHandler.sendStringParameter(title);
	messageHandler.sendStringParameter(author);
	messageHandler.sendStringParameter(text);
	messageHandler.sendCode(Protocol::COM_END);
}

void ClientCommandHandler::reqDeleteArticle(int idN, int idA){
	messageHandler.sendCode(Protocol::COM_DELETE_ART);
	messageHandler.sendIntParameter(idN);
	messageHandler.sendIntParameter(idA);
	messageHandler.sendCode(Protocol::COM_END);
}

void ClientCommandHandler::reqGetArticle(int idN, int idA){
	messageHandler.sendCode(Protocol::COM_GET_ART);
	messageHandler.sendIntParameter(idN);
	messageHandler.sendIntParameter(idA);
	messageHandler.sendCode(Protocol::COM_END);
}
