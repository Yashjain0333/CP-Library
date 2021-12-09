vector<vector<int>> adj;
vector<int> color, parent;
vector<bool> vis;
int cycle_start = -1, cycle_end = -1;

bool isCycle(int cur, int p) {
    color[cur] = 1;
    vis[cur] = true;
    for (auto x : adj[cur]) {
        if (color[x] == 0) { // visit this node since this has not yet been visited
            parent[x] = cur;
            if (isCycle(x))
                return true;
        }
        else if (color[x] == 1) { // This is in the process of 'visiting' hence we have found the cycle
            cycle_end = cur;
            cycle_start = x;
            return true;
        }
    }
    color[cur] = 2;
    return false;
}

void solve() {
    int n; cin >> n;
    adj.clear(); color.clear(); parent.clear();
    adj.resize(n + 1); color.resize(n + 1); parent.resize(n + 1);
    forn(i, n) {
        int x, y; cin >> x >> y;
        adj[x].eb(y);
    }
    if (dfs(1, -1)) {
        vector<int> cycle;
        cycle.eb(cycle_start);
        for (int v = cycle_end; v != cycle_start; v = parent[v]) {
            cycle.eb(v);
        }
    }
    else {
        cout << "No Cycle in the graph!\n";
    }
}