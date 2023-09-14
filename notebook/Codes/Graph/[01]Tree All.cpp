using Tree = Graph;
namespace talgo {
int time;
void dfs(int u, int p, vec &par, vec &lvl, Tree &T) {
  for (int e : T[u]) {
    int v = T(e).to(u);
    if (v == p) continue;
    par[v] = u, lvl[v] = lvl[u] + 1;
    dfs(v, u, par, lvl, T);
  }
}

mat ancestorTable(vec &par) {
  int n = par.size(), sz = __lg(n) + 1;
  mat anc(sz, par);

  for (int k = 1; k < sz; k++) {
    for (int i = 0; i < n; i++) {
      anc[k][i] = anc[k - 1][anc[k - 1][i]];
    }
  }
  return anc;
}

int getAncestor(int u, int ht, mat &anc) {
  int sz = anc.size();

  for (int k = 0; k < sz; k++) {
    if (ht >> k & 1) u = anc[u][k];
  }
  return u;
}

bool isAncestor(int u, int par, vec &st, vec &en) {
  return st[par] <= st[u] and en[par] >= en[u];
}
int subtreeSize(int u, vec &st, vec &en) { return en[u] - st[u] + 1 >> 1; }

int lca(int u, int v, vec &lvl, mat &anc) {
  if (lvl[u] > lvl[v]) swap(u, v);

  for (int k = anc.size() - 1; ~k; k--) {
    if (lvl[u] + (1 << k) <= lvl[v]) v = anc[k][v];
  }
  if (u == v) return u;

  for (int k = anc.size() - 1; ~k; k--) {
    if (anc[k][u] != anc[k][v]) u = anc[k][u], v = anc[k][v];
  }
  return anc[0][u];
}

int dis(int u, int v, vec &lvl, mat &anc) {
  int g = lca(u, v, lvl, anc);
  return lvl[u] + lvl[v] - 2 * lvl[g];
}
}

namespace ct {
int getCentroid(int u, int p, int st, vec &sz, vec &blk, Tree &T) {
  for (int e : T[u]) {
    int v = T(e).to(u);
    if (v == p or blk[v] or sz[v] * 2 <= sz[st]) continue;
    return getCentroid(v, u, st, sz, blk, T);
  }
  return u;
}
int compCalc(int u, int p, vec &sz, vec &blk, Tree &T) {
  sz[u] = 1;
  for (int e : T[u]) {
    int v = T(e).to(u);
    if (v == p or blk[v]) continue;
    sz[u] += compCalc(v, u, sz, blk, T);
  }
  return sz[u];
}

int decompose(int u, int p, vec &sz, vec &blk, Tree &T, Tree &CT) {
  compCalc(u, -1, sz, blk, T);
  u = getCentroid(u, -1, u, sz, blk, T);
  blk[u] = 1;
  for (int e : T[u]) {
    int v = T(e).to(u);
    if (blk[v]) continue;
    v = decompose(v, u, sz, blk, T, CT);
    CT.addEdge(u, v);
  }
  return u;
}
int getCentroidTree(int root, Tree &T, Tree &CT) {
  vec sz(T.n), blk(T.n);
  return decompose(root, -1, sz, blk, T, CT);
}
} 

