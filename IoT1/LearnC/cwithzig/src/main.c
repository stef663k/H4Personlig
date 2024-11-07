#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846
float radius;
float area;
int i, j;
int *p;


void swap(int *l, int *d) {
    int t;

    t = *l;
    *l = *d;
    *d = t;
}

int main(void) {
    printf("Hello, World!\n");
    radius = 5.0;
    area = PI * pow(radius, 2);
    printf("Area of the circle: %f\n", area);

    p = &i;
    *p = 5;
    j = i;

    int e, s[4], t[4], u=0;

    for (e = 0; e < 4; e++) {
        s[e] = e;
        t[e] = e;
    }
    printf("s:t\n");

    for (e = 0; e < 4; e++) {
        printf("%d:%d\n", s[e], t[e]);
    }
    printf("u: %d\n", u);
    printf("%d %d %d\n", i, j, *p);

    printf("%d %d\n", p, &i);
    p = &i;
    printf("%d %d\n", p, &i);

    int a, b;

    a = 5;
    b = 10;
    printf("a: %d, b: %d\n", a, b);
    swap(&a, &b);
    printf("a: %d, b: %d\n", a, b);

    return 0;
}
