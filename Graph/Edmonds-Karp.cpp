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

int n;
vector<vector<int>> capacity;

/*
The matrix capacity stores the capacity for every pair of vertices.
adj is the adjacency list of the undirected graph, since we have also to use the reversed of
directed edges when we are looking for augmenting paths.
*/

vector<vector<int>> adj;

int bfs(int src, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[src] = -2;
    queue<pair<int, int>> q;
    q.push({src, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (auto next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next] > 0) {
                parent[next] = cur;
                int newFlow = min(flow, capacity[cur][next]);
                if (next == t) return newFlow;
                q.push({next, newFlow});
            }
        }
    }

    return 0;
}

int maxFlow(int src, int t) { // s -> source  t -> sink
    int flow = 0;   // Will have the maxFlow at the end
    vector<int> parent(n);
    int newFlow;

    while (newFlow = bfs(src, t, parent)) {
        flow += newFlow;

        // Now backtrack the path found
        int cur = t;
        while (cur != src) {
            int prev = parent[cur];
            capacity[prev][cur] -= newFlow;
            capacity[cur][prev] += newFlow;
            cur = prev;
        }
    }

    return flow;
}

void solve() {
    int m; cin >> n >> m;
    capacity.clear(); adj.clear();
    capacity.resize(n); adj.resize(n);
    forn(i, n) capacity[i].assign(n, 0);
    forn(i, m) {
        int x, y, z; cin >> x >> y >> z; x--; y--;
        capacity[x][y] += z;
        capacity[y][x] += 0;
        adj[x].eb(y);
        adj[y].eb(x);
    }
    cout << maxFlow(0, n - 1);
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