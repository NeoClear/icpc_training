#include <bits/stdc++.h>
#include <algorithm>

typedef long long i64;
#define inf 105

using namespace std;

static char ch[inf];
static i64 lm, ln, lt;
static i64 m[inf], n[inf], t[inf];

inline void mul()
{
    int i;
    memset(t, 0, sizeof(t));
    for (i64 i = 1; i <= lm; i++)
        for (int j = 1; j <= ln; j++)
            t[i + j - 1] += m[i] * n[j];
    lt = lm + ln - 1;
    for (i64 i = 1; i <= lt; i++) {
        if (t[i] >= 10)
            lt = max(lt, i + 1);
        t[i + 1] += t[i] / 10;
        t[i] %= 10;
    }
}

inline void print()
{
    for (i64 i = lt; i; i--)
        printf("%lld", t[i]);
    printf("\n");
}

int main()
{
    freopen("in.txt", "r", stdin);
    scanf("%s", ch + 1);
    lm = strlen(ch + 1);
    for (int i = 1; i <= lm; i++)
        m[i] = ch[lm - i + 1] - '0';
    scanf("%s", ch + 1);
    ln = strlen(ch + 1);
    for (int i = 1; i <= ln; i++)
        n[i] = ch[ln - i + 1] - '0';
    mul();
    print();
    return 0;
}
