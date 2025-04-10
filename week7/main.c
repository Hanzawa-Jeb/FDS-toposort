#include <stdio.h>
#include <stdlib.h>

void init_refTable(int * tab, int num);
void Union(int * tab, int num, int c1, int c2);
int Find(int * tab, int num, int element);
void Check(int * tab, int num, int c1, int c2);
void finalCheck(int * tab, int num);

int main()
{
    int num, op1, op2;
    /*repectively the number of computers, the indices of the first computer and the second computer*/
    char opType;
    /*the type of operation, SCI*/
    scanf("%d\n", &num);
    int * refTable = (int *)calloc(num + 1, sizeof(int));
    init_refTable(refTable, num);
    /*initialize the reference table*/
    scanf("%c", &opType);
    while (opType != 'S') {
        scanf("%d %d\n", &op1, &op2);
        /*get the input of op1 and op2 if the operator is not S*/
        if (opType == 'I') {
            /*union the relation*/
            Union(refTable, num, op1, op2);
        }
        else if (opType == 'C') {
            /*check whether the relation exists*/
            Check(refTable, num, op1, op2);
        }
        scanf("%c", &opType);
    }
    finalCheck(refTable, num);
    /*when encountered with operator S, finish the entire process*/
    return 0;
}

void init_refTable(int* tab, int num) {
    /*initialize the reference table, with every value set to -1 representing the size.*/
    for (int i = 1; i < num + 1; i ++) {
    /*note that we store from index 1*/
        tab[i] = -1;
    }
}

void Union(int * tab, int num, int c1, int c2) {
    /*used to union the two sets*/
    int root1 = Find(tab, num, c1), root2 = Find(tab, num, c2);
    int size1 = -tab[root1], size2 = -tab[root2];
    if (size1 > size2) {
        /*root2 will be under root1*/
        tab[root1] = tab[root1] + tab[root2];
        /*reset the size of root1*/
        tab[root2] = root1;
        /*reset the parent node of root2*/
    } else {
        /*root 1 will be under root2*/
        tab[root2] = tab[root1] + tab[root2];
        /*reset the size of root2*/
        tab[root1] = root2;
        /*reset the root of root1*/
    }
}

int Find(int * tab, int num, int element) {
    /*find the root of the element*/
    int root;
    if (tab[element] > 0) {
        return tab[element] = Find(tab, num, tab[element]);
    } else {
        return element;
    }
}

void Check(int * tab, int num, int c1, int c2) {
    /*determine whether the connection exists*/
    if (Find(tab, num, c1) == Find(tab, num, c2)) {
        printf("yes\n");
    } else {
        printf("no\n");
    }
}

void finalCheck(int * tab, int num) {
    /*it is used to check whether the entire network is connected*/
    int negCnt = 0;
    for (int i = 1; i < num + 1; i ++) {
        if (tab[i] < 0) {
            negCnt ++;
        }
    }
    if (negCnt == 1) {
        printf("The network is connected.");
    }
    else {
        printf("There are %d components.", negCnt);
    }
}