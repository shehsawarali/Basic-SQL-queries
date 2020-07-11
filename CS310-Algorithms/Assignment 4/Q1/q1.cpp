#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
 
using namespace std;

int recursive(int n);
vector<int> RH;
vector<int> RL;
vector<int> memory;
vector<int> flag;

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


	for(int i = 0; i < size; i++) //initializing mem and flag size to n value
	{
		flag.push_back(-1); //initializing to default values indicating unprocessed index
		memory.push_back(-1);
	}

	getline(data, line);
	stringstream s2(line);
	s2 >> temp; //read RH
	while(!s2.eof() && s2 >> val)
	{
		RH.push_back(val);
	}

	getline(data, line);
	stringstream s3(line);
	s3 >> temp; //read RL
	while(!s3.eof() && s3 >> val)
	{
		RL.push_back(val);
	}

	int rev = recursive(size - 1);
	// cout<<rev<<endl;

	for(int i = size - 1; i > 0; i--) //going from problem to subproblem
	{
		if(flag[i] == 2) //if a day yields max revenue on high, set the previous day to priming
			{flag[i - 1] = 0;} //flag of 0 means priming on that day
	}

	string ans = "";
	for(int i = 0; i < size; i++) //ANS FORMAT
	{
		ans += "Week " + to_string(i + 1);
		ans += ": ";

		if(flag[i] == 0) //if priming
			{ ans += "Priming"; }

		else if(flag[i] == 2) //if high
			{ ans += "High " + to_string(RH[i]); }

		else if(flag[i] == 1) //if low
			{ ans += "Low " + to_string(RL[i]); }

		ans += "\n";
	}

	ans += "Total Revenue: " + to_string(rev);
	ans += "\n";
	cout << ans;
	return 0;
}

int recursive(int n) //O(n)
{
	if(n >= 0 && memory[n] >= 0) //If max for day is in memory array return that max *memoization*
		{return memory[n];}

	/*if(n == 0)
	{
		if(RH[n] > RL[n])
		{
			flag[n] = "high";
			memory[n] = RH[n];
		}
		else
		{
			flag[n] = "low";
			memory[n] = RL[n];
		}
		return memory[n];
	}*/

	if(n < 0) //Base case
		{return 0;}

	int high, low;

	high =  RH[n] + recursive(n - 2); //in case  of high, n-1 will be priming so we check nonpriming n - 2
	low = RL[n] + recursive(n - 1);//in case of low, n-1 will be nonpriming so we check it

	if(high > low)//max
	{
		flag[n] = 2; //flag of 2 means high on that day will yield max revenue
		memory[n] = high;
	}
	else
	{
		flag[n] = 1; //flag of 1 means low on that day will yield max revenue
		memory[n] = low;
		// return low;
	}

	return memory[n];
}

//Recurrence relation -> 2T(n-1) + c
//Complexity -> O(n) because every value is computed only once
//Rest of the algo is constant time

