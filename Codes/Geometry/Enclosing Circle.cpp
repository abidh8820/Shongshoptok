// returns false if points are collinear, true otherwise
// circle p touch each arm of triangle abc
bool inscribedCircle(Point a, Point b, Point c, Circle &p) {
    using Linear::distancePointLine;
    static_assert(is_same<Tf, Ti>::value);
    if(orient(a, b, c) == 0) return false;
    Tf u = length(b - c);
    Tf v = length(c - a);
    Tf w = length(a - b);
    p.o = (a * u + b * v + c * w) / (u + v + w);
    p.r = distancePointLine(p.o, Line(a, b));
    return true;
}

// set of points A(x, y) such that PA : QA = rp : rq
Circle apolloniusCircle(Point P, Point Q, Tf rp, Tf rq) {
    static_assert(is_same<Tf, Ti>::value);
    rq *= rq; rp *= rp;
    Tf a = rq - rp;
    assert(dcmp(a));
    Tf g = (rq * P.x - rp * Q.x)/a;
    Tf h = (rq * P.y - rp * Q.y)/a;
    Tf c = (rq * P.x * P.x - rp * Q.x * Q.x + rq * P.y * P.y - rp * Q.y * Q.y)/a;
    Point o(g, h);
    Tf R = sqrt(g * g + h * h - c);
    return Circle(o, R);
}

// returns false if points are collinear, true otherwise
// circle p goes through points a, b && c
bool circumscribedCircle(Point a, Point b, Point c, Circle &p) {
    using Linear::lineLineIntersection;
    if(orient(a, b, c) == 0) return false;
    Point d = (a + b) / 2, e = (a + c) / 2;
    Point vd = rotate90(b - a), ve = rotate90(a - c);
    bool f = lineLineIntersection(d, vd, e, ve, p.o);
    if(f) p.r = length(a - p.o);
    return f;
}

// Following three methods implement Welzl's algorithm for
// the smallest enclosing circle problem: Given a set of
// points, find out the minimal circle that covers them all.
// boundary(p) determines (if possible) a circle that goes
// through the points in p. Ideally |p| <= 3.
// welzl() is a recursive helper function doing the most part
// of Welzl's algorithm. Call minidisk with the set of points
// Randomized Complexity: O(CN) with C~10 (practically lesser)

Circle boundary(const vector<Point> &p) {
    Circle ret;
    int sz = p.size();
    if(sz == 0)         ret.r = 0;
    else if(sz == 1)    ret.o = p[0], ret.r = 0;
    else if(sz == 2)    ret.o = (p[0] + p[1]) / 2, ret.r = length(p[0] - p[1]) / 2;
    else if(!circumscribedCircle(p[0], p[1], p[2], ret))    ret.r = 0;
    return ret;
}
Circle welzl(const vector<Point> &p, int fr, vector<Point> &b) {
    if(fr >= (int) p.size() || b.size() == 3)   return boundary(b);

    Circle c = welzl(p, fr + 1, b);
    if(!c.contains(p[fr])) {
        b.push_back(p[fr]);
        c = welzl(p, fr + 1, b);
        b.pop_back();
    }
    return c;
}
Circle minidisk(vector<Point> p) {
    random_shuffle(p.begin(), p.end());
    vector<Point> q;
    return welzl(p, 0, q);
}