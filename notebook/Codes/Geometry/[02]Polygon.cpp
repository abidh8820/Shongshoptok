using Poly = vector<Pt>;
Tf signedPolyArea(Poly p) {
  Tf ret = 0;
  for(int i = 0; i < (int) p.size() - 1; i++)
    ret += crs(p[i]-p[0],  p[i+1]-p[0]);
  return ret / 2;
}
// given a polygon p of n vertices, generates the convex hull in ch
// in CCW && returns the number of vertices in the convex hull
int convexHull(Poly p, Poly &ch) {
  sort(p.begin(), p.end());
  int n = p.size();
  ch.resize(n + n);
  int m = 0;    // preparing lower hull
  for(int i = 0; i < n; i++) {
    while(m > 1 && dcmp(crs(ch[m - 1] - ch[m - 2], p[i] - ch[m - 1])) <= 0) m--;
    ch[m++] = p[i];
  }
  int k = m;    // preparing upper hull
  for(int i = n - 2; i >= 0; i--) {
    while(m > k && dcmp(crs(ch[m - 1] - ch[m - 2], p[i] - ch[m - 2])) <= 0) m--;
    ch[m++] = p[i];
  }
  if(n > 1) m--;
  ch.resize(m);
  return m;
}
// for a pt o and polygon p returns:
//   -1 if o is strictly inside p
//  0 if o is on a segs of p
//  1 if o is strictly outside p
// computes via winding numbers
int ptInPoly(Pt o, Poly p) {
  using Linear::onSeg;
  int wn = 0, n = p.size();
  for(int i = 0; i < n; i++) {
    int j = (i + 1) % n;
    if(onSeg(o, Seg(p[i], p[j])) || o == p[i]) return 0;
    int k = dcmp(crs(p[j] - p[i], o - p[i]));
    int d1 = dcmp(p[i].y - o.y);
    int d2 = dcmp(p[j].y - o.y);
    if(k > 0 && d1 <= 0 && d2 > 0) wn++;
    if(k < 0 && d2 <= 0 && d1 > 0) wn--;
  }
  return wn ? -1 : 1;
}
// returns the longest line segs of l that is inside or on the
// simply polygon p. O(n lg n). TESTED: TIMUS 1955
Tf longestSegInPoly(Line l, const Poly &p) {
  using Linear::lineLineIntscn;
  int n = p.size();
  vector<pair<Tf, int>> ev;
  for(int i=0; i<n; ++i) {
    Pt a = p[i], b = p[(i + 1) % n], z = p[(i - 1 + n) % n];
    int ora = ornt(l.a, l.b, a), orb = ornt(l.a, l.b, b), orz = ornt(l.a, l.b, z);
    if(!ora) {
      Tf d = dot(a - l.a, l.b - l.a);
      if(orz && orb) {
        if(orz != orb) ev.emplace_back(d, 0);
      }
      else if(orz) ev.emplace_back(d, orz);
      else if(orb) ev.emplace_back(d, orb);
    }
    else if(ora == -orb) {
      Pt ins;
      lineLineIntscn(l, Line(a, b), ins);
      ev.emplace_back(dot(ins - l.a, l.b - l.a), 0);
    }
  }
  sort(ev.begin(), ev.end());
  Tf ret = 0, cur = 0, pre = 0;
  bool active = false;
  int sign = 0;
  for(auto &qq : ev) {
    int tp = qq.second;
    Tf d = qq.first;
    if(sign) {
      cur += d - pre;
      ret = max(ret, cur);
      if(tp != sign) active = !active;
      sign = 0;
    }
    else {
      if(active) cur += d - pre, ret = max(ret, cur);
      if(tp == 0) active = !active;
      else sign = tp;
    }
    pre = d;
    if(!active) cur = 0;
  }
  ret /= len(l.b - l.a);
  return ret;
}
