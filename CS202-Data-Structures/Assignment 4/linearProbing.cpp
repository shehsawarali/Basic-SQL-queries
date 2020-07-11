#ifndef LINEARPROBING_CPP
#define LINEARPROBING_CPP

#include "linearProbing.h"
#include "hashfunctions.cpp"


HashL::HashL()
{
    tableSize = 1000; // you cant change this
    count = 0;
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
	// int siz = tableSize;
	unsigned long ret = madCompression(bitHash(value), tableSize);
	return ret;
}

void HashL::resizeTable()
{
	long oldsize = tableSize;
	tableSize *= 7;
	block **table2 = new block*[tableSize];

	for(int counter = 0; counter < tableSize; counter++)
	{
		table2[counter] = NULL;
	}

	for(int counter = 0; counter < oldsize; counter++)
	{
		if(hashTable[counter] == NULL || hashTable[counter]->key == -1)
			continue;

		unsigned long i =  hash(hashTable[counter]->value);
		while(table2[i] != NULL)
		{
			i = (i + 1) % tableSize;
		}
		table2[i] = new block(i, hashTable[counter]->value);
	}

	delete [] hashTable;
	// hashTable = NULL;
	hashTable = table2;
}

void HashL::insert(string value)
{
	if (count * 2 >= tableSize)
	{
		resizeTable();
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
		{return hashTable[i];}

	return NULL;
}
#endif