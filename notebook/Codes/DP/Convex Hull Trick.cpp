#include <bits/stdc++.h>
using namespace std;

using LL = long long;

const int N = 3e5 + 9;
const int M = 1e9 + 7;

struct CHT {
  vector<LL> m, b;
  int ptr = 0;

  bool bad(int l1, int l2, int l3) {
    return 1.0 * (b[l3] - b[l1]) * (m[l1] - m[l2]) <= 1.0 * (b[l2] - b[l1]) * (m[l1] - m[l3]);  //(slope dec+query min),(slope inc+query max)
    return 1.0 * (b[l3] - b[l1]) * (m[l1] - m[l2]) > 1.0 * (b[l2] - b[l1]) * (m[l1] - m[l3]);  //(slope dec+query max), (slope inc+query min)
  }

  void add(LL _m, LL _b) {
    m.push_back(_m);
    b.push_back(_b);
    int s = m.size();
    while (s >= 3 && bad(s - 3, s - 2, s - 1)) {
      s--;
      m.erase(m.end() - 2);
      b.erase(b.end() - 2);
    }
  }

  LL f(int i, LL x) { return m[i] * x + b[i]; }

  //(slope dec+query min), (slope inc+query max) -> x increasing
  //(slope dec+query max), (slope inc+query min) -> x decreasing
 
  LL query(LL x) {
    if (ptr >= m.size()) ptr = m.size() - 1;
    while (ptr < m.size() - 1 && f(ptr + 1, x) < f(ptr, x)) ptr++;
    return f(ptr, x);
  }

  LL bs(int l, int r, LL x) {
    int mid = (l + r) / 2;
    if (mid + 1 < m.size() && f(mid + 1, x) < f(mid, x)) return bs(mid + 1, r, x);  // > for max
    if (mid - 1 >= 0 && f(mid - 1, x) < f(mid, x)) return bs(l, mid - 1, x);  // > for max
    return f(mid, x);
  }
};
