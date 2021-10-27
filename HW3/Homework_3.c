#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

int num = 0;

typedef struct text {
    char x[10000];
    char y[100];
}Text;

int subsequenceCount(Text* arr) {


    int sSize = strlen(arr[num].x);
    int tSize = strlen(arr[num].y);

    if (tSize > sSize) return 0;
    int** mat = malloc(sizeof(int) * tSize + 1);
    for (int i = 0; i < tSize + 1; i++) {
        mat[i] = (int*)malloc(sizeof(int) * sSize + 1);
    }

    for (int i = 0; i <= tSize; i++) {
        mat[i][0] = 0;
    }
    for (int j = 0; j <= sSize; j++) {
        mat[0][j] = 1;
    }

    for (int i = 0; i < tSize; i++) {
        for (int j = 0; j < sSize; j++) {
            if (arr[num].y[i] == arr[num].x[j]) {
                mat[i + 1][j + 1] = mat[i][j] + mat[i + 1][j];
            }
            else {
                mat[i + 1][j + 1] = mat[i + 1][j];
            }
        }
    }
    printf("Result : %d\n", mat[tSize][sSize]);
    num++;
}
int main() {

    int n;

    printf("Type the number of test sets : ");
    scanf("%d", &n);

    Text* sentence = malloc(sizeof(sentence) * n);


    for (int i = 0; i < n; i++) {
        printf("Type sequence : ");
        scanf("%s", sentence[i].x);
        printf("Type sub-sequence : ");
        scanf("%s", sentence[i].y);
        subsequenceCount(sentence);
    }
    return 0;

}
