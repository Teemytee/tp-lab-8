#include <iostream>
#include <vector>
#include <map>
#include <deque>
#include <fstream>
#include "stdlib.h"
#include <random>
#include <limits.h>
#include <string>
#include <ctime>

const int NPREF = 2;
const int MAXGEN = 1000;
typedef std::deque<std::string> prefix;
typedef std::vector<std::string> suffix;

int main() {
	int maxIndex;
	std::ifstream fd_input("input.txt");
	std::string result;
	std::map<prefix, suffix> statetab;
	std::deque<std::string> data, base;

	for (int i = 0; i < NPREF; ++i) {
		getline(fd_input, result, ' ');
		data.push_back(result);
	}
	base = data;
	while (getline(fd_input, result, ' ')) {
		statetab[data].push_back(result);
		data.pop_front();
		data.push_back(result);
	}
	std::ofstream out("output.txt");
	std::vector<std::string> tmp;
	data = std::move(base);
	for (int i = 0; i < NPREF; ++i) {
		out << data[i] << ' ';
	}

	//std::random_device devRand;
	//std::mt19937 gen(devRand());
	//std::uniform_int_distribution<int> uid(1, INT_MAX);
	srand(time(0));
	for (int i = 0; i < MAXGEN - 2; i++) {
		tmp = statetab[data];
		maxIndex = tmp.size();
		int index = rand() % maxIndex;
		out << tmp[index] << ' ';
		data.pop_front();
		data.push_back(tmp[index]);
	}
	return 0;
}