#ifndef DOUBLEHASH_CPP
#define DOUBLEHASH_CPP

#include "doubleHash.h"
#include "hashfunctions.cpp"


HashD::HashD()
{
    tableSize = 10000; // you cant change this
    count = 0;
    hashTable = new block*[tableSize];

    for(int i = 0; i < tableSize; i++)
    {
    	hashTable[i] = NULL;
    }
}

HashD::~HashD()
{
	for(int i = 0; i < tableSize; i++)
	{
		delete hashTable[i];
	}
	delete[] hashTable;
}

void HashD::resizeTable()
{
	long oldsize = tableSize;
	tableSize *= 10;
	block **table2 = new block*[tableSize];

	for(int counter = 0; counter < tableSize; counter++)
	{
		table2[counter] = NULL;
	}

	for(int counter = 0; counter < oldsize; counter++)
	{
		if(hashTable[counter] == NULL || hashTable[counter]->key == -1)
			continue;

		unsigned long i1 = hash1(hashTable[counter]->value);
		unsigned long i2 = hash2(hashTable[counter]->value);
		unsigned long i = i1;
		int c = 0;

		while(table2[i] != NULL)
		{
			i = (i1 + c*i2) % tableSize;
			c++;
		}
		table2[i] = new block(i, hashTable[counter]->value);
	}

	delete [] hashTable;
	hashTable = table2;
}

void HashD::insert(string value)
{
	if (count/float(tableSize) >= 0.069)
	{
		resizeTable();
	}
	
	unsigned long i1 = hash1(value);

	if (hashTable[i1] != NULL)
	{
		if(hashTable[i1]->key == -1)
		{
			delete hashTable[i1];
			hashTable[i1] = new block(i1, value);
		}

		unsigned long i2 = hash2(value);
		unsigned long i;

		int c = 1;
		while (1)
		{
			i = (i1 + c*i2) % tableSize;
			if(hashTable[i] == NULL)
			{
				hashTable[i] = new block(i, value);
				break;
			}
			if(hashTable[i]->key == -1)
			{
				delete hashTable[i];
				hashTable[i] = new block(i, value);
				break;	
			}
			c++;
		}
	}
	else
	{
		hashTable[i1] = new block(i1, value);
	}

	count++;
}

void HashD::deleteWord(string value)
{
	if (count == 0)
		{return;}

	unsigned long i1 = hash1(value);
	unsigned long i2 = hash2(value);
	unsigned long i = i1;
	int c = 0;

	if(hashTable[i] == NULL)
		{return;}

	while(hashTable[i] != NULL && hashTable[i]->value != value)
	{
		i = (i1 + c*i2) % tableSize;
		c++;
	}

	if(hashTable[i] != NULL && hashTable[i]->value == value)
	{
		count--;
		delete hashTable[i];
		hashTable[i] = new block(-1, "");
	}
}

block* HashD::lookup(string value)
{
	if (count == 0)
		{return NULL;}

	unsigned long i1 = hash1(value);
	unsigned long i2 = hash2(value);
	unsigned long i = i1;
	int c = 0;

	if(hashTable[i] == NULL)
		{return NULL;}

	while(hashTable[i] != NULL && hashTable[i]->value != value)
	{
		i = (i1 + c*i2) % tableSize;
		c++;
	}

	if(hashTable[i] != NULL && hashTable[i]->value == value)
		{return hashTable[i];}

	return NULL;
}

unsigned long HashD::hash1(string value)
{
	unsigned long ret = madCompression(bitHash(value), tableSize);
	return ret;
}

unsigned long HashD::hash2(string value){
	unsigned long ret = divCompression(bitHash(value), tableSize);
	return ret;
}

#endif