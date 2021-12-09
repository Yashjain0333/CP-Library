struct HLD_LCA {
    vi sz, in, out, head, par;
    vector<vi> g;
    HLD_LCA(vector<vector<int>> &_g) : g(_g), sz(_g.size()), in(_g.size()), out(_g.size()), head(_g.size()), par(_g.size()) {}
    void dfs_sz(int cur, int pre) {
        sz[cur] = 1;
        for (int &next : g[cur]) {
            if (next == pre) continue;
            dfs_sz(next, cur);
            par[next] = cur;
            sz[cur] += sz[next];
            if (sz[next] > sz[g[cur][0]]) swap(next, g[cur][0]);
        }
    }

    void dfs_hld(int cur, int pre, int &idx) {
        in[cur] = idx++;
        for (int& next : g[cur]) {
            if (next == pre) continue;
            if (next == g[cur][0]) head[next] = head[cur];
            else head[next] = next;
            dfs_hld(next, cur, idx);
        }
        out[cur] = idx;
    }

    void build() {
        dfs_sz(0, -1);
        int idx = 0;
        dfs_hld(0, -1, idx);
    }
    int lca(int u, int v) {
        for (;; v = par[head[v]]) {
            if (in[u] > in[v]) swap(u, v);
            if (head[u] == head[v]) return u;
        }
    }
};