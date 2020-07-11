#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

//void read(string name, vector<int>& row, vector<int>& colomn, int& size);

int main(int argc, char** argv)
{
	string ans ="";
	string file = argv[1]; //Assuming command is entered properly

	ifstream data;
	data.open(file); //Assuming filename is entered correctly

	string line; //Variables for file reading
	string temp;
	int val;
	int size;

	getline(data,line);
	stringstream s1(line);
	s1 >> temp;	// read n
	s1 >> size;	// read n value
	int i = size;

	int row[size]; //Arrays for each attribute
	int colomn[size]; 

	getline(data, line);
	stringstream s2(line);
	s2 >> temp; //read 'row'

	int counter = 0; //Counter to fill attribute array

	while(counter < size) //O(n)
	{
		s2 >> val;
		row[counter] = val;
		counter++;
	}

	getline(data, line);
	stringstream s3(line);
	s3 >> temp; //read 'row'

	counter = 0; //Counter again 0 to fill 2nd attribute

	while(counter < size) //O(n)
	{
		s3 >> val;
		colomn[counter] = val;
		counter++;
	}

	for(i = 0; i < size; i++) //O(n)
	{
		int j = 0;
		int count = 0;
		int x = 0;
		while(row[i] > 0)
		{
			if(x == 2)
				{ans = "Not Possible\n"; break;}

			if(colomn[j] > 0) //If space empty in  coloumn, place the piece O(n2)
			{
				if(count != 0)
				{
					ans += " ";
				}
				ans += "(" + to_string(i+1) + "," + to_string(j+1) + ")";
				row[i]--;
				colomn[j]--;
				count++;
			}

			j++;
		}
		ans += "\n";
	}

	bool cond =  true;
	for(i = 0; i < size; i++)
	{
		if(row[i] != 0 || colomn[i] != 0)
		{
			ans = "Not Possible\n";
			break;
		}
	}

	cout<<ans; //Complexity is O(n^2)
	return 0;
}