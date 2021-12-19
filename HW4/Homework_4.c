#define _CRT_SECURE_NO_WARININGS

#include <stdio.h>
#include <stdlib.h>

void Find_minCost_Cal(int**** input, int*** cost, int row, int col, int min);
void Find_minCost_Table(int*** input, int row, int col);

int main() {
	int row, col;
	int num;
	int** arr = NULL;
	printf("Enter test case : ");
	scanf("%d", &num);
	for (int i = 0; i < num; i++) {
		printf("Enter col and row : ");
		scanf("%d %d", &col, &row);

		arr = (int**)malloc(sizeof(int*) * row);
		for (int i = 0; i < row; i++) {
			arr[i] = (int*)malloc(sizeof(int) * col);
		}
		for (int i = 0; i < col; i++) {
			for (int j = 0; j < row; j++) {
				scanf("%d", &arr[i][j]);
			}
		}

		Find_minCost_Table(&arr, row, col);
		free(arr);
	}

}

void Find_minCost_Table(int*** input, int row, int col) {

	int min = 0;
	int** cost = malloc(sizeof(int*) * (row + 1));
	for (int i = 0; i < row + 1; i++) {
		cost[i] = malloc(sizeof(int) * (col + 1));
	}
	for (int i = 0; i < col; i++) {
		cost[i][0] = (*input)[i][0];
	}
	for (int j = 1; j < row; j++) {
		for (int i = 0; i < col; i++) {
			min = cost[(i - 1 + col) % col][j - 1];
			if (cost[i][j - 1] < min)
				min = cost[i][j - 1];
			if (cost[(i + 1) % col][j - 1] < min)
				min = cost[(i + 1) % col][j - 1];
			cost[i][j] = (*input)[i][j] + min;
		}
	}

	Find_minCost_Cal(&input, &cost, row, col, min);
	free(cost);


}
void Find_minCost_Cal(int**** input, int*** cost, int row, int col, int min) {

	int flag, result = 0;
	int* path = (int*)malloc(sizeof(int) * 10);
	int* pathRe = (int*)malloc(sizeof(int) * 10);
	min = (*cost)[0][row - 1];
	path[row - 1] = (**input)[0][row - 1];
	flag = 0;
	for (int i = 1; i < col; i++) {
		if ((*cost)[i][row - 1] < min) {
			min = (*cost)[i][row - 1];
			path[row - 1] = (**input)[i][row - 1];
			flag = i;
		}
	}
	pathRe[row] = flag;
	result = min;

	for (int j = row - 1; j >= 0; j--) {
		int i = flag;
		min = (*cost)[i][j];
		path[j] = (**input)[i][j];
		pathRe[j] = flag;

		if ((*cost)[(i - 1 + col) % col][j] < min) {
			min = (*cost)[(i - 1 + col) % col][j];
			path[j] = (**input)[(i - 1 + col) % col][j];
			flag = (i - 1 + col) % col;
			pathRe[j] = flag;

		}
		if ((*cost)[(i + 1) % col][j] < min) {
			min = (*cost)[(i + 1) % col][j];
			path[j] = (**input)[(i + 1) % col][j];
			flag = (i + 1) % col;
			pathRe[j] = flag;
		}
	}
	printf("\npath\n");
	for (int i = 0; i < row; i++) {
		printf("[%d] ", path[i]);
	}

	printf("\noutput\n");
	for (int i = 0; i < row; i++) {
		printf("[%d] ", pathRe[i]+1);
	}
	printf("\n%d\n", result);
	free(path);
}

