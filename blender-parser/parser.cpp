#include "parser.h"

Parser::Parser() {

}

Parser::~Parser() {
	
}

void Parser::parse(char* filename) {
	std::ifstream input(filename);

	for (std::string line; getline(input, line); ) {
		std::stringstream ss(line);
		std::string item;

		getline(ss, item, ' ');

		if (item == "o") { // start of a new object
			objects.push_back(currObj);
			currObj = new Object;
		} else if (item == "v") { // vertex
			float coords[3];

			for (int i = 0; getline(ss, item, ' '); i++) {
				coords[i] = atof(item.c_str());
			}

			Vertex* v = new Vertex(coords);
			v->getPos();
			vertices.push_back(new Vertex(coords));

			for (auto i : vertices) {
				// i->getPos();
				// cout << i->getPos().getX() << endl;
			}

		} else if (item == "f") { // face
			while (getline(ss, item, ' ')) {
				cout << item << endl;
			}
		}
	}

}