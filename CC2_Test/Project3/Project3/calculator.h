#pragma once
#include "iomanager.h"

class Calculator {
public:
	Calculator();
	~Calculator();
	vector<Result> calculateEquations(vector<Equation> equations);
};

