#include <iostream>

#include "parser.h"
using namespace std;

int main(int argc, char** argv) {
	char* filename;

	if (argc < 2) {
		cout << "Specify filename" << endl;
	}

	filename = argv[1];

	Parser parser;
	parser.parse(filename);

	/*
	for (auto i : parser.getObjects()) {
		for (auto j : i->getFaces()) {
			cout << "face" << endl;
			for (auto k : j->getVertices()) {
				cout << k->getPos().x << endl;
			}
		}
	}
	*/

	return 0;
}