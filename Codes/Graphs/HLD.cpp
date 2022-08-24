const int N = 1e6+7;
template <typename DT>
struct Segtree {
    vector<DT> tree, prob, a;
    Segtree(int n) {
        tree.resize(n * 4);
        prob.resize(n), a.resize(n);
    }
    void build(int u, int l, int r) {
        if (l == r) {
            tree[u] = a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(u * 2, l, mid);
        build(u * 2 + 1, mid + 1, r);
        tree[u] = (tree[u * 2] + tree[u * 2 + 1]);
    }
    void propagate(int u) {
        prob[u * 2] += prob[u], tree[u * 2] += prob[u];
        prob[u * 2 + 1] += prob[u], tree[u * 2 + 1] += prob[u];
        prob[u] = 0;
    }
    void update(int u, int l, int r, int i, int j, int val) {
        if (r < i || l > j) return;
        if (l >= i && r <= j) {
            tree[u] = val;
            return;
        }
        int mid = (l + r) / 2;
        update(u * 2, l, mid, i, j, val);
        update(u * 2 + 1, mid + 1, r, i, j, val);
        tree[u] = (tree[u * 2] + tree[u * 2 + 1]);
    }
    DT query(int u, int l, int r, int i, int j) {
        if (l > j || r < i) return 0;
        if (l >= i && r <= j) return tree[u];
        int mid = (l + r) / 2;
        return (query(u * 2, l, mid, i, j) +  query(u * 2 + 1, mid + 1, r, i, j));
    }
};
Segtree<int>tree(N);
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
    if(heavy[u]!=-1) decompose(heavy[u], h);

    for(int v : adj[u]) {
        if(v==par[u]) continue;
        if(v!=heavy[u]) decompose(v, v);
    }
}
int query(int a, int b) {
    int ret = 0;
    for(;head[a]!=head[b]; b=par[head[b]]){
       if(depth[head[a]]>depth[head[b]])  swap(a,b);
       ret += tree.query(1, 0, cnt, pos[head[b]], pos[b]);
    }

    if(depth[a]>depth[b])  swap(a,b);
    ret += tree.query(1,0,cnt,pos[a],pos[b]);
    return ret;
}