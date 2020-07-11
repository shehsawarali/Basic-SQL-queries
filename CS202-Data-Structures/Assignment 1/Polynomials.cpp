#include <iostream>
#include "LinkedList.cpp"
#include <cmath>

using namespace std;

//   _     =


struct Polynomial
{
    int exp;
    int coeff;

    bool operator==(const Polynomial& p2)
    {
        bool ret = true;

        if(coeff != p2.coeff)
        {
            ret = false;
        }
        if(exp != p2.exp)
        {
            ret = false;
        }

        return ret;
    }
};

int main()
{
    LinkedList<Polynomial> p;

    return 0;
}

int Coeff(int exponent, LinkedList<Polynomial> p)
{
    if(!p.Get_Head())
    {
        return 0;
    }

    ListItem<Polynomial>* temp = p.Get_Head();

    while(temp)
    {
        if(temp->value.exp == exponent)
            return temp->value.coeff;
    }

    return 0;
}

int* roots(LinkedList<Polynomial> p)
{
    ListItem<Polynomial>* temp = p.Get_Head();

    if(temp == NULL || temp->next == NULL || temp->next->next == NULL || temp->next->next->next != NULL)
    {
        int a = 0;
        int* po = &a;
        cout<<"Polynomial is not quadratic"<<endl;
        return po;
    }

    int c, b, a;

    c = temp->value.coeff;
    b = temp->next->value.coeff;
    a = temp->next->next->value.coeff;

    int ans[2];

    ans[0] = (- b - sqrt(b^2 - 4*a*c)) / (2*a);
    ans[1] = (- b + sqrt(b^2 - 4*a*c)) / (2*a);

    return ans;
}

LinkedList<Polynomial> sum(LinkedList<Polynomial> p1, LinkedList<Polynomial> p2)
{
    ListItem<Polynomial>* temp1 = p1.Get_Head();
    ListItem<Polynomial>* temp2 = p2.Get_Head();
    LinkedList<Polynomial> sum;

    while(temp1 && temp2)
    {
        Polynomial x;
        if(temp1->value.exp > temp2->value.exp)
        {
            x.coeff = temp1->value.coeff;
            x.exp = temp1->value.exp;
            temp1 = temp1->next;
        }
        if(temp1->value.exp < temp2->value.exp)
        {
            x.coeff = temp2->value.coeff;
            x.exp = temp2->value.exp;
            temp2 = temp2->next;
        }
        else
        {
            x.coeff = temp1->value.coeff + temp2->value.coeff;
            x.exp = temp1->value.exp;
            temp1 = temp1->next;
            temp2 = temp2->next;
        }

        sum.Insert_at_Tail(x);
    }

    while(temp1 || temp2)
    {
        Polynomial x;
        if(temp1)
        {
            x.coeff = temp1->value.coeff;
            x.exp = temp1->value.exp;
            temp1 = temp1->next;
        }
        if(temp2)
        {
            x.coeff = temp2->value.coeff;
            x.exp = temp2->value.exp;
            temp2 = temp2->next;
        }

        sum.Insert_at_Tail(x);
    }

    return sum;
}

LinkedList<Polynomial> prod(LinkedList<Polynomial> p1, LinkedList<Polynomial> p2)
{
    ListItem<Polynomial>* temp1 = p1.Get_Head();
    ListItem<Polynomial>* temp2 = p2.Get_Head();
    LinkedList<Polynomial> prod;

    while (temp1)
    {
        while (temp2)
        {
            int coeff, exp;

            coeff = temp2->value.coeff * temp2->value.coeff;
            exp = temp1->value.exp + temp2->value.exp;
            Polynomial x;
            x.coeff = coeff;
            x.exp = exp;

            prod.Insert_at_Tail(x);
            temp2 = temp2->next;
        }

        temp1 = temp1->next;
        temp2 = p2.Get_Head();
    }

    temp1 = prod.Get_Head();
    temp2 = temp1->next;

    while(temp1)
    {
        temp2 = temp1->next;

        while(temp2)
        {
            if(temp1->value.exp == temp2->value.exp)
            {
                temp1->value.coeff = temp1->value.coeff + temp2->value.coeff;
                ListItem<Polynomial>* remov = temp2;
                temp2 = temp2->next;
                prod.Delete_Element(remov->value);
            }
            else
                temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }
    return prod;
}

/*int* returnY(LinkedList<Polynomial> p)
{
    int x[2];
    x[0] = roots(p);
    x[1] = roots(p) + 1;

    int y[2];



    for(int i = 0; i < 2; i++)
    {
        ListItem<Polynomial>* temp = p.Get_Head();
        while(temp)
        {
            int s = temp->value.coeff;
            for(int j = 0; j < temp->value.exp; j++)
            {
                s *= x
            }
        }
    }
}*/

int* vertex(LinkedList<Polynomial> p)
{
    int a, b;
    ListItem<Polynomial>* temp = p.Get_Head();

    while(temp)
    {
        if(temp->value.exp == 2)
        {
            a = temp->value.coeff;
        }
        if(temp->value.exp == 1)
        {
            b = temp->value.coeff;
        }

        temp = temp->next;
    }

    int x = (-b)/(2*a);

    int y = 0;

    temp = p.Get_Head();

    while(temp)
    {
        y += temp->value.coeff * x^(temp->value.exp);
    }

    int cord[2] = {x, y};

    return cord;
}
