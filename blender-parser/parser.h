#include <iostream>
#include <fstream>
#include <sstream>

#include "object.h"
using namespace std;

class Parser {
public:
	Parser();
	~Parser();
	void parse(char* filename);
private:
	std::vector<Object*> objects;
	Object* currObj; // current object being parsed
};
