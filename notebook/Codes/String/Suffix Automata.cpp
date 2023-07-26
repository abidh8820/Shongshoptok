const int MAXN = 1e5 + 7, ALPHA = 26;
int len[2 * MAXN], link[2 * MAXN], nxt[2 * MAXN][ALPHA];
int sz;
int last;

void sa_init() {
  memset(nxt, -1, sizeof nxt);
  len[0] = 0, link[0] = -1, sz = 1, last = 0;
}

void add(char ch) {
  int c = ch - 'a';
  int cur = sz++;
  len[cur] = len[last] + 1;

  int u = last;
  while (u != -1 && nxt[u][c] == -1) {
    nxt[u][c] = cur;
    u = link[u];
  }

  if (u == -1) link[cur] = 0;
  else {
    int v = nxt[u][c];
    if (len[v] == len[u] + 1) link[cur] = v;
    else {
      int clone = sz++;
      len[clone] = 1 + len[u], link[clone] = link[v];

      for (int i = 0; i < ALPHA; i++) nxt[clone][i] = nxt[v][i];

      while (u != -1 && nxt[u][c] == v) {
        nxt[u][c] = clone;
        u = link[u];
      }
      link[v] = link[cur] = clone;
    }
  }
  last = cur;
}

vector<int> edge[2 * MAXN];
/// Optional, Call after adding all characters
void makeEdge() {
  for (int i = 0; i < sz; i++) {
    edge[i].clear();
    for (int j = 0; j < ALPHA; j++)
      if (nxt[i][j] != -1) edge[i].push_back(j);
  }
}
// Given a string S, you have to answer some queries:
// If all distinct substrings of string S were sorted
// lexicographically, which one will be the K-th smallest?

long long dp[2 * MAXN];
bool vis[2 * MAXN];

void dfs(int u) {
  if (vis[u]) return;
  vis[u] = 1;
  dp[u] = 1;
  for (int i : edge[u]) {
    if (nxt[u][i] == -1) continue;
    dfs(nxt[u][i]);
    dp[u] += dp[nxt[u][i]];
  }
}

void go(int u, long long rem, string &s) {
  if (rem == 1) return;
  long long sum = 1;
  for (int i : edge[u]) {
    if (nxt[u][i] == -1) continue;
    if (sum + dp[nxt[u][i]] < rem) {
      sum += dp[nxt[u][i]];
    } else {
      s += ('a' + i);
      go(nxt[u][i], rem - sum, s);
      return;
    }
  }
}
