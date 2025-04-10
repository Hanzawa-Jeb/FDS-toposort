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

int belongsto(int a, int * list, int len)
{
    bool flag = false;
    for (int i = 0; i < len; i ++) 
    {
        if (list[i] == a) {
            flag = true;
            break;
        }
    }
    return flag;
}

bool IsTopSeq( LGraph Graph, Vertex Seq[] )
{
    int v_num = Graph->Nv;
    int e_num = Graph->Ne;
    int temp_head_element;
    int temp_next_element;
    PtrToAdjVNode temp_head;
    PtrToAdjVNode temp_next;
    /*get the number of vertices and edges*/
    AdjList graph = Graph->G;
    int * indegreeCNT = (int *)calloc(v_num, sizeof(int));
    /*count the in-degree's of the node*/
    int ** indegreeSTG = (int **)calloc(v_num, sizeof(int *));
    /*store the specific nodes of in-degree*/
    for (int i = 0; i < v_num; i ++) {
        indegreeSTG[i] = (int *)calloc(v_num, sizeof(int));
    }
    /*initialize the indegree reference tables, indexed from 0*/
    /*next we need to parse*/
    for (int i = 0; i < v_num; i ++)
    {
        temp_head = (graph + i)->FirstEdge;
        temp_next = temp_head->Next;
        temp_head_element = temp_head->AdjV;
        temp_next_element = temp_next->AdjV;
        while (temp_next != NULL)
        {
            indegreeSTG[temp_next_element-1][indegreeCNT[temp_next_element-1]] = temp_next_element;
            indegreeCNT[temp_next_element-1] ++;
            temp_head = temp_next;
            temp_next = temp_head->Next;
            temp_head_element = temp_head->AdjV;
            temp_next_element = temp_next->AdjV;
        }
    }
    /*initialize all the reference tables for in-degree*/
    bool flag = true;
    Vertex curr_element;
    for (int i = 0; i < v_num; i ++)
    /*read the sequence*/
    {
        curr_element = Seq[i];
        if (indegreeCNT[Seq[i]-1] != 0) {
            flag = false;
            break;
        }
        for (int i = 0; i < v_num; i ++)
        {
            if (belongsto(curr_element, indegreeSTG[i], v_num))
            {
                indegreeCNT[i] --;
            }
        }
    }
    return flag;
}
