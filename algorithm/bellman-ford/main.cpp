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

struct line
{
    i64 p;
    i64 v;
    struct line *next;
};

static i64 N, M;
static struct line *lines[inf];
static i64 dis[inf];

void insert(i64 p1, i64 p2, i64 v)
{
    struct line *q = static_cast<struct line *>(malloc(sizeof(line)));
    q->p = p2;
    q->v = v;
    q->next = nil;
    struct line *p = lines[p1];
    if (p == nil)
        lines[p1] = q;
    else {
        while (p->next != nil)
            p = p->next;
        p->next = q;
    }
}

inline void init()
{
    freopen("in.txt", "r", stdin);
    N = io::read_i64();
    M = io::read_i64();
    i64 p1, p2, v;
    loo(i, N) {
//        cout<<"sa"<<endl;
        dis[i] = inf;
        lines[i] = nil;
    }
    loz(i, M) {
        p1 = io::read_i64();
        p2 = io::read_i64();
        v = io::read_i64();
//        cout<<p1<<p2<<v<<endl;
        insert(p1, p2, v);
    }
    dis[1] = 0;
    struct line *p = lines[1];
    while (p != nil) {
        dis[p->p] = p->v;
        p = p->next;
    }
}

void bellman_ford()
{
    loz(i, M) {
        loo(j, N) {
            struct line *p = lines[j];
            while (p != nil) {
                if (dis[p->p] > dis[j] + p->v)
                    dis[p->p] = dis[j] + p->v;
                p = p->next;
            }
        }
    }
}

namespace debug {
    void print_dis()
    {
        loo(i, N) {
            cout<< dis[i]<< " ";
        }
        cout<<endl;
    }

}

int main()
{
    init();
    bellman_ford();
    debug::print_dis();
    return 0;
}
