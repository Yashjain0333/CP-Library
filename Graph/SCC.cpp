// Kosaraju's Algo for SCCs

int n, m;
vector<vector<int>> adj, adj_rev;
vector<bool> vis;
vector<int> topo, component;

void dfs1(int u) {
    vis[u] = true;
    for (int v : adj[u]) {
        if (!vis[v]) dfs1(v);
    }
    topo.eb(u);
}

void dfs2(int u) {
    vis[u] = true;
    for (int v : adj_rev[u]) {
        if (!vis[v]) dfs2(v);
    }
    component.eb(u);
}

void solve() {
    cin >> n >> m;
    adj.resize(n); vis.assign(n, false); adj_rev.resize(n);
    forn(i, m) {
        int x, y; cin >> x >> y; x--; y--;
        adj[x].eb(y);
        adj_rev[y].eb(x);
    }
    forn(i, n) if (!vis[i]) dfs1(i);
    reverse(all(topo));
    vis.assign(n, false);
    vector<int> roots(n, 0), root_nodes;
    vector<vector<int>> adj_scc(n);

    for (auto v : topo) {
        if (!vis[v]) {
            dfs2(v);
            int root = component.front();
            for (auto u : component) roots[u] = root;
            root_nodes.push_back(root);
            component.clear();
        }
    }

    for (int v = 0; v < n; v++) {
        for (auto u : adj[v]) {
            int root_v = roots[v], root_u = roots[u];
            if (root_u != root_v) adj_scc[root_v].push_back(root_u);
        }
    }
}