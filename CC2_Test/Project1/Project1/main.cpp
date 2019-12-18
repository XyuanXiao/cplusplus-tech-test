#include "iomanager.h"
#include "calculator.h"

int main(int argc, char *argv[]) {

	IOManager iom;
	Calculator calculator;

	vector<Equation> equations = iom.readFile();
	vector<Result> results = calculator.calculateEquations(equations);
	iom.writeFile(equations, results);

	return 0;
}
