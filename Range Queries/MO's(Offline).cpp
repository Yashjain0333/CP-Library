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

// Change BLOCK_SIZE
const int MXN = 3e5 + 5, BLOCK_SIZE = sqrt(MXN);

inline int64_t gilbertOrder(int x, int y, int pow, int rotate) {
    if (pow == 0) {
        return 0;
    }
    int hpow = 1 << (pow - 1);
    int seg = (x < hpow) ? ((y < hpow) ? 0 : 3) : ((y < hpow) ? 1 : 2);
    seg = (seg + rotate) & 3;
    const int rotateDelta[4] = {3, 0, 0, 1};
    int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
    int nrot = (rotate + rotateDelta[seg]) & 3;
    int64_t subSquareSize = int64_t(1) << (2 * pow - 2);
    int64_t ans = seg * subSquareSize;
    int64_t add = gilbertOrder(nx, ny, pow - 1, nrot);
    ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
    return ans;
}

struct Query {
    int l, r, idx;
    int64_t ord;

    inline void calcOrder() {
        ord = gilbertOrder(l, r, 21, 0);
    }
};

inline bool operator<(const Query &a, const Query &b) {
    return a.ord < b.ord;
}

int A[MXN], freq[MXN], counter[MXN];
int cur_freq = 0;

// Change this part according to the question
void operate(int idx, int delta) {
    int x = A[idx];
    counter[freq[x]]--;
    freq[x] += delta;
    counter[freq[x]]++;
    if (delta == 1) cur_freq = max(freq[x], cur_freq);
    else while (counter[cur_freq] == 0) cur_freq--;
}

void solve() {
    int n, m; cin >> n >> m;
    forn(i, n) cin >> A[i];
    vector<Query> q(m);
    forn(i, m) {
        cin >> q[i].l >> q[i].r;
        q[i].l--; q[i].r--;
        q[i].idx = i;
        q[i].calcOrder();
    }
    sort(all(q));
    vi res(m);
    int i = 0, j = -1;
    for (auto x : q) {
        int l = x.l, r = x.r, idx = x.idx;
        while (j < r) operate(++j, 1); // first increment and then remove
        while (i > l) operate(--i, 1);

        while (i < l) operate(i++, -1); // first remove and then increment
        while (j > r) operate(j--, -1);

        int tot = r - l + 1;
        res[idx] = max(1ll, 2 * cur_freq - tot);
    }
    for (auto x : res) cout << x << endl;
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