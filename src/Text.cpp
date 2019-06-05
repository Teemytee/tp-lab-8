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

int main() {

	prefix pr;
	vector<string> suf;
	map<prefix, vector<string> > statetab; // префикс-суффиксы
	prefix start;

	ifstream inFile("input.txt");
	string word;
	for (int i = 0; i < NPREF; i++) {
		inFile >> word;
		pr.push_back(word);
		start.push_back(word);
	}
	while (inFile >> word) {
		if (statetab.count(pr) == 0) {
			suf.push_back(word);
			statetab.insert(pair<prefix, vector<string> >(pr, suf));
			suf.clear();
		}
		else {
			statetab[pr].push_back(word);
		}
		pr.pop_front();
		pr.push_back(word);
	}
	inFile.close();
	pr.clear();


	ofstream outFile("output.txt");
	for (int i = 0; i < NPREF; i++) {
		outFile << start[i] << " ";
	}
	pr = start;
	srand(time(0));
	for (int i = 0; i < MAXGEN - 2; i++) {
		if (statetab.count(pr)) {
			int n = rand() % statetab[pr].size();
			outFile << statetab[pr][n] << " ";
			pr.push_back(statetab[pr][n]);
			pr.pop_front();

			if ((i + 1) % 10 == 0) { outFile << "\n"; } // разделитель
		}
		else break;
	}
	outFile.close(); 		
}