#include "messagehandler.h"

using namespace std;

MessageHandler::MessageHandler(shared_ptr<Connection> connection) : conn(connection) {} 

void MessageHandler::sendByte(int code) {
	conn->write(static_cast<char>(code));
}

void MessageHandler::sendCode(int code) {
	sendByte(code);
}

void MessageHandler::sendInt(int value) {
	sendByte((value >> 24) & 0xFF);
	sendByte((value >> 16) & 0xFF);
	sendByte((value >> 8) & 0xFF);
	sendByte(value & 0xFF);
}

void MessageHandler::sendIntParameter(int param) {
	sendCode(Protocol::PAR_NUM);
	sendInt(param);
}

void MessageHandler::sendStringParameter(string param) {
	sendCode(Protocol::PAR_STRING);
	sendInt(param.length());
	for(char& c : param) {
		sendByte(c);
	}
}

int MessageHandler::recvByte() {
	int code = conn->read();
	return code;
}

int MessageHandler::recvCode() {
	return recvByte();
}

int MessageHandler::recvInt() {
	int b1 = recvByte() << 24;
	int b2 = recvByte() << 16;
	int b3 = recvByte() << 8;
	int b4 = recvByte();
	return b1 | b2 | b3 | b4;	
}

int MessageHandler::recvIntParameter() {
	int code = recvCode();
	if (code != Protocol::PAR_NUM) 
		cerr << "Protocol Violation, invalid numeric parameter" << endl;
	return recvInt();	

}

string MessageHandler::recvStringParameter() {
	int code = recvCode();
	if (code != Protocol::PAR_STRING)
		cerr << "Protocol Violation, invalid string parameter" << endl;
	int nbr = recvInt();
	if (nbr < 0)
		cerr << "Protocol Violation, number < 0" << endl;
	string param;
	for (int i = 0; i < nbr; ++i) 
		param += static_cast<char>(recvByte());
	return param;
}

shared_ptr<Connection> MessageHandler::getConnection() {
	return conn;
}
