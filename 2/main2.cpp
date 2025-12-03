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


long long invalidsSum(long long min, long long max);
long long invalidsSum2(long long min, long long max);

int main(int argc, char** argv) {
	long long part1ans = 0;
	long long part2ans = 0;

	fstream inputFile;

	string line;
	inputFile.open(inputName, ios::in);
	while (getline(inputFile, line)) {
		//for each input line
		vector<long long> items;
		std::stringstream ss(line);
		long long item;
		while (ss >> item)
			items.push_back(item);
		long long k = 0;
		//all of line's items now in items
	}


	part1ans += invalidsSum(stoll(line), stoll(line.substr(line.find('-') + 1)));
	part2ans += invalidsSum2(stoll(line), stoll(line.substr(line.find('-') + 1)));

	long long currentPos = 0;
	long long lastPos = 0;
	while ((currentPos = line.find(',', lastPos)) != string::npos) {
		long long min = stoll(line.substr(currentPos + 1));
		long long max = stoll(line.substr(line.find('-', currentPos) + 1));
		part1ans += invalidsSum(min, max);
		part2ans += invalidsSum2(min, max);
		lastPos = currentPos + 1;
	}

	cout << "part one:" << part1ans << endl;
	cout << "part two:" << part2ans << endl;
	return 0;
}

long long invalidsSum(long long min, long long max) {
	long long answer = 0;
	for (long long i = min; i <= max; i++) {
		string asString = std::to_string(i);
		long long dCount = asString.size();
		if (dCount % 2)
			continue;
		if (asString.substr(0, dCount / 2) == asString.substr(dCount / 2))
			answer += i;
	}
	return answer;
}

long long invalidsSum2(long long min, long long max) {
	long long answer = 0;
	for (long long i = min; i <= max; i++) {
		string asString = std::to_string(i);
		long long dCount = asString.size();

		for (int j = 1; j < dCount; j++) {
			if (dCount % j)
				continue;
			string base = asString.substr(0, j);
			bool failed = false;
			for (int k = j; k < dCount; k+=j) 
				if (asString.substr(k, j) != base) {
					failed = true;
					break;
				}
			if (!failed) {
				answer += i;
				break;
			}
		}
	}
	return answer;
}