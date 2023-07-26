struct lca_table {
  tree &T;
  int n, LOG = 20;
  vector<vector<int>> anc;
  vector<int> level;

  void setupLifting(int node, int par) {
    for (int v : T[node])
      if (v != par) {
        anc[v][0] = node, level[v] = level[node] + 1;
        for (int k = 1; k < LOG; k++) anc[v][k] = anc[anc[v][k - 1]][k - 1];
        setupLifting(v, node);
      }
  }
  lca_table(tree &T, int root = 0) : T(T), n(T.n) {
    LOG = 33 - __builtin_clz(n);
    anc.assign(n, vector<int>(LOG, root));
    level.resize(n);
    setupLifting(root, root);
  }
  int lca(int u, int v) {
    if (level[u] > level[v]) swap(u, v);
    for (int k = LOG - 1; ~k; k--)
      if (level[u] + (1 << k) <= level[v]) v = anc[v][k];
    if (u == v) return u;
    for (int k = LOG - 1; ~k; k--)
      if (anc[u][k] != anc[v][k]) u = anc[u][k], v = anc[v][k];
    return anc[u][0];
  }
  int getAncestor(int node, int ht) {
    for (int k = 0; k < LOG; k++)
      if (ht & (1 << k)) node = anc[node][k];
    return node;
  }
  int distance(int u, int v) {
    int g = lca(u, v);
    return level[u] + level[v] - 2 * level[g];
  }
};
struct euler_tour {
  int time = 0;
  tree &T;
  int n;
  vector<int> start, finish, level, par;
  euler_tour(tree &T, int root = 0)
      : T(T), n(T.n), start(n), finish(n), level(n), par(n) {
    time = 0;
    call(root);
  }
  void call(int node, int p = -1) {
    if (p != -1) level[node] = level[p] + 1;
    start[node] = time++;
    for (int e : T[node])
      if (e != p) call(e, node);
    par[node] = p;
    finish[node] = time++;
  }
  bool isAncestor(int node, int par) {
    return start[par] <= start[node] and finish[par] >= finish[node];
  }
  int subtreeSize(int node) { return finish[node] - start[node] + 1 >> 1; }
};
tree virtual_tree(vector<int> &nodes, lca_table &table, euler_tour &tour) {
  sort(nodes.begin(), nodes.end(),
       [&](int x, int y) { return tour.start[x] < tour.start[y]; });
  int n = nodes.size();
  for (int i = 0; i + 1 < n; i++)
    nodes.push_back(table.lca(nodes[i], nodes[i + 1]));
  sort(nodes.begin(), nodes.end());
  nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());
  sort(nodes.begin(), nodes.end(),
       [&](int x, int y) { return tour.start[x] < tour.start[y]; });
  n = nodes.size();
  stack<int> st;
  st.push(0);
  tree ans(n);
  for (int i = 1; i < n; i++) {
    while (!tour.isAncestor(nodes[i], nodes[st.top()])) st.pop();
    ans.addEdge(st.top(), i);
    st.push(i);
  }
  return ans;
}
set<int> getCenters(tree &T) {
  int n = T.n;
  vector<int> deg(n), q;
  set<int> s;
  for (int i = 0; i < n; i++) {
    deg[i] = T[i].size();
    if (deg[i] == 1) q.push_back(i);
    s.insert(i);
  }
  for (vector<int> t; s.size() > 2; q = t) {
    for (auto x : q) {
      for (auto e : T[x])
        if (--deg[e] == 1) t.push_back(e);
      s.erase(x);
    }
  }
  return s;
}
