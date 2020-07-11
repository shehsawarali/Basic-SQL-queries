#ifndef HASHFUNCTIONS_CPP
#define HASHFUNCTIONS_CPP
#include <string>
#include <iostream>
#include <cmath>

using namespace std;
// this takes in a string and returns a 64bit hash.
unsigned long polyHash(std::string value,int a = 9)
{
	unsigned long hashcode = 0;

	for(int i = 0; i < value.length(); i++)
	{
		int k = value.length() - i;
		hashcode += int(value[i]) * pow(a, k);
	}

	return hashcode;
}

//does some bitwise operation and generates a 64bit hash.
unsigned long bitHash(std::string value)
{
	unsigned long hashcode = 0;
	for(int i = 0; i < value.length(); i++)
	{
		hashcode ^= (hashcode << 5) + (hashcode >> 2) + int(value[i]); 
	}

	return hashcode;
}
// Size is the size of array maintained by the hashtable.
unsigned long divCompression(unsigned long hash,long size)
{
	if(size > 0)
	{return (hash % size);}

	cout<< "Size must be a nonzero positive integer.";
	return -1;
}
// multiplication addition and division compression. 
unsigned long madCompression(unsigned long hash,long size,int m = 1993,int a = 1637)
{
	if(size > 0)
		{return (m*hash + a) % size;}

	cout<<"Size must be a nonzero positive integer.";
	return -1;
}
#endif
// you may write your own program to test these functions.