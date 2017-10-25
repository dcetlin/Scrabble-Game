#include "gaddog.h"
#include <iostream>
using namespace std;

gaddog::gaddog()
{
	root = newNode(ROOT);
	eow = newNode(EOW);
}

gaddog::~gaddog() {
	deleteNodes(root, 1);
	delete eow;
}

void gaddog::deleteNodes(Node*& root, int sp)
{	
    if (root == nullptr) {
    	cout << "NULL\n";
    	return;
    }
    //cout << "delete {" << root->elem << "} -> " << "(" << root << ")\n";
    //cout << " | ";
    if (root->children != nullptr) {
    	for (int k = 0; k < 27; k++) {
    		for (int k = 0; k < sp - 1; k++)
    			//cout << " | ";
			//cout << "(" << getLetter(k) << ") child: ";
			deleteNodes(root->children[k], sp+1);
    	}
    	delete [] root->children;
    	root->children = nullptr;
    }
    
    if (!root) {
    	delete root; 
    	root = nullptr;
    }
}

Node* gaddog::newNode(char c)
{
	Node* current = new Node;
	current->elem = c;
	current->children = nullptr;
	return current;
}

void gaddog::makeChildren(Node* curr)
{
	if (curr->children == nullptr) {
		curr->children = new Node*[28];
        for (int k = 0; k < 28; k++)
            curr->children[k] = nullptr;
	}
}

int gaddog::index(char c) 
{
    if (c == BREAK)
        return 26;
    else if (c == EOW)
        return 27;
    else 
        return c - 'a';
}

Node*& gaddog::getChild(Node* curr, char c) 
{
	makeChildren(curr);
	return curr->children[index(c)];
}

void gaddog::setChild(Node*& parent, Node* child)
{
	makeChildren(parent);
	parent->children[index(child->elem)] = child;
}

Node* gaddog::addNode(Node* curr, char c)
{
	makeChildren(curr);
	if (getChild(curr, c) == nullptr)
		setChild(curr, newNode(c));
	return getChild(curr, c);
}
void gaddog::addWord(string s)
{
	string s_f = s;
	reverse(s.begin(), s.end());

	Node** importants = new Node*[s.size()];

	for (size_t k = 0; k < s.size(); k++) {
		importants[k] = addNode(root, s[k]);
		for (size_t j = 0; j < k; j++) {
			importants[j] = addNode(importants[j], s[k]);
		}
	}
	for (size_t k = 0; k < s.size(); k++) 
		importants[k] = addNode(importants[k], BREAK);

	for (size_t k = 0; k < s.size() - 1; k++) {
		importants[s.size() - k - 1] = addNode(importants[s.size() - k - 1], s_f[k+1]);

		for (size_t j = s.size() - 1; j > s.size() - 1 - k; j--) {
			if (getChild(importants[j], s_f[k+1]) == nullptr)
				importants[j]->children[index(s_f[k+1])] = importants[s.size() - k - 1];
			importants[j] = getChild(importants[j], s_f[k+1]);
		}
	}
	for (size_t k = 0; k < s.size(); k++) {
		setChild(importants[k], eow);
	}
	delete [] importants;
}

char gaddog::getLetter (int i) 
{
	return "abcdefghijklmnopqrstuvwxyz>$"[i];
}

void gaddog::print()
{
	for (int k = 0; k < 28; k++) {
		if (root->children[k]) {
			string s = "";
			s += (root->children[k]->elem);
			print(s, root->children[k]);
		}
	}
}

void gaddog::print(string const& prefix, Node* const& n) {
    if (n == nullptr)
    	return;
    if (n  == eow) {
    	cout << "{" << prefix << "}\n"; 
    	return;
    }

    for (std::size_t i = 0; i < 28; ++i) {
        if (n->children[i] != nullptr) {
        	//cout << prefix << " + " << n->children[i]->elem << " : ";
        	//cout << prefix + n->children[i]->elem << endl;
            print(prefix + n->children[i]->elem, n->children[i]);
        }
    }
}

bool gaddog::contains(string s)
{
	Node* curr = getChild(getChild(root, s[0]), BREAK);
	for (size_t k = 1; k < s.size(); k++) {
		if ((curr = getChild(curr, s[k])) == nullptr)
			return false;
	}
	return true;
}



