#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

int recursive(string s1, string s2, string s3);
vector<int> memory;
vector<string> out;

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

	string s1, s2, s3;

	getline(data, s1);

	getline(data, s2);

	getline(data, s3);
	for(int i = 0; i < s3.length(); i++)
	{
		memory.push_back(-1);
	}

	string ans =  "";

	if(recursive(s1, s2, s3) == 1)
	{
		ans += "VALID\n";
		reverse(out.begin(), out.end());

		for(int i = 0; i < out.size(); i++)
		{
			string line = out[i];
			char flag =  line[0];
			char letter =  line[3];
			if(i == 0)
			{
				ans += flag;
				ans += ":";
				ans += letter;
			}
			else if(i > 0)
			{
				string line2 = out[i - 1];
				char pflag = line2[0];
				if(flag != pflag)
				{
					ans += "\n";
					ans += flag;
					ans += ":";
					ans += letter;
				}
				else
					{ans += letter;}
			}	
		}
		ans += "\n";
	}
	else
		{ans = "INVALID\n";}

	cout<<ans;

	return 0;
}

int recursive(string s1, string s2, string s3) //O(m+n)
{
	if (s1.length() == 0 && s2.length() == 0 && s3.length() == 0)
        return true;

    if (s3.length() == 0)
        return false;

    if(memory[s3.length() - 1] == -1)
    {
        bool one = (s1[0] == s3[0] && recursive(s1.substr(1), s2, s3.substr(1)) == 1);
        bool two = (s2[0] == s3[0] && recursive(s1, s2.substr(1), s3.substr(1)) == 1);
        
        if(one)
		{
			string x =  "1: "; x += s3[0];
			out.push_back(x);
			memory[s3.length() - 1] = 1;
		}
		else if(two)
		{
			string x =  "2: "; x += s3[0];
			out.push_back(x);
			memory[s3.length() - 1] = 1;
		}
        else
        {
        	memory[s3.length() - 1] = 0;
        }
    }

    	// cout<<"memused"<<endl;
    	return memory[s3.length() - 1];
}
//O(m + n) because function runs O(length of s3) times where everytime it runs constant time
//Recurrence relation -> 2T(m+n-1) + c