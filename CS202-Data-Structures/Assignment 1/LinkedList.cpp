#ifndef __LIST_CPP
#define __LIST_CPP

#include <cstdlib>
#include "LinkedList.h"

using namespace std;

template <class T>
LinkedList<T>::LinkedList()
{
    head = NULL;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& otherLinkedList)
{
    head = NULL;

	ListItem<T> *p = otherLinkedList.head;
	while (p)
	{
		Insert_at_Tail(p->value);
		p = p->next;
	}
}

template <class T>
LinkedList<T>::~LinkedList() //NOT DONEEEEEEEEEEEEEEEE
{

}

template <class T>
void LinkedList<T>::Insert_at_Head(T item)
{
	if (head != NULL)
	{
	    ListItem<T> *p = new ListItem<T>(item);
	    p->prev = NULL;
		p->next = head;
		head->prev = p;
		head = p;
	}
	else
	{
	    ListItem<T> *p = new ListItem<T>(item);
		head = p;
	}
}

template <class T>
void LinkedList<T>::Insert_at_Tail(T item)
{
    ListItem<T> *p = new ListItem<T>(item);
    if(head)
    {
        ListItem<T> *temp = head;
        while(temp->next)
        {
            temp = temp->next;
        }
        temp->next = p;
        p->prev = temp;

    }
    else
    {
        head = p;
    }
}

template <class T>
void LinkedList<T>::Insert_After(T toInsert, T afterWhat)
{
    ListItem<T> *p = Search_For_Element(afterWhat);

    if(head == NULL || p == NULL)
        return;


    ListItem<T> *add = new ListItem<T>(toInsert);
    if(p->next)
    {
        add->next = p->next;
        //add->prev = p;

        p->next->prev = add;
        //p->next = add;
    }

    add->prev = p;
    p->next = add;
}


template <class T>
ListItem<T>* LinkedList<T>::Get_Head()
{
	return head;
}

template <class T>
ListItem<T>* LinkedList<T>::Get_Tail()
{
    if(head)
    {
        ListItem<T> *temp = head;
        while(temp->next)
        {
            temp = temp->next;
        }
        return temp;

    }
    else
    {
        return NULL;
    }
}

template <class T>
ListItem<T> *LinkedList<T>::Search_For_Element(T item)
{
    if(head == NULL)
		{return NULL;}

	if(head->next == NULL && !(head->value == item))
		{return NULL;}

	ListItem<T> *p = head;

	while(p)
    {
        if(p->value == item)
            {return p;}

        p = p->next;
    }
	return NULL;
}

template <class T>
ListItem<T>* LinkedList<T>::Get_Min()
{
	if(!head)
        return NULL;

    if(head->next == NULL)
    {
        return head;
    }

    ListItem<T> *p = head;
    ListItem<T> *ret = head;

    while(p)
    {
        if(p->value < ret->value)
            ret = p;

        p = p->next;
    }

    return ret;
}

template <class T>
ListItem<T>* LinkedList<T>::Get_Max()
{
	if(!head)
        return NULL;

    if(head->next == NULL)
    {
        return head;
    }

    ListItem<T> *p = head;
    ListItem<T> *ret = head;

    while(p)
    {
        if(p->value > ret->value)
            ret = p;

        p = p->next;
    }

    return ret;
}

template <class T>
void LinkedList<T>::Delete_Element(T item)
{
    ListItem<T>* p = Search_For_Element(item);

    if(p == NULL)
        return;

    if(p->next)
    {
        p->next->prev = p->prev;
    }
    if(p->prev)
    {
        p->prev->next = p->next;
    }

    delete p;
}

template <class T>
void LinkedList<T>::Delete_Head()
{
    if(head == NULL)
        return;

    if(head)
    {
        ListItem<T>* temp = head;

        if(head->next != NULL)
        {
            head = head->next;
            head->prev = NULL;
            delete temp;
        }
        else
        {
            delete temp;
            head = NULL;
        }
    }
}

template <class T>
void LinkedList<T>::Delete_Tail()
{
    if(head == NULL)
    {
        return;
    }
    else if(head->next == NULL)
    {
        Delete_Head();
    }
    else
    {
        ListItem<T> *temp = Get_Tail();
        temp->prev->next = NULL;
        delete temp;
    }
}

template <class T>
int LinkedList<T>::Get_Length()
{
    if(head == NULL)
    {
        return 0;
    }

    ListItem<T>* p = head;
    int Count = 0;

    while(p)
    {
        Count++;
        p = p->next;
    }

    return Count;
}

template <class T>
void LinkedList<T>::Reverse_List() //NOT DONEEEEE
{
    if(head == NULL)
    {
        return;
    }
    else if(head->next == NULL)
    {
        return;
    }
    else if(head)
    {
        ListItem<T> *temp = head;
        while(temp)
        {
            ListItem<T>* change = temp->next;
            temp->next = temp->prev;
            temp->prev = change;

            temp = temp->prev;
        }
    }
}

#endif
