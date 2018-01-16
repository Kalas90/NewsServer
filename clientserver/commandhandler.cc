#include "commandhandler.h"

using namespace std;

CommandHandler::CommandHandler(Server& server) {
	conn = server.waitForActivity();
	if (conn == nullptr){ 
		conn = make_shared<Connection>();
		server.registerConnection(conn);
		cout << "registered connection" << endl;
	} 
}

CommandHandler::ansListNewsgroups(){
		
}

CommandHandler::ansCreateNewsgroup(bool success){

}

CommandHandler::ansDeleteNewsgroup(bool success){

}

CommandHandler::ansListArticles(bool success){

}

CommandHandler::ansCreateArticle(bool success){

}

CommandHandler::ansDeleteArticle(bool success){

}

CommandHandler::ansGetArticle(bool success){

}

CommandHandler::reqListNewsgroups(){

}

CommandHandler::reqCreateNewsgroup(string name){

}

CommandHandler::reqDeleteNewsgroup(int id){

}

CommandHandler::reqListArticles(int id){

}

CommandHandler::reqCreateArticle(int id){

}

CommandHandler::reqDeleteArticle(int id){

}

CommandHandler::reqGetArticle(int idN, int idA){

}

CommandHandler::shared_ptr<Connection> getConnection(){

}

