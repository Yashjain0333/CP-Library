vector<int> color(N);
vector<vector<int>> adj(N);
vector<int> dp(N);
vector<int> res(N);

void dfs1(int u, int p = -1) {
    dp[u] = color[u];
    for (auto x : adj[u]) {
        if (x == p) continue;
        dfs1(x, u);
        dp[u] += max((int)0, dp[x]);
    }
}

void dfs2(int u, int p = -1) {
    res[u] = dp[u];
    for (auto x : adj[u]) {
        if (x == p) continue;
        dp[u] -= max((int)0, dp[x]);
        dp[x] += max((int)0, dp[u]);
        dfs2(x, u);
        dp[x] -= max((int)0, dp[u]);
        dp[u] += max((int)0, dp[x]);
    }
}

void solve() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> color[i];
        if (!color[i]) color[i] = -1;
    }
    for (int i = 0; i < n - 1; i++) {
        int x, y; cin >> x >> y; x--; y--;
        adj[x].eb(y); adj[y].eb(x);
    }
    dfs1(0);
    dfs2(0);
    for (int i = 0; i < n; i++) cout << res[i] << " ";
}