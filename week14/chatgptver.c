#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF  65535

void readTable(int * a, int n);
int countNotNegative(int * a, int n);
void buildGraph(int * a, int n, int * indegree, int ** adj, int * adjCnt);
void topoSort(int * a, int n, int total, int * indegree, int ** adj, int * adjCnt, int * result);
void printSeq(int * seq, int len);

int main() {
    int n;
    scanf("%d", &n);
    int * array = (int *)calloc(n, sizeof(int));
    readTable(array, n);
    int total = countNotNegative(array, n);
    int ** adj = (int **)calloc(n, sizeof(int *));
    for (int i = 0; i < n; i ++) {
        adj[i] = (int *)calloc(n, sizeof(int));
    }
    int * adjCnt = (int *)calloc(n, sizeof(int));
    int * indegree = (int *)calloc(n, sizeof(int));
    buildGraph(array, n, indegree, adj, adjCnt);
    int * result = (int *)calloc(n, sizeof(int));
    topoSort(array, n, total, indegree, adj, adjCnt, result);
    printSeq(result, total);
    free(array);
    free(adj);
    free(adjCnt);
    free(indegree);
    free(result);
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

// build the graph
void buildGraph(int * a, int n, int * indegree, int ** adj, int * adjCnt) {
    for (int i = 0; i < n; i++) {
        if (a[i] < 0) {
            indegree[i] = -1;
            continue;
        }
        int home = a[i] % n;
        int dist = (i - home + n) % n;
        indegree[i] = dist;
        //set the in_degree
        //calculate the distance between the expected position and the actual position
        for (int k = 0; k < dist; k++) {
            int u = (home + k) % n;
            //calculate the nodes that have passed
            adj[u][adjCnt[u]++] = i;
            //set their successor
        }
    }
}

// topologically sort the sequence
void topoSort(int * a, int n, int total, int * indegree, int ** adj, int * adjCnt, int * result) {
    int * visited = (int *)calloc(n, sizeof(int));
    int idx = 0;

    for (int t = 0; t < total; t++) {
        int minVal = INF;
        int minIdx = -1;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && indegree[i] == 0) {
                if (a[i] < minVal) {
                    minVal = a[i];
                    minIdx = i;
                    //get the element with in_degree = 1 with the minimum value
                }
            }
        }

        visited[minIdx] = 1;
        result[idx++] = a[minIdx];

        for (int j = 0; j < adjCnt[minIdx]; j++) {
            int v = adj[minIdx][j];
            //delete all the in-degrees of the current deletion node
            indegree[v]--;
        }
    }
    free(visited);
}

//print the sequence with designated length
void printSeq(int * seq, int len) {
    for (int i = 0; i < len; i++) {
        if (i > 0) {
            printf(" ");
        }
        printf("%d", seq[i]);
    }
}