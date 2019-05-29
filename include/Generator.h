#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include<vector>
#include <deque>
#include <random>
using namespace std;
ofstream output("newt.txt");

class Generator 
{
private:
	typedef deque<string> prefix;
	int MAXGEN;
	int NPREF;
	map<prefix, vector<string>> statetab;// префикс-суффиксы
	prefix pref;
	int fsize;
public:
	Generator()
	{
		MAXGEN = 0;
		NPREF = 0;
	}
	Generator(int maxgen, int npref) 
	{
		this->MAXGEN = maxgen;
		this->NPREF = npref;
	}
	

	void TableAdd(prefix & pref, const string & s)
	{
		if (pref.size() == NPREF)
		{
			statetab[pref].push_back(s);
			pref.pop_front();
		}
		pref.push_back(s);
	}
	void CreateTable(ifstream & in)
	{
		string word;
		while (in >> word)
		{
			TableAdd(pref, word);
			fsize++;
		}
		in.clear();
		in.seekg(0);
		int i = 0;
		while (in >> word && i != 0)
		{
			TableAdd(pref, word);
			i--;
		}
		
	}

	void Generate(int num, ifstream &in)
	{
		prefix prefix;
		random_device ran;
		int i = 0;
		string word;
		in.clear();
		in.seekg(0);
		while (in >> word && i < NPREF)
		{
			TableAdd(prefix, word);
			i++;
		}
		output << prefix[0]<<" ";
		output << prefix[1]<<" ";
		cout << prefix[0] << endl;
		cout << prefix[1] << endl;
		for (int i = 0; i < num-NPREF; i++)
		{

			vector<string> suffix = statetab[prefix];
			string word = suffix[ran() % suffix.size()];
			output << word << " ";
			if (i % 3 == 0)
				output << endl;
			cout << word << " ";
			prefix.pop_front();
			prefix.push_back(word);
		}
	}
	~Generator() {};
};