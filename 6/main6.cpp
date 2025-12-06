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
	long long part1ans = 0;
	long long part2ans = 0;

	fstream inputFile;

	string line;
	vector<vector<int>> allItems;
	vector<string> allLines;
	vector<char> ops;
	inputFile.open(inputName, ios::in);
	while (getline(inputFile, line)) {
		//for each input line
		vector<int> items;
		std::stringstream ss(line);
		int item;
		while (ss >> item)
			items.push_back(item);
		allLines.push_back(line);
		//last row
		if (items.size() == 0) {
			for (char c : line)
				if (c != ' ')
					ops.push_back(c);
			break;
		}

		allItems.push_back(items);
	}

	for (int i = 0; i < ops.size(); i++) {
		long long colAns = allItems[0][i];
		char op = ops[i];
		for (int j = 1; j < allItems.size(); j++) {
			if (op == '+')
				colAns += allItems[j][i];
			if (op == '*')
				colAns *= allItems[j][i];
		}
		part1ans += colAns;
	}

	for (int col = allLines[0].size() - 1; col >= 0; col--) {
		vector<int> probNos;
		do {
			int cur = 0;
			for (int row = 0; row < allLines.size(); row++) {
				char dig = allLines[row][col];
				if (dig > '9' || dig < '0')
					continue;
				cur = cur * 10 + dig - '0';
			}
			probNos.push_back(cur);
		} while (allLines[allLines.size() - 1][col--] == ' ');
		char op = allLines[allLines.size() - 1][col + 1];
		long long ans = probNos[0];
		for (int i = 1; i < probNos.size(); i++) {
			if (op == '+')
				ans += probNos[i];
			if (op == '*')
				ans *= probNos[i];
		}
		part2ans += ans;
	}

	cout << "part one:" << part1ans << endl;
	cout << "part two:" << part2ans << endl;
	return 0;
}