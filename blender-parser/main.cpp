#include <iostream>

#include "parser.h"
using namespace std;

int main(int argc, char** argv) {
	char* filename;

	if (argc < 2) {
		cout << "Specify filename" << endl;
		exit(1);
	}

	filename = argv[1];

	Parser::parse(filename);

	for (auto i : Parser::objects) {
		for (auto j : i->getFaces()) {
			for (auto k : j->getVertices()) {
				cout << k->getPos().x << endl;
			}
		}
	}

	return 0;
}