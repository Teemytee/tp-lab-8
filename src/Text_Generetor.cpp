// Text_Generetor.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <deque>
#include <fstream>
#include <ctime>
#include <random>

using namespace std;

typedef deque<string> prefix;          // очередь префиксов
map<prefix, vector<string> > statetab; // префикс-суффиксы
const int NPREF = 2; // количество слов в префиксе
const int MAXGEN = 1000; //объем текста на выходе


int main()
{
	setlocale(LC_ALL, "rus");
	prefix pref, start;
	ifstream fout("text.txt");
	string str;
	vector <string> suf;
	for (int i = 0; i < NPREF; i++)
	{
		fout >> str;
		pref.push_back(str);
		start.push_back(str);
	}
	while (fout>>str)
	{
		statetab[pref].push_back(str);
		pref.pop_front();
		pref.push_back(str);
	}
	fout.close();
	pref.clear();


	ofstream fin("output.txt");
	for (int i = 0; i < NPREF; i++) {
		fin << start[i] << " ";
	}
	pref = start;
	srand(time(0));
	for (int i = 0; i < MAXGEN; i++) {
		if (statetab.count(pref)) {
			int n = rand() % statetab[pref].size();
			fin << statetab[pref][n] << " ";
			pref.push_back(statetab[pref][n]);
			pref.pop_front();
			if (i % 10 == 0) 
			{ 
				fin << "\n"; 
			} 
		}
		else break;
	}
	fin.close();
}

