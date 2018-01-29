#include "databasehandler.h"
#include "structures.h"

#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

vector<Newsgroup> DatabaseHandler::newsgroups;
int DatabaseHandler::nextIdN = 0;

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
		ng.id = nextIdN; 
		nextIdN++;
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
				return (ng.id == id);
			});
	if(it != newsgroups.end())
	       success = true;	
	newsgroups.erase(it, newsgroups.end());
	return success; 
}

pair<bool, vector<Article>> DatabaseHandler::listArticles(const int& id){
	auto it = find(newsgroups.begin(), newsgroups.end(), id); 
	if(it != newsgroups.end()) {
		return make_pair(true, (*it).articles);
	} else {
		return make_pair(false, (*it).articles);
	}
}

bool DatabaseHandler::createArticle(const int& idN, const string& title, const string& author, const string& text){
	bool success = false;
	for_each(newsgroups.begin(), newsgroups.end(), [&](Newsgroup& ng){ 
		if(idN == ng.id){	
			ng.articles.emplace_back(Article{ng.idA, title, author, text});
					ng.idA++;
					cout << "found newsgroup created article" << endl;
					success = true;
				}
			});
	return success;
}

pair<bool, bool> DatabaseHandler::deleteArticle(const int& idN, const int& idA){
	bool newsgroup = false, article = false;
	for_each(newsgroups.begin(), newsgroups.end(), [&](Newsgroup& ng){ 
		if(idN == ng.id){	
			newsgroup = true;
			auto it = remove(ng.articles.begin(), ng.articles.end(), 										idA);	
			if(it != ng.articles.end()){
				article = true;	
				ng.articles.erase(it, ng.articles.end());
			}
		}
	});
	return make_pair(newsgroup, article);	
}

pair<unique_ptr<Article>, bool> DatabaseHandler::getArticle(const int& idN, const int& idA){
	Article* found = nullptr;
	bool foundNewsgroup = false;
	for_each(newsgroups.begin(), newsgroups.end(), [&](Newsgroup& ng){ 
		if(idN == ng.id){	
			foundNewsgroup = true;	
			auto it = find(ng.articles.begin(),ng.articles.end(),idA);
			if(it != ng.articles.end()){
				Article& art = *it;	
				found = new Article(art);
			}
		}
	});
	return make_pair(unique_ptr<Article>(found), foundNewsgroup);	
}
