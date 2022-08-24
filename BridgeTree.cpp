
struct BridgeTree {
    vector<int> adj[N], tree[N];
    vector<pii> bridges; bool vis[N];
    int Time = 0, n, m, dt[N], low[N], col[N];

    BridgeTree(int x, int y) {
        n = x, m = y;
        for (int i = 0; i < N; i++) vis[i] = dt[i] = col[i] = low[i] = 0;
    }

    void read() {
        for (int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }

    void findbriges(int u, int p) {
        low[u] = dt[u] = ++Time;
        for (auto v : adj[u]) {
            if (v == p) continue;
            if (dt[v]) low[u] = min(low[u], dt[v]);
            else {
                findbriges(v, u);
                if (dt[u] < low[v]) bridges.push_back(pii(u, v));
                low[u] = min(low[u], low[v]);
            }
        }
    }

    map<pii, bool> mp;
    void Color(int u, int p, int c) {
        vis[u] = true, col[u] = c;
        for (auto v : adj[u]) {
            if (vis[v] || mp[pii(u, v)]) continue;
            Color(v, u, c);
        }
    }

    int c = 0;
    void Treeform() {
        findbriges(1, 0);
        for (auto [u, v] : bridges) {
            mp[pii(u, v)] = true;
            mp[pii(v, u)] = true;
        }

        for (int i = 1; i <= n; i++) {
            if (!vis[i]) {
                Color(i, i, ++c);
            }
        }

        for (auto [x, y] : bridges) {
            tree[col[x]].push_back(col[y]);
            tree[col[y]].push_back(col[x]);
        }
    }
};
