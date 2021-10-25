#include <stdio.h>

int findMaxPos(int arr[], int input);
void Pancake(int arr[], int input);
void flip(int arr[], int input);

void main() {

	int input;
	int arr[30] = { 0, };

	while (1) {
		printf("Enter input size : ");
		scanf_s("%d", &input);

		printf("Enter input value : ");
		for (int i = 0; i < input; i++) {
			scanf_s("%d", &arr[i]);
		}

		printf("\n");
		Pancake(arr, input);
		printf("\n");

		for (int i = 0; i < input; i++) {
			printf("%d ", arr[i]);

		}
		printf("\n\n");
	}
}

int findMaxPos(int arr[], int input) {

	int arrMax_Pos = 0;

	for (int i = 0; i < input; i++) {
		if (arr[i] >= arr[arrMax_Pos])
			arrMax_Pos = i;
	}
	return arrMax_Pos;
}
void Pancake(int arr[], int input) {

	int resultFlip[30] = { 0, };
	int flipPos = 0;
	for (int i = input; i > 1; --i) {
		int maxFlag = findMaxPos(arr, i);

		if (maxFlag != i - 1) {
			if (maxFlag == 0) {
				flip(arr, i - 1);
				resultFlip[flipPos] = input - (i - 1);
				flipPos++;
			}
			else {
				flip(arr, maxFlag);
				resultFlip[flipPos] = input - maxFlag;
				flipPos++;
				flip(arr, i - 1);
				resultFlip[flipPos] = input - (i - 1);
				flipPos++;
			}
		}
	}

	printf("Result : ");
	for (int i = 0; i < flipPos + 1; ++i) {
		printf("flip(%d)  ", resultFlip[i]);
	}
}

void flip(int arr[], int input) {

	int temp = 0;
	for (int i = 0; i < input; i++) {
		temp = arr[i];
		arr[i] = arr[input];
		arr[input] = temp;
		input--;
	}

}