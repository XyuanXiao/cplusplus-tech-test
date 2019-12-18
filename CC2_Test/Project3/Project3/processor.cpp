#include "processor.h"
#include <math.h>


Processor::Processor() {}

Processor::~Processor() {}

vector<vector<string>> Processor::processBrackets(vector<string> equations) {
	vector<vector<Pair>> bracketsPairs;

	//Get all brackets pairs by position of each bracket inside each equation string
	for (size_t i = 0; i < equations.size(); i++) {
		vector<Pair> auxPairs;
		bracketsPairs.insert(bracketsPairs.end(), auxPairs);

		for (int j = 0; j < equations[i].size(); j++) {
			char c = equations[i][j];
			if (c == '(') {
				Pair halfPair;
				halfPair.start = j;
				auxPairs.insert(auxPairs.end(), halfPair);
			}
			else if (c == ')') {
				Pair pair;
				pair.start = auxPairs[auxPairs.size() - 1].start;
				pair.finish = j;
				bracketsPairs[i].insert(bracketsPairs[i].end(), pair);
				auxPairs.erase(auxPairs.begin() + auxPairs.size() - 1);
			}
		}
	}

	return makeCombinations(equations, bracketsPairs);
}

vector<vector<string>> Processor::makeCombinations(vector<string> equations, vector<vector<Pair>> bracketsPairs) {
	vector<vector<string>> results;

	for (size_t i = 0; i < bracketsPairs.size(); i++) { //For each equation
		int total = pow(2, bracketsPairs[i].size());
		results.insert(results.end(), createRepetitions(equations[i], total));
		int half = total;

		for (size_t j = 0; j < bracketsPairs[i].size(); j++) { //For each bracket pair of given equation
			int counter2 = 0;
			half = half / 2;
			bool remove = false;

			for (size_t k = 0; k < total; k++) {
				if (counter2 == half) {
					counter2 = 0;
					remove = !remove;
				}
				if (remove) {
					//Replace brackets for space
					int start = bracketsPairs[i][j].start;
					int finish = bracketsPairs[i][j].finish;
					results[i][k][start] = ' ';
					results[i][k][finish] = ' ';
					counter2++;
				}
				else {
					counter2++;
				}
			}
		}
		results[i].erase(results[i].begin()); //Erase the first because it it equal to the original equation

		for (size_t l = 0; l < results[i].size(); l++) { //Truncate the strings to remove spaces
			for (int m = results[i][l].size() - 1; m >= 0; m--) {
				if (results[i][l][m] == ' ') {
					results[i][l].replace(m, 1, "");
				}
			}
		}
	}
	
	return results;
}

vector<string> Processor::createRepetitions(string equation, int repetitions) {
	vector<string> repEquations;
	for (size_t i = 0; i < repetitions; i++) {
		repEquations.insert(repEquations.end(), equation);
	}
	return repEquations;
}
