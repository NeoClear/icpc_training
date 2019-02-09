#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <math.h>

typedef long long i64;

using namespace std;

i64 fuel, incre;

i64 power(i64 base, i64 time)
{
    i64 ans = 1;
    for (i64 i = 0; i < time; i++)
        ans *= base;
    return ans;
}

i64 qpower(i64 base, i64 time)
{
    if (time == 0)
        return 1;
    i64 temp = qpower(base, time / 2);
    if (time % 2 == 1)
        return temp * temp * base;
    else
        return temp * temp;
}

i64 dpower(i64 base, i64 time)
{
    if (time == 0)
        return 1;
    i64 temp = dpower(base, time >> 1);
    if (time & 1 == 1)
        return temp * temp * base;
    else
        return temp * temp;
}

i64 npower(i64 base, i64 time)
{
    if (time == 0)
        return 1;
    i64 ans = 1;
    while (time > 0) {
        if (time & 1 == 1)
            ans *= base;
        time >>= 1;
        base *= base;
    }
    return ans;
}

inline void init()
{
    freopen("in.txt", "r", stdin);
    scanf("%lld%lld", &fuel, &incre);
}

inline void calc()
{
    printf("%lld\n", npower(fuel, incre));
}

int main()
{
    init();
    calc();
    return 0;
}
