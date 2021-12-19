#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <limits.h>

#define NUM_INPUT 8

// data structure for point
struct point {
    double x, y;
};

// data structure for line
struct segment {
    struct point e1, e2;
};

// to check location
double compare(struct point p1, struct point p2) {
    double comp;
    comp = p1.y - p2.y;
    if (comp == 0.0) comp = p1.x - p2.x;

    return comp;
}

double WhichSide(struct point p, struct segment s) {
    double a, b;
    a = (p.x - s.e1.x) * (s.e2.y - s.e1.y);
    b = (p.y - s.e1.y) * (s.e2.x - s.e1.x);

    return a - b;
}

int comp(double dx1, double dy1, double dx2, double dy2) {
    double angle1, angle2;
    angle1 = atan2(dy1, dx1);
    angle2 = atan2(dy2, dx2);

    if (angle1 < angle2) return -1;
    if (angle1 > angle2) return 1;

    return 0;
}

// sorting based on the angle between 0-th point and the indext point
void sort(struct point* p, int n) {
    struct point temp;
    int i, j;

    for (i = 1; i < n; i++) {
        for (j = 1; j < n - 1; j++) {
            if (comp(p[j].x - p[0].x, p[j].y - p[0].y, p[j + 1].x - p[0].x, p[j + 1].y - p[0].y) > 0) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%.lf %.lf\n", (p[i]).x, (p[i]).y);
    }
}

void graham_scan(int n, int* m, struct point* p) {
    int i, min;
    struct point q;
    struct segment line;

    // to find the min location in the map
    min = 0;
    for (i = 0; i < n; i++) {
        if (compare(p[i], p[min]) < 0)
            min = i;
    }

    // to exchange the min point with the 0 index point
    q = p[0];
    p[0] = p[min];
    p[min] = q;

    // sorting the stored points in p array
    sort(p, n);

    *m = 1;
    for (i = 2; i < n; i++) {
        line.e2 = p[i];
        while (*m > 0) {
            line.e1 = p[*m - 1];
            if (WhichSide(p[*m], line) <= 0)
                (*m)--;
            else
                break;
        }
        (*m)++;
        q = p[*m];
        p[*m] = p[i];
        p[i] = q;
    }
}

void main(void) {
    // Init the points to be tested
    int num_convex = 0;
    struct point p[NUM_INPUT] = { {1, -1}, {2, 1}, {1, 1}, {0, 3}, {-1, 1}, {-2, 0}, {-1, -1}, {-2, -2} };

    // print the convent hull points
    printf("All the input points===========\n");
    for (int i = 0; i < NUM_INPUT; i++) {
        printf("(%.1f, %.1f) ", p[i].x, p[i].y);
    }
    printf("\n");

    // get convext hull points
    graham_scan(NUM_INPUT, &num_convex, p);

    printf("The input points consisting convex hull(graham)===========\n");
    for (int i = 0; i <= num_convex; i++) {
        printf("(%.1f, %.1f) ", p[i].x, p[i].y);
    }
    printf("\n");

}