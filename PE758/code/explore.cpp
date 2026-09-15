#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// Simulate water pouring to find P(a,b) for small values
ll bfs_P(ll a, ll b) {
    ll cap_s = a, cap_m = b, cap_l = a + b;
    
    // State: (s, m, l) amounts
    using State = tuple<ll,ll,ll>;
    set<State> visited;
    queue<pair<State, int>> q;
    
    State start = {a, b, 0};
    visited.insert(start);
    q.push({start, 0});
    
    while (!q.empty()) {
        auto [state, dist] = q.front(); q.pop();
        auto [s, m, l] = state;
        
        // Check if we have 1 liter
        if (s == 1 || m == 1 || l == 1) return dist;
        
        // Possible pours: S→M, S→L, M→S, M→L, L→S, L→M
        // S→M: pour from S to M until S empty or M full
        {
            ll pour = min(s, cap_m - m);
            if (pour > 0) {
                State ns = {s - pour, m + pour, l};
                if (!visited.count(ns)) {
                    visited.insert(ns);
                    q.push({ns, dist + 1});
                }
            }
        }
        // S→L
        {
            ll pour = min(s, cap_l - l);
            if (pour > 0) {
                State ns = {s - pour, m, l + pour};
                if (!visited.count(ns)) {
                    visited.insert(ns);
                    q.push({ns, dist + 1});
                }
            }
        }
        // M→S
        {
            ll pour = min(m, cap_s - s);
            if (pour > 0) {
                State ns = {s + pour, m - pour, l};
                if (!visited.count(ns)) {
                    visited.insert(ns);
                    q.push({ns, dist + 1});
                }
            }
        }
        // M→L
        {
            ll pour = min(m, cap_l - l);
            if (pour > 0) {
                State ns = {s, m - pour, l + pour};
                if (!visited.count(ns)) {
                    visited.insert(ns);
                    q.push({ns, dist + 1});
                }
            }
        }
        // L→S
        {
            ll pour = min(l, cap_s - s);
            if (pour > 0) {
                State ns = {s + pour, m, l - pour};
                if (!visited.count(ns)) {
                    visited.insert(ns);
                    q.push({ns, dist + 1});
                }
            }
        }
        // L→M
        {
            ll pour = min(l, cap_m - m);
            if (pour > 0) {
                State ns = {s, m + pour, l - pour};
                if (!visited.count(ns)) {
                    visited.insert(ns);
                    q.push({ns, dist + 1});
                }
            }
        }
    }
    return -1;
}

int main() {
    cout << "Computing P(a,b) for small coprime pairs:\n";
    cout << "P(3,5) = " << bfs_P(3,5) << " (expected 4)\n";
    cout << "P(7,31) = " << bfs_P(7,31) << " (expected 20)\n";
    cout << "P(1234,4321) = " << bfs_P(1234,4321) << " (expected 2780, may be slow)\n";
    
    cout << "\nSmall values:\n";
    for (ll b = 2; b <= 15; b++) {
        for (ll a = 1; a < b; a++) {
            if (gcd(a,b) != 1) continue;
            ll p = bfs_P(a, b);
            // Compute Euclidean algorithm info
            ll x = b, y = a;
            vector<ll> quot;
            while (y > 0) {
                quot.push_back(x / y);
                ll r = x % y;
                x = y; y = r;
            }
            ll sum_q = 0;
            for (ll q : quot) sum_q += q;
            cout << "P(" << setw(2) << a << "," << setw(2) << b << ")=" << setw(4) << p
                 << " quot_sum=" << sum_q << " quot=";
            for (ll q : quot) cout << q << ",";
            cout << "\n";
        }
    }
    
    // Try to find pattern
    cout << "\n\nTrying to relate P to Euclidean algorithm:\n";
    cout << "For a=7, b=31:\n";
    cout << "Euclidean: 31=4*7+3, 7=2*3+1. quotients=[4,2]\n";
    cout << "Sum of q*(q+1)/2? 4*5/2 + 2*3/2 = 10+3=13. Not 20.\n";
    cout << "Sum of q*(2a)?\n";
    
    // Let me try formula P = Σ (2*q_i - 1) * something
    // For (3,5): q=[1,1,2]. Σ(2q-1)=1+1+3=5. But P=4.
    // For (7,31): q=[4,2,3]. Σ(2q-1)=7+3+5=15. But P=20.
    
    // Maybe: P = 2*Σ q_i + remaining steps?
    // (3,5): 2*(1+1+2)=8. P=4. Nope.
    // (7,31): 2*(4+2+3)=18. P=20. Close!
    
    // Let me compute Σ(2*q_i) carefully:
    // (7,31): q=[4,2,3]. 2*4+2*2+2*3=8+4+6=18. P=20=18+2.
    // (3,5): q=[1,1,2]. 2+2+4=8. P=4≠8+2=10.
    
    // What about: P = Σ(q_i + 1)?
    // (3,5): 2+2+3=7. No.
    // (7,31): 5+3+4=12. No.
    
    return 0;
}
