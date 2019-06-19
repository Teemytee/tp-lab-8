#include<iostream>
#include<map>
#include<vector>
#include<deque>
#include<string>
#include<fstream>
#include<ctime>

using namespace std;

const int NPREF = 2;
const int MAXGEN = 1000; 
typedef deque<string> prefix;

int main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));

	map<prefix, vector<string> > statetab;
	string str;
	prefix start;
	prefix current_prefix;
	vector <string> suf;
	ifstream f("input.txt");
		
		for (int i = 0; i < NPREF; i++)
		{
			f >> str;
			current_prefix.push_back(str);
			start.push_back(str);
		}
		while (f>> str)
		{
			statetab[current_prefix].push_back(str);
			current_prefix.pop_front();
			current_prefix.push_back(str);
		}  
		f.close();
		current_prefix.clear();


		ofstream f_out("output.txt");
		for (int i = 0; i < NPREF; i++) {
			f_out << start[i] << " ";
		}
		current_prefix = start;
		for (int i = 0; i < MAXGEN-2; ++i) {
			if (statetab.count(current_prefix)) {
				int n = rand() % statetab[current_prefix].size();
				f_out << statetab[current_prefix][n] << " ";
				current_prefix.push_back(statetab[current_prefix][n]);
				current_prefix.pop_front();
				if(i % 5 == 0)
				f_out <<endl;
			}
			else break;
		}
		f_out.close();
	return 0;
}