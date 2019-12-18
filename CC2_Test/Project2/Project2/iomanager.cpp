#include "iomanager.h"
#include <string>
#include <fstream>
#include <vector>
using namespace std;


IOManager::IOManager() {}

IOManager::~IOManager() {}

vector<TestCase> IOManager::readFile() {

	ifstream file("input2.txt");
	string line;
	vector<TestCase> testCases;
	TestCase auxCase;
	int quantity;
	step currentStep = sNone;

	while (getline(file, line)) {
		if (line.size() == 0) {
			currentStep = sNone;
		}
		else {
			switch (currentStep) {
			case sNone:
				currentStep = sDivisor;
				break;
			case sDivisor:
				auxCase.distance = stol(line) * 10000000; //Centimeter to nanometer
				currentStep = sDistance;
				break;
			case sDistance:
				quantity = stoi(line);
				currentStep = sQuantity;
				break;
			case sQuantity:
				currentStep = sWires;
			case sWires:
				auxCase.wires.insert(auxCase.wires.end(), stol(line));
				quantity--;
				if (quantity == 0) {
					testCases.insert(testCases.end(), auxCase);
					auxCase.wires.clear();
					currentStep = sNone;
				}
				break;
			}
		}
	}
	file.close();

	return testCases;
}

void IOManager::writeFile(vector<vector<long>> results) {

	ofstream outputFile;
	outputFile.open("output2.txt");

	for (size_t i = 0; i < results.size(); i++) {
		outputFile << "========\n";
		vector<long> result = results[i];
		if (result[0] == 0) {
			outputFile << "danger\n";
		}
		else {
			outputFile << "yes " << result[0] << " " << result[1] << "\n";
		}
	}
	outputFile.close();
}
