//BY: YASH JAIN, CF: yashjain0333
#include <bits/stdc++.h>
using namespace std;
#define May_the_fork_be_with_you ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define all(x) (x).begin(), (x).end()
#define deb(x) cout<<#x<<": "<<x<<endl;
#define MOD 1000000007
#define INF 1e18
#define pi 3.14159265358979323846
#define ll long long
#define f first
#define s second
#define pb push_back
#define eb emplace_back
#define endl "\n"
// #define int long long
#define N 100005

int at[N], last[N], par[N], group[N], lider[N];
char str[N];
// Inititally last will have all zeros

int inline find (int u) {
    return (u == par[u] ? u : find(par[u]));
}

void inline unionset (int x, int y) {
    int u = find(x), v = find(y);
    if (u == v) return;
    // always make 1st node/group as the parent
    par[v] = u;
}

void solve() {
    int n, m; cin >> n >> m;
    int cnt = 1, res = 0;

    // Going row by row and keeping a track of the previous row
    for (int i = 0; i < n; i++) {

        string s; cin >> s;

        for (int j = 0; j < m; j += 4) {
            char ch = s[j / 4];
            bitset<4> b;
            if (ch >= 'A') b = bitset<4>(ch - 'A' + 10);
            else b = bitset<4>(ch - '0');
            string cur = b.to_string();

            for (int k = j; k < j + 4; k++) {
                if (cur[k - j] == '1')
                    at[k] = 1;
                else at[k] = 0;
            }
        }

        for (int k = m; k < 2 * m; k++) par[k] = k;

        if (at[0]) res++;
        for (int j = 1; j < m; j++) {
            if (!at[j]) continue;
            res++;
            if (at[j] && at[j - 1]) {
                unionset (j + m, j - 1 + m);
                res--;
            }
        }

        for (int j = 0; j < m; j++) {
            if (last[j] == 1 && at[j] == 1 && find(j) != find(j + m)) {
                res--;
                unionset(j, j + m);
            }
            last[j] = at[j];
        }

        // Make 2*m groups
        for (int j = 0; j < 2 * m; j++) group[j] = -1;

        for (int j = 0; j < m; j++) {
            int x = find(j + m);
            if (group[x] == -1) {
                lider[j] = j;
                group[x] = j;
            }
            else lider[j] = group[x];
        }

        for (int j = 0; j < m; j++) par[j] = j;

        for (int j = 0; j < m; j++)
            unionset (j, lider[j]);
    }
    cout << res;
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
    // cin >> t;
    cout << fixed << setprecision(12);
    while (t--) {
        solve();
    }

    cerr << "Time Taken : " << (float)clock() / CLOCKS_PER_SEC << " secs" << endl;
}