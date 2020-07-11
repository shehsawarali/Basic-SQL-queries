#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int divide(const vector<int>& photo, int low, int high);
int conquer(const vector<int>& photo, int low, int high, int leftspecie, int rightspecie);


bool decode(int a, int b) //for comparision according to question
{
	if(a == b)
		{return true;}

	return false;
}

int main(int argc, char** argv)
{
	string file = argv[1]; //filename
	ifstream data(file);
	if(!data.is_open()) //check
	{
		string ans = "Unable to open file";
		cout<<ans<<endl;
		return -1;
	}

	string line; //Variables for file reading
	string temp;
	int val;
	int size;
	int m;

	getline(data,line);
	stringstream s1(line);
	s1 >> temp;	// read n
	s1 >> size;	// read n value

	getline(data,line);
	stringstream s2(line);
	s1 >> temp;	// read m
	s1 >> m;	// read m value

	getline(data,line);
	stringstream s3(line);

	vector<int> photo; //vector for data storage
 
	while(s3 >> val)
	{
		photo.push_back(val); //data read and push to vector
	}

	data.close();

	int dominant = divide(photo, 0, photo.size());//O(nlogn) //recursive function to divide data
	string indices = "";
	string ans = "";
	int domcount = 0;

	for(int i = 0; i < size; i++)
	{
		if(decode(dominant, photo[i])) //check if photo element is same as dominant species
		{
			if(domcount != 0) //if yes, add that element index to output
				{indices += " ";}

			indices += to_string(i);
			domcount++;
		}
	}

	if(domcount > size/2)
	{
		ans += "Success";
		ans += "\n";
		ans += "Dominant Species Count " + to_string(domcount);
		ans += "\n";
		ans += "Dominant Species Indices " + indices;
	}
	else
	{
		ans = "Failure";
	}
	cout<<ans<<endl;
	
	return 0;
}

int divide(const vector<int>& photo, int low, int high) //O(nlogn) //similar to mergesort
{
	if (low == high - 1) //Base Case where only one element exists so present specie is dominant
	{
		return photo[low];
	}
	else
	{
		int mid = (low + high)/2;

		int left = divide(photo, low, mid); //specie dominant in left subarray //O(logn)
		int right = divide(photo, mid, high); //specie dominant in right subarray //O(logn)

		int dominant = conquer(photo, low, high, left, right); //specie dominant in both subarrays //O(nlogn)
		return dominant;
	}
}

int conquer(const vector<int>& photo, int low, int high, int leftspecie, int rightspecie) //function to  conquer data (check dominant specie) //O(n)
{
	int left = 0; //count of left dominant specie in big array
	int right = 0; //count of right dominant specie in big array

	for (int i = low; i < high; i++) //check entire big array
	{
		if(decode(leftspecie, photo[i])) //if left dominant specie present
			{left++;}

		if(decode(rightspecie, photo[i])) //if right dominant specie present
			{right++;}
	}

	if(left >= right) //return overall dominant specie
		{return leftspecie;}

	return rightspecie;
}

//Relation T(n) = 2T(n/2) + C*n