using Linear::lineLineIntscn;
struct DirLine {
  Pt p, v;
  Tf ang;
  DirLine() {}
  /// Directed line containing pt P in the direction v
  DirLine(Pt p, Pt v) : p(p), v(v) { ang = atan2(v.y, v.x); }
  bool operator<(const DirLine& u) const { return ang < u.ang; }
};
// returns true if pt p is on the ccw-left side of ray l
bool onLeft(DirLine l, Pt p) { return dcmp(crs(l.v, p-l.p)) >= 0; }
// Given a set of directed lines returns a polygon such that
// the polygon is the intersection by halfplanes created by the
// left side of the directed lines. MAY CONTAIN DUPLICATE ptS
int halfPlaneIntscn(vector<DirLine> &li, Poly &poly) {
  int n = li.size();
  sort(li.begin(), li.end());
  int first, last;
  Pt* p = new Pt[n];
  DirLine* q = new DirLine[n];
  q[first = last = 0] = li[0];
  for(int i = 1; i < n; i++) {
    while(first < last && !onLeft(li[i], p[last - 1])) last--;
    while(first < last && !onLeft(li[i], p[first])) first++;
    q[++last] = li[i];
    if(dcmp(crs(q[last].v, q[last-1].v)) == 0) {
      last--;
      if(onLeft(q[last], li[i].p)) q[last] = li[i];
    }
    if(first < last)
      lineLineIntscn(q[last - 1].p, q[last - 1].v, q[last].p, q[last].v, p[last - 1]);
  }
  while(first < last && !onLeft(q[first], p[last - 1])) last--;
  if(last - first <= 1) {
    delete[] p;
    delete[] q;
    poly.clear();
    return 0;
  }
  lineLineIntscn(q[last].p, q[last].v, q[first].p, q[first].v, p[last]);
  int m = 0;
  poly.resize(last - first + 1);
  for(int i = first; i <= last; i++) poly[m++] = p[i];
  delete[] p;
  delete[] q;
  return m;
}
