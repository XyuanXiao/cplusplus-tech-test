#pragma once
#include <vector>
using namespace std;


enum operation : int {
	oPlus = 1,
	oMinus = -1,
	oMultiply = 0
};

class Equation {
public:
	vector<int> number1;
	int sign1;
	vector<int> number2;
	int sign2;
	operation operation;
};

class Result {
public:
	vector<int> number;
	int sign;
};

class IOManager {
public:
	IOManager();
	~IOManager();
	vector<Equation> readFile();
	void writeFile(vector<Equation> equations, vector<Result> results);

private:
	vector<Equation> equations;
	Equation auxEquation;
	void setEquation();
	string makeValueLine(int sign, vector<int> value);
};