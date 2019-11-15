#include <cstdio>
#include <cstdlib>
#include <iostream>
#define size 100010
typedef long long int64;

using namespace std;

struct seg_node {
	int l, r;
	int64 weight;
	int64 lazy;
};

int N, Q;

struct seg_node tree[size * 4 + 1];

int64 read_int64() {
	char ch = getchar();
	int64 ans = 0, f = 1;
	while (ch < '0' || ch > '9') {
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		ans = ans * 10 + ch - '0';
		ch = getchar();
	}
	return ans * f;
}

char read_char() {
	char ch;
	while ((ch = getchar()) == ' ') {}
	return ch;
}

void build(int l, int r, int k) {
	tree[k].l = l;
	tree[k].r = r;
	tree[k].lazy = 0;
	if (l == r) {
		tree[k].weight = read_int64();
		return;
	}
	int mid = (l + r) / 2;
	build(l, mid, k * 2);
	build(mid + 1, r, k * 2 + 1);
	tree[k].weight = tree[k * 2].weight + tree[k * 2 + 1].weight;
}

void down(int k) {
	tree[k * 2].weight += tree[k].lazy * (tree[k * 2].r - tree[k * 2].l + 1);
	tree[k * 2 + 1].weight += tree[k].lazy * (tree[k * 2 + 1].r - tree[k * 2 + 1].l + 1);
	tree[k * 2].lazy += tree[k].lazy;
	tree[k * 2 + 1].lazy += tree[k].lazy;
	tree[k].lazy = 0;
}

void update(int l, int r, int64 delta, int k) {
	if (tree[k].l >= l && tree[k].r <= r) {
		tree[k].weight += delta * (tree[k].r - tree[k].l + 1);
		tree[k].lazy += delta;
		return;
	}
	if (tree[k].lazy)
		down(k);
	int mid = (tree[k].l + tree[k].r) / 2;
	if (l <= mid)
		update(l, r, delta, k * 2);
	if (r > mid)
		update(l, r, delta, k * 2 + 1);
	tree[k].weight = tree[k * 2].weight + tree[k * 2 + 1].weight;
}

int64 query(int l, int r, int k) {
	if (tree[k].l >= l && tree[k].r <= r)
		return tree[k].weight;
	if (tree[k].lazy)
		down(k);
	int mid = (tree[k].l + tree[k].r) / 2;
	int64 sum = 0;
	if (l <= mid)
		sum += query(l, r, k * 2);
	if (r > mid)
		sum += query(l, r, k * 2 + 1);
	return sum;
}



int main() {
	N = read_int64();
	Q = read_int64();
	build(1, N, 1);
	for (int i = 0; i < Q; i++) {
		char op;
		int a, b, c;
		op = read_char();
		a = read_int64();
		b = read_int64();
		if (op == 'Q') {
			printf("%lld\n", query(a, b, 1));
		} else if (op == 'C') {
			c = read_int64();
			update(a, b, c, 1);
		}
	}
	return 0;
}