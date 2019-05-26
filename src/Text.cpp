#include "Text.h"
Text::Text(){}
void Text::Process(ifstream &input)
{
	vector<string> tmp_sufix;
	deque<string> tmp_prefix;
	string word;
	for (int i = 0; i < NPREF; i++)
	{
		input >> word;
		tmp_prefix.push_back(word);
		for_start.push_back(word);
	}
	while ((input >> word))
	{
		if (statetab.count(tmp_prefix) == 0)
		{
			tmp_sufix.push_back(word);
			statetab.insert(pair<prefix, vector<string> >(tmp_prefix, tmp_sufix));
			tmp_sufix.clear();
		}
		else
			statetab[tmp_prefix].push_back(word);
		tmp_prefix.pop_front();
		tmp_prefix.push_back(word);
	}
}
void Text::Generate(ofstream &output)
{
	int count = 0;
	string word;
	deque<string> tmp_prefix;
	tmp_prefix = for_start;
	for (int i = 0; i < NPREF; i++)
		output << tmp_prefix[i] << ' ';

	while (MAXGEN>count)
	{
		srand(time(0));
		count++;
		if (statetab.count(tmp_prefix) != 0)
		{
			word = statetab[tmp_prefix][rand() % (statetab[tmp_prefix].size())];
			output << word << ' ';
			tmp_prefix.pop_front();
			tmp_prefix.push_back(word);
		}
		else count = MAXGEN;
	}

}