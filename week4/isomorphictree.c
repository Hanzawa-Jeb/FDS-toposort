#include <stdio.h>
#include <stdlib.h>

typedef char ElementType;

typedef struct TreeNode *Tree;
struct TreeNode {
    ElementType Element;
    Tree  Left;
    Tree  Right;
};

Tree BuildTree(); /* details omitted */

int Isomorphic( Tree T1, Tree T2 );

int main()
{
    Tree T1, T2;
    T1 = BuildTree();
    T2 = BuildTree();
    printf("%d\n", Isomorphic(T1, T2));
    return 0;
}

/* Your function will be put here */


/*int Isomorphic(Tree T1, Tree T2)
{
    if (T1 == NULL && T2 == NULL)
    {
        return 1;
    }
    else if (T1->Element != T2->Element)
    {
        return 0;
    }
    else
    {
        if (T1->Left == NULL && T2->Left == NULL && T1->Right == NULL && T2->Right == NULL)
        {
            if (T1->Element == T2->Element)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else if (T1->Left == NULL && T2->Left == NULL && (T1->Right->Element == T2->Right->Element))
        {
            return Isomorphic(T1->Right, T2->Right);
        }
        else if (T1->Right == NULL && T2->Right == NULL && (T1->Left->Element == T2->Right->Element))
        {
            return Isomorphic(T1->Left, T2->Left);
        }
        else if (T1->Right == NULL && T2->Left == NULL && (T1->Left->Element == T2->Right->Element))
        {
            return Isomorphic(T1->Left, T2->Right);
        }
        else if (T1->Left == NULL && T2->Right == NULL && (T1->Right->Element == T2->Left->Element))
        {
            return Isomorphic(T2->Right, T1->Left);
        }
        else if (T1->Left->Element == T2->Left->Element && T1->Right->Element == T2->Right->Element)
        {
            if (Isomorphic(T1->Left, T2->Left) && Isomorphic(T1->Right, T2->Right))
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else if (T1->Left->Element == T2->Right->Element && T1->Right->Element == T2->Left->Element)
        {
            if (Isomorphic(T1->Left, T2->Right) && Isomorphic(T1->Right, T2->Left))
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
}*/

int Isomorphic(Tree T1, Tree T2)
{
    if (T1 == NULL && T2 == NULL)
    {
        return 1;
    }
    else if (T1 == NULL || T2 == NULL)
    {
        return 0;
    }
    else if (T1->Element != T2->Element)
    {
        return 0;
    }
    else {
        if (Isomorphic(T1->Left, T2->Left) && Isomorphic(T1->Right, T2->Right))
        {
            return 1;
        }
        else if (Isomorphic(T1->Left, T2->Right) && Isomorphic(T1->Right, T2->Left))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}