#include <stdio.h>
#include <stdlib.h>
typedef struct Node *PtrToNode;
struct Node  {
    int Coefficient;
    int Exponent;
    PtrToNode Next;
};
typedef PtrToNode Polynomial;

Polynomial Read(); /* details omitted */
void Print( Polynomial p ); /* details omitted */
Polynomial Add( Polynomial a, Polynomial b );

int main()
{
    Polynomial a, b, s;
    a = Read();
    b = Read();
    s = Add(a, b);
    Print(s);
    return 0;
}

Polynomial Add(Polynomial a, Polynomial b)
{
    Polynomial sum, tempPointer;
    int tempSum;
    sum = (PtrToNode)calloc(1, sizeof(struct Node));
    sum->Next = NULL;
    tempPointer = sum;
    PtrToNode pt1 = a->Next, pt2 = b->Next;
    while (pt1 != NULL && pt2 != NULL)
    {
        if (pt1->Exponent > pt2->Exponent)
        {
            tempPointer->Next = (PtrToNode)calloc(1, sizeof(struct Node));
            tempPointer->Next->Exponent = pt1->Exponent;
            tempPointer->Next->Coefficient = pt1->Coefficient;
            tempPointer->Next->Next = NULL;
            tempPointer = tempPointer->Next;
            pt1 = pt1->Next;
        }
        else if (pt1->Exponent < pt2->Exponent)
        {
            tempPointer->Next = (PtrToNode)calloc(1, sizeof(struct Node));
            tempPointer->Next->Exponent = pt2->Exponent;
            tempPointer->Next->Coefficient = pt2->Coefficient;
            tempPointer->Next->Next = NULL;
            pt2 = pt2->Next;
            tempPointer = tempPointer->Next;
        }
        else
        {
            tempSum = pt1->Coefficient + pt2->Coefficient;
            if (tempSum == 0)
            {
                pt1 = pt1->Next;
                pt2 = pt2->Next;
            }
            else 
            {
            tempPointer->Next = (PtrToNode)calloc(1, sizeof(struct Node));
            tempPointer->Next->Exponent = pt1->Exponent;
            tempPointer->Next->Coefficient = tempSum;
            tempPointer->Next->Next = NULL;
            pt1 = pt1->Next;
            pt2 = pt2->Next;
            tempPointer = tempPointer->Next;
            }
        }
    }
    if (pt1 != NULL)
    {
        while (pt1 != NULL)
        {
            tempPointer->Next = (PtrToNode)calloc(1, sizeof(struct Node));
            tempPointer->Next->Exponent = pt1->Exponent;
            tempPointer->Next->Coefficient = pt1->Coefficient;
            tempPointer->Next->Next = NULL;
            tempPointer = tempPointer->Next;
            pt1 = pt1->Next;
        }
    }
    else if (pt2 != NULL)
    {
        while (pt2 != NULL)
        {
            tempPointer->Next = (PtrToNode)calloc(1, sizeof(struct Node));
            tempPointer->Next->Exponent = pt2->Exponent;
            tempPointer->Next->Coefficient = pt2->Coefficient;
            tempPointer->Next->Next = NULL;
            pt2 = pt2->Next;
            tempPointer = tempPointer->Next;
        }
    }
    return sum;
}