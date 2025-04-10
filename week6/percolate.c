#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
#define MinData -1

typedef struct HeapStruct *PriorityQueue;
struct HeapStruct {
    ElementType  *Elements;
    int Capacity;
    int Size;
};

PriorityQueue Initialize( int MaxElements ); /* details omitted */

void PercolateUp( int p, PriorityQueue H );
void PercolateDown( int p, PriorityQueue H );

void Insert( ElementType X, PriorityQueue H ) 
{
    int p = ++H->Size;
    H->Elements[p] = X;
    PercolateUp( p, H );
}

ElementType DeleteMin( PriorityQueue H ) 
{ 
    ElementType MinElement; 
    MinElement = H->Elements[1];
    H->Elements[1] = H->Elements[H->Size--];
    PercolateDown( 1, H );
    return MinElement; 
}

int main()
{
    int n, i, op, X;
    PriorityQueue H;

    scanf("%d", &n);
    H = Initialize(n);
    for ( i=0; i<n; i++ ) {
        scanf("%d", &op);
        switch( op ) {
        case 1:
            scanf("%d", &X);
            Insert(X, H);
            break;
        case 0:
            printf("%d ", DeleteMin(H));
            break;
        }
    }
    printf("\nInside H:");
    for ( i=1; i<=H->Size; i++ )
        printf(" %d", H->Elements[i]);
    return 0;
}

void PercolateUp( int p, PriorityQueue H )
{
    int parentIndex, temp;
    parentIndex = p / 2;
    while (H->Elements[parentIndex] > H->Elements[p])   //still needs to percolate up
    {
        temp = H->Elements[parentIndex];
        H->Elements[parentIndex] = H->Elements[p];
        H->Elements[p] = temp;                          //exchange values
        p = p / 2;                                      //percolate up p
        parentIndex = p / 2;                            //update parentIndex
    }
}

void PercolateDown( int p, PriorityQueue H )
{
    int leftSubIndex, rightSubIndex, size = H->Size, temp;
    while (1)
    {
        leftSubIndex = 2 * p;
        rightSubIndex = 2 * p + 1;
        if (leftSubIndex > size)
        {
            break;
        }
        else if (rightSubIndex > size)
        {
            if (H->Elements[leftSubIndex] < H->Elements[p])
            {
                temp = H->Elements[leftSubIndex];
                H->Elements[leftSubIndex] = H->Elements[p];
                H->Elements[p] = temp;
            }
            break;
        }
        else
        {
            if (H->Elements[leftSubIndex] < H->Elements[rightSubIndex])
            {
                if (H->Elements[p] > H->Elements[leftSubIndex])
                {
                    temp = H->Elements[leftSubIndex];
                    H->Elements[leftSubIndex] = H->Elements[p];
                    H->Elements[p] = temp;
                    p = leftSubIndex;
                }
                else
                {
                    break;
                }
            }
            else
            {
                if (H->Elements[p] > H->Elements[rightSubIndex])
                {
                    temp = H->Elements[rightSubIndex];
                    H->Elements[rightSubIndex] = H->Elements[p];
                    H->Elements[p] = temp;
                    p = rightSubIndex;
                }
                else
                {
                    break;
                }
            }
        }
    }
}