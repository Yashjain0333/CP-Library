class dsu {
public:
	int n, cnt;
	vector<int> p, sz;

	dsu() {}

	dsu(int _n) : n(_n) {
		p.resize(n);
		sz.resize(n, 1);
		cnt = n;
		iota(p.begin(), p.end(), 0);
	}

	int find(int x) {
		return (x == p[x] ? x : (p[x] = find(p[x])));
	}

	bool inline unite(int u, int v) {
		u = find(u), v = find(v);
		if (sz[u] < sz[v]) swap(u, v);
		if (u != v) {
			cnt--;
			p[v] = u;
			sz[u] += sz[v];
			return true;
		}
		return false;
	}

	int inline num_connect() {
		return cnt;
	}
};