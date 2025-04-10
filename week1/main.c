#include <stdio.h>
#include <stdlib.h>

int countNum(int * que, int height, int initPos, int , int max);
int elementInQue(int * que, int num, int queLen);

int main()
{
    int balloonNum, babyHeight;
    int maxNum = 0, maxNumQue[1000], queTail;
    int minPos = 100001, maxPos = -100001;
    scanf("%d %d", &balloonNum, &babyHeight);
    int * balloonPosTab = (int *)calloc(balloonNum, sizeof(int));
    for (int tmp, it = 0; it < balloonNum; it ++)
    {
        scanf("%d", &tmp);
        if (tmp < minPos)
        {
            minPos = tmp;
        }
        if (tmp > maxPos)
        {
            maxPos = tmp;
        }
        balloonPosTab[it] = tmp;
    }
int tmpval;
    for (int i = minPos; i < maxPos; i ++)
    {
        tmpval = countNum(balloonPosTab, babyHeight, i, balloonNum, maxPos);
        if (tmpval > maxNum)
        {
            queTail = 0;
            maxNum = tmpval;
            maxNumQue[queTail] = i;
            queTail ++;
        }
    }
    printf("%d %d", maxNumQue[0], maxNum);
}

int countNum(int * que, int height, int initPos, int queLen, int max)
{
    int cnt = 0;
    for (int i = 0; i <= height && i < max - initPos; i ++)
    {
        if (elementInQue(que, initPos + i, queLen))
        {
            cnt ++;
        }
    }
    return cnt;
}

int elementInQue(int * que, int num, int queLen)
{
    int flag = 0;
    for (int i = 0; i < queLen; i ++)
    {
        if (que[i] == num)
        {
            flag = 1;
            return flag;
        }
    }
    return flag;
}