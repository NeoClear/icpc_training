#include <bits/stdc++.h>
#include <algorithm>

#define MAX 0xffff
typedef long long i64;
typedef double f64;
#define loz(i, n) for (i64 i = 0; i < static_cast<i64>(n); i++)
#define loo(i, n) for (i64 i = 1; i <= static_cast<i64>(n); i++)

using namespace std;

namespace conv {
    struct point
    {
        f64 x, y;
    };
    typedef point vector;
    static struct point graph[MAX];
    static i64 graph_num;
    static i64 conv[MAX];
    static i64 top = 0;

    namespace core {
        f64 multi(vector x, vector y)
        {
            return x.x * y.y - y.x * x.y;
        }
        vector minus(point x, point y)
        {
            vector tmp;
            tmp.x = x.x - y.x;
            tmp.y = x.y - y.y;
            return tmp;
        }
        f64 dis(point x, point y)
        {
            return sqrt((x.x - y.x) * (x.x - y.x) + (x.y - y.y) * (x.y - y.y));
        }
        bool cmp(point x, point y)
        {
            f64 tmp = multi(minus(x, graph[0]), minus(y, graph[0]));
            if (tmp < 0)
                return true;
            if (static_cast<f64>(abs(tmp)) < 0.000001 && dis(x, graph[0]) < dis(y, graph[0]))
                return true;
            return false;
        }
        inline void solve()
        {
            conv[top++] = 0;
            conv[top++] = 1;
            for (i64 i = 2; i <= graph_num - 1; i++) {

                if (multi(minus(graph[i], graph[conv[top - 1]]), minus(graph[conv[top - 1]], graph[conv[top - 2]])) < 0) {
                    top--;
                }
                conv[top++] = i;
            }
        }
    }

    namespace debug {
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
        inline void run()
        {
            freopen("in.txt", "r", stdin);
            graph_num = read_i64();
            i64 left = 0;
            loz(i, graph_num) {
                graph[i].x = read_f64();
                graph[i].y = read_f64();
                if (graph[i].x < graph[left].x)
                    left = i;
            }
            swap(graph[0], graph[left]);
            sort(graph + 1, graph + graph_num, core::cmp);
            core::solve();
        }
        inline void print_graph()
        {
            loz(i, graph_num) {
                printf("(%llf, %llf)\n", graph[i].x, graph[i].y);
            }
        }
        inline void print_conv()
        {
            loz(i, top) {
                cout<< graph[conv[i]].x<< ", "<< graph[conv[i]].y<< endl;
            }
        }
    }
}

int main()
{
    conv::debug::run();
//    conv::debug::print_graph();
    conv::debug::print_conv();
    return 0;
}
