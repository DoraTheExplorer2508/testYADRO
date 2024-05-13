#include <iostream>
#include "CompClub.h"
using namespace std;

int main() {
	CompClub c1;
	try {
		CheckFile("file1.txt");
		ReadFile("file1.txt", c1);
	}
	catch (const std::string& e) {
		cerr << e << endl;
		exit(1);
	}

	return 0;
}