typedef double Tf;
typedef Tf Ti;      /// use long long for exactness
const Tf PI = acos(-1), EPS = 1e-9;
int dcmp(Tf x) { return abs(x) < EPS ? 0 : (x<0 ? -1 : 1);}

struct Pt {
  Ti x, y;
  Pt(Ti x = 0, Ti y = 0) : x(x), y(y) {}
  Pt operator + (const Pt& u) const { return Pt(x + u.x, y + u.y); }
  Pt operator - (const Pt& u) const { return Pt(x - u.x, y - u.y); }
  Pt operator * (const long long u) const { return Pt(x * u, y * u); }
  Pt operator * (const Tf u) const { return Pt(x * u, y * u); }
  Pt operator / (const Tf u) const { return Pt(x / u, y / u); }

  bool operator == (const Pt& u) const { return dcmp(x - u.x) == 0 && dcmp(y - u.y) == 0; }
  bool operator != (const Pt& u) const { return !(*this == u); }
  bool operator < (const Pt& u) const { return dcmp(x - u.x) < 0 || (dcmp(x - u.x) == 0 && dcmp(y - u.y) < 0); }
  friend istream &operator >> (istream &is, Pt &p) { return is >> p.x >> p.y; }
  friend ostream &operator << (ostream &os, const Pt &p) { return os << p.x << " " << p.y; }
};
using vec_p = vector<Pt>;

Ti dot(Pt a, Pt b) { return a.x * b.x + a.y * b.y; }
Ti crs(Pt a, Pt b) { return a.x * b.y - a.y * b.x; }
Tf len(Pt a) { return sqrt(dot(a, a)); }
Ti sqlen(Pt a) { return dot(a, a); }
Tf dis(Pt a, Pt b) {return len(a-b);}
Tf angle(Pt u) { return atan2(u.y, u.x); }
// returns angle between oa, ob in (-PI, PI]
Tf angleBetween(Pt a, Pt b) {
  double ans = angle(b) - angle(a);
  return ans <= -PI ? ans + 2*PI : (ans > PI ? ans - 2*PI : ans);
}
// Rotate a ccw by rad radians
Pt rotate(Pt a, Tf rad) {
  return Pt(a.x * cos(rad) - a.y * sin(rad), a.x * sin(rad) + a.y * cos(rad));
}
// rotate a ccw by angle th with cos(th) = co && sin(th) = si
Pt rotatePrecise(Pt a, Tf co, Tf si) {
  return Pt(a.x * co - a.y * si, a.y * co + a.x * si);
}
Pt rotate90(Pt a) { return Pt(-a.y, a.x); }
// scales vector a by s such that len of a becomes s
Pt scale(Pt a, Tf s) {
  return a / len(a) * s;
}
// returns an unit vector perpendicular to vector a
Pt normal(Pt a) {
  Tf l = len(a);
  return Pt(-a.y / l, a.x / l);
}
int ornt(Pt a, Pt b, Pt c) {
  return dcmp(crs(b - a, c - a));
}
bool half(Pt p){      // returns true for pt above x axis or on negative x axis
  return p.y > 0 || (p.y == 0 && p.x < 0);
}
bool polarComp(Pt p, Pt q){  //to be used in sort() function
  return make_tuple(half(p), 0) < make_tuple(half(q), crs(p, q));
}
struct Seg {
  Pt a, b;
  Seg(Pt aa, Pt bb) : a(aa), b(bb) {}
};
typedef Seg Line;
struct Crc {
    Pt o;
    Tf r;
    Crc(Pt o = Pt(0, 0), Tf r = 0) : o(o), r(r) {}
    // returns true if pt p is in || on the crc
    bool contains(Pt p) {
      return dcmp(sqlen(p - o) - r * r) <= 0;
    }
    // returns a pt on the crc rad radians away from +X CCW
    Pt pt(Tf rad) {
      return Pt(o.x + cos(rad) * r, o.y + sin(rad) * r);
    }
    // area of a circular sector with central angle rad
    Tf area(Tf rad = PI + PI) { return rad * r * r / 2; }
    // area of the circular sector cut by a chord with central angle alpha
    Tf sector(Tf alpha) { return r * r * 0.5 * (alpha - sin(alpha)); }
};
