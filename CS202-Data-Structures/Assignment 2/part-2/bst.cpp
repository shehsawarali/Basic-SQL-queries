#ifndef __BST_CPP
#define __BST_CPP
#include "bst.h"
#include <iostream>
#include <queue>

template <class T>
BST<T>::BST()
{
	root = NULL;
}

template <class T>
BST<T>:: ~BST()
{
    destruct(root);
}

template<class T>
void destruct(node<T>* p)
{
    if(p == NULL)
        {return;}

    destruct(p->left);
    destruct(p->right);
    delete  p;
    p = NULL;
    return;
}

template <class T>
int BST<T> :: height (node<T>* p)
{
    if(p == NULL)
        {return 0;}

    if(height(p->left) > height(p->right))
        {return (height(p->left) + 1);}

    return (height(p->right) + 1);
}

template <class T>
void BST<T> :: insert(string value,T k)
{
    root = insertHelper(value,k,root);
}

template <class T>
node<T>* BST<T> :: insertHelper(string value,T k, node<T> *p)
{
    if(p == NULL)
        {node<T>* temp = new node<T>(k, value); return temp;}

    if(k < p->key)
    {
        p->left = insertHelper(value, k, p->left);
    }

    if(k > p->key)
    {
        p->right = insertHelper(value, k, p->right);
    }

    return p;
}

template<class T>
node<T>* BST<T> :: search(T key)
{
    return srecursion(key, root);
}

template<class T>
node<T>* srecursion(T key, node<T>* p)
{
    if(p == NULL)
        {return NULL;}

    if (key == p->key)
        {return p;}
     
    if (key < p->key)
        {return srecursion(key, p->left);}

    return srecursion(key, p->right);
}

template<class T>
node<T>* BST<T> :: findmin(node<T> *p)
{
    if(p->left == NULL)
        {return p;}

    return findmin(p->left);
}

template<class T>
node<T>* BST<T>::removemin(node<T>* p)
{
    if(p->left == NULL)
    {
        if(p->right == NULL)
        {
            delete p;
            return NULL;
        }
        else
        {
            node<T>* temp = p->right;
            delete p;
            p =  temp;
        }
    }
    else
    {
        p->left = removemin(p->left);
    }
}

template<class T>
void BST<T>::delete_node(T k)
{
    root = remove(root, k);
}

template<class T>
node<T>*  BST<T>::remove(node<T>* p, T k) // k key deletion from p tree
{
    if(p == NULL)
        {return NULL;}

    else if(p->key < k)
        {p->right = remove(p->right, k);}

    else if(p->key > k)
        {p->left =  remove(p->left, k);}

    else
    {
        if(p->left == NULL && p->right == NULL)
        {
            delete p; return NULL;
        }

        if(p->left == NULL || p->right == NULL)
        {
            node<T>* ret;
            if(p->left == NULL)
                ret = p->right;

            if(p->right == NULL)
                ret = p->left;

            delete p;
            p = ret;
        }

        if(p->left != NULL && p->right != NULL)
        {
            node<T>* ret = findmin(p->right);

            p->key = ret->key;
            p->value = ret->value;
            p->right= removemin(p->right);
        }
    }

    return p;
}

template<class T>
node<T>* BST<T>::getRoot()
{
    return root;
}
#endif
