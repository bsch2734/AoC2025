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

int maxJoltage(string line);
int largestDigit(string s);
long long maxJoltage2(string line);

int main(int argc, char** argv) {
	int part1ans = 0;
	long long part2ans = 0;

	fstream inputFile;

	string line;
	vector<string> lines;
	inputFile.open(inputName, ios::in);
	while (getline(inputFile, line)) {
		lines.push_back(line);
		//for each input line
		vector<int> items;
		std::stringstream ss(line);
		int item;
		while (ss >> item) {
			items.push_back(item);
		}
		//all of line's items now in item
		part1ans += maxJoltage(line);
		part2ans += maxJoltage2(line);
	}

	cout << "part one:" << part1ans << endl;
	cout << "part two:" << part2ans << endl;
	return 0;
}

int maxJoltage(string line) {
	int tens = largestDigit(line.substr(0, line.size() - 1));
	int sPos = line.find('0' + tens);
	int ones = largestDigit(line.substr(sPos + 1));
	
	return tens * 10 + ones;
}

int largestDigit(string s) {
	char largest = '9';
	while (s.find(largest) == string::npos)
		largest--;
	return largest - '0';
}

long long maxJoltage2(string s) {
	long long answer = 0;
	int startPos = 0;
	for (int i = 12; i > 0; i--) {
		int cd = largestDigit(s.substr(startPos, s.size() - i + 1 - startPos));
		int where = s.find('0' + cd, startPos);
		startPos = where + 1;
		answer = 10 * answer + cd;
	}

	return answer;
}