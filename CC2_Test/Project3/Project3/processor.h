#pragma once
#include <vector>
using namespace std;


class Pair {
public:
	int start;
	int finish;
};

class Processor {
public:
	Processor();
	~Processor();
	vector<vector<string>> processBrackets(vector<string> equations);

private:
	vector<vector<string>> makeCombinations(vector<string> equations, vector<vector<Pair>> bracketsPairs);
	vector<string> createRepetitions(string equation, int repetitions);
};

