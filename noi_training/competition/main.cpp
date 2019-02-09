#include <iostream>
#include <stdio.h>
#include <stdlib.h>

typedef long long i64;

using namespace std;

int expo;

int power(int base, int time)
{
    int ans = 1;
    for (int i = 0; i < time; i++)
        ans *= base;
    return ans;
}

int next(int giv, int max)
{
    if (giv >= max)
        return 1;
    return giv + 1;
}

int main()
{
    freopen("in.txt", "r", stdin);
    scanf("%d", &expo);
    int player = power(2, expo);
    for (int i = 1;i <= player; i++) {
        int start = i;
        for (int j = 0; j < player; j++) {
            if (j == player - 1)
                printf("%d\n", start);
            else {
                printf("%d   ", start);
                start = next(start, player);
            }
        }
    }
    return 0;
}
