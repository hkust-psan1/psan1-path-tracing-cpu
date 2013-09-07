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

	return 0;
}