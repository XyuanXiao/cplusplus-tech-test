#pragma once
#include <vector>
using namespace std;


enum step : int {
	sNone = 0,
	sDivisor = 1,
	sDistance = 2,
	sQuantity = 3,
	sWires = 4
};

class TestCase { //Everything in nanometer
public:
	long distance;
	vector<long> wires;
};

class IOManager {
public:
	IOManager();
	~IOManager();
	vector<TestCase> readFile();
	void writeFile(vector<vector<long>> results);
};
