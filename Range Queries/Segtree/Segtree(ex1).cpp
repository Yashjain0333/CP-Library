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
#define N 200000
#define sq(x) ((x)*(x))
typedef vector<int> vi;
ll gcd(ll a, ll b) {if (!b)return a; return gcd(b, a % b);}
ll power(ll x, ll y, ll p = INF) {ll result = 1; x %= p; while (y > 0) {if (y & 1)result = (result * x) % p; y = y >> 1; x = (x * x) % p;} return result;}
// Do Not use power when calculating powers of 2 (its inefficient)

struct segtree {

    int size;
    vector<int> cnt;
    vector<int> operations;
    int NO_OPERATION = INT_MAX;
    // 0 means all 0s and 1 means all 1s

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

    void init(int n) {
        size = 1;
        while (size < n) size *= 2;
        cnt.assign(2 * size, 0ll);
        operations.assign(2 * size, NO_OPERATION);
    }

    void propagate(int x, int lx, int rx) {
        if (rx - lx == 1) return;  // reached the leaf
        int m = (rx + lx) / 2;
        apply_mod_op(operations[2 * x + 1], operations[x], 1);
        apply_mod_op(operations[2 * x + 2], operations[x], 1);
        apply_mod_op(cnt[2 * x + 1], operations[x], m - lx);
        apply_mod_op(cnt[2 * x + 2], operations[x], rx - m);
        operations[x] = NO_OPERATION;
    }

    void build(string& s, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < s.length() && s[lx] == '1') cnt[x]++;
            return;
        }
        int m = (rx + lx) / 2;
        build(s, 2 * x + 1, lx, m);
        build(s, 2 * x + 2, m, rx);
        cnt[x] = calc_op(cnt[2 * x + 1], cnt[2 * x + 2]);
    }

    void build(string& s) {
        build(s, 0, 0, size);
    }

    void set(int l, int r, int v, int x, int lx, int rx) {
        propagate(x, lx, rx);
        if (l >= rx || r <= lx) return;
        if (lx >= l && rx <= r) {
            operations[x] = v;
            if (v == 1) cnt[x] = rx - lx;
            else cnt[x] = 0;
            return;
        }
        int m = (rx + lx) / 2;
        set(l, r, v, 2 * x + 1, lx, m);
        set(l, r, v, 2 * x + 2, m, rx);
        cnt[x] = calc_op(cnt[2 * x + 1], cnt[2 * x + 2]);
    }

    void set(int l, int r, int v) {
        set(l, r, v, 0, 0, size);
    }

    int count(int l, int r, int x, int lx, int rx) {
        propagate(x, lx, rx);
        if (l >= rx || r <= lx) return 0;
        if (lx >= l && rx <= r) return cnt[x];
        int m = (rx + lx) / 2;
        int cnt1 = count(l, r, 2 * x + 1, lx, m);
        int cnt2 = count(l, r, 2 * x + 2, m, rx);
        return calc_op(cnt1, cnt2);
    }

    int count(int l, int r) {
        return count(l, r, 0, 0, size);
    }

};

void solve() {
    // The key here was to start backwards
    int n, q; cin >> n >> q;
    string s, t; cin >> s >> t;
    segtree st;
    st.init(n);
    st.build(t);
    bool foo = true;
    vector<pair<int, int>> queries(q);
    forn(i, q) cin >> queries[i].f >> queries[i].s;
    reverse(all(queries));
    forn(i, q) {
        int l = queries[i].f, r = queries[i].s;
        l--; r--;
        int cnt = st.count(l, r + 1);
        if (r - l + 1 - cnt > cnt) st.set(l, r + 1, 0);
        else if (r - l + 1 - cnt < cnt) st.set(l, r + 1, 1);
        else foo = false;
    }
    if (!foo) {
        cout << "NO\n";
        return;
    }
    string cur = "";
    forn(i, n) {
        int one = st.count(i, i + 1);
        if (one == 1) cur += '1';
        else cur += '0';
    }
    if (cur != s) cout << "NO\n";
    else cout << "YES\n";
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
    cin >> t;
    cout << fixed << setprecision(12);
    while (t--) {
        // cout << "Case #" << x << ": ";
        solve();
        x++;
    }
    cerr << "Time Taken : " << (float)clock() / CLOCKS_PER_SEC << " secs" << endl;
}