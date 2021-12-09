#include <bits/stdc++.h>
using namespace std;

class dsu {
public:
	int n;
	vector<int> p, sz;

	dsu() {}

	dsu(int _n) : n(_n) {
		p.resize(n);
		sz.resize(n, 1);
		iota(p.begin(), p.end(), 0);
	}

	int inline find(int x) {
		return (x == p[x] ? x : (p[x] = find(p[x])));
	}

	bool inline unite(int u, int v) {
		u = find(u), v = find(v);
		if (sz[u] < sz[v]) swap(u, v);
		if (u != v) {
			p[v] = u;
			sz[u] += sz[v];
			return true;
		}
		return false;
	}

	int inline num_connect() {
		vector<int> cnt(n, 0);
		int res = 0;
		for (int i = 0; i < n; i++) {
			int par = find(i);
			cnt[par]++;
		}
		for (int i = 0; i < n; i++) {
			if (cnt[i] > 0) res++;
		}
		return res;
	}
};

struct Edge {
	int u, v, weight;
	bool operator<(Edge const& other) {
		return weight < other.weight;
	}
};

int main() {

	// Just sort the edges and add them one by one if they don't belong to the same subtree

	int n;
	vector<Edge> edges;

	int cost = 0;
	vector<Edge> result;
	dsu d(n);

	sort(edges.begin(), edges.end());

	for (Edge e : edges) {
		if (d.find(e.u) != d.find(e.v)) {
			cost += e.weight;
			result.push_back(e);
			d.unite(e.u, e.v);
		}
	}
}