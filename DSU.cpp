#include "bits/stdc++.h"
using namespace std;

const int N = 1e5 + 7;

struct DSU{
    int par[N];
    void init() {
        for (int i = 0; i < N; i++) par[i] = i;
    }

    int find(int u) {
        if (u == par[u]) return u;
        return par[u] = find(par[u]);
    }
    void merge(int u, int v) { par[find(u)] = find(v); }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
}

