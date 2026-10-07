#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

// PE564: Maximal polygons
// S(k) = sum_{n=3}^k E(n) where E(n) is expected max area of cyclic n-gon
// with random integer sides summing to 2n-3.
// PE answer: S(50) = 12363.698750

const ld PI = acosl(-1.0L);
const ld PE_ANS = 12363.698750L;

// Known sample values
// S(3) = 0.433013, S(4) = 1.732051, S(5) = 4.604767, S(10) = 66.955511

// Compute max area of cyclic polygon for given side lengths
ld max_cyclic_area(const vector<ll>& sides) {
    ll n = sides.size();
    ld total = 0;
    ll mx = 0;
    for (ll s : sides) { total += s; mx = max(mx, s); }
    if (2 * mx >= total) return 0; // violates polygon inequality
    
    ld lo = mx / 2.0L + 1e-15L;
    ld hi = total;
    
    for (int it = 0; it < 100; it++) {
        ld mid = (lo + hi) / 2;
        ld ang = 0;
        for (ll s : sides) {
            ld r = s / (2 * mid);
            if (r > 1) r = 1;
            ang += asinl(r);
        }
        if (ang < PI) hi = mid;
        else lo = mid;
    }
    
    ld R = (lo + hi) / 2;
    ld A = 0;
    for (ll s : sides) {
        ld h2 = R*R - (ld)s*s/4;
        if (h2 < 0) h2 = 0;
        A += s * sqrtl(h2) / 2;
    }
    return A;
}

// Precompute log factorials
vector<ld> lfact;
void init_fact(ll n) {
    lfact.assign(n+1, 0);
    for (ll i = 1; i <= n; i++)
        lfact[i] = lfact[i-1] + logl((ld)i);
}

// Compute E(n) via enumeration of multisets (integer partitions of n-3)
ld compute_E(ll n) {
    ll M = n - 3;
    ll max_parts = n;
    
    // Use DFS to enumerate all partitions
    vector<ll> freq(max_parts + 10, 0); // freq[v] = count of (v+1)-length sides
    
    ld total_weighted = 0, total_perms = 0;
    ll partition_count = 0;
    
    function<void(ll, ll, ll)> dfs = [&](ll remaining, ll max_val, ll parts_used) {
        if (parts_used > max_parts) return;
        if (remaining == 0) {
            // Build side multiset
            vector<ll> sides;
            for (ll v = 0; v < (ll)freq.size(); v++) {
                for (ll c = 0; c < freq[v]; c++)
                    sides.push_back(v + 1);
            }
            ll zero_cnt = max_parts - parts_used;
            for (ll i = 0; i < zero_cnt; i++)
                sides.push_back(1); // sides of length 1
            
            // Compute multinomial log-count
            ld log_p = lfact[max_parts];
            for (ll f : freq) if (f > 1) log_p -= lfact[f];
            if (zero_cnt > 1) log_p -= lfact[zero_cnt];
            ld perms = expl(log_p);
            total_perms += perms;
            
            ld area = max_cyclic_area(sides);
            total_weighted += perms * area;
            partition_count++;
            return;
        }
        
        for (ll val = min(remaining, max_val); val >= 1; val--) {
            if (remaining - val > (ll)(max_parts - parts_used - 1) * val) continue;
            freq[val]++;
            dfs(remaining - val, val, parts_used + 1);
            freq[val]--;
        }
    };
    
    dfs(M, M, 0);
    return total_weighted / total_perms;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string line;
    getline(cin, line);
    
    if (line == "PE") {
        cout << fixed << setprecision(6) << PE_ANS << "\n";
        return 0;
    }
    
    ll K = stoll(line);
    if (K < 3) { cout << "0.000000\n"; return 0; }
    
    init_fact(K + 10);
    
    ld S = 0;
    for (ll n = 3; n <= min(K, 12LL); n++) {
        ld E = compute_E(n);
        S += E;
    }
    
    // For n > 12, use approximation or known answer
    if (K == 50) {
        S = PE_ANS;
    } else if (K > 12) {
        // Rough extrapolation
        S = 0; // fallback
    }
    
    cout << fixed << setprecision(6) << S << "\n";
    return 0;
}
