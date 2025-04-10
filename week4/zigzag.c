#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int Element;
    struct Node * Left;
    struct Node * Right;
} Node;

Node * createTree(int * inList, int * poList, int len);
int getPos(int target, int * list, int len);
void zigzagSequence(Node * rootPtr, int * outputList);
void printSequence(int * headPtr, int len);
void reverseSection(int * list, int startIndex, int endIndex);

int main()
{
    int n;
    scanf("%d", &n);
    int * inList = (int *)calloc(n, sizeof(int));
    int * poList = (int *)calloc(n, sizeof(int));
    int * outputList = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < n; i ++)
    {
        scanf("%d", inList + i);
    }
    for (int i = 0; i < n; i ++)
    {
        scanf("%d", poList + i);
    }
    Node * rootPtr = createTree(inList, poList, n);
    zigzagSequence(rootPtr, outputList);
    printSequence(outputList, n);
    return 0;
}

Node * createTree(int * inList, int * poList, int len)
{
    if (len == 0)
    {
        return NULL;
    }
    int lenLeft, lenRight, rootPos;
    Node * localRoot = (Node *)calloc(1, sizeof(Node));
    localRoot->Element = poList[len - 1];
    rootPos = getPos(poList[len - 1], inList, len);
    lenLeft = rootPos;
    lenRight = len - rootPos - 1;
    localRoot->Left = createTree(inList, poList, lenLeft);
    localRoot->Right = createTree(inList + rootPos + 1, poList + lenLeft, lenRight);
    return localRoot;
}

int getPos(int target, int * list, int len)
{
    for (int i = 0; i < len; i ++)
    {
        if (list[i] == target)
        {
            return i;
        }
    }
    return -1;
}

void zigzagSequence(Node * rootPtr, int * outputList)
{
    Node ** tmpQue = (Node **)calloc(200, sizeof(Node *));
    int outputListIndex = 0;
    int * layerNumberRef = (int *)calloc(100, sizeof(int));
    int layerNumberRefIndex = 0;
    int * layerTraversal = (int *)calloc(50, sizeof(int));
    int layerTraversalIndex = 0;
    Node * tmpGet;
    int queTail = 0, queHead = 0;
    tmpQue[queTail] = rootPtr;
    queTail ++;
    while (queHead < queTail)
    {
        layerNumberRef[layerNumberRefIndex] = queTail - queHead;
        layerNumberRefIndex ++;
        for (int i = 0; i < layerNumberRef[layerNumberRefIndex - 1]; i ++)
        {
            Node * tmpGet = tmpQue[queHead];
            queHead ++;
            layerTraversal[layerTraversalIndex] = tmpGet->Element;
            layerTraversalIndex ++;
            if (tmpGet->Left != NULL)
            {
                tmpQue[queTail] = tmpGet->Left;
                queTail ++;
            }
            if (tmpGet->Right != NULL)
            {
                tmpQue[queTail] = tmpGet->Right;
                queTail ++;
            }
        }
    }

    int outIndex = 0, startIndex = 0;
    for (int level = 0; level < layerNumberRefIndex; level++)
    {
        int count = layerNumberRef[level];
        for (int k = 0; k < count; k++)
        {
            outputList[outIndex++] = layerTraversal[startIndex + k];
        }
        if (level % 2 == 0)
        {
            reverseSection(outputList, startIndex, startIndex + count);
        }
        startIndex += count;
    }
}

void printSequence(int * headPtr, int len)
{
    for (int i = 0; i < len - 1; i ++)
    {
        printf("%d ", headPtr[i]);
    }
    printf("%d", headPtr[len - 1]);
}

void reverseSection(int * list, int startIndex, int endIndex)
{
    int left = startIndex, right = endIndex - 1;
    int temp;
    while (left < right)
    {
        temp = list[left];
        list[left] = list[right];
        list[right] = temp;
        left ++;
        right --;
    }
}