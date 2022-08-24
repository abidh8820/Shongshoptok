// Given a list of segments v, finds a pair (i, j)
// st v[i], v[j] intersects. If none, returns {-1, -1}
// Tested Timus 1469, CF 1359F
struct Event {
    Tf x;
    int tp, id;
    bool operator < (const Event &p) const {
        if(dcmp(x - p.x)) return x < p.x;
        return tp > p.tp;
    }
};

pair<int, int> anyIntersection(const vector<Segment> &v) {
    using Linear::segmentsIntersect;
    static_assert(is_same<Tf, Ti>::value);

    vector<Event> ev;
    for(int i=0; i<v.size(); i++) {
        ev.push_back({min(v[i].a.x, v[i].b.x), +1, i});
        ev.push_back({max(v[i].a.x, v[i].b.x), -1, i});
    }
    sort(ev.begin(), ev.end());

    auto comp = [&v] (int i, int j) {
        Segment p = v[i], q = v[j];
        Tf x = max(min(p.a.x, p.b.x), min(q.a.x, q.b.x));
        auto yvalSegment = [&x](const Line &s) {
            if(dcmp(s.a.x - s.b.x) == 0) return s.a.y;
            return s.a.y + (s.b.y - s.a.y) * (x - s.a.x) / (s.b.x - s.a.x);
        };
        return dcmp(yvalSegment(p) - yvalSegment(q)) < 0;
    };

    multiset<int, decltype(comp)> st(comp);
    typedef decltype(st)::iterator iter;
    auto prev = [&st](iter it) {
        return it == st.begin() ? st.end() : --it;
    };
    auto next = [&st](iter it) {
        return it == st.end() ? st.end() : ++it;
    };

    vector<iter> pos(v.size());
    for(auto &cur : ev) {
        int id = cur.id;
        if(cur.tp == 1) {
            iter nxt = st.lower_bound(id);
            iter pre = prev(nxt);
            if(pre != st.end() && segmentsIntersect(v[*pre], v[id]))   return {*pre, id};
            if(nxt != st.end() && segmentsIntersect(v[*nxt], v[id]))   return {*nxt, id};
            pos[id] = st.insert(nxt, id);
        }
        else {
            iter nxt = next(pos[id]);
            iter pre = prev(pos[id]);
            if(pre != st.end() && nxt != st.end() && segmentsIntersect(v[*pre], v[*nxt]))
                return {*pre, *nxt};
            st.erase(pos[id]);
        }
    }
    return {-1, -1};
}