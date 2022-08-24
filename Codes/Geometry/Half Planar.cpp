using Linear::lineLineIntersection;
struct DirLine {
    Point p, v;
    Tf ang;
    DirLine() {}
    /// Directed line containing point P in the direction v
    DirLine(Point p, Point v) : p(p), v(v) { ang = atan2(v.y, v.x); }
    /// Directed Line for ax+by+c >=0
    DirLine(Tf a, Tf b, Tf c) {
        assert(dcmp(a) || dcmp(b));
        p = dcmp(a) ? Point(-c/a, 0) : Point(0,-c/b);
        v = Point(b, -a);
        ang = atan2(v.y, v.x);
    }
    bool operator<(const DirLine& u) const { return ang < u.ang; }
    bool onLeft(Point x) const { return dcmp(cross(v, x-p)) >= 0; }
};

// Returns the region bounded by the left side of some directed lines
// MAY CONTAIN DUPLICATE POINTS
// OUTPUT IS UNDEFINED if intersection is unbounded
// Complexity: O(n log n) for sorting, O(n) afterwards
Polygon halfPlaneIntersection(vector<DirLine> li) {
    int n = li.size(), first = 0, last = 0;
    sort(li.begin(), li.end());
    vector<Point> p(n);
    vector<DirLine> q(n);
    q[0] = li[0];

    for(int i = 1; i < n; i++) {
        while(first < last && !li[i].onLeft(p[last - 1])) last--;
        while(first < last && !li[i].onLeft(p[first])) first++;
        q[++last] = li[i];
        if(dcmp(cross(q[last].v, q[last-1].v)) == 0) {
            last--;
            if(q[last].onLeft(li[i].p)) q[last] = li[i];
        }
        if(first < last)
            lineLineIntersection(q[last - 1].p, q[last - 1].v, q[last].p, q[last].v, p[last - 1]);
    }

    while(first < last && !q[first].onLeft(p[last - 1])) last--;
    if(last - first <= 1) return {};
    lineLineIntersection(q[last].p, q[last].v, q[first].p, q[first].v, p[last]);
    return Polygon(p.begin()+first, p.begin()+last+1);
}

// O(n^2 lg n) implementation of Voronoi Diagram bounded by INF square
// returns region, where regions[i] = set of points for which closest
// point is site[i]. This region is a polygon.
const Tf INF = 1e10;
vector<Polygon> voronoi(const vector<Point> &site, Tf bsq) {
    int n = site.size();
    vector<Polygon> region(n);
    Point A(-bsq, -bsq), B(bsq, -bsq), C(bsq, bsq), D(-bsq, bsq);

    for(int i = 0; i < n; ++i) {
        vector<DirLine> li(n - 1);
        for(int j = 0, k = 0; j < n; ++j) {
            if(i == j) continue;
            li[k++] = DirLine((site[i] + site[j]) / 2, rotate90(site[j] - site[i]));
        }
        li.emplace_back(A, B - A);
        li.emplace_back(B, C - B);
        li.emplace_back(C, D - C);
        li.emplace_back(D, A - D);
        region[i] = halfPlaneIntersection(li);
    }
    return region;
}