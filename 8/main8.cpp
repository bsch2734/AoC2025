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

class p3d {
public:
	p3d(int x, int y, int z) :
		x(x),
		y(y),
		z(z) {};

	long long x, y, z;
	
	long long squareDistanceTo(const p3d& other) {
		long long dx = x - other.x;
		long long dy = y - other.y;
		long long dz = z - other.z;
		return dx * dx + dy * dy + dz * dz;
	}
};

int main(int argc, char** argv) {
	long long part1ans = 0;
	long long part2ans = 0;

	fstream inputFile;

	string line;
	//note: must replace commas with spaces in input
	inputFile.open(inputName, ios::in);
	vector<p3d> allPoints;
	while (getline(inputFile, line)) {
		//for each input line
		vector<int> items;
		std::stringstream ss(line);
		int item;
		while (ss >> item)
			items.push_back(item);

		allPoints.push_back(p3d(items[0], items[1], items[2]));
	}

	map<pair<p3d*, p3d*>, long long> ds;
	for (int i = 0; i < allPoints.size(); i++)
		for (int j = i + 1; j < allPoints.size(); j++) {
			p3d* p1 = &allPoints[i];
			p3d* p2 = &allPoints[j];
			long long dist = p1->squareDistanceTo(*p2);
			ds[{p1, p2}] = dist;
		}
	

	vector<pair<pair<p3d*, p3d*>, long long>> v(ds.begin(), ds.end());
	sort(v.begin(), v.end(),
			[](const auto& a, const auto& b) {
				return a.second < b.second;
			}
	);

	vector<unordered_set<p3d*>*> circuits;
	for (p3d& tp : allPoints) {
		unordered_set<p3d*>* n = new unordered_set<p3d*>;
		n->insert(&tp);
		circuits.push_back(n);
	}

	int i = 0;
	while(circuits.size() > 1) {
		p3d* p1 = v[i].first.first;
		p3d* p2 = v[i].first.second;
		unordered_set<p3d*>* p1s = nullptr;
		unordered_set<p3d*>* p2s = nullptr;
		int p2pos;
		for (int j = 0; j < circuits.size(); j++) {
			unordered_set<p3d*>* s = circuits[j];
			auto r = s->find(p1);
			if (r != s->end())
				p1s = s;

			auto r2 = s->find(p2);
			if (r2 != s->end()) {
				p2pos = j;
				p2s = s;
			}
		}
		if (p1s != p2s) {
			for (auto vr : *p2s)
				p1s->insert(vr);			
			circuits.erase(circuits.begin() + p2pos);
		}
		if (circuits.size() == 1)
			part2ans = p1->x * p2->x;


		i++;
		if (i == 1000) {
			sort(circuits.begin(), circuits.end(),
				[](const auto& a, const auto& b) {
					return a->size() > b->size();
				}
			);
			part1ans = circuits[0]->size() * circuits[1]->size() * circuits[2]->size();
		}
	}



	cout << "part one:" << part1ans << endl;
	cout << "part two:" << part2ans << endl;
	return 0;
}