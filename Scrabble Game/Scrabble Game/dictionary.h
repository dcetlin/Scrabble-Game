#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "gaddog.h"
#include <iostream>
#include <fstream>

class Dictionary {

public:
	Dictionary(std::string);
	~Dictionary();
	bool exists(std::string);


private:
	void parse(std::string);
	gaddog g_dog;




};

#endif
