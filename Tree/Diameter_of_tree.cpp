vector<vector<int>> adj(N + 1);
vector<int> par(N + 1);

pair<int, int> bfs(int v, int n, vector<int>& dist) {
    dist[v] = 0;
    queue<int> q;
    q.push(v);
    int res = 0;
    int l = v;
    while (!q.empty()) {
        int cur = q.front(); q.pop();
        for (int k : adj[cur]) {
            if (dist[k] > dist[cur] + 1) {
                dist[k] = dist[cur] + 1;
                if (res < dist[k]) {
                    res = dist[k];
                    l = k;
                }
                q.push(k);
                par[k] = cur;
            }
        }
    }
    return {l, res};
}