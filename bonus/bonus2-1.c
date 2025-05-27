/* Author : Huang Yuheng; ID : 3240102750; No.02 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void heapify(int *heap, int size, int i);
void buildMinHeap(int *heap, int size);
int getMin(int *heap, int *size);
void heapInsert(int *heap, int *size, int value);
void replacementSelection(int *input, int totalCnt, int memCap);

int main() {
    int totalCnt, memCap;
    scanf("%d %d", &totalCnt, &memCap);
    int *array = (int*)malloc(totalCnt * sizeof(int));
    for (int i = 0; i < totalCnt; i++) {
        scanf("%d", &array[i]);
    }
    replacementSelection(array, totalCnt, memCap);
    return 0;
}

void heapify(int * heap, int size, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < size && heap[left] < heap[smallest]) smallest = left;
    if (right < size && heap[right] < heap[smallest]) smallest = right;
    if (smallest != i) {
        int tmp = heap[i]; 
        heap[i] = heap[smallest]; 
        heap[smallest] = tmp;
        heapify(heap, size, smallest);
    }
}

void buildMinHeap(int *heap, int size) {
    for (int i = size/2 - 1; i >= 0; i--) {
        heapify(heap, size, i);
    }
}

int getMin(int *heap, int *size) {
    int ret = heap[0];
    heap[0] = heap[*size - 1];
    (*size)--;
    heapify(heap, *size, 0);
    return ret;
}

void heapInsert(int *heap, int *size, int value) {
    int i = (*size)++;
    heap[i] = value;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap[parent] > heap[i]) {
            int tmp = heap[parent]; heap[parent] = heap[i]; heap[i] = tmp;
            i = parent;
        } else break;
    }
}

void replacementSelection(int * input, int totalCnt, int memCap) {
    int * active = (int*)malloc(memCap * sizeof(int));
    int * inactive = (int*)malloc(memCap * sizeof(int));
    int activeSize = 0, inactiveSize = 0;
    int i = 0;
    for (i = 0; i < memCap && i < totalCnt; i++) {
        active[activeSize++] = input[i];
    }
    buildMinHeap(active, activeSize);
    int lastOutput = INT_MIN;
    int firstInRun = 1;

    while (activeSize > 0) {
        int m = getMin(active, &activeSize);
        if (!firstInRun) {
            printf(" ");
        }
        printf("%d", m);
        firstInRun = 0;
        lastOutput = m;
        if (i < totalCnt) {
            int next = input[i++];
            if (next >= lastOutput) {
                heapInsert(active, &activeSize, next);
            } else {
                heapInsert(inactive, &inactiveSize, next);
            }
        }
        if (activeSize == 0) {
            printf("\n");
            int *tmp = active; active = inactive; inactive = tmp;
            activeSize = inactiveSize;
            inactiveSize = 0;
            buildMinHeap(active, activeSize);
            lastOutput = INT_MIN;
            firstInRun = 1;
        }
    }
}