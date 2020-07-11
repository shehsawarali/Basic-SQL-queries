#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;


struct node
{
	int name;
	vector<int> edges;
	int degree;

	node(int n)
	{
		name = n;
		degree = 0;
	}
};

int main(int argc, char** argv)
{
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
	vector<node> nodes;

	for(int i = 0; i < size; i++)
	{
		int name;
		getline(data,line);
		stringstream s(line);

		s >> name;
		s >> temp; //read semicolon
		node n(name);

		while(s >> val)
		{
			n.edges.push_back(val);
			n.degree++;
		}

		nodes.push_back(n);
	}

	cout<<"n "<<size<<endl;
	for(int i = 0; i < nodes.size(); i++)
	{
		node n =  nodes[i];
		cout<<n.name<<" : ";

		for(int j = 0; j < n.edges.size(); j++)
		{
			cout<<to_string(n.edges[j])<<" ";
		}
		cout<<endl;
	}
	cout<<endl;

	return 0;
}