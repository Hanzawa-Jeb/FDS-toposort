#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct AdjV {
    int Element;
    struct AdjV* Next;
} AdjV;
typedef AdjV* AdjVPtr;

void createGraph(int eCnt, int vCnt, AdjVPtr* AdjList)
{
    int vertex1, vertex2;
    for (int i = 0; i < eCnt; i++) {
        scanf("%d %d", &vertex1, &vertex2);
        // Add edge vertex1 -> vertex2
        AdjVPtr newNode = (AdjVPtr)malloc(sizeof(AdjV));
        newNode->Element = vertex2;
        newNode->Next = AdjList[vertex1]->Next;
        AdjList[vertex1]->Next = newNode;
        
        // Add edge vertex2 -> vertex1
        newNode = (AdjVPtr)malloc(sizeof(AdjV));
        newNode->Element = vertex1;
        newNode->Next = AdjList[vertex2]->Next;
        AdjList[vertex2]->Next = newNode;
    }
}

bool checkConnect(AdjVPtr* AdjList, int vertex1, int vertex2)
{
    AdjVPtr curr = AdjList[vertex1]->Next;
    while (curr) {
        if (curr->Element == vertex2) {
            return true;
        }
        curr = curr->Next;
    }
    return false;
}

bool judgeCycle(int vCnt, AdjVPtr* AdjList)
{
    int seqLen;
    scanf("%d", &seqLen);
    
    // Quick check for length
    if (seqLen != vCnt + 1) {
        // Clear input
        int temp;
        for (int i = 0; i < seqLen; i++) scanf("%d", &temp);
        return false;
    }
    
    static int inputTable[10001];
    static bool visited[10001] = {false};
    
    // Read sequence
    for (int i = 0; i < seqLen; i++) {
        scanf("%d", &inputTable[i]);
    }
    
    // Check first and last vertices
    if (inputTable[0] != inputTable[seqLen-1]) {
        return false;
    }
    
    // Reset visited array
    for (int i = 1; i <= vCnt; i++) {
        visited[i] = false;
    }
    
    // Mark vertices as visited and check path
    visited[inputTable[0]] = true;
    for (int i = 0; i < seqLen - 1; i++) {
        if (!checkConnect(AdjList, inputTable[i], inputTable[i+1])) {
            return false;
        }
        visited[inputTable[i]] = true;
    }
    
    // Check if all vertices are visited
    for (int i = 1; i <= vCnt; i++) {
        if (!visited[i]) {
            return false;
        }
    }
    
    return true;
}

int main()
{
    int vCnt, eCnt;
    scanf("%d %d", &vCnt, &eCnt);
    
    // Initialize adjacency lists
    AdjVPtr* AdjList = (AdjVPtr*)malloc((vCnt + 1) * sizeof(AdjVPtr));
    for (int i = 1; i <= vCnt; i++) {
        AdjList[i] = (AdjVPtr)malloc(sizeof(AdjV));
        AdjList[i]->Next = NULL;
    }
    
    createGraph(eCnt, vCnt, AdjList);
    
    int judgeCnt;
    scanf("%d", &judgeCnt);
    for (int i = 0; i < judgeCnt; i++) {
        printf(judgeCycle(vCnt, AdjList) ? "YES\n" : "NO\n");
    }
    
    // Free memory
    for (int i = 1; i <= vCnt; i++) {
        AdjVPtr curr = AdjList[i];
        while (curr) {
            AdjVPtr temp = curr;
            curr = curr->Next;
            free(temp);
        }
    }
    free(AdjList);
    
    return 0;
}