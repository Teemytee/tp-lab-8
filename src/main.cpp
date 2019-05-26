#include "Common.h"
#include "Text.h"
int main()
{
	setlocale(LC_ALL, "rus");
	ifstream input;          
	input.open("../data/input.txt");
	if (input.is_open())
		cout << "File for reading is open\n";
	else
	{
		cout << "Problems with file for reading\n";
		return 0;
	}
	ofstream output("../data/output.txt");
	if (output.is_open())
		cout << "File for writing is open\n";
	else
	{
		cout << "Problems with file for writing\n";
		return 0;
	}
	Text mytext;
	mytext.Process(input);
	mytext.Generate(output);
	system("pause");
	return 0;
}