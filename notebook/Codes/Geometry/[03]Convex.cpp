/// minkowski sum of two polygons in O(n)
Poly minkowskiSum(Poly A, Poly B) {
  int n = A.size(), m = B.size();
  rotate(A.begin(), min_element(A.begin(), A.end()), A.end());
  rotate(B.begin(), min_element(B.begin(), B.end()), B.end());
  A.push_back(A[0]);
  B.push_back(B[0]);
  for (int i = 0; i < n; i++) A[i] = A[i + 1] - A[i];
  for (int i = 0; i < m; i++) B[i] = B[i + 1] - B[i];
  Poly C(n + m + 1);
  C[0] = A.back() + B.back();
  merge(A.begin(), A.end() - 1, B.begin(), B.end() - 1, C.begin() + 1, polarComp(Pt(0, 0), Pt(0, -1)));
  for (int i = 1; i < C.size(); i++) C[i] = C[i] + C[i - 1];
  C.pop_back();
  return C;
}
void rotatingCalipersGetRectangle(Pt* p, int n, Tf& area, Tf& perimeter) {
  using Linear::disPtLine;
  p[n] = p[0];
  int l = 1, r = 1, j = 1;
  area = perimeter = 1e100;
  for(int i = 0; i < n; i++) {
    Pt v = (p[i + 1] - p[i]) / len(p[i + 1] - p[i]);
    while(dcmp(dot(v, p[r % n] - p[i]) - dot(v, p[(r + 1) % n] - p[i])) < 0) r++;
    while(j < r || dcmp(crs(v, p[j % n] - p[i]) - crs(v, p[(j + 1) % n] - p[i])) < 0) j++;
    while(l < j || dcmp(dot(v, p[l % n] - p[i]) - dot(v, p[(l + 1) % n] - p[i])) > 0) l++;
    Tf w = dot(v, p[r % n] - p[i]) - dot(v, p[l % n] - p[i]);
    Tf h = disPtLine(p[j % n], Line(p[i], p[i + 1]));
    area = min(area, w * h);
    perimeter = min(perimeter, 2 * w + 2 * h);
  }
}
// returns the left side of polygon u after cutting it by ray a->b
Poly cutPoly(Poly u, Pt a, Pt b) {
  using Linear::lineLineIntscn, Linear::onSeg;
  Poly ret;
  int n = u.size();
  for(int i = 0; i < n; i++) {
    Pt c = u[i], d = u[(i + 1) % n];
    if(dcmp(crs(b-a, c-a)) >= 0) ret.push_back(c);
    if(dcmp(crs(b-a, d-c)) != 0) {
      Pt t;
      lineLineIntscn(a, b - a, c, d - c, t);
      if(onSeg(t, Seg(c, d))) ret.push_back(t);
    }
  }
  return ret;
}
// returns true if pt p is in or on tri abc
bool ptInTri(Pt a, Pt b, Pt c, Pt p) {
  return dcmp(crs(b - a, p - a)) >= 0 && dcmp(crs(c - b, p - b)) >= 0 && dcmp(crs(a - c, p - c)) >= 0;
}
// pt must be in ccw order with no three collinear pts
// returns inside = -1, on = 0, outside = 1
int ptInConvexPoly(const Poly &pt, Pt p) {
  int n = pt.size();
  assert(n >= 3);
  int lo = 1, hi = n - 1;
  while(hi - lo > 1) {
    int mid = (lo + hi) / 2;
    if(dcmp(crs(pt[mid] - pt[0], p - pt[0])) > 0) lo = mid;
    else  hi = mid;
  }
  bool in = ptInTri(pt[0], pt[lo], pt[hi], p);
  if(!in) return 1;
  if(dcmp(crs(pt[lo] - pt[lo - 1], p - pt[lo - 1])) == 0) return 0;
  if(dcmp(crs(pt[hi] - pt[lo], p - pt[lo])) == 0) return 0;
  if(dcmp(crs(pt[hi] - pt[(hi + 1) % n], p - pt[(hi + 1) % n])) == 0) return 0;
  return -1;
}
// Extreme Pt for a direction is the farthest pt in that direction
// poly is a convex polygon, sorted in CCW, doesn't contain redundant pts
// u is the direction for extremeness
int extremePt(const Poly &poly, Pt u = Pt(0, 1)) {
  int n = (int) poly.size();
  int a = 0, b = n;
  while(b - a > 1) {
    int c = (a + b) / 2;
    if(dcmp(dot(poly[c] - poly[(c + 1) % n], u)) >= 0 && dcmp(dot(poly[c] - poly[(c - 1 + n) % n], u)) >= 0) {
      return c;
    }
    bool a_up = dcmp(dot(poly[(a + 1) % n] - poly[a], u)) >= 0;
    bool c_up = dcmp(dot(poly[(c + 1) % n] - poly[c], u)) >= 0;
    bool a_above_c = dcmp(dot(poly[a] - poly[c], u)) > 0;
    if(a_up && !c_up) b = c;
    else if(!a_up && c_up) a = c;
    else if(a_up && c_up) {
      if(a_above_c) b = c;
      else a = c;
    }
    else {
      if(!a_above_c) b = c;
      else a = c;
    }
  }
  if(dcmp(dot(poly[a] - poly[(a + 1) % n], u)) > 0 && dcmp(dot(poly[a] - poly[(a - 1 + n) % n], u)) > 0)
    return a;
  return b % n;
}
// For a convex polygon p and a line l, returns a list of segss
// of p that are touch or intersect line l.
// the i'th segs is considered (p[i], p[(i + 1) modulo |p|])
// #1 If a segs is collinear with the line, only that is returned
// #2 Else if l goes through i'th pt, the i'th segs is added
// If there are 2 or more such collinear segss for #1,
// any of them (only one, not all) should be returned (not tested)
// Complexity: O(lg |p|)
vector<int> lineConvexPolyIntscn(const Poly &p, Line l) {
  assert((int) p.size() >= 3);
  assert(l.a != l.b);

  int n = p.size();
  vector<int> ret;

  Pt v = l.b - l.a;
  int lf = extremePt(p, rotate90(v));
  int rt = extremePt(p, rotate90(v) * Ti(-1));
  int olf = ornt(l.a, l.b, p[lf]);
  int ort = ornt(l.a, l.b, p[rt]);

  if(!olf || !ort) {
    int idx = (!olf ? lf : rt);
    if(ornt(l.a, l.b, p[(idx - 1 + n) % n]) == 0)
      ret.push_back((idx - 1 + n) % n);
    else  ret.push_back(idx);
    return ret;
  }
  if(olf == ort) return ret;
  for(int i=0; i<2; ++i) {
    int lo = i ? rt : lf;
    int hi = i ? lf : rt;
    int olo = i ? ort : olf;

    while(true) {
      int gap = (hi - lo + n) % n;
      if(gap < 2) break;
      int mid = (lo + gap / 2) % n;
      int omid = ornt(l.a, l.b, p[mid]);
      if(!omid) {
        lo = mid;
        break;
      }
      if(omid == olo) lo = mid;
      else hi = mid;
    }
    ret.push_back(lo);
  }
  return ret;
}
// Calculate [ACW, CW] tangent pair from an external pt
constexpr int CW = -1, ACW = 1;
bool isGood(Pt u, Pt v, Pt Q, int dir) { return ornt(Q, u, v) != -dir; }
Pt better(Pt u, Pt v, Pt Q, int dir) { return ornt(Q, u, v) == dir ? u : v; }
Pt ptPolyTng(const Poly &pt, Pt Q, int dir, int lo, int hi) {
  while(hi - lo > 1) {
    int mid = (lo + hi) / 2;
    bool pvs = isGood(pt[mid], pt[mid - 1], Q, dir);
    bool nxt = isGood(pt[mid], pt[mid + 1], Q, dir);
    if(pvs && nxt) return pt[mid];
    if(!(pvs || nxt)) {
      Pt p1 = ptPolyTng(pt, Q, dir, mid + 1, hi);
      Pt p2 = ptPolyTng(pt, Q, dir, lo, mid - 1);
      return better(p1, p2, Q, dir);
    }
    if(!pvs) {
      if(ornt(Q, pt[mid], pt[lo]) == dir)         hi = mid - 1;
      else if(better(pt[lo], pt[hi], Q, dir) == pt[lo])   hi = mid - 1;
      else  lo = mid + 1;
    }
    if(!nxt) {
      if(ornt(Q, pt[mid], pt[lo]) == dir)         lo = mid + 1;
      else if(better(pt[lo], pt[hi], Q, dir) == pt[lo])   hi = mid - 1;
      else  lo = mid + 1;
    }
  }

  Pt ret = pt[lo];
  for(int i = lo + 1; i <= hi; i++) ret = better(ret, pt[i], Q, dir);
  return ret;
}
// [ACW, CW] Tng
pair<Pt, Pt> ptPolyTngs(const Poly &pt, Pt Q) {
  int n = pt.size();
  Pt acw_tan = ptPolyTng(pt, Q, ACW, 0, n - 1);
  Pt cw_tan = ptPolyTng(pt, Q, CW, 0, n - 1);
  return make_pair(acw_tan, cw_tan);
}
