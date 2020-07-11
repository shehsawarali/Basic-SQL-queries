#ifndef __TREE_CPP
#define __TREE_CPP
#include "tree.h"
#include "iostream"
#include <cstdlib>
#include "queue.cpp"
using namespace std;



Tree::Tree(string name)
{
	root = new TreeItem(name);
	root->name = name;
	root->generation = 1;
}

Tree::~Tree()
{
	if (root == NULL)
		{return;}

	Queue<TreeItem*> myqueue;
	myqueue.enqueue(root);

	while (!myqueue.isEmpty())
	{
		TreeItem *temp = myqueue.dequeue();

		for (int i = 0; i < temp->children.size(); i++)
		{
			myqueue.enqueue(temp->children[i]);
		}

		delete temp;
	}
}

void Tree::AddChild(string parent_name, string child_name) //WORKS
{
	if(root == NULL)
	{
		cout<<"Missing root";
		return;
	}

	/*if(root->name == parent_name)
		{
			TreeItem* child = new TreeItem(child_name);
			child->generation = 2;
			root->children.push_back(child);
			return;
		}

	Queue<TreeItem*> myqueue;
	myqueue.enqueue(root);

	while(!myqueue.isEmpty())
	{
		TreeItem* temp = myqueue.dequeue();

		if(temp->name == parent_name)
			{
				TreeItem* child = new TreeItem(child_name);
				child->generation = temp->generation + 1;
				temp->children.push_back(child);
				return;
			}

		for(int i = 0; i < temp->children.size(); i++)
		{
			myqueue.enqueue(temp->children[i]);
		}
	}*/

	TreeItem* temp = GetPerson(parent_name);
	TreeItem* child = new TreeItem(child_name);
	child->generation =  temp->generation + 1;
	temp->children.push_back(child);
}

TreeItem* Tree::GetPerson(string person_name) //WORKS
{
	if(root == NULL)
	{
		TreeItem* temp;
		temp->generation = 0;
	}

	Queue<TreeItem*> myqueue;
	myqueue.enqueue(root);

	while(!myqueue.isEmpty())
	{
		TreeItem* temp = myqueue.dequeue();

		if(temp->name == person_name)
			{return temp;}

		for(int i = 0; i < temp->children.size(); i++)
		{
			myqueue.enqueue(temp->children[i]);
		}
	}
}
void Tree::GetParent(string child_name) //WORKS
{
	if(root == NULL)
	{
		cout<<"No nodes"<<endl;
	}

	if(root->name == child_name)
		{cout<<"no parent";}

	Queue<TreeItem*> myqueue;
	myqueue.enqueue(root);

	while(!myqueue.isEmpty())
	{
		TreeItem* temp = myqueue.dequeue();

		for(int i = 0; i < temp->children.size(); i++)
		{
			if(temp->children[i]->name == child_name)
			{
				cout << temp->name;
				return;
			}
			myqueue.enqueue(temp->children[i]);
		}
	}
}

void Tree::GetChildren(string parent_name) //WORKS
{
	/*if(root == NULL)
	{
		cout<<"No nodes"<<endl;
	}

	Queue<TreeItem*> myqueue;
	myqueue.enqueue(root);

	while(!myqueue.isEmpty())
	{
		TreeItem* temp = myqueue.dequeue();

		if(temp->name == parent_name)
		{
			if(temp->children.size() == 0)
				{cout<<parent_name<<" has no children";}
			else
			{
				for(int i = 0; i < temp->children.size(); i++)
				{
					cout<<root->children[i]->name;
					if(i != temp->children.size() - 1)
						{cout<<", ";}
				}
				cout<<endl;
			}
		}
		else
		{
			for(int i = 0; i < temp->children.size(); i++)
				{
					myqueue.enqueue(temp->children[i]);
				}
		}
	}*/

	TreeItem* temp = GetPerson(parent_name);
	if(temp->children.size() == 0)
		{cout<<temp->name << " has no children"<<endl; return;}

	for(int i = 0; i < temp->children.size(); i++)
		{
			cout<<temp->children[i]->name;
			if(i != temp->children.size() - 1)
				{cout<<", ";}
		}
}

int Tree::GetGeneration(string person_name) //DOESNT WORK
{
	return GetPerson(person_name)->generation;
}

int Tree::GenerationCount(int generation) //WORKS
{
	if(root == NULL)
	{
		return 0;
	}

	if(generation == 1)
	{
		return 1;
	}

	int count = 0;

	Queue<TreeItem*> myqueue;
	myqueue.enqueue(root);

	while(!myqueue.isEmpty())
	{
		TreeItem* temp = myqueue.dequeue();
		if(temp->generation == generation)
			{count++;}

		for(int i = 0; i < temp->children.size(); i++)
		{
			myqueue.enqueue(temp->children[i]);
		}
	}

	return count;
}

int Tree::GenerationGap(string person_name1, string person_name2) //NEED GETGENERATION
{
	int g1 =  GetPerson(person_name1)->generation;
	int g2 =  GetPerson(person_name2)->generation;

	if(g1 > g2)
		{return g1-g2;}

	return g2-g1;
}


void Tree::level_traversal() 
{
	if (root->children.size() == 0)
		{cout<<root->name<<endl; return;}

    Queue<TreeItem*> myqueue1;
    Queue<TreeItem*> myqueue2;

    myqueue1.enqueue(root);

    while (!myqueue1.isEmpty())
    {
        TreeItem* temp = myqueue1.dequeue();
        myqueue2.enqueue(temp);

        for (int i = 0; i < temp->children.size(); i++)
        {
            myqueue1.enqueue(temp->children[i]);
        }
    }

    int count = 0;
    while (!myqueue2.isEmpty())
    {
    	int lim = GenerationCount(count);

        for(int i = 0; i < lim; i++)
        {
        	TreeItem* temp = myqueue2.dequeue();
        	cout<<temp->name;
        	if(i != lim - 1)
        		{cout<<", ";}
        }
        cout<<endl;
        count++;
    }
}
#endif
