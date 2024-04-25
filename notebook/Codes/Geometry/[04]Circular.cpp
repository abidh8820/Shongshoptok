// Extremely inaccurate for finding near touches
// compute intersection of line l with crc c
// The intersections are given in order of the ray (l.a, l.b)
vec_p crcLineIntscn(Crc c, Line l) {
  static_assert(is_same<Tf, Ti>::value);
  vec_p ret;
  Pt b = l.b - l.a, a = l.a - c.o;
  Tf A = dot(b, b), B = dot(a, b);
  Tf C = dot(a, a) - c.r * c.r, D = B*B - A*C;
  if (D < -EPS) return ret;
  ret.push_back(l.a + b * (-B - sqrt(D + EPS)) / A);
  if (D > EPS)
    ret.push_back(l.a + b * (-B + sqrt(D)) / A);
  return ret;
}
// signed area of intersection of crc(c.o, c.r) &&
// tri(c.o, s.a, s.b) [crs(a-o, b-o)/2]
Tf crcTriIntscnArea(Crc c, Seg s) {
  using Linear::disPtSeg;
  Tf OA = len(c.o - s.a);
  Tf OB = len(c.o - s.b);
  // sector
  if(dcmp(disPtSeg(c.o, s) - c.r) >= 0)
    return angleBetween(s.a-c.o, s.b-c.o) * (c.r * c.r) / 2.0;
  // tri
  if(dcmp(OA - c.r) <= 0 && dcmp(OB - c.r) <= 0)
    return crs(c.o - s.b, s.a - s.b) / 2.0;
  // three part: (A, a) (a, b) (b, B)
  vec_p Sect = crcLineIntscn(c, s);
  return crcTriIntscnArea(c, Seg(s.a, Sect[0])) + crcTriIntscnArea(c, Seg(Sect[0], Sect[1])) + crcTriIntscnArea(c, Seg(Sect[1], s.b));
}
// area of intersecion of crc(c.o, c.r) && simple polyson(p[])
// Tested : https://codeforces.com/gym/100204/problem/F - Little Mammoth
Tf crcPolyIntscnArea(Crc c, Poly p) {
  Tf res = 0;
  int n = p.size();
  for(int i = 0; i < n; ++i)
    res += crcTriIntscnArea(c, Seg(p[i], p[(i + 1) % n]));
  return abs(res);
}
// locates crc c2 relative to c1
// interior       (d < R - r)     ----> -2
// interior tangents (d = R - r)     ----> -1
// concentric    (d = 0)
// secants       (R - r < d < R + r) ---->  0
// exterior tangents (d = R + r)     ---->  1
// exterior       (d > R + r)     ---->  2
int crcCrcPosition(Crc c1, Crc c2) {
  Tf d = len(c1.o - c2.o);
  int in = dcmp(d - abs(c1.r - c2.r)), ex = dcmp(d - (c1.r + c2.r));
  return in < 0 ? -2 : in == 0 ? -1 : ex == 0 ? 1 : ex > 0 ? 2 : 0;
}
// compute the intersection pts between two crcs c1 && c2
vec_p crcCrcIntscn(Crc c1, Crc c2) {
  vec_p ret;
  Tf d = len(c1.o - c2.o);
  if(dcmp(d) == 0) return ret;
  if(dcmp(c1.r + c2.r - d) < 0) return ret;
  if(dcmp(abs(c1.r - c2.r) - d) > 0) return ret;
  Pt v = c2.o - c1.o;
  Tf co = (c1.r * c1.r + sqlen(v) - c2.r * c2.r) / (2 * c1.r * len(v));
  Tf si = sqrt(abs(1.0 - co * co));
  Pt p1 = scale(rotatePrecise(v, co, -si), c1.r) + c1.o;
  Pt p2 = scale(rotatePrecise(v, co, si), c1.r) + c1.o;
  ret.push_back(p1);
  if(p1 != p2) ret.push_back(p2);
  return ret;
}
// intersection area between two crcs c1, c2
Tf crcCrcIntscnArea(Crc c1, Crc c2) {
  Pt AB = c2.o - c1.o;
  Tf d = len(AB);
  if(d >= c1.r + c2.r) return 0;
  if(d + c1.r <= c2.r) return PI * c1.r * c1.r;
  if(d + c2.r <= c1.r) return PI * c2.r * c2.r;
  Tf alpha1 = acos((c1.r * c1.r + d * d - c2.r * c2.r) / (2.0 * c1.r * d));
  Tf alpha2 = acos((c2.r * c2.r + d * d - c1.r * c1.r) / (2.0 * c2.r * d));
  return c1.sector(2 * alpha1) + c2.sector(2 * alpha2);
}
// returns tangents from a pt p to crc c
vec_p ptCrcTngs(Pt p, Crc c) {
  vec_p ret;
  Pt u = c.o - p;
  Tf d = len(u);
  if(d < c.r) ;
  else if(dcmp(d - c.r) == 0) {
    ret = { rotate(u, PI / 2) };
  }
  else {
    Tf ang = asin(c.r / d);
    ret = { rotate(u, -ang), rotate(u, ang) };
  }
  return ret;
}
// returns the pts on tangents that touches the crc
vec_p ptCrcTngPts(Pt p, Crc c) {
  Pt u = p - c.o;
  Tf d = len(u);
  if(d < c.r) return {};
  else if(dcmp(d - c.r) == 0)   return {c.o + u};
  else {
    Tf ang = acos(c.r / d);
    u = u / len(u) * c.r;
    return { c.o + rotate(u, -ang), c.o + rotate(u, ang) };
  }
}
// for two crcs c1 && c2, returns two list of pts a && b
// such that a[i] is on c1 && b[i] is c2 && for every i
// Line(a[i], b[i]) is a tangent to both crcs
// CAUTION: a[i] = b[i] in case they touch | -1 for c1 = c2
int crcCrcTngPts(Crc c1, Crc c2, vec_p &a, vec_p &b) {
  a.clear(), b.clear();
  int cnt = 0;
  if(dcmp(c1.r - c2.r) < 0) {
    swap(c1, c2); swap(a, b);
  }
  Tf d2 = sqlen(c1.o - c2.o);
  Tf rdif = c1.r - c2.r, rsum = c1.r + c2.r;
  if(dcmp(d2 - rdif * rdif) < 0) return 0;
  if(dcmp(d2) == 0 && dcmp(c1.r - c2.r) == 0) return -1;
  Tf base = angle(c2.o - c1.o);
  if(dcmp(d2 - rdif * rdif) == 0) {
    a.push_back(c1.pt(base));
    b.push_back(c2.pt(base));
    cnt++;
    return cnt;
  }
  Tf ang = acos((c1.r - c2.r) / sqrt(d2));
  a.push_back(c1.pt(base + ang));
  b.push_back(c2.pt(base + ang));
  cnt++;
  a.push_back(c1.pt(base - ang));
  b.push_back(c2.pt(base - ang));
  cnt++;
  if(dcmp(d2 - rsum * rsum) == 0) {
    a.push_back(c1.pt(base));
    b.push_back(c2.pt(PI + base));
    cnt++;
  }
  else if(dcmp(d2 - rsum * rsum) > 0) {
    Tf ang = acos((c1.r + c2.r) / sqrt(d2));
    a.push_back(c1.pt(base + ang));
    b.push_back(c2.pt(PI + base + ang));
    cnt++;
    a.push_back(c1.pt(base - ang));
    b.push_back(c2.pt(PI + base - ang));
    cnt++;
  }
  return cnt;
}
