#include <iostream>
#include "stack.cpp"
#include "fstream"
#include <stack>
#include<conio.h>

using namespace std;

void stringWise();
void charWise();

//      _
int main()
{
    stringWise();
    cout<<"\n\n";
    charWise();
    return 0;
}

void stringWise()
{
    string temp;
    Stack<string> mystack;
    ifstream File;
    File.open("text.txt");

    if (File.is_open())
    {
        while (!File.eof())
        {
            File >> temp;
            mystack.Push(temp);
        }
    }

    File.close();

    while(mystack.Is_Empty() == false)
    {
        cout<< mystack.Pop()<<" ";
    }
}

void charWise()
{
    char temp;
    Stack<char> mystack;
    ifstream File;
    File.open("text.txt");

    if (File.is_open())
    {
        while (!File.eof())
        {
            File.get(temp);
            //cout<<temp<<" ";
            mystack.Push(temp);
        }
    }

    File.close();

    while(!mystack.Is_Empty())
    {
        cout<< mystack.Pop();
    }
}
