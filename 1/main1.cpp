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

	int dPos = 50;
	while (getline(inputFile, line)) {
		//for each input line
		vector<string> items;
		std::stringstream ss(line);
		string item;
		while (ss >> item) {
			items.push_back(item);
		}
		//all of line's items now in items

		int newPos = dPos;
		int dist = stoi(&(item[1]));
		bool isLeft = item[0] == 'L';
		if (isLeft) {
			newPos -= dist;
		}
		else {
			newPos += dist;
		}
		part1ans += (newPos % 100) == 0;
		//full rotations + landed ons + skipped overs
		part2ans += (dist / 100) + ((newPos % 100) == 0) + ((dPos != 0 && isLeft) && ((dist%100) > dPos)) + (!isLeft && (((dist % 100) + dPos) > 100));

		dPos = (newPos + 1000000) % 100;
	}

	cout << "part one:" << part1ans << endl;
	cout << "part two:" << part2ans << endl;
	return 0;
}