vector<vector<int>> components;
vector<int> depth, low;
stack<int> st;
vector<int> id;
vector<edge> bridges;
graph tree;
void find_bridges(int node, graph &G, int par = -1, int d = 0) {
  low[node] = depth[node] = d;
  st.push(node);
  for (int id : G[node]) {
    int to = G(id).to(node);
    if (par != to) {
      if (depth[to] == -1) {
        find_bridges(to, G, node, d + 1);
        if (low[to] > depth[node]) {
          bridges.emplace_back(node, to);
          components.push_back({});
          for (int x = -1; x != to; x = st.top(), st.pop())
            components.back().push_back(st.top());
        }
      }
      low[node] = min(low[node], low[to]);
    }
  }
  if (par == -1) {
    components.push_back({});
    while (!st.empty()) components.back().push_back(st.top()), st.pop();
  }
}
graph &create_tree() {
  for (auto &comp : components) {
    int idx = tree.addNode();
    for (auto &e : comp) id[e] = idx;
  }
  for (auto &[l, r] : bridges) tree.addEdge(id[l], id[r]);
  return tree;
}
void init(graph &G) {
  int n = G.n;
  depth.assign(n, -1), id.assign(n, -1), low.resize(n);
  for (int i = 0; i < n; i++)
    if (depth[i] == -1) find_bridges(i, G);
}
