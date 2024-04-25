// returns true if pt p is on segs s
bool onSeg(Pt p, Seg s) {
  return dcmp(crs(s.a - p, s.b - p)) == 0 && dcmp(dot(s.a - p, s.b - p)) <= 0;
}
// returns true if segs p && q touch or intersect
bool segssIntersect(Seg p, Seg q) {
  if(onSeg(p.a, q) || onSeg(p.b, q)) return true;
  if(onSeg(q.a, p) || onSeg(q.b, p)) return true;
  Ti c1 = crs(p.b - p.a, q.a - p.a);
  Ti c2 = crs(p.b - p.a, q.b - p.a);
  Ti c3 = crs(q.b - q.a, p.a - q.a);
  Ti c4 = crs(q.b - q.a, p.b - q.a);
  return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
}
bool linesParallel(Line p, Line q) {
  return dcmp(crs(p.b - p.a, q.b - q.a)) == 0;
}
// lines are represented as a ray from a pt: (pt, vector)
// returns false if two lines (p, v) && (q, w) are parallel or collinear
// true otherwise, intersection pt is stored at o via reference
bool lineLineIntscn(Pt p, Pt v, Pt q, Pt w, Pt& o) {
  if(dcmp(crs(v, w)) == 0) return false;
  Pt u = p - q;
  o = p + v * (crs(w,u)/crs(v,w));
  return true;
}
// returns false if two lines p && q are parallel or collinear
// true otherwise, intersection pt is stored at o via reference
bool lineLineIntscn(Line p, Line q, Pt& o) {
  return lineLineIntscn(p.a, p.b - p.a, q.a, q.b - q.a, o);
}
// returns the dis from pt a to line l
Tf disPtLine(Pt p, Line l) {
  return abs(crs(l.b - l.a, p - l.a) / len(l.b - l.a));
}
// returns the shortest dis from pt a to segs s
Tf disPtSeg(Pt p, Seg s) {
  if(s.a == s.b) return len(p - s.a);
  Pt v1 = s.b - s.a, v2 = p - s.a, v3 = p - s.b;
  if(dcmp(dot(v1, v2)) < 0)     return len(v2);
  else if(dcmp(dot(v1, v3)) > 0)  return len(v3);
  else return abs(crs(v1, v2) / len(v1));
}
// returns the shortest dis from segs p to segs q
Tf disSegSeg(Seg p, Seg q) {
  if(segssIntersect(p, q)) return 0;
  Tf ans = disPtSeg(p.a, q);
  ans = min(ans, disPtSeg(p.b, q));
  ans = min(ans, disPtSeg(q.a, p));
  ans = min(ans, disPtSeg(q.b, p));
  return ans;
}
// returns the projection of pt p on line l
Pt projectPtLine(Pt p, Line l) {
  Pt v = l.b - l.a;
  return l.a + v * ((Tf) dot(v, p - l.a) / dot(v, v));
}
