#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>

#define MAX 100001
#define DEBUG

typedef long long i64;

int distance, terran, car;
double ans;

inline void init()
{
    freopen("in.txt", "r", stdin);
    scanf("%d%d%d", &distance, &terran, &car);
}

inline void calc()
{
    double x = ((double)distance * (double)terran * 2.0) / (3.0 * (double)terran + (double)car);
    printf("%.2lf\n", x / (double)terran + ((double)distance - x) / (double)car);
    printf("%.2lf\n", (2.0 * (double)distance - 3.0 * x) / (double)car + ((double)distance - x) / (double)car);
}

int main()
{
    init();
    calc();
    return 0;
}
