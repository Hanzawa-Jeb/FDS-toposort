#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 1000
#define INF  65535

void readTable(int * a, int n);
int countNotNegative(int * a, int n);
void buildGraph(int * a, int n, int * indegree, int ** adj, int * adjCnt);
void extSeq(int * a, int n, int total, int * indegree, int ** adj, int * adjCnt, int * result);
void printSeq(int * seq, int len);

int main() {
    int n;
    scanf("%d", &n);
    int * array = (int *)calloc(n, sizeof(int));
    readTable(array, n);
    int total = countNotNegative(array, n);
    static int adj[MAXN][MAXN];
    int adjCnt[MAXN] = {0};
    int indegree[MAXN];
    buildGraph(array, n, indegree, adj, adjCnt);
    int result[MAXN];
    extSeq(array, n, total, indegree, adj, adjCnt, result);
    printSeq(result, total);
    free(array);
    return 0;
}

//read the table from the user input
void readTable(int * a, int n) {
    for (int i = 0; i < n; i++) {
        scanf("%d", a + i);
    }
}

//count how many non-negative elements there are
int countNotNegative(int * a, int n) {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] >= 0) cnt++;
    }
    return cnt;
}

// build indegree[] and adjacency lists adj from final table a[]
void buildGraph(int * a, int n, int * indegree, int ** adj, int * adjCnt) {
    for (int i = 0; i < n; i++) {
        if (a[i] < 0) {
            indegree[i] = -1;
            continue;
        }
        int home = a[i] % n;
        int dist = (i - home + n) % n;
        indegree[i] = dist;
        for (int k = 0; k < dist; k++) {
            int u = (home + k) % n;
            adj[u][adjCnt[u]++] = i;
        }
    }
}

// perform the topological extraction: pick indegree=0 & smallest value each time
void extSeq(int * a, int n, int total, int * indegree, int ** adj, int * adjCnt, int * result) {
    int visited[MAXN] = {0};
    int idx = 0;

    for (int t = 0; t < total; t++) {
        int minVal = INF;
        int minIdx = -1;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && indegree[i] == 0) {
                if (a[i] < minVal) {
                    minVal = a[i];
                    minIdx = i;
                }
            }
        }

        visited[minIdx] = 1;
        result[idx++] = a[minIdx];

        for (int j = 0; j < adjCnt[minIdx]; j++) {
            int v = adj[minIdx][j];
            indegree[v]--;
        }
    }
}

// print the reconstructed sequence with spaces, no trailing space
void printSeq(int * seq, int len) {
    for (int i = 0; i < len; i++) {
        if (i > 0) {
            printf(" ");
        }
        printf("%d", seq[i]);
    }
}