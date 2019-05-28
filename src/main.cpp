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

	const int NPREF = 2; 
	const int MaXGEN = 1000; 

	vector <string> temp; 
	string str;				
	prefix pref;
	map<prefix, vector<string>>::iterator it; 
	vector<string> ::iterator itVec;		
	vector<string> firstWords;				

	ifstream f("input.txt");				
	if (f.is_open())						
	{
		for (int i = 0; i < NPREF; i++) {	
			f >> str;
			firstWords.push_back(str);		
			pref.push_back(str);			
		}
		while (f >> str) {					
			
			temp.push_back(str);			
											

			it = statetab.find(pref);		
			if (it == statetab.end()) {		
				statetab.emplace(pref, temp);
			}
			else							
			{
				itVec = find(it->second.begin(), it->second.end(), str);
				if (itVec == it->second.end()) 
					(it->second).push_back(str);
			}

			pref.pop_front(); 
			pref.push_back(str); 
			temp.clear();		
		}
	}
	else {
		cout << "cannot open\n";
	}

	f.close();						

	ofstream f2("output.txt");		
	pref.clear();					

	for (int i = 0; i < NPREF; i++) {  
		f2 << firstWords[i] << ' ';		
		pref.push_back(firstWords[i]);	
	}
	
	int n;		
									
	srand(time(NULL));					

	for (int i = 0; i < MaXGEN; i++)	
	{
		it = statetab.find(pref);		
		if (it != statetab.end()) {		
			n = rand() % it->second.size(); 
											
			f2 << it->second[n] << ' ';		
			pref.pop_front();				
			pref.push_back(it->second[n]);  
		}
	}
	f2.close();								

	return 0;
}