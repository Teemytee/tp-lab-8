#include "header.h"

int main() {

	int n;
	prefix pref;
	vector<string> vec;
	map<prefix, vector<string> > statetab;
	string str;
	vector<string> p;
	ifstream fin("input.txt");

	if (fin.is_open()) {
		for (int i = 0; i < NPREF; i++) {
			fin >> str;
			p.push_back(str);
			pref.push_back(str);
		}
		while (fin >> str) {
			if (statetab.count(pref) == 0) {
				vec.push_back(str);
				statetab.insert(pair<prefix, vector<string>>(pref, vec));
				vec.clear();
			}
			else {
				statetab[pref].push_back(str);
			}
			pref.pop_front();
			pref.push_back(str);
		}
	}
	else {
		cout << "File is not corrected!" << endl;
	}
	fin.close();
	pref.clear();

	for (int i = 0; i < NPREF; i++) {
		pref.push_back(p[i]);
	}

	ofstream out("output.txt");
	srand(time(0));
	out << pref[0] << " " << pref[1];
	for (int i = 0; i < MAXGEN - 2; i++) {
		if (statetab.count(pref)) {
			n = rand() % statetab[pref].size();
			out << statetab[pref][n] << " ";
			if ((i + 1) % 10 == 0) out << endl;
			pref.push_back(statetab[pref][n]);
			pref.pop_front();

		}
		else break;
	}
	out.close();

	return 0;

}
