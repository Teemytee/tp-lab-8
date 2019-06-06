#include "header.h"

int main() {

	int n;
	prefix pref; //тек вводимый префикс
	vector<string> vec; //суффиксы
	map<prefix, vector<string> > statetab; //префикс-суффиксы
	string str;
	prefix p;
	ifstream fin("input.txt"); //файл с исходным текстом

	if (fin.is_open()) { //считываем файл
		for (int i = 0; i < NPREF; i++) {
			fin >> str; 
			pref.push_back(str); //запись префикса
			p.push_back(str);
		}
		while (fin >> str) {
			if (statetab.count(pref) == 0) {
				vec.push_back(str); //запись суффикса
				statetab.insert(pair<prefix, vector<string>>(pref, vec)); //помещаем полученные  префф-суфф в statetab
				vec.clear(); 
			}
			else {
				statetab[pref].push_back(str);
			}
			pref.pop_front();
			pref.push_back(str);
		}
	}
	else {
		cout << "File is not corrected!" << endl;
	}
	fin.close();
	pref.clear(); 

	for (int i = 0; i < NPREF; i++) {
		pref.push_back(p[i]); 
	}

	ofstream out("output.txt");
	srand(time(0));
	out << pref[0] << " " << pref[1];
	for (int i = 0; i < MAXGEN - 2; i++) {
		if (statetab.count(pref)) { //берем префф 
			n = rand() % statetab[pref].size(); //для него выбирается случайный суфф
			out << statetab[pref][n] << " "; 
			if ((i + 1) % 10 == 0) out << endl; //разделить строки между собой
			pref.push_back(statetab[pref][n]);
			pref.pop_front();

		}
		else break;
	}
	out.close();
	return 0;
}
