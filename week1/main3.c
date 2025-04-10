#include <stdio.h>
#include <stdlib.h>

int balloonCount(int startIndex, int babyHeight, int balloonNum, int * balloonList);

int main()
{
    int balloonNum, babyHeight;
    int maxCount = 1, maxPosition = 0;
    int tailBias;
    scanf("%d %d", &balloonNum, &babyHeight);
    int * balloonList = (int *)calloc(balloonNum, sizeof(int));
    for (int i = 0; i < balloonNum; i ++)
    {
        scanf("%d", balloonList + i);
    }
    /*if (balloonNum == 1)
    {
        printf("%d %d", balloonList[0] - babyHeight, 1);
        return 0;
    }*/
    for (int i = 0; i < balloonNum; i ++)
    {
        if (balloonCount(i, babyHeight, balloonNum, balloonList) > maxCount)
        {
            maxCount = balloonCount(i, babyHeight, balloonNum, balloonList);
            maxPosition = i;
        }
    }
    tailBias = balloonList[maxPosition + maxCount - 1] - balloonList[maxPosition] - babyHeight;
    printf("%d %d", balloonList[maxPosition] + tailBias, maxCount);
    free(balloonList);
    return 0;
}

int balloonCount(int startIndex, int babyHeight, int balloonNum, int * balloonList)
{
    int popCount = 0;
    for (int i = startIndex; i < balloonNum; i ++)
    {
        if (balloonList[i] <= balloonList[startIndex] + babyHeight)
        {
            popCount ++;
        }
        else{
            return popCount;
        }
    }
    return popCount;
}