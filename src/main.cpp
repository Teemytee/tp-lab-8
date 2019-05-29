#include <iostream>
#include <vector>
#include <map>
#include <deque>
#include <fstream>
#include "stdlib.h"
#include <time.h>

using namespace std;
const int NPREF=2;
const int MAXGEN=100;

int main()
{
    ifstream file("File.txt");
    string result;
    map< deque<string>, vector<string> > statetab;
    deque<string> storage, start;
    for (int i = 0; i < NPREF; i++)
    {
        getline(file, result, ' ');
        storage.push_back(result);
    }
    start = storage;
    while(getline(file, result, ' '))
    {
        statetab[storage].push_back(result);
        storage.pop_front();
        storage.push_back(result);
    }

    vector<string> tmp;
    storage = start;
    for (int i = 0; i < NPREF; i++)
    {
        cout<<storage[i]<<" ";
    }
    srand(time(0));
    for (int i = 0; i < MAXGEN; i++)
    {
        tmp = statetab[storage];
        int max_index = tmp.size();
        int index = rand()%max_index;
        cout<<tmp[index]<<" ";
        storage.pop_front();
        storage.push_back(tmp[index]);
    }
    return 0;
}
