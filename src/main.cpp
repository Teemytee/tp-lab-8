#include <iostream>
#include <deque>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <time.h>
using namespace std;

	const int NPREF = 2;	// количество слов в префиксе
	const int MAXGEN = 1000;	//объем текста на выходе

int main()
{
	setlocale(LC_ALL, "Russian");
	typedef deque<string> prefix;
	map<prefix, vector<string>> statetab;
	prefix pref, pref12;
	vector<string> suff;
	string word;
	ifstream in("../data/input.txt");
	int random;
	if (in.is_open()){
		for (int i = 0; i < NPREF; i++){	//заполнили очереди префиксов первыми двумя словами
			in >> word;
			pref12.push_back(word);
			pref.push_back(word);
		}
		while (in >> word) {//обрабатываем оставшийся текст
			if (statetab.find(pref) == statetab.end()) {//если ключа в виде очереди таких префиксов нет - заполняем элемент словаря парой
				suff.push_back(word);
				statetab.insert(pair<prefix, vector<string>>(pref, suff));
				suff.clear();
			}
			else {//если очередь с префиксами есть, добавляем к их значениям еще один суффикс
				if(find(statetab.find(pref)->second.begin(),statetab.find(pref)->second.end(),word)== statetab.find(pref)->second.end())
					statetab[pref].push_back(word);//если суффикса еще нет в нашем словаре
			}
			pref.pop_front();//заменить W1 и W2
			pref.push_back(word);//на W2 и W3
		}
	}
	in.close();
	pref.clear();
	pref = pref12;
	ofstream out;
	out.open("../data/output.txt");
	srand(time(0));//суффиксы будут выбираться случайным образом
	out << pref[0] << ' ' << pref[1] << ' ';
	for (int i = 0; i < MAXGEN - 2; i++) {
		if (statetab.find(pref) != statetab.end()) {//если элемент с таким ключом существует, то выбираем суфф
			random = rand() % statetab[pref].size();
			out << statetab[pref][random] << ' ';
			if (i % 4 == 0)
				out << endl;
			pref.push_back(statetab[pref][random]); // заменить W1 и W2
			pref.pop_front();//на W2 и W3
		}
		else 
			break;
	}
	out.close();
    return 0;
}