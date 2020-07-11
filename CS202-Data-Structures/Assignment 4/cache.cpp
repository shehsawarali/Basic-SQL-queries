#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <stdio.h>
#include <bits/stdc++.h>
#include "hashfunctions.cpp"

using namespace std;

class block{
    public:
        unsigned long key;
        string value;
        int visits = 0;
        block(unsigned long _key,string _value){
            this->key = _key;
            this->value = _value;
        }
};


class HashL{
    private:
        block** hashTable;
        long tableSize = 1000;
        unsigned long hash(string value); // return the corresponding key of the value
        long count = 0; // keeps a count of the number of entries in the table.
        // void resizeTable();
    public:
        HashL();
        ~HashL();
        void insert(string value);
		void deleteWord(string value);
		block* lookup(string value);
};

HashL::HashL()
{
    hashTable = new block*[tableSize];

    for(int i = 0; i < tableSize; i++)
    {
    	hashTable[i] = NULL;
    }
}

HashL::~HashL()
{
	for(int i = 0; i < tableSize; i++)
	{
		delete hashTable[i];
	}
	delete[] hashTable;
}

unsigned long HashL :: hash(string value)
{
	unsigned long ret = madCompression(bitHash(value), tableSize);
	return ret;
}

void HashL::insert(string value)
{
	if(count >= tableSize)
	{
		unsigned long low_i = 0;
		long low_f = 9999999;

		for(int counter = 0; counter < tableSize; counter++)
		{
			if(hashTable[counter]->visits < low_f)
			{
				low_f = hashTable[counter]->visits;
				low_i = counter;
			}
		}

		delete hashTable[low_i];
		hashTable[low_i] = new block(low_i, value);
		return;
	}

	unsigned long i = hash(value);

	while(hashTable[i] != NULL && hashTable[i]->key != -1)
	{
		i = (i + 1) % tableSize;
	}

	if(hashTable[i] != NULL && hashTable[i]->key == -1)
	{
		delete hashTable[i];
	}
	
	hashTable[i] = new block(i, value);
	count++;
}

void HashL::deleteWord(string value)
{
	if (count == 0)
		{return;}

	unsigned long i = hash(value);

	if(hashTable[i] == NULL)
		{return;}

	while(hashTable[i] != NULL && hashTable[i]->value != value)
	{
		i = (i + 1) % tableSize;
	}

	if(hashTable[i] != NULL && hashTable[i]->value == value)
	{
		count--;
		delete hashTable[i];
		hashTable[i] = new block(-1, "");
	}
}

block* HashL::lookup(string value)
{
	if (count == 0)
		{return NULL;}

	unsigned long i = hash(value);

	if(hashTable[i] == NULL)
		{return NULL;}

	while(hashTable[i] != NULL && hashTable[i]->value != value)
	{
		i = (i + 1) % tableSize;
	}

	if(hashTable[i] != NULL && hashTable[i]->value == value)
	{
		hashTable[i]->visits++;
		return hashTable[i];
	}

	return NULL;
}

string search(unsigned long code)
{
	ifstream data("dictionary.txt");
	string line;
	int hashcode;
	string word;

	for(int counter = 0; counter <= code; counter++)
	{
		getline(data, line);
	}

	stringstream s(line);
	s >> hashcode;
	s >> word;
	return word;
}
	
int main()
{
	clock_t t; 
    t = clock();

	HashL mytable;

	ifstream data("secret1.txt");
	unsigned long code;
	char temp;
	while(!data.eof())
	{
		data >> code;
		data >> temp;

		/*block* temp = mytable.lookup(code);

		if(temp == NULL)
		{
			string word = search(code);
			mytable.insert(word);
			cout<<word<<" ";
		}
		else
		{
			cout<<temp->value<<" ";
		}*/
	}
	data.close();
	cout<<endl;

	t = clock() - t; 
    double time = ((double)t) / CLOCKS_PER_SEC; 
    cout << "Time taken with cache: " << time << endl; //434 secret1
}