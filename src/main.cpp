//
// Created by pavel on 01.06.19.
//
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <vector>
#include <map>

using namespace std;

int main()
{
    srand(time(NULL));
    typedef deque<string> prefix;          // очередь префиксов
    map<prefix, vector<string> > statetab; // префикс-суффиксы
    vector <string>  suff;
    const int NPREF=2; // количество слов в префиксе
    const int MAXGEN=1000; //объем текста на выходе
    ifstream file("../data/in.txt");
    string word;
    prefix pref, initial_pref;

    if (file.is_open())
    {
        for (int i(0); i < NPREF; i++)
        {
            file >> word;
            pref.push_back(word);
        }
        initial_pref = pref;
        while (file >> word)
        {

            statetab[pref].push_back(word);
            pref.pop_front();
            pref.push_back(word);
        }
    }
    pref = initial_pref;

    ofstream out("../data/out.txt");
    out << initial_pref[0] << ' ' << initial_pref[1] << ' ';
    for (int i(0); i < MAXGEN; i++)
    {
        int n = rand() % statetab[pref].size();
        out << statetab[pref][n] << ' ';
        if (i % 3 == 0)
            out << endl;
        pref.push_back(statetab[pref][n]);
        pref.pop_front();
    }
    file.close();
    out.close();
    return 0;
}