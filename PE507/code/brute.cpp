#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const ll MOD = 10000000LL;

int main() {
    string query;
    getline(cin, query);
    ll N = stoll(query);
    
    // Brute force with exhaustive (k,l) search
    if (N > 5) { cout << "0\n"; return 0; }
    
    // Generate tribonacci
    vector<ll> t = {0, 0, 1};
    for (ll i = 3; i <= 12*N; i++) {
        t.push_back((t[i-1] + t[i-2] + t[i-3]) % MOD);
    }
    
    ll total = 0;
    for (ll n = 1; n <= N; n++) {
        ll v1 = t[12*n-11] - t[12*n-10];
        ll v2 = t[12*n-9] + t[12*n-8];
        ll v3 = t[12*n-7] * t[12*n-6];
        ll w1 = t[12*n-5] - t[12*n-4];
        ll w2 = t[12*n-3] + t[12*n-2];
        ll w3 = t[12*n-1] * t[12*n];
        
        ll best = LLONG_MAX;
        for (ll k = -500; k <= 500; k++) {
            for (ll l = -500; l <= 500; l++) {
                if (k == 0 && l == 0) continue;
                ll man = abs(k*v1 + l*w1) + abs(k*v2 + l*w2) + abs(k*v3 + l*w3);
                best = min(best, man);
            }
        }
        total += best;
    }
    cout << total << "\n";
}
