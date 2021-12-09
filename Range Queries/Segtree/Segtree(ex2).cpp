//BY: YASH JAIN, CF: yashjain0333
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
ll power(ll x, ll y, ll p = INF) {ll result = 1; x %= p; while (y > 0) {if (y & 1)result = (result * x) % p; y = y >> 1; x = (x * x) % p;} return result;}
// Do Not use power when calculating powers of 2 (its inefficient)

struct segtree {

    int size;    // This considers extra elements also to fill upto 2^k elements
    vector<int> operations;
    vector<int> values;
    int NEUTRAL_ELEMENT = 0;
    int NO_OPERATION = LLONG_MAX;

    int modify_op(int a, int b, int len) {
        if (b == NO_OPERATION) return a;
        else return (b * len);
    }

    int calc_op(int a, int b) {
        return a + b;
    }

    void apply_mod_op(int& a, int b, int len) {
        a = modify_op(a, b, len);
    }

    void build(int x, int lx, int rx) {
        if (rx - lx == 1) {
            values[x] = 1ll;
            return;
        }
        int m = (lx + rx) / 2;
        build(2 * x + 1, lx, m);
        build(2 * x + 2, m, rx);
        values[x] = calc_op(values[2 * x + 1], values[2 * x + 2]);
    }

    void init(int n) {
        size = 1;
        while (size < n) size *= 2;
        operations.assign(2 * size, 0ll);
        values.assign(2 * size, 0ll);
        // build(0, 0, size);
    }

    void propagate(int x, int lx, int rx) {
        if (rx - lx == 1) return; // don't propagate
        int m = (lx + rx) / 2;
        apply_mod_op(operations[2 * x + 1], operations[x], 1);
        apply_mod_op(operations[2 * x + 2], operations[x], 1);
        apply_mod_op(values[2 * x + 1], operations[x], m - lx);
        apply_mod_op(values[2 * x + 2], operations[x], rx - m);
        operations[x] = NO_OPERATION;
    }

    void modify(int l, int r, int v, int x, int lx, int rx) {
        propagate(x, lx, rx);
        if (lx >= r || l >= rx) return; // completly outside
        if (lx >= l && rx <= r) {
            apply_mod_op(operations[x], v, 1);
            apply_mod_op(values[x], v, rx - lx);
            return;
        }
        int m = (lx + rx) / 2;
        modify(l, r, v, 2 * x + 1, lx, m);
        modify(l, r, v, 2 * x + 2, m, rx);
        values[x] = calc_op(values[2 * x + 1], values[2 * x + 2]);
    }

    void modify(int l, int r, int v) {
        return modify(l, r, v, 0, 0, size);
    }

    int calc(int l, int r, int x, int lx, int rx) {
        propagate(x, lx, rx);
        if (lx >= r || l >= rx) return NEUTRAL_ELEMENT;
        if (lx >= l && rx <= r) return values[x];
        int m = (lx + rx) / 2;
        int val1 = calc(l, r, 2 * x + 1, lx, m);
        int val2 = calc(l, r, 2 * x + 2, m, rx);
        int res = calc_op(val1, val2);
        return res;
    }

    int calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }

};

void solve() {
    int n, m; cin >> n >> m;
    segtree st;
    st.init(n);
    while (m--) {
        int c; cin >> c;
        if (c == 1) {
            int l, r, v; cin >> l >> r >> v;
            st.modify(l, r, v);
        }
        else {
            int l, r; cin >> l >> r;
            cout << st.calc(l, r) << endl;
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
    cerr << "Time Taken : " << (float)clock() / CLOCKS_PER_SEC << " secs" << endl;
}