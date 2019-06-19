#include <fstream>
#include <map>
#include <deque>
#include <vector>
#include <time.h>
#include <iostream>
#include <string>

typedef std::deque<std::string> Prefix;// очередь префиксов

const int NPREF = 2; // количество слов в префиксе
const int MAXGEN = 1000; //объем текста на выходе


int main()
{
	setlocale(LC_ALL, "Russian");

	std::map<Prefix, std::vector<std::string> > statetab; // префикс-суффикс
	Prefix prefix, start_prefix;
	
	std::ifstream f;
	f.open("nevermore.txt");
	if (f.fail())
	{
		std::cout << "File error!" <<std:: endl;
		return 1;
	}
	std::string pref, suff;
	for (auto i = 0; i < NPREF; ++i)
	{
		f >> pref;
		prefix.push_back(pref);

	}
	start_prefix = prefix;
	std::vector<std::string> suff_vec;
	while (f >> suff)
	{
		if (statetab.find(prefix) == statetab.end())
		{
			suff_vec.push_back(suff);
			statetab.insert(make_pair(prefix, suff_vec));
			suff_vec.clear();
		}
		else
		{
			statetab[prefix].push_back(suff);
		}
		prefix.push_back(suff);
		prefix.pop_front();
		
	}
	prefix = start_prefix;
	int n_suff,words_per_line = 4;
	srand(time(0));
	for (auto & pref : prefix)
		std::cout << pref << " ";
	for (auto i = 0; i < MAXGEN; ++i)
	{
		if (statetab.find(prefix) == statetab.end())
			break;
		n_suff=rand() % statetab[prefix].size();
		std::cout << statetab[prefix][n_suff] << " ";
		prefix.push_back(statetab[prefix][n_suff]);
		prefix.pop_front();
		if(i% words_per_line==0)
			std::cout << std::endl;
	}
	system("pause");
	return 0;
}
