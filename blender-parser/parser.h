#include <iostream>
#include <fstream>
#include <sstream>

#include "object.h"
using namespace std;

namespace Parser {
	extern std::vector<Object*> objects;
	extern Object* currObj; // current object being parsed
	extern std::vector<Vertex*> vertices;

	void parse(char* filename);
};

