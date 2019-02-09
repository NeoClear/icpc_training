#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DEBUG
#define MAX 500000005
typedef long long i64;

using namespace std;

i64 Q;

inline void init()
{
#ifdef DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin>> Q;
}

i64 num(i64 n)
{
    i64 ans = 0;
    for (int i = 1; i64(n / pow(5.0, (double)i)) > 0; i++) {
        ans += i64(n / pow(5.0, (double)i));
    }
    return ans;
}

inline void calc()
{
    i64 bot = 0, top = MAX, mid;
    while (bot <= top) {
        mid = (bot + top) / 2;
        if (num(mid) >= Q)
            top = mid - 1;
        else
            bot = mid + 1;
    }
    printf("%lld", mid);
}

int main()
{
    init();
    calc();
    return 0;
}
