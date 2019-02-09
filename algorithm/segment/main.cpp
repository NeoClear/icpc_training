#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define MAX 9999
typedef long long i64;

using namespace std;

i64 length;
i64 ans;

struct segment_node
{
    i64 left, right;
    i64 value;
    i64 lazy;
}tree[MAX * 4 + 1];

i64 mid(segment_node cur)
{
    return (cur.left + cur.right) / 2;
}

i64 len(segment_node range)
{
    return (range.right - range.left + 1);
}

void build(i64 l, i64 r, i64 k)
{
    tree[k].right = r;
    tree[k].left = l;

    if (l == r) {
        scanf("%lld", &tree[k].value);
        return;
    }

    i64 mid = (l + r) / 2;
    build(l, mid, k * 2);
    build(mid + 1, r, k * 2 + 1);
    tree[k].value = tree[k * 2].value + tree[k * 2 + 1].value;
    return;
}

void down(i64 k)
{
    tree[k * 2].lazy += tree[k].lazy;
    tree[k * 2 + 1].lazy += tree[k].lazy;
    tree[k * 2].value += (tree[k * 2].right - tree[k * 2].left + 1) * tree[k].lazy;
    tree[k * 2 + 1].value += (tree[k * 2 + 1].right - tree[k * 2 + 1].left + 1) * tree[k].lazy;
    tree[k].lazy = 0;
}

i64 get_node(i64 pos, i64 k) {
    if (tree[k].left == tree[k].right)
        return tree[k].value;
    if (tree[k].lazy)
        down(k);
    if (pos <= mid(tree[k]))
        return get_node(pos, k * 2);
    else
        return get_node(pos, k * 2 + 1);
}

void set_node(i64 pos, i64 v, i64 k)
{
    if (tree[k].left == tree[k].right)
        tree[k].value = v;
    if (tree[k].lazy)
        down(k);
    if (pos <= mid(tree[k]))
        set_node(pos, v, k * 2);
    else
        set_node(pos, v, k * 2 + 1);
    tree[k].value = tree[k * 2].value + tree[k * 2 + 1].value;
}

void get_interval(i64 x, i64 y, i64 k)
{
    if (tree[k].left >= x && tree[k].right <= y) {
        ans += tree[k].value;
        return;
    }
    if (tree[k].lazy)
        down(k);
    i64 m = mid(tree[k]);
    if (x <= m)
        get_interval(x, m, k * 2);
    if (y > m)
        get_interval(m + 1, y, k * 2 + 1);

}

void set_interval(i64 v, i64 x, i64 y, i64 k)
{
    printf("miao");
    if (tree[k].left >= x && tree[k].right <= y) {
        tree[k].lazy += v;
        tree[k].value += v * len(tree[k]);
        return;
    }
    i64 m = mid(tree[k]);
    if (tree[k].lazy)
        down(k);
    if (x <= m)
        set_interval(v, x, y, k * 2);
    if (y > m)
        set_interval(v, x, y, k * 2 + 1);
    tree[k].value = tree[k * 2].value + tree[k * 2 + 1].value;
}

int main()
{
    i64 l, r, suc;
    ans = 0;
    freopen("in.txt", "r", stdin);
    scanf("%lld", &length);
    build(1, length, 1);
    cin>> l>>r>>suc;
    set_interval(suc, l, r, 1);
    get_interval(1, length, 1);
    cout<< ans<< endl;
    return 0;
}
