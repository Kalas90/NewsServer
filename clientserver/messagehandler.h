#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include "connectionclosedexception.h"
#include "protocol.h"
#include "connection.h"
 
#include <memory>
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>

using namespace std; 

class MessageHandler {

public:
	MessageHandler(shared_ptr<Connection> connection);
	void sendCode(int code);
	void sendInt(int value);
	void sendIntParameter(int param);
	void sendStringParameter(string param);
	int recvCode();
	int recvInt();
	int recvIntParameter();
	string recvStringParameter();
	
private:
	shared_ptr<Connection> conn;
	void sendByte(int code);
	int recvByte();

};
#endif


