#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

int main(int argc, char** argv)
{
	string ans = "";
	string file = argv[1]; //assuming command is executed properly

	ifstream data;
	data.open(file); //assuming filename is correct

	string line; //Initializing variables for file reading
	string temp;
	double val;
	int size;

	getline(data,line);
	istringstream s1(line);
	s1 >> temp;	// read n
	s1 >> size;	// read n value

	double length[size]; //attribute arrays
	double prob[size]; 

	getline(data, line);
	istringstream s2(line);
	s2 >> temp; //read 'L'

	int counter = 0; //counter to add values to attribute array

	while(counter < size)
	{
		s2 >> val;
		length[counter] = val;
		counter++;
	}

	getline(data, line);
	istringstream s3(line);
	s3 >> temp; //read 'p'

	counter = 0; //counter again set to zero for 2nd attribute

	while(counter < size)
	{
		s3 >> val;
		prob[counter] = val;
		counter++;
	} //FILE READING END

	priority_queue <double, vector<double>, greater<double>> ratio; //pq to sort in less time complexity 
	for(int i = 0; i < size; i++) //O(n)
	{
		double val = length[i] / prob[i]; //ordering by length probabilty ratio
		ratio.push(val);
	}

	int seq[size];//array to store correct seq of output numbers
	counter  = 0;
	while(!ratio.empty()) //storing sequence in array //O(n)
	{
		double rto = ratio.top();
		ratio.pop();
		bool cond = true;

		for(int i = 0; i < size;  i++) //O(n2)
		{
			if(cond == false)
				continue;

			if(length[i] / prob[i] == rto)
			{
				seq[counter] = i;
				// cout<<i<<" ";
				cond = false;
				counter++;
			}
		}
	}

	// cout<<endl;
	double sum = 0;
	double seqlength =  0;

	for(int i = 0; i < size; i++) //Computation O(n)
	{
		int index = seq[i];
		// cout<<index<<" ";
		if(i != 0)
		{
			ans += " ";
		}
		ans += to_string(index+1);

		double p = prob[index];
		double l = length[index];

		seqlength += l;

		sum += p * seqlength;
	}

	ans += "\nExpected Time ";
	ans += to_string(sum);

	cout<<ans; //Complexity is O(n^2)
	return 0;
}