#ifndef __AVL_CPP
#define __AVL_CPP
#include "avl.h"
#include <iostream>
#include <queue>
// HELPER FUNCTIONS HERE...
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
}

template <class T>
int BST<T> :: height (node<T>* p)
{
    if(p == NULL)
        {return 1;}

    if(height(p->left) > height(p->right))
        {return (height(p->left) + 1);}

    return (height(p->right) + 1);
}

template <class T>
int BST<T> :: balanceFactor(node<T>* p)
{
    if (p == NULL)
    {return 1;}

    return (height(p->left) - height(p->right));
}

template <class T>
void BST<T> :: fixHeight(node<T>* p)
{
    p->height = height(p);
}

// ROTATING HELPERS 
template <class T>
node<T>* BST<T> :: rotateleft(node<T>* p)
{
    node<T> *right = p->right;
    node<T> *rightleft = right->left;

    right->left = p;
    p->right = rightleft;

    fixHeight(p);
    fixHeight(right);

    return right;
}

template <class T>
node<T>* BST<T> :: rotateright(node<T>* p)
{
    node<T> *left = p->left;
    node<T> *leftright = left->right;

    left->right = p;
    p->left = leftright;

    fixHeight(p);
    fixHeight(left);

    return left;
}

template <class T>
node<T>* BST<T> :: balance(node<T>* p)
{
    int fac = balanceFactor(p);
    if(fac > 1)//left
    {
        if(balanceFactor(p->left) > 0) //left  left
        {
            p = rotateright(p);
            fixHeight(p);
            return p;
        }

        p->left  = rotateleft(p->left);//left right
        p = rotateright(p);
        fixHeight(p);
        fixHeight(p->left);
        return p;
    }

    if(fac < -1)//right
    {
        if(balanceFactor(p->right) > 0)//right left
        {
        	p->right = rotateright(p->right);
            p = rotateleft(p);
            fixHeight(p->right);
            fixHeight(p);
            return p;
        }

        
        p = rotateleft(p); //right right
        fixHeight(p);
        return p;
        
    }
    return p;
}

// CLASS FUNCTIONS HERE
template <class T>
void BST<T> :: insert(string value,T k)
{
    root = insertHelper(value,k,root);
    //root = balance(root);
}
// insertion helper
template <class T>
node<T>* BST<T> :: insertHelper(string value,T k, node<T> *p) //check
{
    if(p == NULL)
    {
    	node<T>* temp = new node<T>(k, value); 
    	return temp;
    }

    if(k < p->key)
    {
        p->left = insertHelper(value, k, p->left); return balance(p);
    }

    if(k > p->key)
    {
        p->right = insertHelper(value, k, p->right); return balance(p);
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

// DELETE HELPER FUNCTIONS
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
            p =  balance(temp);
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
        if(p->left == NULL && p->right == NULL) //no children
        {
            delete p; return NULL;
        }

        if(p->left == NULL || p->right == NULL) //one child
        {
            node<T>* ret;
            if(p->left == NULL)
                ret = p->right;

            if(p->right == NULL)
                ret = p->left;

            delete p;
            p = ret;
        }

        if(p->left != NULL && p->right != NULL) //two children
        {
            node<T>* ret = findmin(p->right);

            p->key = ret->key;
            p->value = ret->value;
            p->right= removemin(p->right);
        }
    }

    return balance(p);
}

template<class T>
node<T>* BST<T>::getRoot()
{
    return root;
}
#endif
