#pragma once
#include <iostream>
#include <deque>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <ctime>
#include <iterator>

using namespace std;

const int NPREF = 2;//количество слов в префиксе
const int MAXGEN = 1000; //объем текста на вызоде
typedef deque<string> prefix; //очередь префиксов
