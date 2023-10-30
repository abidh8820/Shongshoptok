const int N = 1000006;

using DT = LL;
using LT = LL;
constexpr DT I = 0;
constexpr LT None = 0;

DT val[4 * N];
LT lz[4 * N];
int L, R;
/*****************************************/
void apply(const LT &up, int l, int r, int u) {
  val[u] += (r - l + 1) * up;
  lz[u] += up;
}
void reset(int u) { lz[u] = None; }
void pull(int l, int r, int u) {
  val[u] = val[u << 1] + val[u << 1 | 1];
}
DT merge(const DT &a, const DT &b) { return a + b; }
DT get(int l, int r, int u) { return val[u]; }
/*****************************************/

void push(int l, int r, int u) {
  if (l == r) return;
  int m = l + r >> 1, lft = u << 1, ryt = lft | 1;
  apply(lz[u], l, m, lft);
  apply(lz[u], m + 1, r, ryt);
  reset(u);
}
void build(int l, int r, vector<DT> &v, int u = 1) {
  reset(u);
  if (l == r) {
    val[u] = v[l];
    return;
  }
  int m = l + r >> 1, lft = u << 1, ryt = lft | 1;
  build(l, m, v, lft);
  build(m + 1, r, v, ryt);
  pull(l, r, u);
}
void update(int ql, int qr, LT up, int l = L, int r = R, int u = 1) {
  if (ql > r or l > qr) return;
  if (ql <= l and r <= qr) {
    apply(up, l, r, u);
    return;
  }
  push(l, r, u);
  int m = l + r >> 1, lft = u << 1, ryt = lft | 1;
  update(ql, qr, up, l, m, lft);
  update(ql, qr, up, m + 1, r, ryt);
  pull(l, r, u);
}
DT query(int ql, int qr, int l = L, int r = R, int u = 1) {
  if (ql > r or l > qr) return I;
  if (ql <= l and r <= qr) return get(l, r, u);
  push(l, r, u);
  int m = l + r >> 1, lft = u << 1, ryt = lft | 1;
  DT ret1 = query(ql, qr, l, m, lft);
  DT ret2 = query(ql, qr, m + 1, r, ryt);
  return merge(ret1, ret2);
}
void init(int _L, int _R, vector<DT> &v) {
  L = _L, R = _R;
  build(L, R, v);
}
