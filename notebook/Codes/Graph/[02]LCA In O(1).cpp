int st[N], lvl[N];
int tbl[B][2 * N];
int tt = 0;

void dfs(int u, int p, Tree &T) {
  st[u] = tt;
  tbl[0][tt++] = u;
  for (int v : T[u]) {
    if (v == p) continue;
    lvl[v] = lvl[u] + 1;
    dfs(v, u, T);
    tbl[0][tt++] = u;
  }
}
int low(int u, int v) {
  return make_pair(lvl[u], u) < make_pair(lvl[v], v) ? u : v;
}

void makeTable(int n) {
  int m = 2 * n - 1;
  for (int b = 1; b < B; b++) {
    for (int i = 0; i < m; i++) {
      tbl[b][i] = low(tbl[b - 1][i], tbl[b - 1][i + (1 << b - 1)]);
    }
  }
}

int lca(int u, int v) {
  int l = st[u], r = st[v];
  if (l > r) swap(l, r);
  int k = __lg(r - l + 1);
  return low(tbl[k][l], tbl[k][r - (1 << k) + 1]);
}
void init(int root, Tree &T) {
  lvl[root] = 0;
  dfs(root, root, T);
  makeTable(T.size());
}
