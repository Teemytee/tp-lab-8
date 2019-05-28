#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <deque>
#include <string>
#include <ctime>
#include <iterator>
using namespace std;

const int NPREF = 2; 
const int MAXGEN = 1000; 
typedef deque<string> prefix;          

int main() 
{

	int n;
	prefix prfx;
	vector<string> vec;
	map<prefix, vector<string> > statetab; 
	string s;
	vector<string> v;
	ifstream fin("input.txt");

	if (fin.is_open()) 
	{
		for (int i = 0; i < NPREF; i++) 
		{
			fin >> s;
			v.push_back(s);
			prfx.push_back(s);
		}
		while (fin >> s) {
			if (statetab.count(prfx) == 0) 
			{
				vec.push_back(s);
				statetab.insert(pair<prefix, vector<string>>(prfx, vec));
				vec.clear();
			}
			else 
			{
				statetab[prfx].push_back(s);
			}
			prfx.pop_front();
			prfx.push_back(s);
		}
	}
	else 
	{
		cout << "File is not found" << endl;
	}
	fin.close();
	prfx.clear();

	for (int i = 0; i < NPREF; i++) 
	{
		prfx.push_back(v[i]);
	}

	ofstream out("output.txt");
	srand(time(0));
	out << prfx[0] << " " << prfx[1];
	for (int i = 0; i < MAXGEN - 2; i++) 
	{
		if (statetab.count(prfx)) 
		{
			n = rand() % statetab[prfx].size();
			out << statetab[prfx][n] << " ";
			if ((i + 1) % 10 == 0) out << endl;
			prfx.push_back(statetab[prfx][n]);
			prfx.pop_front();

		}
		else break;
	}
	out.close();

	return 0;

}