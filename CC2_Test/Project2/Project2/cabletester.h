#pragma once
#include "iomanager.h"
#include <vector>
using namespace std;


class CableTester {
public:
	CableTester();
	~CableTester();
	vector<vector<long>> verifyCables(vector<TestCase> testCases);
};

