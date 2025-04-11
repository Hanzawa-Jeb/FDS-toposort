#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct AdjV
{
    int Element;
    struct AdjV * Next;
}AdjV;
typedef AdjV * AdjVPtr;

void createGraph(int eCnt, int vCnt, AdjVPtr * AdjList, AdjVPtr * tailList);
void judgeTop(int eCnt, int vCnt, AdjVPtr * AdjList, AdjVPtr * tailList);
bool judgeCycle(int eCnt, int vCnt, AdjVPtr * AdjList, AdjVPtr * tailList);
bool checkConnect(AdjVPtr * AdjList, int vertex1, int vertex2);

int main()
{
    int vCnt, eCnt;
    scanf("%d %d", &vCnt, &eCnt);
    AdjVPtr * AdjList = (AdjVPtr *)calloc(vCnt + 1, sizeof(AdjVPtr));
    AdjVPtr * tailList = (AdjVPtr *)calloc(vCnt + 1, sizeof(AdjVPtr));
    for (int i = 1; i <= vCnt; i ++) 
    {
        //initialize the basic information of two lists.
        AdjList[i] = (AdjVPtr)calloc(1, sizeof(AdjV));
        AdjList[i]->Element = 0;
        AdjList[i]->Next = NULL;
        tailList[i] = AdjList[i];
    }
    //used to store the graph in Adjacency List format
    createGraph(eCnt, vCnt, AdjList, tailList);
    judgeTop(eCnt, vCnt, AdjList, tailList);
    return 0;
}

void createGraph(int eCnt, int vCnt, AdjVPtr * AdjList, AdjVPtr * tailList)
//used to create the graph as AdjList
{
    int vertex1, vertex2;
    AdjVPtr newNode1, newNode2;
    for (int i = 0; i < eCnt; i ++)
    {
        scanf("%d %d", &vertex1, &vertex2);
        newNode1 = (AdjVPtr)calloc(1, sizeof(AdjV));
        newNode1->Element = 0;
        newNode1->Next = NULL;
        newNode2 = (AdjVPtr)calloc(1, sizeof(AdjV));
        newNode2->Element = 0;
        newNode2->Next = NULL;
        tailList[vertex1]->Element = vertex2;
        tailList[vertex1]->Next = newNode1;
        tailList[vertex1] = newNode1;
        tailList[vertex2]->Element = vertex1;
        tailList[vertex2]->Next = newNode2;
        tailList[vertex2] = newNode2;
    }
}

void judgeTop(int eCnt, int vCnt, AdjVPtr * AdjList, AdjVPtr * tailList)
{
    int judgeCnt;
    scanf("%d", &judgeCnt);
    for (int i = 0; i < judgeCnt; i ++)
    {
        if(judgeCycle(eCnt, vCnt, AdjList, tailList))
        {
            printf("YES\n");
        }
        else
        {
            printf("NO\n");
        }
    }
}

bool judgeCycle(int eCnt, int vCnt, AdjVPtr * AdjList, AdjVPtr * tailList)
{
    int seqLen;
    int vertex1, vertex2;
    bool flag = true;
    scanf("%d", &seqLen);
    int * inputTable = (int *)calloc(seqLen, sizeof(int));
    bool * presTab = (bool *)calloc(vCnt + 1, sizeof(bool));
    for (int i = 0; i < seqLen; i ++)
    {
        scanf("%d", inputTable + i);
    }
    for (int i = 0; i < seqLen - 1; i ++)
    {
        vertex1 = inputTable[i];
        vertex2 = inputTable[i + 1];
        if (!checkConnect(AdjList, vertex1, vertex2))
        {
            flag = false;
            break;
        }
    }
    vertex1 = inputTable[0];
    vertex2 = inputTable[seqLen - 1];
    if (vertex1 != vertex2)
    {
        flag = false;
    }
    if (seqLen != vCnt + 1)
    {
        flag = false;
    }
    for (int i = 0; i < seqLen; i ++)
    {
        presTab[inputTable[i]] = true;
    }
    for (int i = 1; i < vCnt + 1; i ++)
    {
        if (!presTab[i])
        {
            flag = false;
            break;
        }
    }
    return flag;
}

bool checkConnect(AdjVPtr * AdjList, int vertex1, int vertex2)
{
    AdjVPtr curr = AdjList[vertex1];
    int currElement = curr->Element;
    bool flag = false;
    while (1)
    {
        if (currElement == 0)
        {
            break;
        }
        if (currElement == vertex2)
        {
            flag = true;
            break;
        }
        curr = curr->Next;
        currElement = curr->Element;
    }
    return flag;
}