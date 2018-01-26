#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include "messagehandler.h"
#include "server.h"
#include "connection.h"
#include "protocol.h"
#include "connectionclosedexception.h"
#include "structures.h"
#include "databasehandler.h"

#include <memory>
#include <vector>
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <utility>

using namespace std;

class CommandHandler {

public:
	CommandHandler(const shared_ptr<Connection>& connection, DatabaseHandler& dbHandler);
	void ansListNewsgroups();
	void ansCreateNewsgroup();
	void ansDeleteNewsgroup();
	void ansListArticles();
	void ansCreateArticle();
	void ansDeleteArticle();
	void ansGetArticle();
	int recvCode();
	shared_ptr<Connection> getConnection();
private:
	shared_ptr<Connection> conn;
	MessageHandler messageHandler;
	DatabaseHandler& databaseHandler;
	bool confirmEnd();

};
#endif
