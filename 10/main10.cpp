#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <unordered_set>
#include <bitset>

using namespace std;

string inputName = "input.txt";

struct machine {
	int size;
	uint16_t target = 0;
	vector<uint16_t> buttons;
	vector<int> joltages;
};

//iterateor to step through all possible permutations of m nonnegative integers
//that add up to n. e.g. for n=3, m=2, it will yield:
//0, 3
//1, 2
//2, 1
//3, 0
struct CompositionIterator {
	int n, m;
	std::vector<int> v;
	bool first = true;

	CompositionIterator(int n, int m)
		: n(n), m(m), v(m, 0)
	{	
		v[0] = 0;
		v[m - 1] = n; //start at 0,0,...,n
	}

	//returns false when finished
	//else returns true and updates v to the next composition
	bool next() {
		if (first) {
			first = false;
			return true;
		}

		// find the rightmost index we can increment
		for (int i = m - 2; i >= 0; i--)
			if (v[i] < n) {
				int usedBefore = 0;
				for (int j = 0; j < i; j++)
					usedBefore += v[j];

				if (usedBefore + v[i] + 1 <= n) {
					v[i]++;

					int remaining = n - usedBefore + v[i];
					for (int j = i + 1; j < m - 1; j++)
						v[j] = 0;

					v[m - 1] = remaining;
					return true;
				}
			}
		return false; //no more
	}
};

int findPresses(machine m);

int main(int argc, char** argv) {
	long long part1ans = 0;
	long long part2ans = 0;

	fstream inputFile;
	int progress = 0;
	string line;
	inputFile.open(inputName, ios::in);
	while (getline(inputFile, line)) {
		//for each input line
		vector<string> items;
		std::stringstream ss(line);
		string item;
		while (ss >> item)
			items.push_back(item);
		machine m;
		m.size = items[0].size() - 2;
		for (int i = 1; i < items[0].size() - 1; i++) {
			m.target = m.target << 1;
			m.target |= items[0][i] == '#';
		}
		int i = 1;
		while (items[i][0] != '{') {
			uint16_t button = 0;
			for (int j = 1; j < items[i].size() - 1; j += 2)
				button |= 1u << m.size - 1 - (items[i][j] - '0');
			m.buttons.push_back(button);
			i++;
		}
		std::stringstream ss2(items[i].substr(1));
		while (std::getline(ss2, item, ','))
			m.joltages.push_back(std::stoi(item));

		sort(m.buttons.begin(), m.buttons.end(),
			[](const auto& a, const auto& b) {
				return bitset<32>(a).count() < bitset<32>(b).count();
			});


		int maxMask = pow(2, m.buttons.size());
		bool found = false;
		for (int count = 1; count <= m.buttons.size() && !found; count++) {
			for (int mask = 1; mask < maxMask && !found; mask++) {
				int afterPresses = 0;
				bitset<32> bits(mask);
				if (bits.count() == count)
					//found valid mask, use it
					for (int currButton = 0; currButton < m.buttons.size(); currButton++) 
						//if button is included, apply it
						if (1u << currButton & mask)
							afterPresses ^= m.buttons[m.buttons.size() - 1 - currButton];
				if (afterPresses == m.target)
					found = true;
			}
			if (found)
				part1ans += count;
		}
		part2ans +=findPresses(m);
		cout << progress++ << endl;
	}

	cout << "part one:" << part1ans << endl;
	cout << "part two:" << part2ans << endl;
	return 0;
}

int findPresses(machine m) {
	if (m.buttons.empty()) {
		for (int i : m.joltages)
			if (i)
				return -1; //no buttons, joltages not matched, dead end
		return 0; //no buttons, joltages solved, successful path
	}

	bool someLeft = false;
	for (int i : m.joltages)
		if (someLeft = i)
			break;
	if (!someLeft)
		return 0; //joltages solved without using all buttons, successful path

	//minPresses is the highest joltage left; that many presses is a minimum to solve from here
	//maxIndex is the index on m.joltages that contains minPresses
	int minPresses = INT_MAX;
	int maxIndex = -1;
	for (int i = 0; i < m.joltages.size(); i++) {
		int joltage = m.joltages[i];
		if (joltage > 0 && minPresses > joltage) {
			minPresses = joltage;
			maxIndex = i;
		}
	}

	//maxIndex contains index of the most needed
	//try all combos that satisfy it
	
	//find which buttons affect maxIndex
	vector<int> affectingButtons;
	for (int i = 0; i < m.buttons.size(); i++)
		if ((1u << (m.size - 1 - maxIndex)) & m.buttons[i])
			affectingButtons.push_back(i);

	if (affectingButtons.empty())
		return -1; //no buttons affect the largest remaining joltage, dead end

	CompositionIterator iter(minPresses, affectingButtons.size());
	//try all combinations
	int best = INT_MAX;
	auto freshM = m;
	while (iter.next()) {
		m = freshM;
		//press each affecting button
		for (int i = 0; i < affectingButtons.size(); i++) {
			auto thisButton = m.buttons[affectingButtons[i]];
			for (int j = 0; j < m.joltages.size(); j++)
				//if this button changes that joltage
				if(1u << m.size - 1 - j & thisButton)
					m.joltages[j] -= iter.v[i];
		}
		for (int i = affectingButtons.size() - 1; i >= 0; i--)
			m.buttons.erase(m.buttons.begin() + affectingButtons[i]);
		int recur;
		if ((recur = findPresses(m)) != -1)
			best = min(recur + minPresses, best);
	}
	if (best != INT_MAX)
		return best;

	return -1;
}
