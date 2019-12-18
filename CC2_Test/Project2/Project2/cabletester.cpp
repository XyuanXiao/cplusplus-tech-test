#include "cabletester.h"
#include <algorithm>


CableTester::CableTester() {}

CableTester::~CableTester() {}

class Pair {
public:
	long first;
	long second;
	Pair(long f, long s) {
		first = f;
		second = s;
	}
};

vector<vector<long>> CableTester::verifyCables(vector<TestCase> testCases) {

	vector<vector<long>> results;

	for (size_t i = 0; i < testCases.size(); i++) {
		TestCase test = testCases[i];
		vector<Pair> successPairs;

		for (size_t j = 0; j < test.wires.size() - 1; j++) { //Get all cases where the sum is the distance
			for (size_t k = j + 1; k < test.wires.size(); k++) {
				long wire1 = test.wires[j];
				long wire2 = test.wires[k];
				if (wire1 + wire2 == test.distance) {
					Pair pair = Pair(min(wire1, wire2), max(wire1, wire2));
					successPairs.insert(successPairs.end(), pair);
				}
			}
		}

		if (successPairs.size() > 0) { //If there are success cases, get the best solution
			Pair bestPair = Pair(successPairs[0].first, successPairs[0].second);
			for (size_t l = 1; l < successPairs.size(); l++) {
				if (abs(bestPair.first - bestPair.second) < abs(successPairs[l].first - successPairs[l].second)) {
					bestPair = Pair(successPairs[l].first, successPairs[l].second);
				}
			}
			results.insert(results.end(), { bestPair.first, bestPair.second });
		}
		else {
			results.insert(results.end(), { 0, 0 }); //If not, then insert a zero in the place
		}
	}

	return results;
}
