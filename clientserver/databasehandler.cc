#include "databasehandler.h"
#include "structures.h"

#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

vector<Newsgroup> DatabaseHandler::newsgroups;
int DatabaseHandler::maxIdN = 0;

const vector<Newsgroup>& DatabaseHandler::listNewsgroups() {
	return newsgroups;
}

bool DatabaseHandler::createNewsgroup(const string& name){
	vector<Newsgroup>::iterator it;
	it = find_if(newsgroups.begin(), newsgroups.end(), [&](Newsgroup &ng) {
				return !(name.compare(ng.name));
			});
	if(it == newsgroups.end()) {
		Newsgroup ng;
		ng.id = maxIdN++; 
		ng.name = name;
		newsgroups.push_back(ng);
		return true;
	}
	return false;
}

bool DatabaseHandler::deleteNewsgroup(const int& id){
	vector<Newsgroup>::iterator it;
	bool success = false;
	it = remove_if(newsgroups.begin(), newsgroups.end(), [&](Newsgroup &ng) {
				cout << "newsgroups size: " << newsgroups.size() << endl;
				cout << "id is: " << id << endl;
				cout << "ng.id is: " << ng.id << endl;
				if(ng.id == id) {
					cout << "removing: " << ng.id << endl;
					maxIdN = id;
					return true;
				}
				return false;
			});
	if(it != newsgroups.end())
	       success = true;	
	newsgroups.erase(it, newsgroups.end());
	return success; 
}

vector<Article> DatabaseHandler::listArticles(const int& id){

}

bool DatabaseHandler::createArticle(const int& idN, const string& title, const string& author, const string& text){

}

bool DatabaseHandler::deleteArticle(const int& idN, const int& idA){

}

Article DatabaseHandler::getArticle(const int& idN, const int& idA){

}

