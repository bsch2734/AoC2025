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

bool isValid(vector<pair<long long, long long>> ranges, long long item);
long long sumRanges(vector<pair<long long, long long>> ranges);
vector<pair<long long, long long>> mergeRanges(vector<pair<long long, long long>>);

int main(int argc, char** argv) {
	int part1ans = 0;
	long long part2ans = 0;

	fstream inputFile;
	bool rDone = false;
	vector<pair<long long, long long>> ranges;
	vector<pair<long long, long long>> m;
	string line;
	inputFile.open(inputName, ios::in);
	while (getline(inputFile, line)) {
		if (line.empty()) {
			m = mergeRanges(ranges);
			rDone = true;
			continue;
		}

		if (!rDone) 
			ranges.push_back({ stoll(line), stoll(line.substr(line.find('-') + 1)) });
		else
			part1ans += isValid(ranges, stoll(line));
	}

	part2ans = sumRanges(m);

	cout << "part one:" << part1ans << endl;
	cout << "part two:" << part2ans << endl;
	return 0;
}

bool isValid(vector<pair<long long, long long>> ranges, long long item) {
	for (auto r : ranges)
		if (item >= r.first && item <= r.second)
			return true;
	return false;
}

vector<pair<long long, long long>> mergeRanges(vector<pair<long long, long long>> input) {
	vector<pair<long long, long long>> output;
	std::sort(input.begin(), input.end());

	for (int i = 0; i < input.size(); i++) {
		pair<long long, long long> merged = input[i];
		while (input.size() > i + 1 && input[i + 1].first <= merged.second + 1) {
			merged.second = max(input[i + 1].second, merged.second);
			i++;
		}
		output.push_back(merged);
	}

	return output;
}

long long sumRanges(vector<pair<long long, long long>> ranges) {
	long long output = 0;

	for (auto r : ranges)
		output += r.second - r.first + 1;

	return output;
}
