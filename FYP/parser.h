#include <iostream>
#include <fstream>
#include <sstream>

#include "object.h"
#include "scene.h"
using namespace std;

namespace Parser {
	/*
	extern std::vector<Object*> objects;
	extern Object* currObj; // current object being parsed
	extern std::vector<Vertex*> vertices;
	*/

	/* parse obj file for object geometry */
	Scene* parseObjFile(const char* filename);

	/* parse mtl file for material */
	void parseMtlFile(const char* filename);
};

