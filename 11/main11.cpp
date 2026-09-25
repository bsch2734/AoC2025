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

int part1(string start);
long long part2(string start, unordered_set<string> soFar, bool, bool);


map<string, vector<string>> devices;
int main(int argc, char** argv) {
	long long part1ans = 0;
	long long part2ans = 0;

	fstream inputFile;
	string line;
	inputFile.open(inputName, ios::in);
	while (getline(inputFile, line)) {
		//for each input line
		vector<string> items;
		std::stringstream ss(line);
		string item;
		while (ss >> item)
			items.push_back(item);
		string name = items[0].substr(0, 3);
		devices[name] = vector<string>(items.begin() + 1, items.end());
	}

	part1ans = part1("you");
	unordered_set<string> server;
	server.insert("svr");
	part2ans = part2("svr", server, false, false);

	cout << "part one:" << part1ans << endl;
	cout << "part two:" << part2ans << endl;
	return 0;
}

int part1(string start) {
	if (start == "out")
		return 1;

	int ans = 0;
	for (auto s : devices[start])
		ans += part1(s);

	return ans;
}

long long part2(string start, unordered_set<string> soFar, bool foundFft, bool foundDac) {
	static map<tuple<string, bool, bool>, long long> memo;
	map<tuple<string, bool, bool>, long long>::iterator d;
	if ((d = memo.find({ start, foundFft, foundDac })) != memo.end())
		return d->second;

	if (start == "out")
		return soFar.find("dac") != soFar.end() && soFar.find("fft") != soFar.end();

	long long ans = 0;
	for (auto s : devices[start]) {
		foundFft = foundFft || start == "fft";
		foundDac = foundDac || start == "dac";
		if (soFar.find(s) == soFar.end()) {
			soFar.insert(s);
			ans += part2(s, soFar, foundFft, foundDac);
		}
	}
	memo[{start, foundFft, foundDac}] = ans;
	return ans;
}
