#include "dictionary.h"
#include "gaddog.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <unordered_set>
using namespace std;

typedef unordered_set<string> w_list;

Dictionary::Dictionary(string file)
{
	parse(file);
	//g_dog.print();


} 

Dictionary::~Dictionary() {}

void Dictionary::parse(string filename)
{
	ifstream inf(filename.c_str());
	if (!inf.is_open()) {
		cerr << filename << " not found in directory\n";
		exit(1);
	}
	string word;
	while (!inf.eof() && getline(inf, word))
		g_dog.addWord(word);
	inf.close();
}

bool Dictionary::exists(string s)
{
	return g_dog.contains(s);
}

