/* Author : Huang Yuheng;  ID : 3240102750;  No.01*/ 
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

typedef struct {
    int maxSize;
    int currSize;
    int * cont;
} Queue;
typedef Queue * quePtr;

void initQue(quePtr que, int maxSize);
void startProc(quePtr histQue, quePtr cacheQue, int cacheHit, int pageCnt);
void histEnque(quePtr que, int element, int * countTab);
void histDeque(quePtr que, int element, int * countTab);
void histUpdate(quePtr que, int element, int * countTab);
void cacheEnque(quePtr que, int element, int * countTab);
void cacheUpdate(quePtr que, int element, int * countTab);
void printQue(quePtr histQue, quePtr cacheQue);
bool elementInQue(quePtr que, int element);

int main()
{
    int cacheHit, queSize, pageCnt;
    //respectively the threshold for the cache hit, the size of the queue
    //and the count of the page
    scanf("%d %d %d", &cacheHit, &queSize, &pageCnt);
    quePtr histQue = (quePtr)calloc(1, sizeof(Queue));
    quePtr cacheQue = (quePtr)calloc(1, sizeof(Queue));
    initQue(histQue, queSize);
    initQue(cacheQue, queSize);
    startProc(histQue, cacheQue, cacheHit, pageCnt);
    printQue(histQue, cacheQue);
    //start the process of page entering
    return 0;
}

void initQue(quePtr que, int maxSize)
{
    que->cont = (int *)calloc(maxSize, sizeof(int));
    que->currSize = 0;
    que->maxSize = maxSize;
}

void startProc(quePtr histQue, quePtr cacheQue, int cacheHit, int pageCnt)
{
    int curr;
    int * countTab = (int *)calloc(20001, sizeof(int));
    //the table to store the number of visiting
    for (int i = 0 ; i < pageCnt; i ++) {
        scanf("%d", &curr);
        //not in the cacheque
        if (elementInQue(cacheQue, curr)) {
            //in the cacheQue
            cacheUpdate(cacheQue, curr, countTab);
            //update the position in the cacheQue
        } else if (elementInQue(histQue, curr)) {
            countTab[curr] ++;
            //in the histQue
            if (countTab[curr] == cacheHit) {
                histDeque(histQue, curr, countTab);
                cacheEnque(cacheQue, curr, countTab);
            } else {
                histUpdate(histQue, curr, countTab);
            }
        } else {
            //not in anything
            countTab[curr] ++;
            //add to the count
            histEnque(histQue, curr, countTab);
        }
    }
}

void histEnque(quePtr que, int element, int * countTab)
{
    //not implemented yet
    if (que->currSize < que->maxSize) {
        que->cont[que->currSize] = element;
        que->currSize = que->currSize + 1;
    } else {
        for (int i = 0; i < que->maxSize - 1; i ++) {
            que->cont[i] = que->cont[i + 1];
        }
        que->cont[que->maxSize - 1] = element;
    }
}

void histDeque(quePtr que, int element, int * countTab)
{
    int tempPos = 0;
    for (int i = 0; i < que->currSize; i ++) {
        if (que->cont[i] == element) {
            tempPos = i;
            break;
        }
    }
    for (int i = tempPos; i < que->currSize - 1; i ++) {
        que->cont[i] = que->cont[i + 1];
    }
    countTab[element] = 0;
    que->currSize --;
}

void histUpdate(quePtr que, int element, int * countTab)
{
    int tempPos = 0;
    for (int i = 0; i < que->currSize; i ++) {
        if (que->cont[i] == element) {
            tempPos = i;
            break;
        }
    }
    for (int i = tempPos; i < que->currSize - 1; i ++) {
        que->cont[i] = que->cont[i + 1];
    }
    que->cont[que->currSize - 1] = element;
}

void cacheEnque(quePtr que, int element, int * countTab)
{
    if (que->currSize < que->maxSize) {
        que->cont[que->currSize] = element;
        que->currSize = que->currSize + 1;
    } else {
        for (int i = 0; i < que->maxSize - 1; i ++) {
            que->cont[i] = que->cont[i + 1];
        }
        que->cont[que->maxSize - 1] = element;
    }
}

void cacheUpdate(quePtr que, int element, int * countTab)
{
    int tempPos = 0;
    for (int i = 0; i < que->currSize; i ++) {
        if (que->cont[i] == element) {
            tempPos = i;
            break;
        }
    }
    for (int i = tempPos; i < que->currSize - 1; i ++) {
        que->cont[i] = que->cont[i + 1];
    }
    que->cont[que->currSize - 1] = element;
}

void printQue(quePtr histQue, quePtr cacheQue)
{
    if (histQue->currSize == 0) {
        printf("-\n");
    } else {
        for (int i = 0; i < histQue->currSize; i ++) {
            printf("%d", histQue->cont[i]);
            if (i != histQue->currSize - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
    if (cacheQue->currSize == 0) {
        printf("-");
    } else {
        for (int i = 0; i < cacheQue->currSize; i ++) {
            printf("%d", cacheQue->cont[i]);
            if (i != cacheQue->currSize - 1) {
                printf(" ");
            }
        }
    }
}

bool elementInQue(quePtr que, int element)
{
    bool flag = false;
    for (int i = 0; i < que->currSize; i ++) {
        if (que->cont[i] == element) {
            flag = true;
        }
    }
    return flag;
}