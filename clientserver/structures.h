#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>
#include <vector>

using namespace std;

struct Article {
	int id;
	string title;
	string author;
	string text;

	Article(int id, string title, string author, string text) : id(id), title(title), author(author), text(text){}
	bool operator==(const int& idA) {
		return (id == idA);
	}	
};

struct Newsgroup {
	int id;
	string name;
	vector<Article> articles;
	int idA = 0;

	bool operator==(const int& idN) {
		return (id == idN);
	}
};

#endif  	
