#include <bits/stdc++.h>
#include <algorithm>

#define MAX 0xffff
typedef long long i64;
#define loz(i, n) for (i64 i = 0; i < static_cast<i64>(n); i++)

using namespace std;

static char src[MAX];
static char pat[MAX];
static i64 go[MAX];

inline void gen()
{
    i64 j = 0, k = -1;
    go[0] = -1;
    while (j < static_cast<i64>(strlen(pat)) - 1) {
        if (k == -1 || pat[j] == pat[k])
            go[++j] = ++k;
        else
            k = go[k];
    }
}

i64 match()
{
    i64 i = 0, j = 0;
    while (i < static_cast<i64>(strlen(src)) && j < static_cast<i64>(strlen(pat))) {
        if (j == -1 || src[i] == pat[j]) {
            i++;
            j++;
        } else
            j = go[j];
    }
    if (j == static_cast<i64>(strlen(pat)))
        return i - j + 1;
    else
        return -1;
}

inline void print_go()
{
    loz(i, strlen(pat)) {
        cout<< go[i]<< endl;
    }
}

inline void run()
{
    freopen("in.txt", "r", stdin);
    scanf("%s", src);
    scanf("%s", pat);
    gen();
    cout<< match()<< endl;
//    print_go();

}

int main()
{
    run();
    return 0;
}
