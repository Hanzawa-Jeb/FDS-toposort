#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int * data;
    int size;
} completeBST;
typedef completeBST * bst_ptr;

typedef struct 
{
    int * data;
    int size;
    int head;
} List;
typedef List * list_ptr;

void sortList(int len, int * list);
void inOrderTraverse(bst_ptr bst, list_ptr lst, int rootIndex);
void printLvlOrder(bst_ptr bst);

int main()
{
    bst_ptr BST = (bst_ptr)calloc(1, sizeof(completeBST));
    list_ptr LST = (list_ptr)calloc(1, sizeof(List));
    int inputNum;
    LST->data = (int *)calloc(1010, sizeof(int));
    LST->head = 0;
    LST->size = 0;
    BST->data = (int *)calloc(1010, sizeof(int));
    scanf("%d", &inputNum);
    BST->size = inputNum;
    for (int i = 0; i < inputNum; i ++) {
        scanf("%d", LST->data+i);
        LST->size ++;
    }
    sortList(inputNum, LST->data);
    inOrderTraverse(BST, LST, 1);
    printLvlOrder(BST);
}

void sortList(int len, int * list)
{
    int tempPos, tempNum;
    for (int i = 0; i < len; i ++) {
        tempPos = i;
        for (int j = i + 1; j < len; j ++) {
            if (list[tempPos] > list[j])
            {
                tempPos = j;
            }
        }
        tempNum = list[i];
        list[i] = list[tempPos];
        list[tempPos] = tempNum;
    }
}

void inOrderTraverse(bst_ptr bst, list_ptr lst, int rootIndex)
{
    int currBSTPos = rootIndex, leftSubPos = 2 * rootIndex, rightSubPos = leftSubPos + 1;
    if (leftSubPos <= bst->size)
    {
        inOrderTraverse(bst, lst, leftSubPos);
    }
    bst->data[rootIndex] = lst->data[lst->head];
    lst->head ++;
    if (rightSubPos <= bst->size)
    {
        inOrderTraverse(bst, lst, rightSubPos);
    }
}

void printLvlOrder(bst_ptr bst)
{
    int * outputList = (int * )calloc(bst->size, sizeof(int));
    for (int i = 1; i <= bst->size; i ++)
    {
        outputList[i - 1] = bst->data[i];
    }
    for (int i = 0; i < bst->size; i ++) 
    {
        printf("%d", outputList[i]);
        if (i != bst->size - 1)
        {
            printf(" ");
        }
    }
}