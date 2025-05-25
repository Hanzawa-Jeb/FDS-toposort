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
void cacheEnque(quePtr que, int element, int * countTab);
void cacheUpdate(quePtr que, int element, int * countTab);
void printQue(quePtr histQue, quePtr cacheQue);

int main()
{
    int cacheHit, queSize, pageCnt;
    //respectively the threshold for the cache hit, the size of the queue
    //and the count of the page
    scanf("%d %d %d", &cacheHit, &queSize, &pageCnt);
    quePtr histQue, cacheQue;
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
        if (countTab[curr] != INT_MAX) {
            countTab[curr] ++;
            histEnque(histQue, curr, countTab);
        }

        if (countTab[curr] >= cacheHit && countTab[curr] != INT_MAX) {
            //first time in the cacheQue
            countTab[curr] = INT_MAX;
            histDeque(histQue, curr, countTab);
            cacheEnque(cacheQue, curr, countTab);
        } else if (countTab[curr] == INT_MAX) {
            //already in the cacheQue
            cacheUpdate(cacheQue, curr, countTab);
        }

    }
}

void histEnque(quePtr que, int element, int * countTab)
{
    //not implemented yet
}

void histDeque(quePtr que, int element, int * countTab)
{

}

void cacheEnque(quePtr que, int element, int * countTab)
{
    //not implemented yet
}

void cacheUpdate(quePtr que, int element, int * countTab)
{

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