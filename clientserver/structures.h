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

	bool operator==(const Article& a) {
		return (id == a.id);
	}


};

struct Newsgroup {
	int id;
	string name;
	vector<Article> articles;

	bool operator()(const Newsgroup& ng1, const Newsgroup& ng2) {
		return ng1.id < ng2.id;	
	}

	bool operator==(const Newsgroup& ng) {
		return (!(name.compare(ng.name)) || (id == ng.id));
	}
};

#endif  	
