#include <bits/stdc++.h>
using namespace std;


typedef long long LL;
const int N = 1 << 18;

LL tree[N * 4], lazy[N * 4], a[N];

LL combine(LL u, LL v){
    return u + v;
}

void build(int u, int st, int en) {
    lazy[u] = 0;
    if (st == en) {
        tree[u] = a[st];  return;
    }
    int mid = (st + en) / 2;
    build(u * 2, st, mid);
    build(u * 2 + 1, mid + 1, en);
    tree[u] = combine(tree[u * 2], tree[u * 2 + 1]);
}

//for max, min query just add lazy * 1;
void propagate(int u,int st, int en) {
    int mid = (st+en)/2;
    lazy[u * 2] += lazy[u];
    tree[u * 2] += lazy[u]*(mid-st+1);   
    lazy[u * 2 + 1] += lazy[u];
    tree[u * 2 + 1] += lazy[u]*(en-mid);
    lazy[u] = 0;
}

void update(int u, int st, int en, int i, int j, int val) {
    if (en < i || st> j) return;
    if (st >= i && en <= j) {
        // for max, min query just add lazy * 1;
        lazy[u] += val; tree[u] += val*(en-st+1);  return;
    }
    propagate(u,st,en);
    int mid = (st + en) / 2;

    update(u * 2, st, mid, i, j, val);
    update(u * 2 + 1, mid + 1, en, i, j, val);
    tree[u] = combine(tree[u * 2], tree[u * 2 + 1]);
}

LL query(int u, int st, int en, int i, int j) {
    if (st > j || en < i) return 0; // return appropriate identity value
    if (st >= i && en <= j) return tree[u];
    propagate(u,st,en);
    int mid = (st + en) / 2;
    return combine(query(u * 2, st, mid, i, j), query(u * 2 + 1, mid + 1, en, i, j));
} 


