#include <iostream>
#include <fstream>
#include <deque>
#include <vector>
#include <string>
#include <locale.h>
#include <map>
#include <random>
#include <time.h>

typedef std::deque<std::string> prefix;

const int NPREF  = 2;	 //количество слов в префиксе
const int MAXGEN = 1000; //объем текста на выходе

const auto STANDART_INPUT_PATH  = "input.txt";
const auto STANDART_OUTPUT_PATH = "output.txt";

int main(size_t argc, char* argv[])
{
	setlocale(LC_ALL, "russian");
	
	std::map<prefix, std::vector<std::string>> statetab;
	char* path = argv[0];

	/////////////////////////////////////////////////////init statetab////////////
	if (argc > 1)		path = argv[1];

	else				strcpy(path, STANDART_INPUT_PATH);

	std::ifstream input(path);
	if (!input)
	{
		std::cout << "Error opening input file!" << std::endl;
		exit(-1);
	}

	std::string word;
	prefix pref, start_pref;

	for (int i = 0; i < NPREF; ++i)
	{
		input >> word;
		pref.push_back(word);
	}
	start_pref = pref;

	while (input >> word)
	{
		statetab[pref].push_back(word);
		pref.pop_front();
		pref.push_back(word);
	}

	input.close();
	//////////////////////////////////////////////////////////////////////////////
	if (argc > 2)		path = argv[2];

	else				strcpy(path, STANDART_OUTPUT_PATH);

	std::ofstream output(path);
	if (!output)
	{
		std::cout << "Error opening output file!" << std::endl;
		exit(-1);
	}

	auto iter = statetab.begin();
	std::advance(iter, rand() % statetab.size());
	pref = iter->first;
	//pref = start_pref;
	srand(time(NULL));
	for (int i = 0; i < MAXGEN; ++i)
	{
		auto map_it = statetab.find(pref);
		if (map_it != statetab.end())
		{
			auto random = rand() % map_it->second.size();
			output << map_it->second[random] << " ";
			pref.pop_front();
			pref.push_back(map_it->second[random]);
		}
	}
	output.close();


	return 0;
}