#ifndef __LIST_H
#define __LIST_H
#include <cstdlib>

/* This class just holds a single data item. */
template <class T>
struct ListItem
{
    T value;
    ListItem<T> *next;
    ListItem<T> *prev;

    ListItem(T theVal)
    {
        this->value = theVal;
        this->next = NULL;
        this->prev = NULL;
    }
};

/* This is the generic List class */
template <class T>
class LinkedList
{
    ListItem<T> *head;

public:

    // Constructor
    LinkedList();

    // Copy Constructor
    LinkedList(const LinkedList<T>& otherList);

    // Destructor
    ~LinkedList();

    // Insertion Functions
    void Insert_at_Head(T item);
    void Insert_at_Tail(T item);
    void Insert_After(T toInsert, T afterWhat);

    // Lookup Functions
    ListItem<T> *Get_Head();
    ListItem<T> *Get_Tail();
    ListItem<T> *Search_For_Element(T item);
	ListItem<T> *Get_Min();
	ListItem<T> *Get_Max();

    // Deletion Functions
    void Delete_Element(T item);
    void Delete_Head();
    void Delete_Tail();

    // Utility Functions
    int Get_Length();

	//Reverse Function
	void Reverse_List();
};

#endif
