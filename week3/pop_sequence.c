#include <stdio.h>
#include <stdlib.h>

int checkValid(int M, int N, int * seq);

int main()
{
    int M, N, K;
    scanf("%d %d %d", &M, &N, &K);
    int * tmpSeq = (int *)calloc(N, sizeof(int));
    for (int i = 0; i < K; i ++)
    {
        for (int j = 0; j < N; j ++)
        {
            scanf("%d", tmpSeq + j);
        }
        if (checkValid(M, N, tmpSeq))
        {
            printf("YES\n");
        }
        else
        {
            printf("NO\n");
        }
    }
}

int checkValid(int M, int N, int * seq)
{
    int * stack = (int *)calloc(N, sizeof(int));
    stack[0] = 1;
    int stackTop = 0;
    int seqIndex = 0;
    int stackTmpElement = 1;
    while (seqIndex != N)
    {
        while (stack[stackTop] != seq[seqIndex])
        {
            if (stackTop == M)
            {
                return 0;
            }
            else 
            {
                stackTop ++;
                stackTmpElement ++;
                stack[stackTop] = stackTmpElement;
            }
        }
        if (stackTop == M)
        {
            return 0;
        }
        stackTop --;
        seqIndex ++;
    }
    return 1;
}