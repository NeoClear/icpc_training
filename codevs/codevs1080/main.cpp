#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 400001
#define loz(i, n) for (int i = 0; i < n; i++)
#define loo(i, n) for (int i = 1; i <= n; i++)
typedef long long i64;

using namespace std;

extern i64 N, M;
i64 N, M;

struct segtree_node
{
    i64 left, right;
    i64 value;
};

extern struct segtree_node tree[MAX];
struct segtree_node tree[MAX];

namespace core {
    extern i64 ans;
    i64 ans = 0;
    inline void build(i64 l, i64 r, i64 k)
    {
        tree[k].left = l;
        tree[k].right = r;
        if (l == r) {
            scanf("%lld", &tree[k].value);
            return;
        }
        i64 mid = (l + r) / 2;
        build(l, mid, k * 2);
        build(mid + 1, r, k * 2 + 1);
        tree[k].value = tree[k * 2].value + tree[k * 2 + 1].value;
    }
    inline void suc_node(i64 pos, i64 s, i64 k)
    {
        if (tree[k].left == tree[k].right) {
            tree[k].value += s;
            return;
        }
        i64 mid = (tree[k].left + tree[k].right) / 2;
        if (pos <= mid)
            suc_node(pos, s, k * 2);
        else
            suc_node(pos, s, k * 2 + 1);
        tree[k].value = tree[k * 2].value + tree[k * 2 + 1].value;
    }
    inline void query_range(i64 x, i64 y, i64 k)
    {
        if (x <= tree[k].left && y >= tree[k].right) {
            ans += tree[k].value;
            return;
        }
        i64 mid = (tree[k].left + tree[k].right) / 2;
        if (x <= mid)
            query_range(x, y, k * 2);
        if (y > mid)
            query_range(x, y, k * 2 + 1);
    }
}

namespace debug {
    inline void init()
    {
//        freopen("in.txt", "r", stdin);
//        freopen("out.txt", "w", stdout);
        scanf("%lld", &N);
        core::build(1, N, 1);
        scanf("%lld", &M);
    }
}

int main()
{
    debug::init();
    i64 instruction, x, y;
    loz(i, M) {
        scanf("%lld%lld%lld", &instruction, &x, &y);
        switch (instruction) {
        case 1:
            core::suc_node(x, y, 1);
            break;
        case 2:
            core::ans = 0;
            core::query_range(x, y, 1);
            printf("%lld\n", core::ans);
            break;
        }
    }
    return 0;
}
