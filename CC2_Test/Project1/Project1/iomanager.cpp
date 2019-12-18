#include "iomanager.h"
#include <string>
#include <fstream>
using namespace std;


IOManager::IOManager() {}

IOManager::~IOManager() {}

vector<Equation> IOManager::readFile() {

	ifstream equationsFile ("input1.txt");
	string line;
	int equationNumber = 1;

	while (getline(equationsFile, line)) {
		if (line.length() > 1) {
			if (line == "PLUS") {
				auxEquation.operation = oPlus;
				setEquation();
			}
			else if (line == "MINUS") {
				auxEquation.operation = oMinus;
				setEquation();
			}
			else if (line == "MULTIPLY") {
				auxEquation.operation = oMultiply;
				setEquation();
			}
			else if (line[0] == '+') {
				if (equationNumber == 1) {
					auxEquation.sign1 = 1;
					for (size_t i = 0; i < line.length() - 1; i++) {
						auxEquation.number1.insert(auxEquation.number1.end(), line[i + 1] - '0');
						line[1];
					}
					equationNumber = 2;
				}
				else {
					auxEquation.sign2 = 1;
					for (size_t i = 0; i < line.length() - 1; i++) {
						auxEquation.number2.insert(auxEquation.number2.end(), line[i + 1] - '0');
					}
					equationNumber = 1;
				}
			}
			else if (line.at(0) == '-') {
				if (equationNumber == 1) {
					auxEquation.sign1 = -1;
					for (size_t i = 0; i < line.length() - 1; i++) {
						auxEquation.number1.insert(auxEquation.number1.end(), line[i + 1] - '0');
					}
					equationNumber = 2;
				}
				else {
					auxEquation.sign2 = -1;
					for (size_t i = 0; i < line.length() - 1; i++) {
						auxEquation.number2.insert(auxEquation.number2.end(), line[i + 1] - '0');
					}
					equationNumber = 1;
				}
			}
		}
	}
	equationsFile.close();

	return equations;
}

void IOManager::setEquation() {
	equations.insert(equations.end(), auxEquation);
	//Clear auxEquation
	auxEquation.number1.clear();
	auxEquation.number2.clear();
	auxEquation.sign1, auxEquation.sign2 = 0;
}

void IOManager::writeFile(vector<Equation> equations, vector<Result> results) {
	ofstream outputFile;
	outputFile.open("output1.txt");

	for (size_t i = 0; i < equations.size(); i++) {
		outputFile << "========================\n";
		outputFile << makeValueLine(equations[i].sign1, equations[i].number1);
		outputFile << makeValueLine(equations[i].sign2, equations[i].number2);
		switch (equations[i].operation) {
		case oPlus:
			outputFile << "PLUS\n";
			break;
		case oMinus:
			outputFile << "MINUS\n";
			break;
		case oMultiply:
			outputFile << "MULTIPLY\n";
			break;
		}
		outputFile << makeValueLine(results[i].sign, results[i].number);
	}
	outputFile.close();
}

string IOManager::makeValueLine(int sign, vector<int> value) {
	string line = "";

	if (sign == 1) {
		line += "+";
	}
	else {
		line += "-";
	}
	for (size_t i = 0; i < value.size(); i++) {
		line += to_string(value[i]);
	}
	line += "\n";

	return line;
}
