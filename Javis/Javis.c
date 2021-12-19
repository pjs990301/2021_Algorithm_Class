#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <limits.h>

#define NUM_INPUT 8
 
struct point {
    double x, y;
};

int orientation(struct point p, struct point q, struct point r)
{
    double val = (q.y - p.y) * (r.x - q.x) -
                 (q.x - p.x) * (r.y - q.y);

    if (val == 0.0) return 0;  // collinear
    return (val > 0.0) ? 1 : 2; // clock or counterclock wise
}

// Prints convex hull of a set of n points.
void convexHull(int n, int* m, struct point* points)
{
    // There must be at least 3 points
    if (n < 3) return;

    // Initialize Result
    struct point hull[NUM_INPUT];

    // Find the leftmost point
    int l = 0;
    for (int i = 1; i < n; i++)
        if (points[i].x < points[l].x)
            l = i;

    // Start from leftmost point, keep moving counterclockwise until reach the start point again
    int p = l, q;
    int count = 0;
    do
    {
        hull[count] = points[p];

        // Search for a point 'q' such that orientation(p, q, x) is counterclockwise for all points 'x'.
        q = (p + 1) % n;
        for (int i = 0; i < n; i++)
        {
            // If i is more counterclockwise than current q, then update q
            if (orientation(points[p], points[i], points[q]) == 2)
                q = i;
        }

        // Now q is the most counterclockwise with respect to p
        // Set p as q for next iteration, so that q is added to
        // result 'hull'
        p = q;
        count++;

    } while (p != l);  // While we don't come to first point

    for (int i = 0; i < count; i++) {
        points[i] = hull[i];
    }
    *m = count;
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
    convexHull(NUM_INPUT, &num_convex, p);

    printf("The input points consisting convex hull(javis)===========\n");
    for (int i = 0; i < num_convex; i++) {
        printf("(%.1f, %.1f) ", p[i].x, p[i].y);
    }
    printf("\n");

}
