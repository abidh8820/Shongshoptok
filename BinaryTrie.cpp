#include <bits/stdc++.h>
using namespace std;


const int bit = 31;
map<int, int> f;

struct node {
    node *a[2];
    int use;

    node() {
        for (int i = 0; i <= 1; i++) {
            a[i] = NULL;
        }
        use = 0;
    }
} * root;

void insert(int n) {
    node *cur = root;
    for (int i = bit; i >= 0; i--) {
        int x = (n >> i) & 1;
        if (cur->a[x] == NULL) cur->a[x] = new node();
        cur = cur->a[x];
        cur->use += 1;
    }
}
void erase(int n) {
    node *cur = root;
    for (int i = bit; i >= 0; i--) {
        int x = (n >> i) & 1;
        cur = cur->a[x];
        cur->use -= 1;
    }
}
int find(int n) {
    node *cur = root;
    int ans = 0;
    for (int i = bit; i >= 0; i--) {
        int x = (n >> i) & 1;
        int y = x ^ 1;
        ans <<= 1;

        if (cur->a[y] and cur->a[y]->use) {
            cur = cur->a[y];
            ans += 1;
        } else {
            cur = cur->a[x];
        }
    }
    return ans;
}
