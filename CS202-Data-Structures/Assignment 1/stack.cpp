#ifndef __STACK_CPP
#define __STACK_CPP
#include "stack.h"

template <class T>
Stack<T>::Stack():list()
{
}

template <class T>
Stack<T>::Stack(const Stack<T>& otherStack):list(otherStack.list)
{
}

template <class T>
Stack<T>::~Stack()
{

}

template <class T>
void Stack<T>::Push(T item)
{
    list.Insert_at_Head(item);
}

template <class T>
T Stack<T>::Top()
{
    T val = (list.Get_Head())->value;
	return val;
}

template <class T>
T Stack<T>::Pop()
{
    T val = (list.Get_Head())->value;
	list.Delete_Head();
	return val;
}

template <class T>
int Stack<T>::Get_Length()
{
    return list.Get_Length();
}

template <class T>
bool Stack<T>::Is_Empty()
{
    if(list.Get_Head() == NULL)
		return true;

    return false;
}

#endif
