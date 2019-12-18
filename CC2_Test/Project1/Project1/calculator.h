#pragma once
#include "iomanager.h"

class Calculator {
public:
	Calculator();
	~Calculator();
	vector<Result> calculateEquations(vector<Equation> equations);

private:
	Result addition(vector<int> number1, vector<int> number2, int resultSign, bool subtraction);
	Result multiplication(vector<int> number1, vector<int> number2, int resultSign);
};

