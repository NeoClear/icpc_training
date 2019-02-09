#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 0xffff
typedef long long i64;
#define loz(i, n) for (int i = 0; i < n; i++)
#define loo(i, n) for (int i = 1; i <= n; i++)

using namespace std;

static char source[MAX];
static char pattern[0xf];
static i64 go[0xf];

namespace core {
    extern i64 ans;
    i64 ans = 0;
    inline void gen_next()
    {
        go[0] = -1;
        i64 j = 0, k = -1;
        while (j < static_cast<i64>(strlen(pattern)) - 1) {
            if (k == -1 || pattern[j] == pattern[k])
                go[++j] = ++k;
            else
                k = go[k];
        }
    }
    i64 match()
    {
        i64 i = 0, j = 0;
        while (i < static_cast<i64>(strlen(source)) && j < static_cast<i64>(strlen(pattern))) {
            if (j == -1 || source[i] == pattern[i]) {
                i++;
                j++;
                printf("i: %lld, j: %lld\n", i, j);
            } else {
                printf("what???");
                j = go[j];
            }
        }
        printf("%lld\n", j);
        if (j == static_cast<i64>(strlen(pattern)))
            return i - j;
        else
            return -1;
    }
}

namespace debug {
    inline void init()
    {
        freopen("in.txt", "r", stdin);
//        freopen("out.txt", "w", stdout);
        scanf("%s", source);
        scanf("%s", pattern);
    }
    inline void print_go()
    {
        loz(i, static_cast<i64>(strlen(pattern))) {
            printf("%lld ", go[i]);
        }
    }
    inline void print_meta()
    {
        printf("%s\n%s", source, pattern);
    }
}

int main()
{
    debug::init();
    core::gen_next();
    printf("2333%lld\n", core::match());
    debug::print_meta();
    debug::print_go();
    return 0;
}
