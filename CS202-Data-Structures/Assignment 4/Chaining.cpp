#ifndef CHAINING_CPP
#define CHAINING_CPP
#include "Chaining.h"
#include "hashfunctions.cpp"
#include "LinkedList.cpp"

HashC::HashC(int size)
{
	tableSize = size;
	hashTable = new LinkedList<string>[tableSize];
}

HashC::~HashC()
{
	delete[] hashTable;
}

unsigned long HashC :: hash(string input)
{
	unsigned long ret = madCompression(bitHash(input), tableSize);
	return ret;
}

void HashC::insert(string word)
{
	unsigned long i = hash(word);

	hashTable[i].insertAtHead(word);
} 

ListItem<string>* HashC :: lookup(string word)
{
	unsigned long i = hash(word);
	ListItem<string>* ret = hashTable[i].searchFor(word);
	return ret;
}

void HashC :: deleteWord(string word)
{
	unsigned long i = hash(word);
	hashTable[i].deleteElement(word);
}
#endif