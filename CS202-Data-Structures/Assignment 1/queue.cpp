#ifndef __QUEUE_CPP
#define __QUEUE_CPP
#include "queue.h"

template <class T>
Queue<T>::Queue():list()
{

}

template <class T>
Queue<T>::Queue(const Queue<T>& otherQueue):list(otherQueue.list)
{

}

template <class T>
Queue<T>::~Queue()
{

}

template <class T>
void Queue<T>::Enqueue(T item)
{
    list.insertAtTail(item);
}

template <class T>
T Queue<T>::Get_Front()
{
    return list.Get_Head()->value;
}

template <class T>
T Queue<T>::Dequeue()
{
    T ret = (list.getHead())->value;
	list.deleteHead();
	return ret;
}

template <class T>
int Queue<T>::Get_Length()
{
    return list.Get_Length();
}

template <class T>
bool Queue<T>::Is_Empty()
{
    if(list.getHead() == NULL)
		{return true;}
	else
		{return false;}
}


#endif
