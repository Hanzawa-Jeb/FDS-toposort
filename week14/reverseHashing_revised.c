#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int countNonNegative(int *seq, int len);
void printSeq(int *seq, int len);

int main() {
    int n;
    scanf("%d", &n);
    int *hashTable = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &hashTable[i]);
    }

    int total = countNonNegative(hashTable, n);
    int *ans = (int *)malloc(total * sizeof(int));
    int inserted = 0;

    while (inserted < total) {
        int minVal = INT_MAX;
        int minIdx = -1;

        for (int i = 0; i < n; i++) {
            if (hashTable[i] < 0) continue;
            int home = hashTable[i] % n;
            int dep = (i - home + n) % n;
            if (dep == 0 && hashTable[i] < minVal) {
                minVal = hashTable[i];
                minIdx = i;
            }
        }

        if (minIdx != -1) {
            ans[inserted++] = minVal;
            hashTable[minIdx] = -1;  // mark as deleted
        } else {
            // this should not happen in valid input
            break;
        }

        // after removing, update probe distances naturally by loop
        for (int i = 0; i < n; i++) {
            if (hashTable[i] < 0) continue;
            int home = hashTable[i] % n;
            int dep = (i - home + n) % n;
            // nothing to do in update loop, just keep it for logic clarity
        }
    }

    printSeq(ans, total);

    free(hashTable);
    free(ans);
    return 0;
}

int countNonNegative(int *seq, int len) {
    int cnt = 0;
    for (int i = 0; i < len; i++) {
        if (seq[i] >= 0)
            cnt++;
    }
    return cnt;
}

void printSeq(int *seq, int len) {
    for (int i = 0; i < len; i++) {
        if (i > 0) printf(" ");
        printf("%d", seq[i]);
    }
}
