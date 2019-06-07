#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<deque>
#include<string>
#include <ctime>

using namespace std;

int main() {
	typedef deque<string> prefix; 
	map<prefix, vector<string>> statetab; 

	const int NPREF = 3; 

	const int MaXGEN = 1000;  

	string str;				// слово из потока

	prefix pref;			// тут храним NPREF префиксов

	map<prefix, vector<string>>::iterator it; //итератор мапы, сохраняет в себе результат метода find, 
											  //когда мы проверяем, есть ли у нас уже такой префикс или нет
																		
	prefix firstWords;				// тут храним первые NPREF слов, чтобы потом, используя  таблицу,
											// составить дальнейший текст

	ifstream f("D://Clion_projects//lab8//input.txt");				//считываем файл по словам
	if (f.is_open())						// если файл открыт, то начинаем составление таблицы
	{
		for (int i = 0; i < NPREF; i++) {	// создаем самый первый префикс из NPREF слов
			f >> str;
			pref.push_back(str);				// создаем сам префикс
		}
		firstWords = pref;
		while (f >> str) {					// пока поток считывает слова											
		
			statetab[pref].push_back(str);			
			pref.pop_front(); // удаляем первое слово из префикса
			pref.push_back(str); // добавляем новое слово
								// это делается, чтобы идти по тексту и собирать новые префиксы/постфиксы
		}
	}
	else {
		cout <<"cannot open\n";
	}
	
	f.close();						

	ofstream f2("D://Clion_projects//lab8//output.txt");

	pref = firstWords;
	
	for (int i = 0; i < NPREF; i++) {   //стартовые NPREF слова
		f2 << firstWords[i] << ' ';				
	}
	
	int n;								// рандомное число для выбора постфикса (если их несколько)
	int NCycle;							
									
	srand(time(NULL));					

	for (int i = 0; i < MaXGEN; i++){
		it = statetab.find(pref);		
		if (it != statetab.end()) {		

			n = rand() % it->second.size(); // выбираем рандомно номер префикса. рандом высчитвается
											// в зависимости от размера вектора постфиксов
			f2 << it->second[n] << ' ';		// записываем рандомно выбранный постфикс в файл
			pref.pop_front();				// первое слово из префикса выкидываем
			pref.push_back(it->second[n]);  // а новое выбранное рандомно слово добавляем
											// теперь find уже будет делаться по новому префиксу 
		}
	}
	f2.close();								// закрываем поток вывода

	return 0;
}