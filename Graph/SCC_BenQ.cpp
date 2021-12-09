/* SCC from BenQ */
struct SCC {
	int N; vector<vi> adj, radj;
	vi todo, comps, comp; vector<bool> vis;
	void init(int _N) {
		N = _N;
		adj.rsz(N), radj.rsz(N), comp = vi(N, -1), vis.rsz(N);
	}
	void ae(int x, int y) { adj[x].pb(y), radj[y].pb(x); }
	void dfs(int x) {
		vis[x] = 1; trav(y, adj[x]) if (!vis[y]) dfs(y);
		todo.pb(x);
	}
	void dfs2(int x, int v) {
		comp[x] = v;
		trav(y, radj[x]) if (comp[y] == -1) dfs2(y, v);
	}
	void gen(int _N) { // fills allComp
		FOR(i, 1, _N) if (!vis[i]) dfs(i);
		reverse(all(todo));
		trav(x, todo) if (comp[x] == -1) {
			dfs2(x, x); comps.pb(x);
		}
	}
};