#include <bits/stdc++.h>
#include <algorithm>

#define inf 0xffff
typedef long long i64;
typedef double f64;
#define nil NULL
#define loz(i, n) for (i64 i = 0; i < static_cast<i64>(n); i++)
#define loo(i, n) for (i64 i = 1; i <= static_cast<i64>(n); i++)

using namespace std;

namespace io {
    i64 read_i64()
    {
        i64 ans = 0, f = 1;
        int ch = getchar();
        while (!isdigit(ch)) {
            if (ch == '-') {
                f = -1;
            }
            ch = getchar();
        }
        while (isdigit(ch)) {
            ans = ans * 10 + ch - '0';
            ch = getchar();
        }
        return ans * f;
    }

    f64 read_f64()
    {
        f64 ans = 0.0;
        f64 divide = 1.0;
        bool flag = false;
        f64 f = 1.0;
        int ch = getchar();
        while (!isdigit(ch)) {
            if (ch == '-')
                f = -1.0;
            ch = getchar();
        }
        while (isdigit(ch) || ch == '.') {
            if (ch == '.') {
                ch = getchar();
                flag = true;
            }
            ans = ans * 10.0 + static_cast<f64>((ch - '0'));
            if (flag)
                divide *= 10.0;
            ch = getchar();
        }
        return ans * f / divide;
    }

}

static i64 N, M, e[0xff][0xff];
static i64 book[inf];
static i64 dis[inf];

int min_book()
{
    int m = 0;
    for (int i = 2; i <= N; i++) {
        if (!book[i]) {
            if (m == 0)
                m = i;
            else if (dis[i] < dis[m]) {
                m = i;
            }
        }
    }
    return m;
}

void dijkstra()
{
    for (int i = 2; i <= N; ++i) {
        int n = min_book();
        book[n] = 1;
        for (int j = 2; j <= N; j++) {
            if (dis[j] > dis[n] + e[n][j])
                dis[j] = dis[n] + e[n][j];
        }
    }
}

void print_tab()
{
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            cout<<e[i][j]<< " ";
        }
        cout<<endl;
    }
}

inline void init()
{
    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    N = io::read_i64();
    M = io::read_i64();
    loo(i, N) {
        loo(j, N) {
            if (i == j)
                e[i][j] = 0;
            else
                e[i][j] = inf;
        }
    }
    i64 p1, p2, w;
    for (int i = 0; i < M; ++i) {
        p1 = io::read_i64();
        p2 = io::read_i64();
        w = io::read_i64();
        e[p1][p2] = w;
    }
    loo(i, N) {
        dis[i] = inf;
    }
    book[1] = 1;
    dis[1] = 0;
    for (int i = 2; i < N; ++i) {
        dis[i] = e[1][i];
    }
}



int main()
{
    init();
    dijkstra();
//    print_tab();
    for (int i = 1; i <= N; ++i) {
        cout<< dis[i]<< " ";
    }
    return 0;
}
