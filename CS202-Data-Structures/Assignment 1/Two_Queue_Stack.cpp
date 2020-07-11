#include <iostream>
#include "queue.cpp"

using namespace std;


int main()
{
    Queue tempq;
    Queue mainq;

    int Size = 0;

    return 0;
}

template <class T>
void push(T item, Queue& tempq, Queue& mainq, int& Size)
{
    tempq.push(item);

    while (!mainq.Is_Empty())
    {
        tempq.Enqueue(mainq.Dequeue());
    }

    Queue<T> q = mainq;
    mainq = tempq;
    tempq = q;

    Size++;
}

template <class T>
void pop(Queue& mainq, int& Size)
{
    if (mainq.Is_Empty())
    {
        return;
    }

    T temp = mainq.Dequeue();

    Size--;
}


template <class T>
T top(Queue& mainq)
{
    return mainq.Get_Front();
}
