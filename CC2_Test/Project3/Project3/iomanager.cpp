#include "iomanager.h"
#include <string>
#include <fstream>
using namespace std;


IOManager::IOManager() {}

IOManager::~IOManager() {}

vector<string> IOManager::readFile() {

	ifstream equationsFile ("input3.txt");
	string line;
	vector<string> equations;

	while (getline(equationsFile, line)) {
		if (line.length() > 1 && line[0] != '=') {
			equations.insert(equations.end(), line);
		}
	}
	equationsFile.close();

	return equations;
}

void IOManager::writeFile(vector<vector<string>> results) {

	ofstream outputFile;
	outputFile.open("output3.txt");

	for (size_t i = 0; i < results.size(); i++) {
		outputFile << "========\n";

		for (size_t j = 0; j < results[i].size(); j++) {
			outputFile << results[i].at(j) << "\n";
		}
	}
	outputFile.close();
}
