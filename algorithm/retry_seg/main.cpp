#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define MAX 0xffff
typedef long long i64;
#define loz(i, n) for (int i = 0; i < n; i++)
#define loo(i, n) for (int i = 1; i <= n; i++)

using namespace std;

struct seg_tree_node
{
    i64 left, right;
    i64 value;
    i64 cache;
};

//extern struct seg_tree_node tree[MAX];
static struct seg_tree_node tree[MAX];

static i64 seg_tree_length;

namespace calc {
    i64 mid(seg_tree_node n)
    {
        return (n.left + n.right) / 2;
    }
    i64 mid(i64 l, i64 r)
    {
        return (l + r) / 2;
    }
    i64 len(seg_tree_node n)
    {
        return n.right - n.left + 1;
    }
    i64 len(i64 l, i64 r)
    {
        return r - l + 1;
    }
    i64 power(i64 base, i64 time)
    {
        if (!time)
            return 1;
        i64 ans = 1;
        while (time > 0) {
            if ((time & 1) == 1)
                ans *= base;
            base *= base;
            time >>= 1;
        }
        return ans;
    }
}

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
    inline void set_node(i64 pos, i64 v, i64 k)
    {
        if (tree[k].left == tree[k].right) {
            tree[k].value = v;
            return;
        }
        if (tree[k].cache)
            down(k);
        if (pos <= calc::mid(tree[k]))
            set_node(pos, v, k * 2);
        else
            set_node(pos, v, k * 2 + 1);
        tree[k].value = tree[k * 2].value + tree[k * 2 + 1].value;
    }
    inline void suc_node(i64 pos, i64 s, i64 k)
    {
        if (tree[k].left == tree[k].right) {
            tree[k].value += s;
            return;
        }
        if (tree[k].cache)
            down(k);
        if (pos <= calc::mid(tree[k]))
            suc_node(pos, s, k * 2);
        else
            suc_node(pos, s, k * 2 + 1);
        tree[k].value = tree[k * 2].value + tree[k * 2 + 1].value;
    }
    i64 get_node(i64 pos, i64 k)
    {
        if (tree[k].left == tree[k].right)
            return tree[k].value;
        if (pos <= calc::mid(tree[k]))
            return get_node(pos, k * 2);
        else
            return get_node(pos, k * 2 + 1);
    }
    inline void suc_range(i64 x, i64 y, i64 s, i64 k)
    {
        if (x <= tree[k].left && y >= tree[k].right) {
            tree[k].cache += s;
            tree[k].value += calc::len(tree[k]) * s;
            return;
        }
        if (tree[k].cache)
            down(k);
        if (x <= calc::mid(tree[k]))
            suc_range(x, y, s, k * 2);
        if (y > calc::mid(tree[k]))
            suc_range(x, y, s, k * 2 + 1);
        tree[k].value = tree[k * 2].value + tree[k * 2 + 1].value;
    }
    inline void get_range(i64 x, i64 y, i64 k)
    {
        if (x <= tree[k].left && y >= tree[k].right) {
            ans += tree[k].value;
            return;
        }
        if (tree[k].cache)
            down(k);
        if (x <= calc::mid(tree[k]))
            get_range(x, y, k * 2);
        if (y > calc::mid(tree[k]))
            get_range(x, y, k * 2 + 1);
    }
    inline void reset_ans()
    {
        ans = 0;
    }
}

namespace debug {
    inline void init()
    {
        freopen("in.txt", "r", stdin);
        scanf("%lld", &seg_tree_length);
    }
    inline void print(i64 k)
    {
        printf("(%lld, %lld): %lld, %lld\n", tree[k].left, tree[k].right, tree[k].value, tree[k].cache);
        if (tree[k].left == tree[k].right)
            return;
        print(k * 2);
        print(k * 2 + 1);
    }
}

int main()
{
    debug::init();
    core::build(1, seg_tree_length, 1);
    core::suc_range(3, 7, 1, 1);
    core::suc_node(3, -1, 1);
    core::get_range(1, 8, 1);
    cout<< core::ans<< endl;
    return 0;
}
