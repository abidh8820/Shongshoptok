#include "bits/stdc++.h"
using namespace std;

struct BIT {
    int n;
    vector<int> bit; 

    BIT(int n) {
        this->n = n;
        bit.resize(n);
    }
    void update(int x, int delta) {
        for (; x <= n; x += x & -x) bit[x] += delta;
    }

    int query(int x) {
        int sum = 0;
        for (; x > 0; x -= x & -x) sum += bit[x];
        return sum;
    }
};

int main() {}
