#include "calculator.h"
#include <algorithm>
using namespace std;


Calculator::Calculator() {}

Calculator::~Calculator() {}

Result addition(vector<int> number1, vector<int> number2, int resultSign = 1, bool subtraction = false) {
	Result result;

	reverse(number1.begin(), number1.end());
	reverse(number2.begin(), number2.end());
	int remnant = 0;

	for (size_t i = 0; i < number1.size() || i < number2.size(); i++) {
		int n1, n2, total;

		if (i < number1.size()) {
			n1 = number1[i];
		}
		else {
			n1 = 0;
		}
		if (i < number2.size()) {
			n2 = number2[i];
		}
		else {
			n2 = 0;
		}

		if (subtraction) { //Subtract the numbers
			n1 -= remnant;
			if (n1 < n2) {
				total = (n1 + 10) - n2;
				remnant = 1;
			}
			else {
				total = n1 - n2;
				remnant = 0;
			}
		}
		else { //Add the numbers
			total = n1 + n2 + remnant;
			if (total > 9) {
				remnant = 1;
				total -= 10;
			}
			else {
				remnant = 0;
			}
		}

		result.number.insert(result.number.end(), total);
	}
	result.number.insert(result.number.end(), remnant);

	//Remove unnecessary zeros
	for (size_t i = result.number.size() - 1; i > 0; i--) {
		if (result.number[i] == 0) {
			result.number.erase(result.number.begin() + i);
		}
		else {
			break;
		}
	}

	reverse(result.number.begin(), result.number.end());
	result.sign = resultSign;

	return result;
}

Result multiplication(vector<int> number1, vector<int> number2, int resultSign) {
	Result result;
	vector<vector<int>> partials;

	reverse(number1.begin(), number1.end());
	reverse(number2.begin(), number2.end());
	int remnant = 0;

	for (int i = 0; i < number1.size(); i++) {
		vector<int> partial;
		for (int k = i; k > 0; k--) {
			partial.insert(partial.begin(), 0); //Inserting necessary zeros
		}
		for (int j = 0; j < number2.size(); j++) {
			int mult = (number1[i] * number2[j]) + remnant;
			int total;
			if (mult > 9) {
				total = mult % 10;
				remnant = (mult - total) / 10;
			}
			else {
				total = mult;
				remnant = 0;
			}
			partial.insert(partial.begin(), total);
		}
		if (remnant != 0) {
			partial.insert(partial.begin(), remnant);
			remnant = 0;
		}
		partials.insert(partials.end(), partial);
	}

	vector<int> aux = partials[0];
	for (size_t i = 1; i < partials.size(); i++) { //Sum of every partials to get the multiplication final result
		aux = addition(aux, partials[i]).number;
	}

	result.number = aux;
	result.sign = resultSign;
	return result;
}

vector<Result> Calculator::calculateEquations(vector<Equation> equations) {
	vector<Result> results;

	for (size_t i = 0; i < equations.size(); i++) {
		Equation eq = equations[i];

		switch (eq.operation) { //Identify the appropriate operation to process and the result sign
		case oMultiply:
			results.insert(results.end(), multiplication(eq.number1, eq.number2, eq.sign1 * eq.sign2));
			break;

		default:
			if (eq.sign1 == eq.sign2 * eq.operation) {
				//common addition
				results.insert(results.end(), addition(eq.number1, eq.number2, eq.sign1));
				break;
			} 
			else if (eq.number1.size() > eq.number2.size()) {
				//common subtraction
				results.insert(results.end(), addition(eq.number1, eq.number2, eq.sign1, true));
				break;
			}
			else if (eq.number1.size() < eq.number2.size()) {
				//subtraction inverting 1 and 2
				results.insert(results.end(), addition(eq.number2, eq.number1, eq.sign2 * eq.operation, true));
				break;
			}
			else {
				for (size_t j = 0; j < eq.number1.size(); j++) {
					if (eq.number1[j] > eq.number2[j]) {
						//common subtraction
						results.insert(results.end(), addition(eq.number1, eq.number2, eq.sign1, true));
						break;
					}
					else if (eq.number1[j] < eq.number2[j]) {
						//subtraction inverting 1 and 2
						results.insert(results.end(), addition(eq.number2, eq.number1, eq.sign2 * eq.operation, true));
						break;
					}
					else if (j == eq.number1.size() - 1) {
						Result result;
						result.sign = 1;
						result.number.insert(result.number.end(), 0);
						results.insert(results.end(), result);
					}
				}
			}
			break;
		}
	}

	return results;
}
