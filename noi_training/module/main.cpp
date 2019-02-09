#include <iostream>
#include <stdio.h>
#include <stdlib.h>

typedef long long i64;

using namespace std;

i64 base, incre, module;

inline void init()
{
    freopen("in.txt", "r", stdin);
    scanf("%lld%lld%lld", &base, &incre, &module);
}

i64 rmodule(i64 b, i64 t, i64 m)
{
    if (t == 0)
        return 1 % m;
    i64 ans = 1;
    b %= m;
    ans = rmodule(b, t >> 1, m);
    if (t & 1 == 1)
        ans = (ans * ans * b) % m;
    else
        ans = (ans * ans) % m;
    return ans;
}

i64 nrmodule(i64 b, i64 t, i64 m)
{
    if (t == 0)
        return 1 % m;
    i64 ans = 1;
    b %= m;
    while (t > 0) {
        if (t & 1 == 1)
            ans = (ans * b) % m;
        b = (b * b) % m;
        t >>= 1;
    }
    return ans;
}

inline void calc()
{
    printf("%lld\n", nrmodule(base, incre, module));
}

int main()
{
    init();
    calc();
    return 0;
}
