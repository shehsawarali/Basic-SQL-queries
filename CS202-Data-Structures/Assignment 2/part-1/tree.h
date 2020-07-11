#ifndef __TREE_H
#define __TREE_H
#include <cstdlib>
#include <vector>
#include <iostream>
#include <cstring>
#include "queue.cpp"

using namespace std;

struct TreeItem
{
	string name;
	int generation;
	vector<TreeItem*> children; 

	TreeItem()
	{
		name = "";
	}

	TreeItem(string name)
	{
		this->name = name;
	}
};


class Tree
{
	TreeItem *root;

public:
	// Constructor
	Tree(string name); 

	// Destructor
	~Tree();
	

	// Member Functions
	void AddChild(string parent_name, string child_name);
	TreeItem* GetPerson(string person_name);
	void GetParent(string child_name);
	void GetChildren(string parent_name);
	int GetGeneration(string person_name);
	int GenerationCount(int generation);
	int GenerationGap(string person_name1, string person_name2);
	void level_traversal();

	/*You can add additional functions if necessary*/
};
#endif
