#include "parser.h"

namespace Parser {
	std::vector<Object*> objects;
	Object* currObj;
	std::vector<Vertex*> vertices;

	void parse(char* filename) {
		std::ifstream input(filename);

		for (std::string line; getline(input, line); ) {
			std::stringstream ss(line);
			std::string item;

			getline(ss, item, ' ');

			if (item == "o") { // start of a new object
				if (currObj) { // if it's not the first object parsed
					objects.push_back(currObj); // add old object to list
				}

				currObj = new Object;
			} else if (item == "v") { // vertex
				float coords[3];

				for (int i = 0; getline(ss, item, ' '); i++) {
					coords[i] = atof(item.c_str());
				}

				vertices.push_back(new Vertex(coords));

			} else if (item == "f") { // face
				Face* f = new Face;
				while (getline(ss, item, ' ')) {
					int index = atoi(item.c_str());
					f->addVertex(vertices[index]);
				}

				currObj->addFace(f);
			}
		}

		objects.push_back(currObj); // add the last object to the list
	}
};