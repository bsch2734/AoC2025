#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <unordered_set>

using namespace std;

struct PairHash {
	std::size_t operator()(const std::pair<int, int>& p) const {
		return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
	}
};

long long beamCount(pair<int, int> s);

string inputName = "input.txt";
vector<string> input;
int main(int argc, char** argv) {
	long long part1ans = 0;
	long long part2ans = 0;

	fstream inputFile;

	string line;
	inputFile.open(inputName, ios::in);
	while (getline(inputFile, line))
		input.push_back(line);

	unordered_set<pair<int, int>, PairHash> beams;
	int sPos = input[0].find('S');
	beams.insert({ 0, sPos });

	while (!beams.empty()) {
		unordered_set<pair<int, int>, PairHash> nextBeams;
		for (auto b : beams) {
			if (b.first == input.size() - 1)
				continue;
			if (input[b.first + 1][b.second] == '.')
				nextBeams.insert({ b.first + 1, b.second });
			if (input[b.first + 1][b.second] == '^') {
				nextBeams.insert({ b.first + 1, b.second + 1});
				nextBeams.insert({ b.first + 1, b.second - 1});
				part1ans++;
			}
		}
		beams = nextBeams;
	}

	part2ans = beamCount({ 0, sPos });


	cout << "part one:" << part1ans << endl;
	cout << "part two:" << part2ans << endl;
	return 0;
}


long long beamCount(pair<int, int> s) {
	static map<pair<int, int>, long long> memos;

	auto v = memos.find(s);
	if (v != memos.end())
		return (*v).second;

	long long ans = 0;
	
	if (s.first == input.size() - 1) {
		ans = 1;
	}
	else if (input[s.first + 1][s.second] == '.')
		ans = beamCount({s.first + 1, s.second});
	else if (input[s.first + 1][s.second] == '^') {
		ans += beamCount({ s.first + 1, s.second + 1});
		ans += beamCount({ s.first + 1, s.second - 1});
	}

	memos[s] = ans;
	return ans;
}