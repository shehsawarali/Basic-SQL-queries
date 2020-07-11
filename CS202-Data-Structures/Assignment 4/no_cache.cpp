#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

string search(unsigned long code)
{
	ifstream data("dictionary.txt");
	string line;
	int hashcode;
	string word;

	for(int counter = 0; counter <= code; counter++)
	{
		getline(data, line);
	}

	stringstream s(line);
	s >> hashcode;
	s >> word;
	return word;
}

int main()
{
	clock_t t; 
    t = clock();

	ifstream data("secret1.txt");
	unsigned long code;
	char temp;
	while(!data.eof())
	{
		data >> code;
		data >> temp;
		string word = search(code);
		cout << word << " " ;
	}
	data.close();
	cout<<endl;

	t = clock() - t; 
    double time = ((double)t) / CLOCKS_PER_SEC; 
    cout << "Time taken without cache: " << time << "seconds" << endl; //434 secret1
}
