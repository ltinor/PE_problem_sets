#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Brute force for Fsf(n):
// Generate all factorizations of n into factors > 1,
// count those where all factors are squarefree.

bool is_squarefree(ll x) {
    for (ll d = 2; d * d <= x; d++) {
        if (x % (d * d) == 0) return false;
    }
    return true;
}

// Recursively generate factorizations
void gen_factors(ll n, ll min_f, vector<ll>& cur,
                  vector<vector<ll>>& results) {
    if (n == 1) {
        if (cur.size() >= 1) // at least one factor > 1
            results.push_back(cur);
        return;
    }
    
    for (ll f = min_f; f * f <= n; f++) {
        if (n % f == 0) {
            cur.push_back(f);
            gen_factors(n / f, f, cur, results);
            cur.pop_back();
            
            if (f != n / f) {
                cur.push_back(n / f);
                gen_factors(f, f, cur, results);
                cur.pop_back();
            }
        }
    }
    // n itself as a factor
    cur.push_back(n);
    gen_factors(1, n, cur, results);
    cur.pop_back();
}

ll Fsf_brute(ll n) {
    vector<ll> cur;
    vector<vector<ll>> results;
    gen_factors(n, 2, cur, results);
    
    // Deduplicate (different orders of same factors)
    set<vector<ll>> unique_facts;
    for (auto& v : results) {
        sort(v.begin(), v.end());
        unique_facts.insert(v);
    }
    
    ll cnt = 0;
    for (auto& v : unique_facts) {
        bool ok = true;
        for (ll x : v) if (!is_squarefree(x)) { ok = false; break; }
        if (ok) cnt++;
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll N;
    cin >> N;
    
    ll total = 0;
    for (ll n = 2; n <= N; n++) {
        total += Fsf_brute(n);
    }
    cout << total << "\n";
    return 0;
}
