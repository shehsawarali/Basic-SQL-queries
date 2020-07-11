#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class pairs
{
public:
	string team;
	string location;
	int num;

	pairs(string x, string y, int j)
	{
		team = x;
		location = y;
		num = j;
	}
};

int main(int argc, char** argv)
{
	string file = argv[1]; //Assuming command is entered properly

	ifstream data;
	data.open(file); //Assuming filename is entered correctly

	string line; //Variables for file reading
	string temp;
	string val;
	string teamname;
	int size;

	getline(data,line);
	stringstream s1(line);
	s1 >> temp;	// read n
	s1 >> size;	// read n value

	vector<vector<string>> teams;

	for(int i = 0; i < size; i++) //O(n)
	{
		getline(data, line);
		stringstream s(line);
		s >> teamname; //read team name
		s >> temp; //read semicolon
		int x = 1;

		while(!s.eof() && s >> val) //read locations
		{
			teams[i].push_back(val);
		}
	}

	vector<pairs> taken;

	while(taken.size() < size)
	{
		for(int i = 0; i < size; i++)
		{
			CHECK:
			int k = 0; bool check = false;
			while(check == false && k < taken.size())
			{
				if(taken[k].team == to_string(i))
					{check = true;}
				else
					{k++;}
			}

			if(check == true)
			{
				i++;
				goto CHECK;
			}

			for(int j = size - 1; j > 0; j--)
			{
				string lname = teams[i][j];
				if(lname != "-")
				{
					int k = 0; bool check = false;

					while(check == false && k < taken.size())
					{
						if(taken[k].location == lname)
							{check = true;}
						else
							{k++;}
					}

					if(check == false)
					{
						pairs p(to_string(i), lname, j);
						taken.push_back(p);
						j = -1;
						continue;
					}

					if(taken[k].location == lname && j < taken[k].num)
					{
						taken[k].team = i;
						taken[k].num = j;
					}
				}
			}
		}
	}





	/*string ans = "Final Destinations: ";

	for(int i = 1; i <= size; i++)
	{
		stringstream ss;
		ss << i;
		string val = "L";
		val += ss.str();
		// cout<<val;

		ans +=  val;
		ans += " ";
		string teami;

		for(int j = 0; j < size; j++)
		{
			if(team[j].clocation != NULL && team[j].clocation.name == val)
			{
				teami = team[j].name;
				j = size;
			}
		}

		ans += teami;
		if(i < size)
			{ans += ", ";}
	}

	cout << ans;*/
}