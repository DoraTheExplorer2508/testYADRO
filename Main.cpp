#include <iostream>
#include "CompClub.h"
using namespace std;

int main(int argc, char* argv[]) {
	CompClub c1;
	if (argc < 2) {
	    cout << "not enough arguments to call" << endl;
	    exit(1);
	}
	try {
		string fileName = argv[1];
		CheckFile(fileName);
		ReadFile(fileName, c1);
	}
	catch (const string& e) {
		cerr << e << endl;
		exit(1);
	}

	return 0;
}
