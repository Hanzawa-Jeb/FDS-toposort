/* Author : Huang Yuheng;  ID : 3240102750;  No.01*/ 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int maxSize;
    int front;
    int rear;
    int currSize;
    int* cont;
} Queue;
typedef Queue* quePtr;

void initQueue(quePtr q, int size) {
    q->cont = (int*)malloc(size * sizeof(int));
    q->maxSize = size;
    q->front = q->rear = 0;
    q->currSize = 0;
}

void enqueue(quePtr q, int val) {
    if (q->currSize < q->maxSize) {
        q->cont[q->rear] = val;
        q->rear = (q->rear + 1) % q->maxSize;
        q->currSize++;
    }
}

int dequeue(quePtr q) {
    if (q->currSize > 0) {
        int val = q->cont[q->front];
        q->front = (q->front + 1) % q->maxSize;
        q->currSize--;
        return val;
    }
    return -1;
}

int main() {
    int k, n, m;
    scanf("%d %d %d", &k, &n, &m);
    
    // Initialize queue and counters
    Queue histQueue;
    initQueue(&histQueue, n);
    int* count = (int*)calloc(20001, sizeof(int));
    int* result = (int*)malloc(m * sizeof(int));
    int resultSize = 0;
    
    for (int i = 0; i < m; i++) {
        int x;
        scanf("%d", &x);
        
        // Update count and queue
        if (histQueue.currSize < n) {
            if (count[x] == 0) {
                enqueue(&histQueue, x);
            }
        } else {
            if (count[x] == 0) {
                while (count[histQueue.cont[histQueue.front]] != 1) {
                    count[histQueue.cont[histQueue.front]]--;
                    dequeue(&histQueue);
                }
                count[histQueue.cont[histQueue.front]]--;
                result[resultSize++] = dequeue(&histQueue);
                enqueue(&histQueue, x);
            }
        }
        count[x]++;
    }
    
    // Print result
    if (resultSize > 0) {
        printf("%d", result[0]);
        for (int i = 1; i < resultSize; i++) {
            printf(" %d", result[i]);
        }
    }
    
    // Free memory
    free(histQueue.cont);
    free(count);
    free(result);
    
    return 0;
}