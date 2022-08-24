/// you may define the processor function in this namespace
/// instead of passing as an argument; testing shows function
/// defined using lambda and passed as argument performs better
/// tested on:
/// constant width strip - https://codeforces.com/gym/100016/problem/I
/// constant area triangle - https://codeforces.com/contest/1019/problem/D
/// smallest area quadrilateral - https://codingcompetitions.withgoogle.com/codejamio/round/000000000019ff03/00000000001b5e89
/// disjoint triangles count - https://codeforces.com/contest/1025/problem/F
/// smallest and largest triangle - http://serjudging.vanb.org/?p=561
typedef pair< int , int >PII;
void performTrick(vector< Point >pts, const function<void(const vector< Point >&, int)> &processor) {
    int n = pts.size();
    sort(pts.begin(), pts.end());
    vector< int >position(n);
    vector< PII >segments;
    segments.reserve((n*(n-1))/2);
    for (int i = 0; i < n; i++) {
        position[i] = i;
        for (int j = i+1; j < n; j++) {
            segments.emplace_back(i, j);
        }
    }
    assert(segments.capacity() == segments.size());
    sort(segments.begin(), segments.end(), [&](PII p, PII q) {
        Ti prod = cross(pts[p.second]-pts[p.first], pts[q.second]-pts[q.first]);
        if (prod != 0) return prod > 0;
        return p < q;
    });
    for (PII seg : segments) {
        int i = position[seg.first];
        assert(position[seg.second] == i+1);
        processor(pts, i);
        swap(pts[i], pts[i+1]);
        swap(position[seg.first], position[seg.second]);
    }
}