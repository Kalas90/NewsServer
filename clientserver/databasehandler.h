#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include "structures.h"

#include <string>
#include <utility>

using namespace std;

class DatabaseHandler {

public:
	const vector<Newsgroup>& listNewsgroups();
	bool createNewsgroup(const string& name);
	bool deleteNewsgroup(const int& id);
	pair<bool, vector<Article>> listArticles(const int& id);
	bool createArticle(const int& idN, const string& title, const string& author, const string& text);
	pair<bool, bool> deleteArticle(const int& idN, const int& idA);
	pair<unique_ptr<Article>, bool> getArticle(const int& idN, const int& idA);
private:
	static vector<Newsgroup> newsgroups;
	static int nextIdN;
};	

#endif
