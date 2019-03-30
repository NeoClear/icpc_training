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

inline void db()
{
    cout<<"db"<<endl;
}

inline void init()
{
    freopen("in.txt", "r", stdin);
}

namespace sorting {
    struct edge
    {
        i64 u;
        i64 v;
        i64 w;
    };
    static struct edge lines[inf];
    static i64 N, M;
    static i64 boss[inf];
    namespace debug {
        void print_egde()
        {
            loz(i, M) {
                printf("%lld %lld %lld\n", lines[i].u, lines[i].v, lines[i].w);
            }
        }
    }
    i64 find_boss(i64 k) {
        if (boss[k] == k)
            return k;
        boss[k] = find_boss(boss[k]);
        return boss[k];
    }
    bool camp(struct edge s1, struct edge s2)
    {
        return s1.w < s2.w;
    }
    inline void prepare()
    {
        N = io::read_i64();
        M = io::read_i64();
        loo(i, N)
            boss[i] = i;
        loz(i, M) {
            lines[i].u = io::read_i64();
            lines[i].v = io::read_i64();
            lines[i].w = io::read_i64();
        }
        sort(lines, lines + M, camp);
    }
    inline void run()
    {
        prepare();
        loz(i, M) {
            if (find_boss(lines[i].u) == find_boss(lines[i].v))
                continue;
            printf("%lld %lld %lld\n", lines[i].u, lines[i].v, lines[i].w);
            boss[find_boss(lines[i].v)] = find_boss(lines[i].u);
        }
    }
}

namespace dijkstra_style {

}

int main()
{
    init();
    sorting::run();
    return 0;
}
