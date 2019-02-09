#include <bits/stdc++.h>
#include <algorithm>

#define MAX 50001
#define MIN 0.0000001
typedef long long i64;
typedef double f64;
#define loz(i, n) for (i64 i = 0; i < n; i++)

using namespace std;

static i64 N;

struct node
{
    f64 x, y;
    node(f64 a = 0, f64 b = 0): x(a), y(b) {}
    f64 dis()
    {
        return sqrt(x * x + y * y);
    }
    node operator -(node conse)
    {
        return node(x - conse.x, y - conse.y);
    }
    f64 operator *(node conse)
    {
        return x * conse.y - y * conse.x;
    }
};

typedef node nector;

static node graph[MAX];
static i64 conv[MAX];
static node convex[MAX];
static i64 top = 0;
static f64 dis = 0;
static i64 oppo = 0;

f64 read_f64()
{
    f64 ans = 0.0, f = 1.0;
    int ch = getchar();
    while(!isdigit(ch)) {
        if (ch == '-')
            f = -1.0;
        ch = getchar();
    }
    while (isdigit(ch)) {
        ans = ans * 10 + ch - '0';
        ch = getchar();
    }
    return ans * f;
}
bool cmp(node a, node b)
{
    if ((a - graph[0]) * (b - graph[0]) < 0)
        return true;
    if ((a - graph[0]) * (b - graph[0]) < MIN && a.dis() < b.dis())
        return true;
    return false;
}
inline void solve()
{
    conv[top++] = 0;
    conv[top++] = 1;
    for (int i = 2; i < N; i++) {
        if ((graph[i] - graph[conv[top - 1]]) * (graph[conv[top - 1]] - graph[conv[top - 2]]) <= 0) {
            top--;
        }
        conv[top++] = i;
    }
}
i64 nnode(i64 n)
{
    if (n == top - 1)
        return 0;
    return n + 1;
}
f64 distance(i64 a, i64 b, i64 c)
{
    if ((convex[a].x - convex[b].x) < MIN)
        return abs(convex[c].x - convex[a].x);
    f64 k =  (convex[a].y - convex[b].y) / (convex[a].x - convex[b].x);
    f64 A = k;
    f64 B = -1;
    f64 C = convex[a].y - k * convex[a].x;
    return abs(A * convex[c].x + B * convex[c].y + C) / sqrt(A * A + B * B);
}
inline void find()
{
    if (top == 2) {
        dis = (convex[0] - convex[1]).dis();
        return;
    }
    oppo = 2;
    loz(i, top) {
        while (distance(i, nnode(i), nnode(oppo)) >= distance(i, nnode(i), oppo))
            oppo = nnode(oppo);
        dis = max(dis, (convex[i] - convex[oppo]).dis());
        dis = max(dis, (convex[nnode(i)] - convex[oppo]).dis());
    }
}
i64 tatp(f64 t)
{
    if (static_cast<i64>(t) < t)
        return static_cast<i64>(t) + 1;
    return static_cast<i64>(t);
}
inline void run()
{
    freopen("in.txt", "r", stdin);
    scanf("%lld", &N);
    i64 m = 0;
    loz(i, N) {
       graph[i].x = read_f64();
       graph[i].y = read_f64();
       if (graph[i].x < graph[m].x)
           m = i;
    }
    swap(graph[0], graph[m]);
    sort(graph + 1, graph + N, cmp);
    solve();
    loz(i, top) {
        swap(convex[i], graph[conv[i]]);
    }
    find();
    cout<< tatp(dis)<< endl;
}
int main()
{
    run();
    return 0;
}
