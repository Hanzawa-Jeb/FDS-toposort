#include <stdio.h>
#include <stdlib.h>

int main() {
    int balloonNum, babyHeight;
    scanf("%d %d", &balloonNum, &babyHeight);

    int *balloonPosTab = (int *)calloc(balloonNum, sizeof(int));
    int minPos = 1000000, maxPos = -1000000;

    for (int i = 0; i < balloonNum; i++) {
        scanf("%d", &balloonPosTab[i]);
        if (balloonPosTab[i] < minPos) {
            minPos = balloonPosTab[i];
        }
        if (balloonPosTab[i] > maxPos) {
            maxPos = balloonPosTab[i];
        }
    }

    int maxCount = 0;
    int bestI = 0;
    int bestJ = 0;
    int i = 0;

    for (int j = 0; j < balloonNum; j++) {
        while (balloonPosTab[j] - balloonPosTab[i] > babyHeight) {
            i++;
        }
        int currentCount = j - i + 1;

        if (currentCount > maxCount) {
            maxCount = currentCount;
            bestI = i;
            bestJ = j;
        } else if (currentCount == maxCount) {
            // 如果当前区间长度相同，选择起始位置较小的
            if (balloonPosTab[i] < balloonPosTab[bestI]) {
                bestI = i;
                bestJ = j;
            }
        }
    }

    double x = (balloonPosTab[bestI] + balloonPosTab[bestJ]) / 2.0;
    printf("%.1lf %d\n", x, maxCount);

    free(balloonPosTab);
    return 0;
}