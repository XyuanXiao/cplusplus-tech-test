#include "iomanager.h"
#include "cabletester.h"
#include <vector>


int main(int argc, char *argv[]) {

	IOManager iom;
	CableTester tester;

	vector<TestCase> cases = iom.readFile();
	vector<vector<long>> results = tester.verifyCables(cases);
	iom.writeFile(results);

	return 0;
}
