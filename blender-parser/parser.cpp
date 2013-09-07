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
			while (getline(ss, item, ' ')) {
				cout << item << endl;
			}
		} else if (item == "f") { // face
			while (getline(ss, item, ' ')) {
				cout << item << endl;
			}
		}
	}
}