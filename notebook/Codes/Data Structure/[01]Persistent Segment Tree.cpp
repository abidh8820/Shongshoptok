struct Node {
  Node *l, *r;
  int sum;

  Node(int val) : l(nullptr), r(nullptr), sum(val) {}
  Node(Node* l, Node* r) : l(l), r(r), sum(0) {
    if (l) sum += l->sum;
    if (r) sum += r->sum;
  }
};

int a[MAXN];
Node* root[MAXN];

Node* Build(int bg, int ed) {
  if (bg == ed) return new Node(a[bg]);
  int mid = (bg + ed) / 2;
  return new Node(Build(bg, mid), Build(mid + 1, ed));
}

int Query(Node* v, int bg, int ed, int l, int r) {
  if (l > ed || r < bg) return 0;
  if (l <= bg && ed <= r) return v->sum;
  int mid = (bg + ed) / 2;
  return Query(v->l, bg, mid, l, r) + Query(v->r, mid + 1, ed, l, r);
}

Node* Update(Node* v, int bg, int ed, int pos, int new_val) {
  if (bg == ed) return new Node(v->sum + new_val);
  int mid = (bg + ed) / 2;
  if (pos <= mid)
    return new Node(Update(v->l, bg, mid, pos, new_val), v->r);
  else
    return new Node(v->l, Update(v->r, mid + 1, ed, pos, new_val));
}
