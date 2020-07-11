#ifndef __STACK_H
#define __STACK_H
#include "LinkedList.cpp"

/* This is the generic Stack class */
template <class T>
class Stack
{
    LinkedList<T> list;

  public:

    // Constructor
    Stack();

    // Copy Constructor
    Stack(const Stack<T>& otherStack);

    // Destructor
    ~Stack();

    // Required Methods
    void Push(T item);
    T Top();
    T Pop();
    int Get_Length();
    bool Is_Empty();
};

#endif
