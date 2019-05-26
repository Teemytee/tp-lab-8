#ifndef _TEXT_H_
#define _TEXT_H_
#include "Common.h"
class Text
{
private:
	map<prefix, vector<string> > statetab; // prefix - suffixes
	deque<string> for_start;//first and second words
public:
	Text();
	void Process(ifstream &input);
	void Generate(ofstream &output);
};
#endif