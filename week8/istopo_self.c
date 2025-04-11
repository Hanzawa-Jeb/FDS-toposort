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
    //Nv is the count for vertices
    int * indegreeCNT = (int *)calloc(v_num, sizeof(int));
    //calloc space for the indegree count
    PtrToAdjVNode temp_node;
    for (int i = 0; i < v_num; i ++) 
    {
        temp_node = Graph->G[i].FirstEdge;
        while (temp_node != NULL)
        {
            indegreeCNT[temp_node->AdjV] ++;
            //adjv starts from 0 also
            temp_node = temp_node -> Next;
            //mark the in-degree's in respective to the root
        }
    }

    for (int i = 0; i < v_num; i ++)
    {
        if (indegreeCNT[Seq[i] - 1] != 0)
        {
            return false;
        }

        temp_node = Graph->G[Seq[i] - 1].FirstEdge;
        while (temp_node != NULL)
        {
            indegreeCNT[temp_node->AdjV] --;
            //starts from 0!!!
            temp_node = temp_node -> Next;
            //subtract if the root is past
        }
    }
    free(indegreeCNT);
    return true;
}