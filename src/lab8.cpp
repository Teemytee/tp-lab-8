#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<deque>
#include<string>
#include <ctime>

using namespace std;

int main() {
	//setlocale(LC_ALL, "Russian");
	typedef deque<string> prefix;
	map<prefix, vector<string>> statetab;

	const int NPREF = 2;
	const int MaXGEN = 1000;

	map<prefix, vector<string>>::iterator it;
	string str;
	prefix pref;
	prefix startWords;

	ifstream f("text.txt");
	if (f.is_open())
	{
		for (int i = 0; i < NPREF; i++) {
			f >> str;
			pref.push_back(str);
		}

		startWords = pref;

		while (f >> str) {
			
			statetab[pref].push_back(str);
															
			pref.pop_front();
			pref.push_back(str);
		}
	}
	else {
		cout << "cannot open\n";
	}


	ofstream f2("out_text.txt");
	
	int numPostf;

	for (int i = 0; i < NPREF; i++) {
		 f2 << startWords[i] << " ";
	}


	srand(time(NULL));
	pref = startWords;
	for (int i = 0; i < MaXGEN; i++)
	{
		it = statetab.find(pref);
		if (it!=statetab.end())
		{
			numPostf =rand() % (it->second).size();
			f2 << it->second[numPostf] << " ";
			pref.pop_front();
			pref.push_back(it->second[numPostf]);
		}

	}
	f2.close();
	

	return 0;
}