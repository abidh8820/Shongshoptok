const int N = 2e5 + 5;
const int mod = 1e9 + 7;

array < int, N + 1 > fact, inv, inv_fact, Drng;
void init() {
    fact[0] = inv_fact[0] = 1;
    for (int i = 1; i <= N; i++) {
        inv[i] = i == 1 ? 1 : (LL) inv[i - mod % i] * (mod / i + 1) % mod;
        fact[i] = (LL) fact[i - 1] * i % mod;
        inv_fact[i] = (LL) inv_fact[i - 1] * inv[i] % mod;
    }
    Drng[0] = 1, Drng[1] = 0;
    for(int i = 2; i <= N; i++)
        Drng[i] = (LL) (i - 1) * (Drng[i - 1] + Drng[i - 2]) % mod;
}
int C(int n, int r) {
    if (fact[0] != 1) init();
    return (r < 0 or r > n) ? 0 : (LL) fact[n] * inv_fact[r] % mod * inv_fact[n - r] % mod;
}
int D(int n) { 
    return n < 0 ? 0 : Drng[n];
}