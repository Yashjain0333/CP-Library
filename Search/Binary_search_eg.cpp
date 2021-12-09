//BY: YASH JAIN, CF: yashjain0333
#include <bits/stdc++.h>
using namespace std;
#define May_the_fork_be_with_you ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define all(x) (x).begin(), (x).end()
#define rall(v) v.rbegin(),v.rend()
#define deb(x) cout<<#x<<": "<<x<<endl;
#define MOD 1000000007
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
ll gcd(ll a, ll b) {if (!b)return a; return gcd(b, a % b);}
ll power(ll x, ll y, ll p = INF) {ll res = 1; x %= p; while (y > 0) {if (y & 1)res = (res * x) % p; y = y >> 1; x = (x * x) % p;} return res;}

void solve() {
    int n; cin >> n;
    vector<int> res;
    res.eb(n);
    int cnt = 1;
    while (cnt < n) {
        int l = cnt, r = n + 1;
        while (l < r) {
            int mid = l + (r - l) / 2;
            if (n / mid == n / cnt) l = mid + 1;
            else r = mid;
        }
        res.eb(n / l);
        cnt = l;
    }
    sort(all(res));
    if (res[0] != 0) {
        res.eb(0);
        sort(all(res));
    }
    cout << res.size() << endl;
    for (auto x : res) cout << x << " ";
    cout << endl;
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
    cin >> t;
    cout << fixed << setprecision(12);
    while (t--) {
        solve();
    }

    cerr << "Time Taken : " << (float)clock() / CLOCKS_PER_SEC << " secs" << endl;
}