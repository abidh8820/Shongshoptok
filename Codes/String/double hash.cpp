ostream& operator << (ostream& os, PLL hash) {
  return os << "(" << hash.ff << ", " << hash.ss << ")";
}

PLL operator + (PLL a, LL x)     {return PLL(a.ff + x, a.ss + x);}
PLL operator - (PLL a, LL x)     {return PLL(a.ff - x, a.ss - x);}
PLL operator * (PLL a, LL x)     {return PLL(a.ff * x, a.ss * x);}
PLL operator + (PLL a, PLL x)    {return PLL(a.ff + x.ff, a.ss + x.ss);}
PLL operator - (PLL a, PLL x)    {return PLL(a.ff - x.ff, a.ss - x.ss);}
PLL operator * (PLL a, PLL x)    {return PLL(a.ff * x.ff, a.ss * x.ss);}
PLL operator % (PLL a, PLL m)    {return PLL(a.ff % m.ff, a.ss % m.ss);}

PLL base(1949313259, 1997293877);
PLL mod(2091573227, 2117566807);

PLL power (PLL a, LL p) {
  if (!p) return PLL(1, 1);
  PLL ans = power(a, p / 2);
  ans = (ans * ans) % mod;
  if (p % 2) ans = (ans * a) % mod;
  return ans;
}

PLL inverse(PLL a) {
  return power(a, (mod.ff - 1) * (mod.ss - 1) - 1);
}
PLL inv_base = inverse(base);

PLL val;
vector<PLL> P;

void hash_init(int n) {
  P.resize(n + 1);
  P[0] = PLL(1, 1);
  for (int i = 1; i <= n; i++) P[i] = (P[i - 1] * base) % mod;
}

///appends c to string
PLL append(PLL cur, char c) {
  return (cur * base + c) % mod;
}

///prepends c to string with size k
PLL prepend(PLL cur, int k, char c) {
  return (P[k] * c + cur) % mod;
}

///replaces the i-th (0-indexed) character from right from a to b;
PLL replace(PLL cur, int i, char a, char b) {
  cur = (cur + P[i] * (b - a)) % mod;
  return (cur + mod) % mod;
}

///Erases c from the back of the string
PLL pop_back(PLL hash, char c) {
  return (((hash - c) * inv_base) % mod + mod) % mod;
}

///Erases c from front of the string with size len
PLL pop_front(PLL hash, int len, char c) {
  return ((hash - P[len - 1] * c) % mod + mod) % mod;
}
///concatenates two strings where length of the right is k
PLL concat(PLL left, PLL right, int k) {
  return (left * P[k] + right) % mod;
}
///Calculates hash of string with size len repeated cnt times
///This is O(log n). For O(1), pre-calculate inverses
PLL repeat(PLL hash, int len, LL cnt) {
  PLL mul = (P[len * cnt] - 1) * inverse(P[len] - 1);
  mul = (mul % mod + mod) % mod;
  PLL ret = (hash * mul) % mod;

  if (P[len].ff == 1) ret.ff = hash.ff * cnt;
  if (P[len].ss == 1) ret.ss = hash.ss * cnt;
  return ret;
}
LL get(PLL hash) {
  return ( (hash.ff << 32) ^ hash.ss );
}
struct hashlist {
  int len;
  vector<PLL> H, R;

  hashlist() {}
  hashlist(string &s) {
    len = (int)s.size();
    hash_init(len);
    H.resize(len + 1, PLL(0, 0)), R.resize(len + 2, PLL(0, 0));
    for (int i = 1; i <= len; i++) H[i] = append(H[i - 1], s[i - 1]);
    for (int i = len; i >= 1; i--) R[i] = append(R[i + 1], s[i - 1]);
  }
  
  /// 1-indexed
  inline PLL range_hash(int l, int r) {
    int len = r - l + 1;
    return ((H[r] - H[l - 1] * P[len]) % mod + mod) % mod;
  }

  inline PLL reverse_hash(int l, int r) {
    int len = r - l + 1;
    return ((R[l] - R[r + 1] * P[len]) % mod + mod) % mod;
  }

  inline PLL concat_range_hash(int l1, int r1, int l2, int r2) {
    int len_2 = r2 - l2 + 1;
    return concat(range_hash(l1, r1), range_hash(l2, r2), len_2);
  }

  inline PLL concat_reverse_hash(int l1, int r1, int l2, int r2) {
    int len_1 = r1 - l1 + 1;
    return concat(reverse_hash(l2, r2), reverse_hash(l1, r1), len_1);
  }
};