#ifndef GRAPH__CPP
#define GRAPH__CPP
#include "Graph.h"
#include <bits/stdc++.h>
#include <stack>
#include <queue>

struct priorityD //HELPER
{ 
    bool operator()(const node* a, const node* b) 
    { 
        return a->dist > b->dist;
    }
};

struct priorityK //HELPER
{ 
    bool operator()(const edge a, const edge b) 
    { 
        return a.weight > b.weight;
    }
};

void settozero(vector<node*> &v) //HELPER
{
	for(int i = 0; i < v.size(); i++)
	{
		v[i]->visit = 0;
	}
}

node* getnode(vector<node*> v, string s) //HELPER
{
	for(int i = 0; i < v.size(); i++)
	{
		if(v[i]->name == s)
		{
			// N = v[i];
			// cout<<v[i]->name<<endl;
			return v[i];
		}
	}

	return NULL;
}

Graph::Graph(char* file, bool isUnitLength = false) //DONE
{
	ifstream data(file);
	string temp;
	string val;
	int t;
	if(!data.is_open())
	{
		cout<<"Error. File not opened."<<endl;
		return;
	}

	data >> temp; //Read PEOPLE

	while(data >> val && val != "CONNECTIONS")
	{
		node* person = new node(val);
		cities.push_back(person);
		// cout<<val<<endl;
	}

	string source;
	string destination;
	while(!data.eof())
	{
		float weight = 1;
		float temp;
		data >> source;
		data >> destination;
		data >> temp;

		if(!isUnitLength)
			{weight = temp;}

		node* sourcenode; node* destnode;
		for(int i = 0; i < cities.size(); i++)
		{
			if(cities[i]->name == source)
			{
				sourcenode = cities[i];
			}
			if(cities[i]->name == destination)
			{
				destnode = cities[i];
			}
		}

		edge sd(sourcenode, destnode, weight);
		edge ds(destnode, sourcenode, weight);
		sourcenode->edges.push_back(sd);
		destnode->edges.push_back(ds);
		arcs.push_back(sd);
	}

	data.close();
}

void Graph::display(node* temp) //GIVEN
{
	if(temp->visit)
		return;
	
	cout << "Person: " << temp->name;
	temp->visit = 1;
	for(int i=0; i< temp->edges.size(); i++)
	{
		if(!temp->edges[i].Origin->visit || !temp->edges[i].Dest->visit)
		cout << "->" << temp->edges[i].weight << endl;
		display(temp->edges[i].Origin);
		display(temp->edges[i].Dest);
	}
}


bool Graph::Reachable(string start, string dest) //DONE
{

	if(start == dest)
		{return true;}

	settozero(cities);

	node* sourcenode = getnode(cities, start);
	sourcenode->visit = 1;

	/*for(int i = 0; i < sourcenode->edges.size(); i++)
	{
		cout<<sourcenode->edges[i].Dest->name<<endl;
	}*/

	queue<node*> Q;
	Q.push(sourcenode);
	//int count = 0;

	while(!Q.empty())
	{
		node* N = Q.front();
		Q.pop();

		if(N->name == dest)
			{return true;}

		for(int i = 0; i < N->edges.size(); i++)
		{
			if(N->edges[i].Dest->visit == 0)
			{
				N->edges[i].Dest->visit = 1;
				Q.push(N->edges[i].Dest);
			}
		}
		// count++;
	}

	// cout<<count<<endl;
	return false;
}

vector<node*> Graph::Kruskal() //DONE
{
	priority_queue <edge, vector<edge>, priorityK> edges;
	for (int i = 0; i < arcs.size(); i++)
	{
		edges.push(arcs[i]);
		//x
		//x
	}

	vector<edge> mst;

	vector<set<node*>> sets;
	for (int i = 0; i < cities.size(); i++)
	{
		set<node*> s;
		s.insert(cities[i]);
		sets.push_back(s);
	}

	while(sets.size() > 1 && !edges.empty())
	{
		edge E = edges.top();
		edges.pop();

		int src, dest;
		for(int i = 0; i < sets.size(); i++)
		{
			if(sets[i].find(E.Origin) != sets[i].end())
				{src = i;}

			if(sets[i].find(E.Dest) != sets[i].end())
				{dest = i;}
		}

		if(src == dest) //Origin Destination in same set
			{continue;}

		mst.push_back(E); //Origin dest in different sets
		sets[src].insert(sets[dest].begin(), sets[dest].end()); //merge
		sets.erase(sets.begin() + dest);
	}

	vector<node*> tree;
	for(int i = 0; i < cities.size(); i++)
	{
		string val = cities[i]->name;
		// node n(val);
		// node* p = &x;
		node* p = new node(val);
		tree.push_back(p);
	}

	for(int i = 0; i < mst.size(); i++) //for every edge
	{
		string src = mst[i].Origin->name;
		string dest = mst[i].Dest->name;

		node* sourcenode = getnode(tree, src);
		node* destination = getnode(tree, dest);

		if(sourcenode != NULL)
			{sourcenode->edges.push_back(mst[i]);}
		
		else if(destination != NULL)
		{
			edge ds(mst[i].Dest, mst[i].Origin, mst[i].weight); //reverse edge
			destination->edges.push_back(ds);
		}
	}
	
	return tree;
}

