#include <iostream>
#include <vector>
#include <bits/stdc++.h> 


using namespace std;

//Discussed with Sahim  Bhaur

int divide(vector<int> data, int low, int high);
int conquer(vector<int> data, int low, int high, int mid);

class pairs
{
public:
	int smallerindex;
	int largerindex;

	pairs(int x, int y)
	{
		smallerindex = (y);
		largerindex = (x);
	}
};

vector<pairs> p;

int main(int argc, char** argv)
{
	string file = argv[1]; //Assuming command is entered properly

	ifstream data;
	data.open(file); //Assuming filename is entered correctly

	string line; //Variables for file reading
	string temp;
	int size;

	getline(data,line);
	stringstream s1(line);
	s1 >> temp;	// read n
	s1 >> size;	// read n value

	vector<int> dataa;

	getline(data,line);
	stringstream s2(line);

	int val;

	while(s2 >> val)
	{
		dataa.push_back(val);
	}

	int inversions = divide(dataa, 0, size);  //O(nlogn)

	string ans = "Failed Trials ";
	ans += to_string(inversions);
	ans += "\n";

	for(int j = 0; j < size; j++) //O(n^2) ----> this is output complexity not algorithm complexity
	{
		int count = 0;

		for(int i = 0; i < p.size(); i++)
		{
			if(p[i].largerindex == j)
			{
				
				string x =  "(";
				x += to_string(p[i].largerindex) + ",";
				x += to_string(p[i].smallerindex) + ")";

				if(count != 0)
				{
					ans += " ";
				}
				ans += x;
				count++;
			}
		}

		if(count != 0)
		{ans += "\n";}
	}
	

	cout<<ans;
}

int divide(vector<int> data, int low, int high) //O(nlogn)
{
    if(low >= high) //BASE CASE
    {
    	return 0;
    }

    int mid = (low + high) / 2;

    int inversions = 0;
    inversions += divide(data, low, mid); //O(logn)
    inversions += divide(data, mid + 1, high); //O(logn)
    inversions += conquer(data, low, high, mid); //O(nlogn)
    return inversions;
}

int conquer(vector<int> data, int low, int high, int mid) //O(n)
{
    int inversions = 0; 

    int left = 0;
    int right = 0;

    while((left < mid - low + 1) && (right < high - mid)) //O(n)
    {
        if(data[left] <= data[right])
        { 
            left++;
        } 

        else if(data[right] < data[left]/2)
        {
        	inversions++;
        	pairs px(right, low);
        	p.push_back(px);
        	right++;
        }
        else
        {right++;}
    } 

    return inversions;
}

//Relation T(n) = 2T(n/2) + C*n