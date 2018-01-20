#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include "structures.h"

#include <string>

using namespace std;

class DatabaseHandler {

public:
	const vector<Newsgroup>& listNewsgroups();
	bool createNewsgroup(const string& name);
	bool deleteNewsgroup(const int& id);
	vector<Article> listArticles(const int& id);
	bool createArticle(const int& idN, const string& title, const string& author, const string& text);
	bool deleteArticle(const int& idN, const int& idA);
	Article getArticle(const int& idN, const int& idA);
private:
	static vector<Newsgroup> newsgroups;
	static int maxIdN;
};	

#endif
