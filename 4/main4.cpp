#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <unordered_set>

using namespace std;

string inputName = "input.txt";

int main(int argc, char** argv) {
	int part1ans = 0;
	int part2ans = 0;

	fstream inputFile;

	string line;
	inputFile.open(inputName, ios::in);
	vector<string> rollMap;
	while (getline(inputFile, line)) {
		//for each input line
		vector<int> items;
		std::stringstream ss(line);
		int item;
		while (ss >> item) {
			items.push_back(item);
		}
		rollMap.push_back('.' + line + '.');
		//all of line's items now in items
	}

	rollMap.insert(rollMap.begin(), string(rollMap[0].size(), '.'));
	rollMap.push_back(string(rollMap[0].size(), '.'));

	for (int i = 1; i < rollMap.size() - 1; i++) {
		auto row = rollMap[i];
		for (int j = 1; j < row.size() - 1; j++) {
			if (row[j] != '@')
				continue;
			int fullCount = 0;
			if (rollMap[i - 1][j - 1] == '@')
				fullCount++;
			if (rollMap[i - 1][j] == '@')
				fullCount++;
			if (rollMap[i - 1][j + 1] == '@')
				fullCount++;
			if (rollMap[i][j - 1] == '@')
				fullCount++;
			if (rollMap[i][j + 1] == '@')
				fullCount++;
			if (rollMap[i + 1][j - 1] == '@')
				fullCount++;
			if (rollMap[i + 1][j] == '@')
				fullCount++;
			if (rollMap[i + 1][j + 1] == '@')
				fullCount++;
			if (fullCount < 4)
				part1ans++;
		}
	}


	//p2
	for (int i = 1; i < rollMap.size() - 1; i++) {
		bool rem = false;
		auto row = rollMap[i];
		for (int j = 1; j < row.size() - 1; j++ && !rem) {
			if (row[j] != '@')
				continue;
			int fullCount = 0;
			if (rollMap[i - 1][j - 1] == '@')
				fullCount++;
			if (rollMap[i - 1][j] == '@')
				fullCount++;
			if (rollMap[i - 1][j + 1] == '@')
				fullCount++;
			if (rollMap[i][j - 1] == '@')
				fullCount++;
			if (rollMap[i][j + 1] == '@')
				fullCount++;
			if (rollMap[i + 1][j - 1] == '@')
				fullCount++;
			if (rollMap[i + 1][j] == '@')
				fullCount++;
			if (rollMap[i + 1][j + 1] == '@')
				fullCount++;
			if (fullCount < 4) {
				rollMap[i][j] = '.';
				rem = true;
				part2ans++;
			}
		}
		if (rem)
			i = 0;
	}

	cout << "part one:" << part1ans << endl;
	cout << "part two:" << part2ans << endl;
	return 0;
}