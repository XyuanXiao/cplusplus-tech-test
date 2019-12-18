#include "iomanager.h"
#include "processor.h"

int main(int argc, char *argv[]) {

	IOManager iom;
	Processor processor;

	vector<string> equations = iom.readFile();
	vector<vector<string>> results = processor.processBrackets(equations);
	iom.writeFile(results);

	return 0;
}
