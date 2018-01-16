#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include "messagehandler.h"
#include "server.h"
#include "connection.h"
#include "protocol.h"
#include "connectionclosedexception.h"

using namespace std;

class CommandHandler {

public:
	CommandHandler(Server& server);
	ansListNewsgroups();
	ansCreateNewsgroup(bool success);
	ansDeleteNewsgroup(bool success);
	ansListArticles(bool success);
	ansCreateArticle(bool success);
	ansDeleteArticle(bool success);
	ansGetArticle(bool success);
	reqListNewsgroups();
	reqCreateNewsgroup(string name);
	reqDeleteNewsgroup(int id);
	reqListArticles(int id);
	reqCreateArticle(int id);
	reqDeleteArticle(int id);
	reqGetArticle(int idN, int idA);
	shared_ptr<Connection> getConnection();
private:
	shared_ptr<Connection> conn;
	MessageHandler messageHandler;

};
#endif
