#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <deque>
#include <vector>
#include <algorithm>
#include <ctime>
#define  NPREF 2
#define MAXGEN  1000
using namespace std;

typedef deque<string> prefix;
#define pb push_back
int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(0));
    vector<string> suff;
    map <prefix, vector<string> > statetab;
    ifstream file("/Users/artemaroslankin/Documents/Progacpp/untitled1/13306.txt");
    string word;
    prefix source_prefix, pref;

    if(file.is_open()){

        for(int i = 0; i < NPREF; i++){
            file >> word;
            pref.pb(word);
        }
        source_prefix = pref;

        while(file >> word){
            if(statetab.find(pref) == statetab.end()){
                suff.pb(word);
                statetab.emplace(pref, suff);
                suff.clear();
            }
            else{
                statetab[pref].pb(word);
            }
            pref.pop_front();
            pref.pb(word);
        }
    }
    pref = source_prefix;

    ofstream output("/Users/artemaroslankin/Documents/Progacpp/untitled1/output.txt");
    output << source_prefix[0] << ' ' << source_prefix[1] <<' ';
    for(int i = 0; i < MAXGEN; i++){
        if(statetab.find(pref) != statetab.end()){
            int n = rand() % statetab.find(pref)->second.size();
            output << statetab[pref][n] << ' ';
            if(i % 3 == 0)
                output << endl;
            pref.pb(statetab[pref][n]);
            pref.pop_front();
        }
    }
    file.close();
    output.close();



    return 0;
}