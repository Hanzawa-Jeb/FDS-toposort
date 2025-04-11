#include <stdio.h>
#include <stdlib.h>

typedef enum {false, true} bool;
#define MaxVertexNum 10  /* maximum number of vertices */
typedef int Vertex;      /* vertices are numbered from 1 to MaxVertexNum , indexed from 0 in the LGraph*/

typedef struct AdjVNode *PtrToAdjVNode; 
struct AdjVNode{
    Vertex AdjV;
    PtrToAdjVNode Next;
};

typedef struct Vnode{
    PtrToAdjVNode FirstEdge;
} AdjList[MaxVertexNum];

typedef struct GNode *PtrToGNode;
struct GNode{  
    int Nv;
    int Ne;
    AdjList G;
};
typedef PtrToGNode LGraph;

LGraph ReadG(); /* details omitted */

bool IsTopSeq( LGraph Graph, Vertex Seq[] );

int main()
{
    int i, j, N;
    Vertex Seq[MaxVertexNum];
    LGraph G = ReadG();
    scanf("%d", &N);
    for (i=0; i<N; i++) {
        for (j=0; j<G->Nv; j++)
            scanf("%d", &Seq[j]);
        if ( IsTopSeq(G, Seq)==true ) printf("yes\n");
        else printf("no\n");
    }
    return 0;
}

bool IsTopSeq(LGraph Graph, Vertex Seq[])
{
    int v_num = Graph->Nv;
    int *indegreeCNT = (int *)calloc(v_num, sizeof(int));

    for (int i = 0; i < v_num; i++) {
        PtrToAdjVNode current = Graph->G[i].FirstEdge;
        while (current != NULL) {
            indegreeCNT[current->AdjV]++;
            current = current->Next;
        }
    }
    
    bool flag = true;
    for (int i = 0; i < v_num; i++) {
        Vertex curr = Seq[i] - 1;
        if (indegreeCNT[curr] != 0) 
        {
            flag = false;
            break;
        }
        PtrToAdjVNode temp_ptr = Graph->G[curr].FirstEdge;
        while (temp_ptr != NULL) {
            indegreeCNT[temp_ptr->AdjV]--;
            temp_ptr = temp_ptr->Next;
        }
    }
    free(indegreeCNT);
    return flag;
}