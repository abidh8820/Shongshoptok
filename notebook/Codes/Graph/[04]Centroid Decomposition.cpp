class Centroid_Decomposition {
  vector<bool> blocked;
  vector<int> CompSize;
  int CompDFS(tree &T, int node, int par) {
    CompSize[node] = 1;
    for (int &e : T[node])
      if (e != par and !blocked[e]) CompSize[node] += CompDFS(T, e, node);
    return CompSize[node];
  }
  int FindCentroid(tree &T, int node, int par, int sz) {
    for (int &e : T[node])
      if (e != par and !blocked[e])
        if (CompSize[e] > sz / 2) return FindCentroid(T, e, node, sz);
    return node;
  }
  pair<int, int> GetCentroid(tree &T, int entry) {
    int sz = CompDFS(T, entry, entry);
    return {FindCentroid(T, entry, entry, sz), sz};
  }
  c_vector<LL> left[2], right[2];
  int GMin, GMax;
  void dfs(tree &T, int node, int par, int Min, int Max, int sum) {
    if (blocked[node]) return;
    right[Max < sum or Min > sum][sum]++;
    Max = max(Max, sum), Min = min(Min, sum);
    GMin = min(GMin, sum), GMax = max(GMax, sum);
    for (int i = 0; i < T[node].size(); i++)
      if (T[node][i] != par) {
        dfs(T, T[node][i], node, Min, Max, sum + T.col[node][i]);
      }
  }
  LL solve(tree &T, int c, int sz) {
    LL ans = 0;
    left[0].clear(-sz, sz), left[1].clear(-sz, sz);
    for (int i = 0; i < T[c].size(); i++) {
      GMin = 1, GMax = -1;
      dfs(T, T[c][i], c, GMin, GMax, T.col[c][i]);
      ans += right[0][0] + left[1][0] * right[1][0];
      for (int j : {0, 1})
        for (int k = GMin; k <= GMax; k++) {
          ans += right[j][k] * (left[0][-k] + (j == 0) * left[1][-k]);
        }
      for (int j : {0, 1})
        for (int k = GMin; k <= GMax; k++) {
          left[j][k] += right[j][k];
          right[j][k] = 0;
        }
    }
    return ans;
  }

 public:
  LL operator()(tree &T, int entry) {
    blocked.resize(T.n);
    CompSize.resize(T.n);
    for (int i : {0, 1})
      left[i].resize(2 * T.n + 5), right[i].resize(2 * T.n + 5);
    auto [c, sz] = GetCentroid(T, entry);
    LL ans = solve(T, c, sz);
    blocked[c] = true;
    for (int e : T[c])
      if (!blocked[e]) ans += (*this)(T, e);
    return ans;
  }
};
