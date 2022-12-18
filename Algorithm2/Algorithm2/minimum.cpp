#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int n, i, j;
int d[999][2];
int M[999][999];
int P[999][999];
int minmult(int n);
void order(int i, int j);

int min(int x, int y) {
    return x < y ? x : y;
}

int minmult(int n) {
    int a, b;
    int i, j, k;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n - i; j++) {
            a = j;
            b = j + i;
            if (a == b) {
                M[a][b] = 0;
                P[a][b] = 0;
            }
            else {
                M[a][b] = 999999;
                for (k = a; k < b; k++) {
                    int kVal = min(M[a][b], M[a][k] + M[k + 1][b] + (d[a][0] * d[k][1] * d[b][1]));
                    if (M[a][b] > kVal) {
                        M[a][b] = kVal;
                        P[a][b] = k+1;
                    }
                }
            }
        }
    }
    return M[0][n - 1];
}

void  order(int i, int j) {
    if (i == j)
        printf("A%d", i);
    else if (i < j) {
        int k = int(P[i][j]);
        printf("(");
        order(i, k);
        order(k + 1, j);
        printf(")");
    }
    else
        return;
}

int main(void) {
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d %d", &d[i][0], &d[i][1]);
    }
    int answer = minmult(n);
    printf("\n");
    printf("--- M[i][j] ---");
    printf("\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", (M[i][j]));
        }
        printf("\n");
    }
    printf("--- P[i][j] ---");
    printf("\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", (P[i][j]));
        }
        printf("\n");
    }
    printf("\n최소연산 횟수 : %d\n\n", answer);
    order(1, n - 1);
}