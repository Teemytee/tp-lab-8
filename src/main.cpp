// ConsoleApplication2.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include <map>
#include <deque>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
using namespace std;
const int NPREF = 2; // количество слов в префиксе
const int MAXGEN = 1000; //объем текста на выходе
typedef deque<string> prefix;          // очередь префиксов



int main()
{
	setlocale(LC_ALL, "Russian");
	map<prefix, vector<string> > statetab;
	string result;
	prefix start;
	prefix current_pr;
	srand(time(NULL));
	ifstream file("File.txt");
	int n;

	for (int i = 0; i < NPREF; i++)
	{
		getline(file, result, ' ');
		start.push_back(result);
	}
	current_pr = start;
	while (getline(file, result, ' '))
	{
		statetab[current_pr].push_back(result);
		current_pr.pop_front();
		current_pr.push_back(result);
	}
	current_pr = start;

	for (int i = 0; i < NPREF; i++)
	{
		cout << current_pr[i] << " ";
	}

	for (int i = 0; i < MAXGEN; i++)
	{
		if (statetab.count(current_pr) > 0)
		{
			n = rand() % statetab[current_pr].size();
			cout << statetab[current_pr][n] << " ";
			current_pr.push_back(statetab[current_pr][n]);
			current_pr.pop_front();

		}
		else break;
	}
    return 0;
}

