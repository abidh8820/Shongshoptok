const int N = 1e6 + 7;
template <typename DT>
struct Segtree {
  // write lazy segtree here
};
Segtree<int> tree(N);
vector<int> adj[N];
int depth[N], par[N], pos[N];
int head[N], heavy[N], cnt;

int dfs(int u, int p) {
  int SZ = 1, mxsz = 0, heavyc;
  depth[u] = depth[p] + 1;

  for (auto v : adj[u]) {
    if (v == p) continue;
    par[v] = u;
    int subsz = dfs(v, u);
    if (subsz > mxsz) heavy[u] = v, mxsz = subsz;
    SZ += subsz;
  }
  return SZ;
}
void decompose(int u, int h) {
  head[u] = h, pos[u] = ++cnt;
  if (heavy[u] != -1) decompose(heavy[u], h);

  for (int v : adj[u]) {
    if (v == par[u]) continue;
    if (v != heavy[u]) decompose(v, v);
  }
}
int query(int a, int b) {
  int ret = 0;
  for (; head[a] != head[b]; b = par[head[b]]) {
    if (depth[head[a]] > depth[head[b]]) swap(a, b);
    ret += tree.query(1, 0, cnt, pos[head[b]], pos[b]);
  }

  if (depth[a] > depth[b]) swap(a, b);
  ret += tree.query(1, 0, cnt, pos[a], pos[b]);
  return ret;
}
