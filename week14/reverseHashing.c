#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void findSeq(int * hashTable, int n, int recDep, int * printTable, int printTableHead);
void sortSeq(int * seq, int len);
void printSeq(int * printSeq, int seqLen);

int countPositive(int * seq, int len);

int main() {
    int n;
    int posCnt;
    scanf("%d", &n);    //get the number of the input
    int * hashTable = (int *)calloc(n, sizeof(int));
    int * printTable = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < n; i ++) {
        scanf("%d", hashTable + i);
        //get the input from the table
    }
    posCnt = countPositive(hashTable, n);
    findSeq(hashTable, n, 0, printTable, 0);
    printSeq(printTable, posCnt);
    free(hashTable);
    free(printTable);
    return 0;
}

void findSeq(int * hashTable, int n, int recDep, int * printTable, int printTableHead) {
    int expPos; //the expected position
    int * tempSeq = (int *)calloc(n, sizeof(int));
    int seqHead = 0;
    bool flag = false;
    for (int i = 0; i < n; i ++) {
        expPos = hashTable[i] % n;
        if ((i - expPos + n) % n == recDep && hashTable[i] >= 0) {
            tempSeq[seqHead] = hashTable[i];
            seqHead ++;
            flag = true;
            hashTable[i] = -1;
        }
    }
    sortSeq(tempSeq, seqHead);
    for (int i = 0; i < seqHead; i ++) {
        printTable[i + printTableHead] = tempSeq[i];
    }
    if (flag) {
    findSeq(hashTable, n, recDep + 1, printTable, printTableHead + seqHead);
    } else {
        free(tempSeq);
        return;
    }
    free(tempSeq);
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