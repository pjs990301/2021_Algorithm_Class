#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
struct TrainTime {
    int time;
    char City[100];
    int index;
}Time[100][100];

struct SectionTime {
    int time;
    char ArrCity[100];
    char DepCity[100];
}STime[100][100];

int minarr[100][2];
int TestCase;
int CityCase;
char CityArr[100][100];
int routeCase;
int DepTimeCase[100];
int time, start, end;

int getIndex(char* str);
void FindMin();

int main() {

    char temp[255];
    scanf("%d", &TestCase);
    for (int i = 0; i < TestCase; i++) {
        scanf("%d", &CityCase);
        for (int i = 0; i < CityCase; i++) {
            scanf("%s", CityArr[i]);
        }

        scanf("%d", &routeCase);
        for (int i = 0; i < routeCase; i++) {
            scanf("%d", &DepTimeCase[i]);
            for (int j = 0; j < DepTimeCase[i]; j++) {
                scanf("%d %s", &Time[i][j].time, Time[i][j].City);
                Time[i][j].index = getIndex(Time[i][j].City);
            }
        }

        scanf("%d", &time);
        scanf("%s", temp);
        start = getIndex(temp);
        scanf("%s", temp);
        end = getIndex(temp);
        FindMin();
    }

}

void FindMin() {
    int temp[100], pos;


    for (int i = 0; i < CityCase; i++) {
        minarr[i][0] = 2400;
        minarr[i][1] = -1;
        temp[i] = 0;
    }
    minarr[start][0] = time;

    for (int i = 0; i < routeCase; i++) {
        pos = -1;
        for (int j = 0; j < routeCase; j++) {
            if (temp[j]) {
                continue;
            }
            if (pos == -1 || minarr[pos][0] > minarr[j][0])
                pos = j;

        }
        if (minarr[pos][0] == 2400) break;
        temp[pos] = -1;

        for (int j = 0; j < routeCase; j++) {
            for (int k = 0; k < DepTimeCase[j] - 1; k++) {
                if (Time[j][k].index == pos && minarr[pos][0] <= Time[j][k].time) {

                    if (minarr[Time[j][k + 1].index][0] > Time[j][k + 1].time)
                        minarr[Time[j][k + 1].index][0] = Time[j][k + 1].time;

                }
            }
        }
    }

    if (temp[end] == 0)
        return;

    for (int i = 0; i < CityCase; i++) {
        temp[i] = 0;
    }

    minarr[end][1] = minarr[end][0];

    for (int i = 0; i < CityCase; i++) {
        pos = -1;
        for (int j = 0; j < CityCase; j++) {
            if (temp[j])
                continue;
            if (pos == -1 || minarr[pos][1] < minarr[j][1])
                pos = j;

        }

        temp[pos] = 1;
        for (int j = 0; j < routeCase; j++) {
            for (int k = 1; k < DepTimeCase[j]; k++) {
                if (Time[j][k].index == pos && minarr[pos][1] >= Time[j][k].time) {
                    if (minarr[Time[j][k - 1].index][1] < Time[j][k - 1].time) {
                        minarr[Time[j][k - 1].index][1] = Time[j][k - 1].time;
                    }
                }
            }
        }

    }


    printf("\n----------------------\n");
    printf("#Departure : %04d %s\n", minarr[start][1], CityArr[start]);
    printf("#Arrival : %4d %s\n", minarr[end][0], CityArr[end]);

}
int getIndex(char* str) {
    for (int i = 0; i < CityCase; i++) {
        if (strcmp(CityArr[i], str) == 0) {
            return i;
        }
    }
    return -1;

}