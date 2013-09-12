#include <iostream>
#include <fstream>
#include <sstream>

#include "object.h"
#include "scene.h"
using namespace std;

namespace Parser {
	/* parse obj file for object geometry */
	Scene* parseObjFile(const char* filename);

	/* parse mtl file for material */
	Material* parseMtlFile(const char* filename);
};

