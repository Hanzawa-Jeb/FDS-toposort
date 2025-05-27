#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int n = 10;
    int a[100];
    
    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        a[i] = rand() % 100 + 1; 
        printf("Random Number generated #%d: %d\n", i+1, a[i]);
    }
    
    sort(a, n);

    printf("\nResults after sorting:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    
    return 0;
}

int sort(int * a, int n)
{
    int temp;
    int j;
    for (int i = 1; i < n; i ++) {
        temp = a[i];
        j = i - 1;
        while (j >= 0 && a[j] > temp) {
            a[j+1] = a[j];
            j --;
        }
        a[j+1] = temp;
    }
    return 0;
}


/*
int sort(int * a, int n) {
    int tmp = 0, j = 0;
    for (int i = 1; i < n; i ++) {
        tmp = a[i];
        j = i - 1;
        while (j >= 0 && a[j] >= tmp) {
            a[j + 1] = a[j];
            j --;
        }
        a[j + 1] = tmp;
    }

    return 0;
}
    */

/*int sort(int * a, int n)
{
    int tempIns;
    for (int i = 1; i < n; i ++) {
        tempIns = a[i];
        for (int j = i - 1; j >= 0; j --) {
            if (tempIns > a[j]) {
                a[j+1] = tempIns;
                break;
            } else {
                a[j+1] = a[j];
            }
        }
    }
    return 0;
}*/

/*int sort(int *a, int n) {
    for (int i = 1; i < n; i++) {
        int temp = a[i]; 
        int j = i - 1;
       
        while (j >= 0 && a[j] > temp) {
            a[j + 1] = a[j];
            j--;
        }
        
        a[j + 1] = temp;
    }
    return 0;
}*/