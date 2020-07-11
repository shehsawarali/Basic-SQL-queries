#include <iostream> 
#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <bits/stdc++.h> 
using namespace std; 
  
int** memory;
string** mem2;
vector<int> cutpositions;
int recursive(int low, int high, string& seq, int extra);

int main(int argc, char** argv) 
{ 
	string file = argv[1]; //Assuming command is entered properly

	ifstream data;
	data.open(file); //Assuming filename is entered correctly
	/*if(!data.is_open())
	{
		cout<<"Invalid filename"<<endl;
		return 0;
	}*/

	string line; //Variables for file reading
	string temp;
	int val;
	int size;
	

	getline(data,line);
	stringstream s1(line);
	s1 >> temp;	// read n
	s1 >> size;	// read n value

	getline(data,line);
	stringstream s2(line);
	s2 >> temp; // read m
	while(s2 >> val)
	{
		cutpositions.push_back(val);
	}

	memory = new int*[size];
	mem2 = new string*[size];

	for(int i =  0; i < size; i++)
	{
		memory[i] =  new int[size];
		mem2[i] = new string[size];
		for(int j = 0; j < size; j++)
		{
			memory[i][j] = -1;
			mem2[i][j] = "\0";
		}
	}

	string seq = "";
	int cost = recursive(0 , size, seq, 0);
	string ans = "Optimal cut ordering:  ";
	ans += seq;
	ans += "\n";
	ans += "Least cost: " + to_string(cost);
	ans += "\n";
	cout<<ans;

	for(int i = 0; i < size; i++)
	{
		delete memory[i];
	}
	delete[] memory;
    return 0;
}

int recursive(int low, int high, string& seq, int extra)//O(mlogn)
{
	if(memory[high - 1][low] != -1)
	{
		// seq += " " + mem2[high - 1][low];
		if(extra == 0)
			{seq += mem2[high - 1][low];}
		else
			{seq += " " + mem2[high - 1][low];}

		return memory[high - 1][low];
	}

	if(high - 1 == low)
		{return 0;}

	string minseq;
	int minimum = INT_MAX;

	for(int i = 0; i < cutpositions.size(); i++)
	{
		int cut = cutpositions[i];
		string s = to_string(cut);
		// cout<<minseq<<endl;
		if(cut < high && cut > low)
		{
			int cost = recursive(low, cut, s, 1) + recursive(cut, high, s, 1); 
			if(cost < minimum)
			{
				minimum = cost;
				minseq = s;
			}
		}
	}

	if(minimum == INT_MAX)
	{
		minimum = 0;
	}
	else
	{
		minimum += high - low;
		if(extra == 0)
			{seq += minseq;}
		else
			{seq += " " + minseq;}
		// seq = seq + " " + minseq;
		// cout<<minseq;
	}

	memory[high - 1][low] = minimum;
	mem2[high -  1][low] = minseq;
	return minimum;
}

//Recurrence relation -> 2T(n/2) + O(m)
//Complexity -> O(mlogn)