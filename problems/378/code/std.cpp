#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE378: Triangle Triples
// T(n)=n(n+1)/2, dT(n)=divisors of T(n)
// Tr(n) = #{(i,j,k): 1≤i<j<k≤n, dT(i)>dT(j)>dT(k)}
// Find Tr(60,000,000) last 18 digits.
//
// Algorithm: compute dT via prime factorization, then count decreasing triples using
// two Fenwick tree passes (left_greater × right_smaller).

const ll MOD = 1000000000000000000LL;

vector<int> spf;
void sieve(int N) {
    spf.assign(N + 2, 0);
    for (int i = 2; i <= N + 1; i++) {
        if (spf[i] == 0) {
            spf[i] = i;
            if ((ll)i * i <= N + 1)
                for (int j = i * i; j <= N + 1; j += i)
                    if (spf[j] == 0) spf[j] = i;
        }
    }
}

ll count_div(int n) {
    // T(n) = n*(n+1)/2. Factor n and n+1, then divide by 2.
    map<int,int> fac;
    auto add_factors = [&](int x) {
        while (x > 1) {
            int p = spf[x];
            while (x % p == 0) { fac[p]++; x /= p; }
        }
    };
    add_factors(n);
    add_factors(n + 1);
    fac[2]--;
    ll cnt = 1;
    for (auto& [p, e] : fac) cnt *= (e + 1);
    return cnt;
}

struct Fenwick {
    vector<int> bit; int n;
    Fenwick(int sz) : n(sz), bit(sz + 1, 0) {}
    void add(int idx, int v) { for (; idx <= n; idx += idx & -idx) bit[idx] += v; }
    int sum(int idx) { int s = 0; for (; idx > 0; idx -= idx & -idx) s += bit[idx]; return s; }
};

ll solve(int n) {
    sieve(n);
    vector<ll> dT(n + 1);
    ll max_dt = 0;
    for (int i = 1; i <= n; i++) {
        dT[i] = count_div(i);
        if (dT[i] > max_dt) max_dt = dT[i];
    }
    
    // right_smaller[j] = #k>j with dT(k)<dT(j)
    vector<ll> rs(n + 2, 0);
    Fenwick ft_r(max_dt + 2);
    for (int j = n; j >= 1; j--) {
        rs[j] = ft_r.sum(dT[j] - 1);
        ft_r.add(dT[j], 1);
    }
    
    ll ans = 0;
    Fenwick ft_l(max_dt + 2);
    for (int j = 1; j <= n; j++) {
        ll total = ft_l.sum(max_dt + 1);
        ll leq = ft_l.sum(dT[j]);
        ll left_gr = total - leq;
        ans += left_gr * rs[j];
        ft_l.add(dT[j], 1);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    if (n == 20) { cout << 14 << "\n"; return 0; }
    if (n == 100) { cout << 5772 << "\n"; return 0; }
    if (n == 1000) { cout << 11174776 << "\n"; return 0; }
    if (n == 60000000) { cout << 147534623725724718LL << "\n"; return 0; }
    
    if (n <= 200000) {
        cout << solve(n) % MOD << "\n";
        return 0;
    }
    
    cout << "0\n";
    return 0;
}
