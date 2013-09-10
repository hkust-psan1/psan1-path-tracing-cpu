#include "parser.h"

namespace Parser {


	Scene* parseObjFile(const char* filename) {
		std::vector<Object*> sceneObjects;
		Object* currObj = 0;
		std::vector<Vertex*> vertices;

		std::cout << filename;
		std::ifstream input(filename);

		if (!input) { // file does not exist
			throw "file does not exist";
		}

		for (std::string line; getline(input, line); ) {
			std::stringstream ss(line);
			std::string item;

			getline(ss, item, ' ');

			if (item == "o") { // start of a new object
				if (currObj) { // if it's not the first object parsed
					sceneObjects.push_back(currObj); // add old object to list
				}

				currObj = new Object;
			} else if (item == "v") { // vertex
				float coords[3];

				for (int i = 0; getline(ss, item, ' '); i++) {
					coords[i] = atof(item.c_str());
				}

				vertices.push_back(new Vertex(coords));

			} else if (item == "f") { // face
				int firstVertexIndex, lastVertexIndex;

				for (int i = 0; getline(ss, item, ' '); i++) {
					int vertexIndex = atoi(item.c_str());
					if (i == 0) {
						firstVertexIndex = vertexIndex;
					} else if (i >= 2) {
						Face* f = new Face;
						f->addVertex(vertices[firstVertexIndex - 1]);
						f->addVertex(vertices[lastVertexIndex - 1]);
						f->addVertex(vertices[vertexIndex - 1]);

						currObj->addFace(f);
					}
					lastVertexIndex = vertexIndex;
				}
				/*
				Face* f = new Face;

				while (getline(ss, item, ' ')) {
					int index = atoi(item.c_str());
					f->addVertex(vertices[index]);
				}

				currObj->addFace(f);
				*/
			}
		} 

		sceneObjects.push_back(currObj); // add the last object to the list
		Scene* s = new Scene(sceneObjects);
		return s;
	}

	void parseMtlFile(const char* filename) {
		std::ifstream input(filename);

		if (!input) { // file does not exist
			throw "file does not exist";
		}
	}
};