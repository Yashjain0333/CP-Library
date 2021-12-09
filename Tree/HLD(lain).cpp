#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using pii = pair<int, int>;

// My simple use lazy segtree
// This is Lain's HLD template
template<class T>
struct LazySegTree {
  int n;
  vector<T> t, lz;
  T E = 0;
  T ID = 0;

  T comb(T a, T b) { // Segtree function
    return a + b;
  }
  void push(int node, int l, int r) { // Propagation
    t[node] += (r - l + 1) * lz[node];
    if (l != r) { // Propagate
      for (int it = 0; it < 2; it++) {
        lz[2 * node + it] += lz[node];
      }
    }
    lz[node] = ID;
  }
  LazySegTree() {}
  LazySegTree(int _n) : n(_n), t(4 * n + 5), lz(4 * n + 5) {
  }
  LazySegTree(vector<T>& bld) : n(bld.size()), t(4 * n + 5), lz(4 * n + 5) {
    build(bld, 1, 0, n - 1);
  }
  void build(vector<T>& bld, int node, int tl, int tr) {
    if (tl == tr) {
      t[node] = bld[tl];
    }
    else {
      int tm = (tl + tr) / 2;
      build(bld, 2 * node, tl, tm);
      build(bld, 2 * node + 1, tm + 1, tr);
      pull(node);
    }
  }
  void pull(int node) { t[node] = comb(t[2 * node], t[2 * node + 1]); }
  void apply(int l, int r, T val) { apply(l, r, val, 1, 0, n - 1); }
  void apply(int l, int r, T val, int node, int tl, int tr) {
    push(node, tl, tr);
    if (r < tl || tr < l) return;
    if (l <= tl && tr <= r) {
      lz[node] = val;
      push(node, tl, tr);
      return;
    }
    int tm = (tl + tr) / 2;
    apply(l, r, val, 2 * node, tl, tm);
    apply(l, r, val, 2 * node + 1, tm + 1, tr);
    pull(node);
  }
  T query(int l, int r) {return query(l, r, 1, 0, n - 1);}
  T query(int l, int r, int node, int tl, int tr) {
    push(node, tl, tr);
    if (r < tl || tr < l) return E;
    if (l <= tl && tr <= r) return t[node];
    int tm = (tl + tr) / 2;
    return comb(query(l, r, 2 * node, tl, tm), query(l, r, 2 * node + 1, tm + 1, tr));
  }
};

struct HLD {
  int n;
  vector<vector<int>> adj;
  vector<int> parent, root, depth, sz, pos, rpos;
  int timer;
  bool usingEdge;
  vector<ll> val; // Read into this
  LazySegTree<ll> T;

  HLD(int _n, bool _usingEdge = false) : n(_n), adj(n), parent(n), root(n),
    depth(n), sz(n), pos(n), usingEdge(_usingEdge), val(n), T(n) {}

  void add_edge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  void size_dfs(int s) {
    sz[s] = 1;
    for (auto& u : adj[s]) {
      parent[u] = s;
      depth[u] = depth[s] + 1;
      adj[u].erase(find(adj[u].begin(), adj[u].end(), s));
      size_dfs(u);
      sz[s] += sz[u];
      if (sz[u] > sz[adj[s][0]])
        swap(u, adj[s][0]);
    }
  }

  void hld_dfs(int s) {
    pos[s] = timer++;
    rpos.push_back(s);
    for (auto& u : adj[s]) {
      root[u] = (u == adj[s][0] ? root[s] : u);
      hld_dfs(u);
    }
  }

  // build with specific root
  void build(int r = 0) {
    parent[r] = depth[r] = timer = 0;
    size_dfs(r);
    root[r] = r;
    hld_dfs(r);
    vector<ll> bld(n);
    for (int i = 0; i < n; i++) bld[pos[i]] = val[i];
    T = LazySegTree<ll>(bld);
  }

  // Get LCA in log time
  int lca(int u, int v) {
    for (; root[u] != root[v]; v = parent[root[v]])
      if (depth[root[u]] > depth[root[v]])
        swap(u, v);
    return depth[u] < depth[v] ? u : v;
  }

  template <class BinaryOp>
  void process_path(int u, int v, BinaryOp op) {
    for (; root[u] != root[v]; v = parent[root[v]]) {
      if (depth[root[u]] > depth[root[v]])
        swap(u, v);
      op(pos[root[v]], pos[v]);
    }
    if (depth[u] > depth[v])
      swap(u, v);
    op(pos[u] + usingEdge, pos[v]);
  }

  //Updates path
  void update(int u, int v, ll val) {
    process_path(u, v, [this, &val](int l, int r) {
      T.apply(l, r, val);
    });
  }

  //Updates subtree
  void update(int u, ll val) {
    T.apply(pos[u] + usingEdge, pos[u] + sz[u] - 1, val);
  }

  ll query(int u, int v) {
    ll res = 0;
    process_path(u, v, [this, &res](int l, int r) {
      res += T.query(l, r);
    });
    return res;
  }
};

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}
