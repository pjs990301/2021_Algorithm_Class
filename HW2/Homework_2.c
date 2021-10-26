#include <stdio.h>

void main() {

	int student_num = -1;
	int student_input[100] = {0,};
	int total_spent = 0;
	int for_each = 0;
	int exchage[100];
	int sum = 0;
	while (1) {
		printf("Type the number of students (End:'0') : ");
		scanf_s("%d", &student_num);

		if (student_num <= 0 || student_num >= 100) {
			break;
		}

		for (int i = 0; i < student_num; i++) {
			printf("%d-th money spent:", i + 1);
			scanf_s("%d", &student_input[i]);
			total_spent += student_input[i];
		}

		for_each = total_spent / student_num;
		for (int i = 0; i < student_num; i++) {
			exchage[i] = student_input[i] - for_each;
		}

		for (int i = 0; i < student_num; i++) {
			if (exchage[i] >= 0) {
				sum = sum + exchage[i];
			}
		}
		printf("The money exchage is %d(Won)\n", sum);
		for (int i = 0; i < 30; i++) {
			student_input[i] = 0;
		}
		printf("\n");
		sum = 0;
		total_spent = 0;
	}
}