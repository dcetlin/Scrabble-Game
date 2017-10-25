#ifndef GADDOG_H
#define GADDOG_H

#include <string>

struct Node {
	char elem;
	Node** children;
};

class gaddog {

public:

	gaddog();
	~gaddog();
	void deleteNodes(Node*&, int);
	void addWord(std::string);
	void print();
	bool contains(std::string);

private:
	
	Node* root;
	Node* eow;

	Node* addNode(Node*, char);
	
	Node* newNode(char);
	void makeChildren(Node*);
	int index(char);
	Node*& getChild(Node*, char);
	void setChild(Node*&, Node*);
	char getLetter (int);

	void print(std::string const&, Node* const&);

    const char BREAK = '>';
    const char EOW = '$';
	const char ROOT = '@';


};
#endif
