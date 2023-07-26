struct state {
  int len, link;
  map<char, int> next;
};
state st[MAX];
int id, last;
string s;
ll ans[MAX];
void init() {
  for (int i = 0; i <= id; i++) {
    st[i].len = 0; st[i].link = 0;
    st[i].next.clear(); ans[i] = 0;
  }
  st[1].len = -1; st[1].link = 1;
  st[2].len = 0; st[2].link = 1;
  id = 2; last = 2;
}
void extend(int pos) {
  while (s[pos - st[last].len - 1] != s[pos]) last = st[last].link;
  int newlink = st[last].link;
  char c = s[pos];
  while (s[pos - st[newlink].len - 1] != s[pos]) newlink = st[newlink].link;
  if (!st[last].next.count(c)) {
    st[last].next[c] = ++id;
    st[id].len = st[last].len + 2;
    st[id].link = (st[id].len == 1 ? 2 : st[newlink].next[c]);
    ans[id] += ans[st[id].link];
    if (st[id].len > 2) {
      int l = st[id].len / 2 + (st[id].len % 2 ? 1 : 0);
      if (h.range_hash(pos - st[id].len + 1, pos - st[id].len + l) == h.reverse_hash(pos - st[id].len + 1, pos - st[id].len + l)) ans[id]++;
    }
  }
  last = st[last].next[c];
}
