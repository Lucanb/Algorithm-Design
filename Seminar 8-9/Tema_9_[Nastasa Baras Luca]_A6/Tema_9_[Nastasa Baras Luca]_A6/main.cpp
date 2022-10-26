// Tema_9_[Nastasa Baras Luca]_A6.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include<fstream>
#include"Functions.cpp"
using namespace std;
int main()
{
	string x;
	vector<string> text;
	vector<string>pattern;
	ll textrow;
	ll textcol;
	ll patrow;
	ll patcol;
	cin >> textrow >> textcol;
	cin >> patrow >> patcol;
	for(int i=0;i<textrow;i++)
		for (int j = 0; j < textcol; j++)
		{
			cin >> x;
			text.push_back(x);
		}
	for (int i = 0; i < patrow; i++)
		for (int j = 0; j < patcol; j++)
		{
			cin >> x;
			pattern.push_back(x);
		}
	BaezaYatesAlgo(text, textrow, textcol,pattern,patrow,patcol);
}
