#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 273: Sum of Squares
// Sum S(N) for squarefree N with prime factors 4k+1 < 150
// S(N) = sum of 'a' for all a^2+b^2=N, 0<=a<=b

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int plim; cin >> plim;

    // Get primes 4k+1 < plim
    vector<int> primes;
    vector<pair<ll,ll>> reps; // (a,b) for each prime
    vector<bool> isp(plim+1, true);
    for (int i = 2; i <= plim; i++) {
        if (isp[i]) {
            for (int j = i*2; j <= plim; j += i) isp[j] = false;
            if (i % 4 == 1) {
                primes.push_back(i);
                for (ll a = 0; a*a <= i; a++) {
                    ll b2 = i - a*a;
                    ll b = sqrt(b2);
                    if (b*b == b2) { reps.push_back({a, b}); break; }
                }
            }
        }
    }

    int k = primes.size();
    // Precompute product N and S(N) for all subsets
    ll total = 0;
    for (int mask = 1; mask < (1<<k); mask++) {
        // Compute N and all (a,b) representations
        vector<pair<ll,ll>> cur = {{0, 1}}; // representation of 1
        for (int i = 0; i < k; i++) {
            if (!(mask & (1<<i))) continue;
            vector<pair<ll,ll>> nxt;
            for (auto& [a1, b1] : cur) {
                ll a2 = reps[i].first, b2 = reps[i].second;
                ll x1 = a1*a2 + b1*b2;
                ll y1 = abs(a1*b2 - b1*a2);
                if (x1 > y1) swap(x1, y1);
                nxt.push_back({x1, y1});
                ll x2 = abs(a1*a2 - b1*b2);
                ll y2 = a1*b2 + b1*a2;
                if (x2 > y2) swap(x2, y2);
                nxt.push_back({x2, y2});
            }
            cur = nxt;
        }
        // Deduplicate and sum a values
        set<pair<ll,ll>> uniq;
        for (auto& p : cur) uniq.insert(p);
        ll sum_a = 0;
        for (auto& [a, b] : uniq) sum_a += a;
        total += sum_a;
    }

    cout << total << "\n";
    return 0;
}
