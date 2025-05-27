/* Author : Huang Yuheng;  ID : 3240102750;  No.01*/ 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int maxSize;    
    int currSize;   
    int *cont;      
} Queue;
typedef Queue * quePtr;

void initQue(quePtr que, int maxSize) {
    que->cont = (int *)calloc(maxSize, sizeof(int));
    que->currSize = 0;
    que->maxSize = maxSize;
}


void startProc(quePtr histQue, quePtr cacheQue, int cacheHit, int pageCnt) {
    int curr;
    int *countTab = (int *)calloc(20001, sizeof(int)); 
    for (int i = 0; i < pageCnt; i++) {
        scanf("%d", &curr);
        if (elementInQue(cacheQue, curr)) {
            cacheUpdate(cacheQue, curr);
        }
        else if (elementInQue(histQue, curr)) {
            countTab[curr]++;
            if (countTab[curr] == cacheHit) {
                histDeque(histQue, curr);
                cacheEnque(cacheQue, curr);
            } else {
                histUpdate(histQue, curr);
            }
        }
        else {
            countTab[curr] = 1;
            histEnque(histQue, curr);
        }
    }

    free(countTab);
}

void histEnque(quePtr que, int element) {
    if (que->currSize == que->maxSize) {
        // 队头出队
        for (int i = 1; i < que->currSize; i++)
            que->cont[i-1] = que->cont[i];
        que->currSize--;
    }
    que->cont[que->currSize++] = element;
}

void histDeque(quePtr que, int element) {
    int idx=-1;
    for (int i = 0; i < que->currSize; i++) {
        if (que->cont[i] == element) { idx = i; break; }
    }
    if (idx==-1) return;
    for (int i = idx+1; i < que->currSize; i++)
        que->cont[i-1] = que->cont[i];
    que->currSize--;
}

void histUpdate(quePtr que, int element) {
    int idx=-1;
    for (int i = 0; i < que->currSize; i++) {
        if (que->cont[i] == element) { idx = i; break; }
    }
    if (idx==-1) return;
    int tmp = que->cont[idx];
    for (int i = idx+1; i < que->currSize; i++)
        que->cont[i-1] = que->cont[i];
    que->cont[que->currSize-1] = tmp;
}

void cacheEnque(quePtr que, int element) {
    if (que->currSize == que->maxSize) {
        for (int i = 1; i < que->currSize; i++)
            que->cont[i-1] = que->cont[i];
        que->currSize--;
    }
    que->cont[que->currSize++] = element;
}

void cacheUpdate(quePtr que, int element) {
    int idx=-1;
    for (int i = 0; i < que->currSize; i++) {
        if (que->cont[i] == element) { idx = i; break; }
    }
    if (idx==-1) return;
    int tmp = que->cont[idx];
    for (int i = idx+1; i < que->currSize; i++)
        que->cont[i-1] = que->cont[i];
    que->cont[que->currSize-1] = tmp;
}

void printQue(quePtr histQue, quePtr cacheQue) {
    if (histQue->currSize == 0) {
        printf("-\n");
    } else {
        for (int i = 0; i < histQue->currSize; i++) {
            printf("%d", histQue->cont[i]);
            if (i + 1 < histQue->currSize) printf(" ");
        }
        printf("\n");
    }
    if (cacheQue->currSize == 0) {
        printf("-\n");
    } else {
        for (int i = 0; i < cacheQue->currSize; i++) {
            printf("%d", cacheQue->cont[i]);
            if (i + 1 < cacheQue->currSize) printf(" ");
        }
        printf("\n");
    }
}

bool elementInQue(quePtr que, int element) {
    for (int i = 0; i < que->currSize; i++) {
        if (que->cont[i] == element) return true;
    }
    return false;
}

int main() {
    int cacheHit, queSize, pageCnt;
    scanf("%d %d %d", &cacheHit, &queSize, &pageCnt);

    Queue histQ, cacheQ;
    initQue(&histQ, queSize);
    initQue(&cacheQ, queSize);

    startProc(&histQ, &cacheQ, cacheHit, pageCnt);
    printQue(&histQ, &cacheQ);

    free(histQ.cont);
    free(cacheQ.cont);
    return 0;
}
