#include <iostream>
#include <map>
#include <deque>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
using namespace std;
const int NPREF = 2;
const int MAXGEN = 100;
typedef deque<string> prefix;


int main()
{
	setlocale(LC_ALL, "Russian");
	map<prefix, vector<string> > statetab;
	string str;
	prefix start;
	prefix cur;
	ifstream file("F.txt");

	for (int i = 0; i < NPREF; i++) {
		file >> str;
		start.push_back(str);
	}

	cur = start;

	while (getline(file, str, ' ')) {

		statetab[cur].push_back(str);

		cur.pop_front();
		cur.push_back(str);
	}

	cur = start;
	for (int i = 0; i < NPREF; i++)
	{
		cout << cur[i] << " ";
	}
	srand(time(NULL));
	for (int i = 0; i < MAXGEN; i++)
	{
		if (statetab.count(cur) > 0)
		{
			int n = rand() % statetab[cur].size();
			cout << statetab[cur][n] << " ";
			cur.push_back(statetab[cur][n]);
			cur.pop_front();

		}
		else break;
	}
	return 0;
}