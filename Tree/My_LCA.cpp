//BY: YASH JAIN, CF: BitSane
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file 
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> pbds;
#define May_the_fork_be_with_you ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define all(x) (x).begin(), (x).end()
#define rall(v) v.rbegin(),v.rend()
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
#define for1(i, n) for (int i = 1; i <= (int)(n); ++i)
#define ford(i, n) for (int i = (int)(n) - 1; i >= 0; --i)
#define fore(i, a, b) for (int i = (int)(a); i <= (int)(b); ++i)
#define deb(x) cout<<#x<<": "<<x<<endl;
#define debn(x) cout<<#x<<": "<<x<<"  ";
#define MOD 1000000007
#define mod 998244353
#define INF 1e18
#define ll long long
#define f first
#define s second
#define pb push_back
#define eb emplace_back
#define endl "\n"
#define int long long
#define N 200005
#define sq(x) ((x)*(x))
typedef vector<int> vi;
ll gcd(ll a, ll b) {if (!b)return a; return gcd(b, a % b);}
ll power(ll x, ll y, ll p = INF) {ll res = 1; x %= p; while (y > 0) {if (y & 1)res = (res * x) % p; y = y >> 1; x = (x * x) % p;} return res;}
// Do Not use power when calculating powers of 2 (its inefficient)

#define LOG 18
vector<vi> adj;
int up[N][LOG];
vi depth;

void dfs(int u, int p = -1) {
    for (int v : adj[u]) {
        if (v == p) continue;
        depth[v] = depth[u] + 1;
        up[v][0] = u;
        for (int j = 1; j < LOG; j++) {
            up[v][j] = up[up[v][j - 1]][j - 1];
        }
        dfs(v, u);
    }
}

int LCA(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v];
    for (int j = LOG - 1; j >= 0; j--) {
        if (1 & (diff >> j)) u = up[u][j];
    }
    if (u == v) return u;
    for (int j = LOG - 1; j >= 0; j--) {
        if (up[u][j] != up[v][j]) {
            u = up[u][j];
            v = up[v][j];
        }
    }
    return up[u][0];
}

int kthancestor(int u, int k) {
    int res = u;
    for (int j = LOG - 1; j >= 0; j--) {
        if (1 & (k >> j)) res = up[res][j];
    }
    return res;
}

void solve() {
    int n, q; cin >> n >> q;
    adj.clear(); adj.resize(n);
    depth.clear(); depth.assign(n, 0);
    forn(i, n - 1) {
        int x; cin >> x;
        adj[x - 1].eb(i + 1);
    }
    depth[0] = 0;
    dfs(0);
    while (q--) {
        int x, y; cin >> x >> y; x--; y--;
        cout << LCA(x, y) + 1 << endl;
    }
}

int32_t main() {

#ifndef ONLINE_JUDGE
    // for geting input form input.txt
    freopen("input.txt", "r", stdin);
    // for wrting output to output.txt
    freopen("output.txt", "w", stdout);
#endif

    May_the_fork_be_with_you
    int t = 1;
    int x = 1;
    // cin >> t;
    cout << fixed << setprecision(12);
    while (t--) {
        // cout << "Case #" << x << ": ";
        solve();
        x++;
    }

#ifndef ONLINE_JUDGE
    cerr << "Time Taken : " << (float)clock() / CLOCKS_PER_SEC << " secs" << endl;
#endif
}