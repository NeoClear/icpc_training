#include <math.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long i64;

using namespace std;

static char ch[50005];
static i64 lm, ln, lt;
static i64 m[50005], n[50005], t[50005];

i64 max(i64 a, i64 b)
{
    if (a > b)
        return a;
    return b;
}

bool judge(i64 k)
{
    memset(t, 0, sizeof(t));
    for (int i = 1; i <= ln; i++)
        t[i] = n[i] * k;
    lt = ln;
    for (int i = 1; i <= lt; i++) {
        if (t[i] >= 10)
            lt = max(i + 1, lt);
        t[i + 1] += t[i] / 10;
        t[i] %= 10;
    }
    if (lt > lm)
        return true;
    if (lt < lm)
        return false;
    for (int i = lt; i >= 1; i--) {
        if (t[i] > m[i])
            return true;
        if (t[i] < m[i])
            return false;
    }
    return true;
}

inline void print()
{
    for (int i = lm; i >= 1; i--)
        cout<< m[i];
    cout<< endl;
    for (int i = lt; i >= 1; i--)
        cout<< t[i];
    cout<< endl;
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

    i64 l = 0, r = 2000000000, mid, ans = 2000000000;
//    cout<< judge(13)<< endl;
//    cout<< lt<< endl;
//    print();

    while (l <= r) {
        mid = (l + r) >> 1;
        if (judge(mid)) {
            if (mid < ans)
                ans = mid;
            r = mid - 1;
        }
        else
            l = mid + 1;
    }
    cout<< ans<< endl;
    return 0;
}
