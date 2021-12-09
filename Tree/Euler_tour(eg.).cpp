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
#define N 100005
#define sq(x) ((x)*(x))
typedef vector<int> vi;
ll gcd(ll a, ll b) {if (!b)return a; return gcd(b, a % b);}
ll power(ll x, ll y, ll p = INF) {ll res = 1; x %= p; while (y > 0) {if (y & 1)res = (res * x) % p; y = y >> 1; x = (x * x) % p;} return res;}
// Do Not use power when calculating powers of 2 (its inefficient)

struct segtree {

    int size;    // This considers extra elements also to fill upto 2^k elements
    vector<int> sums;

    void init(int n) {
        size = 1;
        while (size < n) size *= 2;
        sums.assign(2 * size, 0ll);
    }

    void build(vector<int>& a, int x, int lx, int rx) {
        int n = a.size();
        if (rx - lx == 1) {
            if (lx < n) {
                sums[x] = a[lx];
            }
            return;
        }
        int m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        sums[x] = sums[2 * x + 1] + sums[2 * x + 2];
    }

    void build(vector<int>& a) {
        build(a, 0, 0, size);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (rx - lx == 1) {   // we are at the leaf
            sums[x] = v;
            return;
        }
        int m = (lx + rx) / 2;
        if (i < m) {
            set(i, v, 2 * x + 1, lx, m);
        }
        else {
            set(i, v, 2 * x + 2, m, rx);
        }
        sums[x] = sums[2 * x + 1] + sums[2 * x + 2];
    }

    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    int find(int l, int r, int x, int lx, int rx) {
        if (lx >= r || l >= rx) return 0; // completly outside
        if (lx >= l && rx <= r) return sums[x]; // completly inside
        int m = (lx + rx) / 2;
        int sum1 = find(l, r, 2 * x + 1, lx, m);
        int sum2 = find(l, r, 2 * x + 2, m, rx);
        return sum1 + sum2;
    }

    int find(int l, int r) {
        return find(l, r, 0, 0, size);
    }

};

vector<vector<int>> adj;
vi sub, last, a, idx;
int ti = 0;

void dfs(int u, int p) {
    sub[ti] = a[u];
    idx[u] = ti;
    ti++;
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
    }
    last[u] = ti - 1;
}

void solve() {
    int n, q; cin >> n >> q;
    a.clear(); a.resize(n);
    idx.clear(); idx.resize(n);
    forn(i, n) cin >> a[i];
    segtree st;
    st.init(n);
    adj.clear(); adj.resize(n);
    forn(i, n - 1) {
        int x, y; cin >> x >> y; x--; y--;
        adj[x].eb(y);
        adj[y].eb(x);
    }
    sub.clear(); sub.resize(n);
    last.clear(); last.resize(n);
    dfs(0, -1); // Euler Tour
    st.build(sub);
    while (q--) {
        int c; cin >> c;
        if (c == 1) {
            int s, x; cin >> s >> x; s--;
            st.set(idx[s], x);
        }
        else {
            int v; cin >> v;
            int left = idx[v - 1];
            int right = last[v - 1];
            cout << st.find(left, right + 1) << endl;
        }
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