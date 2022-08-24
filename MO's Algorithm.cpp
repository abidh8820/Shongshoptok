#include "bits/stdc++.h"
using namespace std;

const int N = 1e6 + 7;
const int S = 450;

int long a[N], cnt[N];
long long ans[N], cur;

void remove(int id) {
}

void add(int id) {
}

struct Query {
    int l, r, id;
    bool operator<(Query other) const {
        return make_pair(l / S, r) < make_pair(other.l / S, other.r);
    }
};

int main() {

    int n, q;
    scanf("%d %d", &n, &q);

    for(int i=1; i<=n; i++) scanf("%d",&a[i]);

    vector<Query> Q(q);
    for(int i=0; i<q; i++) {
        scanf("%d %d", &Q[i].l, &Q[i].r);
        Q[i].id = i;
    }
    sort(Q.begin(), Q.end());
    
    int l = 1, r = 0;
    for (int i = 0; i < q; i++) {
        while (l > Q[i].l) add(--l);
        while (r < Q[i].r) add(++r);
        while (l < Q[i].l) remove(l++);
        while (r > Q[i].r) remove(r--);
        ans[Q[i].id] = cur;
    }
    for(int i=0; i<q; i++) printf("%lld\n", ans[i]);
}
