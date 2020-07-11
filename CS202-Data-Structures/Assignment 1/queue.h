#ifndef __QUEUE_H
#define __QUEUE_H
#include "LinkedList.cpp"

/* This is the generic Queue class */
template <class T>
class Queue
{
    LinkedList<T> list;

  public:

    // Constructor
    Queue();

    // Copy Constructor
    Queue(const Queue<T>& otherQueue);

    // Destructor
    ~Queue();

    // Required Methods
    void Enqueue(T item);
    T Get_Front();
    T Dequeue();
    int Get_Length();
    bool Is_Empty();
};

#endif