vector<string> Graph::Dijkstra(string start, string dest, float &d) //DONE
{
	settozero(cities);
	node* sourcenode = getnode(cities, start);

	for(int i = 0; i < cities.size(); i++)
	{
		cities[i]->dist = INT_MAX;
	}

	sourcenode->dist = 0;
	sourcenode->predecessor = NULL;
	priority_queue <node*, vector<node*>, priorityD> Q;
	Q.push(sourcenode);

	while(!Q.empty())
	{
		node* N = Q.top();
		Q.pop();

		if(N->visit != 0)
			{continue;}

		if(N->name != dest)
		{
			N->visit = 1;

			for(int i = 0; i < N->edges.size(); i++)
			{
				node* N2 =  N->edges[i].Dest;

				if(N2->dist > (N->dist + N->edges[i].weight))
				{
					N2->dist = N->dist + N->edges[i].weight;
					N2->predecessor = N;
					Q.push(N2);
				}
			}
		}
		else
		{
			d = N->dist;
			vector<string> path;
			while(N)
			{
				path.push_back(N->name);
				N = N->predecessor;
			}
			reverse(path.begin(), path.end());
			// d = path.size();
			return path;
		}
	}
}

int main()
{
	// cout<<"Initialize your graph in main!"<<endl;
	ifstream data("friends.txt");
	if(!data.good())
	{cout<<"Error in file"<<endl; return 0;}

	Graph g("friends.txt", true);
	bool c1, c2, c3;
	cout<<"1) Reachability"<<endl;
	cout<<"(Mannan, Ali): ";
	if(c1 = g.Reachable("Mannan", "Ali"))
		cout<<"Reachable"<<endl;
	else
		cout<<"Not reachable"<<endl;

	cout<<"(Mannan, Trump) : ";
	if(c2 = g.Reachable("Mannan", "Trump"))
		cout<<"Reachable"<<endl;
	else
		cout<<"Not reachable"<<endl;

	cout<<"(Ali, Trump) : ";
	if(c3 = g.Reachable("Ali", "Trump"))
		cout<<"Reachable"<<endl;
	else
		cout<<"Not reachable"<<endl;

	if(c1 && c2 && c3)
		{cout<<"Dataset is connected"<<endl;}

	cout<<endl;


	cout<<"2) and 3) Hops"<<endl; //dijkstra
	float d;
	if(c3)
	{
		vector<string> v = g.Dijkstra("Ali", "Trump", d);
		cout<<"Hops between Ali and Trump: "<<d<<endl;
	}
	d = 0;
	if(c2)
	{
		vector<string> v = g.Dijkstra("Mannan", "Trump", d);
		cout<<"Hops between Mannan and Trump: "<<d<<endl;
	}
	cout<<endl;


	cout<<"4) Smaller value of path in terms of index of friendship"<<endl;
	Graph weighted("friends.txt", false);
	if(weighted.Reachable("Ali", "Trump"))
	{
		vector<string> v = weighted.Dijkstra("Ali", "Trump", d);
		cout<<"Path value of Ali and Trump: "<<d<<endl;
	}

	float d2;
	if(weighted.Reachable("Mannan", "Mannan"))
	{
		vector<string> v = weighted.Dijkstra("Mannan", "Trump", d2);
		cout<<"Path value of Mannan and Trump: "<<d2<<endl;
	}

	if(d == d2)
		{cout<<"Both paths are equal in length"<<endl;}
	else if(d > d2)
		{cout<<"Ali-Mannan have smaller value of path"<<endl;}
	else if(d < d2)
		{cout<<"Ali-Trump have smaller value of path"<<endl;}

	cout<<endl<<endl;

	vector<node*> unit = g.Kruskal();
	vector<node*> index = weighted.Kruskal();

	if(unit.size() >= 1)
		{cout<<"Unit length MST -> ";}

	for(int i = 0; i < unit.size(); i++)
	{
		for(int j = 0; j < unit[i]->edges.size(); j++)
		{
			cout<<unit[i]->edges[j].Origin->name<<" "<<unit[i]->edges[j].Dest->name<<" "<<unit[i]->edges[j].weight<<endl;
		}
	}
	cout<<endl<<endl;

	if(index.size() >= 1)
		{cout<<"Weighted length MST -> ";}
	for(int i = 0; i < index.size(); i++)
	{
		for(int j = 0; j < index[i]->edges.size(); j++)
		{
			cout<<index[i]->edges[j].Origin->name<<" "<<index[i]->edges[j].Dest->name<<" "<<index[i]->edges[j].weight<<endl;
		}
	}

	cout<<endl<<endl;

	cout<<"There can be multiple MSTs for both weighted and unweighted graphs. In weighted graphs that is only possible if edges are allowed to have equal weights. "<<endl;
	cout<<"MST of a weighted graph and a similar unweighted graph can be same but with different MST weight. "<<endl;
	cout<<"Social media websites can use MSTs to optimize their user-recommendation system. "<<endl;
	cout<<"In social connection graphs, MSTs can also be used to figure out which relationships to strengthen so network connectivity can be increased. "<<endl;
	cout<<endl;
}

#endif
