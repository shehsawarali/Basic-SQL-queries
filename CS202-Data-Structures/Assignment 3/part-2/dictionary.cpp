#ifndef __DICTIONARY_CPP
#define __DICTIONARY_CPP
#include "dictionary.h"
#include "bst.h"
#include "bst.cpp"
#include <time.h>
#include <stdio.h>
#include <fstream>
#include <chrono>

using namespace std;


Dictionary::Dictionary()
{
	wordsTree = NULL; 
}

Dictionary::~Dictionary()
{
    
}

void Dictionary::initialize(string wordsFile)
{
	string word;
	int cond = 0;

	ifstream data(wordsFile);

	if(data.is_open())
	{
		while ((cond < 10000) && (data >> word))
		{
			cond++;
			insertWord(word);
			// cond = insertWord(word);
			//cout<<word<<endl;
	   	}
	    
	    data.close();
	}
	else
	{
		cout << "File missing" << endl;
	}
}

bool Dictionary::deleteWord(string word)
{
	if(wordsTree == NULL)
		{return false;}

	if(wordsTree->search(word) == NULL)
		{return false;}

	wordsTree->delete_node(word);
	return true;
}

bool Dictionary::editWord(string oldWord, string newWord)
{
	if(wordsTree == NULL)
		{return false;}

	if(wordsTree->search(oldWord) == NULL)
		{return false;}

	deleteWord(oldWord);
	insertWord(newWord);
}

bool Dictionary::insertWord(string word)
{
	if(wordsTree == NULL)
	{
		wordsTree = new BST<string>;
		wordsTree->insert(word, word);
		cout<<word<<endl;
		return true;
	}
	else
	{
		if(wordsTree->search(word) == NULL)
		{
			wordsTree->insert(word, word);
			cout<<word<<endl;
			return true;
		}
		return false;
	}
}

node<string>* Dictionary::findWord(string word)
{
	auto t1 = chrono::high_resolution_clock::now();

    node<string>* temp = wordsTree->search(word);

    auto t2 = chrono::high_resolution_clock::now();

    if(temp == NULL)
    {
    	cout<<"Not found"<<endl;
    	return NULL;
    }

    auto dif = chrono::duration_cast < chrono::nanoseconds > (t2-t1).count();
    cout << "findWord() took " << dif << "nanosec to search for " << word << endl;  
    return temp;
}

#endif

int main()
{
	// cout<<"check";
	Dictionary d;
	// cout<<"check";
	d.initialize("words.txt");
	// cout<<"check";

	d.insertWord("alvarado");

	d.findWord("alvarado");
	d.findWord("becrusted");
	d.findWord("chauvin");
	d.findWord("dogstone");
	d.findWord("economists");
	d.findWord("fozier");
	d.findWord("gallinae");
	d.findWord("homotransplant");
	d.findWord("interred");
	d.findWord("jumbo");
	d.findWord("keepworthy");
	d.findWord("lyocratic");
	d.findWord("micropetrology");
	d.findWord("naticidae");
	d.findWord("orl");
	d.findWord("print");
	d.findWord("quick-change");
	d.findWord("rusty-rested");
	d.findWord("sellie");
	d.findWord("tropary");
	d.findWord("uredosorus");
	d.findWord("viticetum");
	d.findWord("wearisomely");
	d.findWord("xns");
	d.findWord("yeti");
	d.findWord("zooblast");
}
