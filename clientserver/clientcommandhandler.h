#ifndef CLIENTCOMMANDHANDLER_H
#define CLIENTCOMMANDHANDLER_H

#include "messagehandler.h"
#include "connection.h"
#include "protocol.h"

using namespace std;

class ClientCommandHandler {

public:
	ClientCommandHandler(const shared_ptr<Connection>& connection);
	void reqListNewsgroups();
	void reqCreateNewsgroup(string name);
	void reqDeleteNewsgroup(int id);
	void reqListArticles(int id);
	void reqCreateArticle(int id, string title, string author, string text);
	void reqDeleteArticle(int idN, int idA);
	void reqGetArticle(int idN, int idA);

private:
	MessageHandler messageHandler;
};
#endif
