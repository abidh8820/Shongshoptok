struct node {
  int val;
  node *lft, *rt;
  node() {}
  node(int val = 0) : val(val), lft(NULL), rt(NULL) {}
};

struct implicit_segtree {
  node *root;
  implicit_segtree() {}
  implicit_segtree(int n) {
    root = new node(n);
  }
  void update(node *now, int L, int R, int idx, int val) {
    if (L == R) {
      now -> val += val;
      return;
    }
    int mid = L + (R - L) / 2;
    if (now->lft == NULL) now->lft = new node(mid - L + 1);
    if (now->rt == NULL) now->rt = new node(R - mid);
    if (idx <= mid) update(now->lft, L, mid, idx, val);
    else update(now->rt, mid + 1, R, idx, val);
    now->val = (now->lft)->val + (now->rt)->val;
  }

  int query(node *now, int L, int R, int k) {
    if (L == R) return L;
    int mid = L + (R - L) / 2;
    if (now->lft == NULL) now->lft = new node(mid - L + 1);
    if (now->rt == NULL) now->rt = new node(R - mid);
    if (k <= (now->lft)->val) return query(now->lft, L, mid, k);
    else return query(now->rt, mid + 1, R, k - (now->lft)->val);
  }
};
