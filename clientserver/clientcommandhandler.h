#ifndef CLIENTCOMMANDHANDLER_H
#define CLIENTCOMMANDHANDLER_H

#include "connectionclosedexception.h"
#include "nakexception.h"
#include "messagehandler.h"
#include "connection.h"
#include "protocol.h"

using namespace std;

class ClientCommandHandler {

public:
	ClientCommandHandler(const shared_ptr<Connection>& connection);
	void reqListNewsgroups();
	void reqCreateNewsgroup(const string& name);
	void reqDeleteNewsgroup(const int& id);
	void reqListArticles(const int& id);
	void reqCreateArticle(const int& id, const string& title, const string& author, const string& text);
	void reqDeleteArticle(const int& idN, const int& idA);
	void reqGetArticle(const int& idN, const int& idA);

private:
	void confirmEnd();
	void wrongCode();
	void doesNotExist();
	MessageHandler messageHandler;
};
#endif
