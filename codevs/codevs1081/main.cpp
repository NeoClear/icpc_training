#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define MAX 400001
typedef long long i64;
#define loz(i, n) for (int i = 0; i < n; i++)
#define loo(i, n) for (int i = 1; i <= n; i++)

using namespace std;

namespace segment_tree {
    struct segment_tree_node
    {
        i64 left, right;
        i64 value;
        i64 cache;
    };
    extern struct segment_tree_node tree[MAX];
    struct segment_tree_node tree[MAX];

    extern i64 N, Q;
    i64 N, Q;

    namespace calc {
        i64 mid(segment_tree_node n)
        {
            return (n.left + n.right) / 2;
        }
        i64 mid(i64 l, i64 r)
        {
            return (l + r) / 2;
        }
        i64 len(segment_tree_node n)
        {
            return n.right - n.left + 1;
        }
        i64 len(i64 l, i64 r)
        {
            return r - l + 1;
        }
    }

    namespace core {
        inline void build(i64 l, i64 r, i64 k)
        {
            tree[k].left = l;
            tree[k].right = r;
            if (l == r) {
                scanf("%lld", &tree[k].value);
                return;
            }
            build(l, calc::mid(l, r), k * 2);
            build(calc::mid(l, r) + 1, r, k * 2 + 1);
            tree[k].value = tree[k * 2].value + tree[k * 2 + 1].value;
        }
        inline void down(i64 k)
        {
            tree[k * 2].cache += tree[k].cache;
            tree[k * 2 + 1].cache += tree[k].cache;
            tree[k * 2].value += calc::len(tree[k * 2]) * tree[k].cache;
            tree[k * 2 + 1].value += calc::len(tree[k * 2 + 1]) * tree[k].cache;
            tree[k].cache = 0;
        }
        inline void suc_range(i64 x, i64 y, i64 s, i64 k)
        {
            if (x <= tree[k].left && y >= tree[k].right) {
                tree[k].cache += s;
                tree[k].value += s * calc::len(tree[k]);
                return;
            }
            if (tree[k].cache)
                down(k);
            if (x <= calc::mid(tree[k]))
                suc_range(x, y, s, k * 2);
            if (y > calc::mid(tree[k]))
                suc_range(x, y, s, k * 2 + 1);
            tree[k].value += tree[k * 2].value + tree[k * 2 + 1].value;
        }
        i64 get_node(i64 pos, i64 k)
        {
            if (tree[k].left == tree[k].right)
                return tree[k].value;
            if (tree[k].cache)
                down(k);
            if (pos <= calc::mid(tree[k]))
                return get_node(pos, k * 2);
            else
                return get_node(pos, k * 2 + 1);
        }
    }

    namespace debug {
        inline void run()
        {
            freopen("in.txt", "r", stdin);
            freopen("out.txt", "w", stdout);
            scanf("%lld", &N);
            core::build(1, N, 1);
            scanf("%lld", &Q);
            i64 instruction, l, r, v;
            loz(i, Q) {
                scanf("%lld", &instruction);
                switch (instruction) {
                case 1:
                    scanf("%lld%lld%lld", &l, &r, &v);
                    core::suc_range(l, r, v, 1);
                    break;
                case 2:
                    scanf("%lld", &v);
                    printf("%lld\n", core::get_node(v, 1));
                    break;
                }
            }
        }
    }
}

int main()
{
    segment_tree::debug::run();
    return 0;
}
