#pragma once
#include <vector>
using namespace std;


class IOManager {
public:
	IOManager();
	~IOManager();
	vector<string> readFile();
	void writeFile(vector<vector<string>> results);
};