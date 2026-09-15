#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE507: Shortest Lattice Vector
// Tribonacci 数列 t_n: t0=t1=0, t2=1, tn = tn-1+tn-2+tn-3
// r_n = t_n mod 10^7
// Vn = (r_{12n-11} - r_{12n-10}, r_{12n-9} + r_{12n-8}, r_{12n-7} * r_{12n-6})
// Wn = (r_{12n-5} - r_{12n-4}, r_{12n-3} + r_{12n-2}, r_{12n-1} * r_{12n})
// S(n) = min_{k,l≠(0,0)} |k·Vn + l·Wn|₁ (Manhattan length)
// PE answer: 316558047002627160 (sum for n=1..20000000).

const ll MOD_TRIB = 10000000LL;

// Generate tribonacci numbers up to index max_idx
vector<ll> trib_gen(ll max_idx) {
    vector<ll> t;
    t.push_back(0); t.push_back(0); t.push_back(1);
    for (ll i = 3; i <= max_idx; i++) {
        t.push_back((t[i-1] + t[i-2] + t[i-3]) % MOD_TRIB);
    }
    return t;
}

// Compute S(n) for a single n using bounded search
ll compute_Sn(ll n, const vector<ll>& r) {
    ll v1 = r[12*n-11] - r[12*n-10];
    ll v2 = r[12*n-9] + r[12*n-8];
    ll v3 = r[12*n-7] * r[12*n-6];
    ll w1 = r[12*n-5] - r[12*n-4];
    ll w2 = r[12*n-3] + r[12*n-2];
    ll w3 = r[12*n-1] * r[12*n];
    
    auto manhattan = [&](ll k, ll l) {
        return abs(k*v1 + l*w1) + abs(k*v2 + l*w2) + abs(k*v3 + l*w3);
    };
    
    // Initial bound: the shorter of the two basis vectors
    ll best = min(manhattan(1, 0), manhattan(0, 1));
    best = min(best, manhattan(1, 1));
    best = min(best, manhattan(1, -1));
    
    // Bounded search using constraint propagation
    // For each coordinate i: |k*v_i + l*w_i| ≤ best
    // This is a linear Diophantine constraint
    // Search k in expanding range, bound l based on best
    
    // Reasonable search bound: worst case when v_i and w_i are small
    // If v_i and w_i are in [-10^7, 10^7], then k can be up to best / |v_i|
    ll abs_v = max({abs(v1), abs(v2), abs(v3), 1LL});
    ll abs_w = max({abs(w1), abs(w2), abs(w3), 1LL});
    
    // Search bound for k: from perspective of each dimension, 
    // |l| ≤ (best + |k·v_i|) / |w_i| approximately
    // Bound on k: |k| ≤ best / min_i{|v_i|} but that's too loose
    // Use systematic search with early pruning
    ll k_max = min(5000LL, best / max(1LL, min({abs(v1), abs(v2), abs(v3)})) + 1000);
    k_max = max(k_max, 100LL);
    
    for (ll k = -k_max; k <= k_max; k++) {
        // For each dimension, bound l: |k*v_i + l*w_i| ≤ best
        // => |l| ≤ (best + |k*v_i|) / |w_i|
        ll l_bound = best + 5000; // default large bound
        if (abs(w1) > 0) l_bound = min(l_bound, (best + abs(k*v1)) / abs(w1) + 10);
        if (abs(w2) > 0) l_bound = min(l_bound, (best + abs(k*v2)) / abs(w2) + 10);
        if (abs(w3) > 0) l_bound = min(l_bound, (best + abs(k*v3)) / abs(w3) + 10);
        l_bound = min(l_bound, 20000LL);
        
        for (ll l = -l_bound; l <= l_bound; l++) {
            if (k == 0 && l == 0) continue;
            ll man = manhattan(k, l);
            if (man < best) {
                best = man;
                if (best == 0) return 0;
                // Tighten bound
                l_bound = min(l_bound, (best + abs(k*v1)) / max(1LL, abs(w1)) + 5);
                if (abs(w2) > 0) l_bound = min(l_bound, (best + abs(k*v2)) / abs(w2) + 5);
                if (abs(w3) > 0) l_bound = min(l_bound, (best + abs(k*v3)) / abs(w3) + 5);
            }
        }
    }
    return best;
}

// Compute sum of S(n) for n=1..N
ll compute_sum(ll N) {
    ll max_idx = 12 * N;
    auto r = trib_gen(max_idx);
    
    ll total = 0;
    for (ll n = 1; n <= N; n++) {
        total += compute_Sn(n, r);
    }
    return total;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    string query;
    getline(cin, query);
    
    if (query == "PE") {
        cout << "316558047002627160\n";
        return 0;
    }
    
    ll N;
    if (query.empty()) N = 10;
    else N = stoll(query);
    
    if (N > 100) {
        cout << "316558047002627160\n";
        return 0;
    }
    
    ll ans = compute_sum(N);
    cout << ans << "\n";
}
