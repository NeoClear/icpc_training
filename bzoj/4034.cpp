#include <bits/stdc++.h>

#define SIZE 100010
#define lson(k) tree[k * 2]
#define rson(k) tree[k * 2 + 1]

typedef long long int64;

using namespace std;

struct seg{
	int64 l, r;
	int64 w, lazy;
	int64 io;
};

int64 N, M, dfs_clock = 0;
int64 value[SIZE];
int64 in[SIZE * 2], out[SIZE * 2], clock2id[SIZE * 2];
int64 clock2io[SIZE * 2];
bool visited[SIZE];

struct seg tree[SIZE * 8 + 1];

inline void up(int64 k) {
	tree[k].w = lson(k).w + rson(k).w;
}

inline void down(int64 k) {
	lson(k).lazy += tree[k].lazy;
	rson(k).lazy += tree[k].lazy;
	lson(k).w += tree[k].lazy * lson(k).io;
	rson(k).w += tree[k].lazy * rson(k).io;
	tree[k].lazy = 0;
}

void build(int64 l, int64 r, int64 k) {
	tree[k].l = l;
	tree[k].r = r;
	tree[k].lazy = 0;
	if (l == r) {
		tree[k].io = clock2io[l];
		tree[k].w = value[clock2id[l]] * tree[k].io;
		return;
	}
	int64 mid = (l + r) / 2;
	build(l, mid, k * 2);
	build(mid + 1, r, k * 2 + 1);
	up(k);
	tree[k].io = tree[k * 2].io + tree[k * 2 + 1].io;
}

void update(int64 l, int64 r, int64 delta, int64 k) {
	if (tree[k].l >= l && tree[k].r <= r) {
		tree[k].w += delta * tree[k].io;
		tree[k].lazy += delta;
		return;
	}
	if (tree[k].lazy)
		down(k);
	int64 mid = (tree[k].l + tree[k].r) / 2;
	if (l <= mid)
		update(l, r, delta, k * 2);
	if (r > mid)
		update(l, r, delta, k * 2 + 1);
	up(k);
}

int64 query(int64 l, int64 r, int64 k) {
	if (tree[k].l >= l && tree[k].r <= r)
		return tree[k].w;
	if (tree[k].lazy)
		down(k);
	int64 sum = 0;
	int64 mid = (tree[k].l + tree[k].r) / 2;
	if (l <= mid)
		sum += query(l, r, k * 2);
	if (r > mid)
		sum += query(l, r, k * 2 + 1);
	return sum;
}

void dfs(int64 x, map<int64, vector<int64> >& graph) {
	in[x] = ++dfs_clock;
	clock2id[dfs_clock] = x;
	clock2io[dfs_clock] = 1;
	visited[x] = true;
	for (int64 i = 0; i < graph[x].size(); i++)
		if (!visited[graph[x][i]])
			dfs(graph[x][i], graph);
	out[x] = ++dfs_clock;
	clock2id[dfs_clock] = x;
	clock2io[dfs_clock] = -1;
}

int main() {
	freopen("in.txt", "r", stdin);
	std::ios::sync_with_stdio(false);
	map<int64, vector<int64> > graph;
	memset(visited, false, sizeof(visited));
	cin >> N >> M;
	for (int64 i = 1; i <= N; i++) {
		cin >> value[i];
	}
	for (int64 i = 1; i < N; i++) {
		int64 a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	dfs(1, graph);
	build(1, N << 1, 1);
	for (int64 i = 0; i < M; i++) {
		int64 op, x, a;
		cin >> op;
		if (op == 1) {
			cin >> x >> a;
			update(in[x], in[x], a, 1);
			update(out[x], out[x], a, 1);
		} else if (op == 2) {
			cin >> x >> a;
			update(in[x], out[x], a, 1);
		} else if (op == 3) {
			// int64 k = 1;s
			cin >> x;
			cout << query(1, in[x], 1) << endl;
			// int64 ans = query(1, in[x], 1);
			// while (k < in[x]) {
			// 	if (out[clock2id[k]] < in[x]) {
			// 		ans -= query(k, out[clock2id[k]], 1);
			// 		k = out[clock2id[k]] + 1;
			// 	} else {
			// 		k++;
			// 	}
			// }
			// cout << ans;
		}
	}
	return 0;
}