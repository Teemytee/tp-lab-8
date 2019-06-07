#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <deque>
#include <string>
#include <ctime>
#include <iterator>

using namespace std;

const int NPREF = 2;			// количество слов в префиксе
const int MAXGEN = 2000;		//объем текста на выходе

typedef deque<string> prefix;	// очередь префиксов

int main()
{
	setlocale(LC_ALL, "Russian");

	string curr_str;						// считываемая строка
	prefix curr_prefix;						// префикс
	map<prefix, vector<string> > statetab;	// "таблица" префиксов-суффиксов
	vector<string> tmpVecStr;				// вектор для хранения строки
	vector<string> chosenPrefixesVec;		// вектор для хранения выбранных префиксов

	ifstream input_file("input.txt"); // Откроем файл с исходным текстом для чтения (корпус)

	if (input_file.is_open()) // если файл открыть удалось
	{
		cout << "File opened successfully!" << endl;
		for (int i = 0; i < NPREF; i++) // выберем префикс
		{
			input_file >> curr_str; // считываем слово из файла и записываем в переменную curr_str
			curr_prefix.push_back(curr_str); // добавим это слово в конец очереди префиксов
			chosenPrefixesVec.push_back(curr_str); // "запомним" только что добавленное слово
		}

		while (input_file >> curr_str) // до тех пор, пока можем считывать слова
		{
			if (statetab.count(curr_prefix) == 0) // если "таблица" пуста
			{
				tmpVecStr.push_back(curr_str); // добавляем наше слово в вектор
				statetab.insert(pair<prefix, vector<string>>(curr_prefix, tmpVecStr)); // вставляем его в таблицу
				tmpVecStr.clear(); // очищаем вектор чтобы добавить другое слово
			}
			else statetab[curr_prefix].push_back(curr_str); // иначе просто добавляем в таблицу наше только что считанное слово
			
			curr_prefix.pop_front(); // удалим первое слово префикс
			curr_prefix.push_back(curr_str); // добавим другое слово
		}
	}
	else cout << "Can not open the file!" << endl;

	input_file.close(); // закрываем файл для чтения
	curr_prefix.clear(); // очистим вектор префиксов

	for (int i = 0; i < NPREF; i++) // заново заполним массив префиксов первыми словами
	{
		curr_prefix.push_back(chosenPrefixesVec[i]); // возьмем из "памяти" наши слова и заполним ими вектор префиксов
	}

	int rand_num; // будучи рандомный индекс

	ofstream output_file("output.txt"); // Откроем файл для записи

	srand(time(0)); // для генерации рандома
	output_file << curr_prefix[0] << " " << curr_prefix[1] << " "; // выведем первые два префикса на экран
	for (int i = 0; i < MAXGEN - 2; i++) // пройдемся по всему оставшемуся
	{
		if (statetab.count(curr_prefix)) // если "таблица" не пуста
		{
			rand_num = rand() % statetab[curr_prefix].size(); // сгенерируем случайное число
			
			output_file << statetab[curr_prefix][rand_num] << " "; // запишем случайный префикс и пробел
			if ((i + 1) % 10 == 0) output_file << endl;	// красная строка для каждого 10ого слова
			
			// "продвигаем" очередь
			curr_prefix.push_back(statetab[curr_prefix][rand_num]); // подтягиваем следующее на очереди слово
			curr_prefix.pop_front(); //удаляем первое слово из очереди
		}
		else break;
	}
	output_file.close(); // закрываем файл для записи

	return 0;
}