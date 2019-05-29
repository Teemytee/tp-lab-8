#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include<vector>
#include <deque>
#include <random>
#include "Generator.h"
using namespace std;
ifstream file("text.txt");


int main()
{
	setlocale(LC_ALL, "rus");
	Generator gen(100, 2);
	gen.CreateTable(file);
	gen.Generate(100, file);
	system("pause");
	return 0;
}