#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
struct Node {
    ElementType Element;
    Position Next;
};

List Read(); /* details omitted */
void Print( List L ); /* details omitted */
List Reverse( List L );

int main()
{
    List L1, L2;
    L1 = Read();
    L2 = Reverse(L1);
    Print(L1);
    Print(L2);
    return 0;
}

List Reverse( List L )
{
    Position prevPtr = L, currPtr = L->Next, newHead, nextPtr;
    if (currPtr == NULL)
    {
        newHead = (Position)calloc(1, sizeof(struct Node));
        newHead->Next = NULL;
        L->Next = newHead->Next;
        return newHead;
    }
    prevPtr = prevPtr->Next;
    currPtr = currPtr->Next;
    prevPtr->Next = NULL;
    while (currPtr != NULL)
    {
        nextPtr = currPtr->Next;
        currPtr->Next = prevPtr;
        prevPtr = currPtr;
        currPtr = nextPtr;
    }
    newHead = (Position)calloc(1, sizeof(struct Node));
    newHead->Next = prevPtr;
    L->Next = newHead->Next;
    return newHead;
}