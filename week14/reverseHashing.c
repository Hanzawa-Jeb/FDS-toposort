#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void findSeq(int * hashTable, int n, int * printTable);
void sortSeq(int * seq, int len);
void printSeq(int * printSeq, int seqLen);

int countPositive(int * seq, int len);

int main() {
    int n;
    scanf("%d", &n);
    int * hashTable = (int *)calloc(n, sizeof(int));
    int * printTable = (int *)calloc(n, sizeof(int));
    
    for (int i = 0; i < n; i++) {
        scanf("%d", hashTable + i);
    }
    
    int posCnt = countPositive(hashTable, n);
    findSeq(hashTable, n, printTable);
    printSeq(printTable, posCnt); 
    
    free(hashTable);
    free(printTable);
    return 0;
}

void findSeq(int * hashTable, int n, int * printTable) {
    bool * visited = (bool *)calloc(n, sizeof(bool));
    int * restList = (int *)calloc(n, sizeof(int));
    int restCount = 0;
    int printCount = 0;
    
    // First find numbers that are in their ideal position
    for (int i = 0; i < n; i++) {
        if (hashTable[i] >= 0) {
            if (hashTable[i] % n == i) {
                printTable[printCount++] = hashTable[i];
                visited[i] = true;
            } else {
                restList[restCount++] = hashTable[i];
            }
        }
    }
    
    // Process remaining numbers
    while (printCount > 0) {
        // Sort current output batch
        sortSeq(printTable, printCount);
        
        // Get smallest number and mark its path
        int current = printTable[0];
        int startPos = current % n;
        
        // Mark path as visited
        for (int i = startPos; i != hashTable[current]; i = (i + 1) % n) {
            visited[i] = true;
        }
        
        // Find next available numbers
        for (int i = 0; i < restCount; i++) {
            if (restList[i] != -1) {
                int pos = restList[i] % n;
                bool canAdd = true;
                
                // Check if path to final position is blocked
                for (int j = pos; j != hashTable[restList[i]]; j = (j + 1) % n) {
                    if (!visited[j]) {
                        canAdd = false;
                        break;
                    }
                }
                
                if (canAdd) {
                    printTable[printCount++] = restList[i];
                    restList[i] = -1;
                }
            }
        }
        
        // Remove processed number
        for (int i = 0; i < printCount - 1; i++) {
            printTable[i] = printTable[i + 1];
        }
        printCount--;
    }
    
    free(visited);
    free(restList);
}

void sortSeq(int *seq, int len) {
    for (int i = 1; i < len; i++) {
        int current = seq[i];
        int j = i;
        while (j > 0 && seq[j-1] > current) {
            seq[j] = seq[j-1];
            j --;
        }
        seq[j] = current;
    }
}

void printSeq(int * printSeq, int seqLen) {
    for (int i = 0; i < seqLen; i ++) {
        printf("%d", printSeq[i]);
        if (i != seqLen - 1) {
            printf(" ");
        }
    }
}

int countPositive(int * seq, int len) {
    int cnt = 0;
    for (int i = 0; i < len; i ++) {
        if (seq[i] >= 0) {
            cnt ++;
        }
    }
    return cnt;
}