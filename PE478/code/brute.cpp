#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// Brute force for PE478: count subsets of M(n) that can produce (1:1:1).
// This uses simple enumeration for tiny n.

// Check if (1,1,1) can be expressed as non-negative combination
// of given vectors. For small sets, simple approach.
bool can_produce(const vector<array<ll,3>>& sub) {
    if (sub.empty()) return false;
    // For n=1 case: vectors are (0,0,1), (0,1,0), (0,1,1),
    //   (1,0,0), (1,0,1), (1,1,0), (1,1,1)
    // (1,1,1) can be produced by exactly one vector: (1,1,1) itself.
    // Or by (1,0,0)+(0,1,0)+(0,0,1) etc.
    // Check if any subset sums to (k,k,k) for some k>0 (then divide by k).
    ll m = sub.size();
    // For tiny m, try all combinations with bounded coefficients
    // Since components ≤ 1 for n=1, we just need to check if
    // there's a positive sum that gives equal components.
    // Limit coefficients to 3 (since max component is 1).
    for (ll mask = 0; mask < (1LL << m); mask++) {
        array<ll,3> sum = {0,0,0};
        for (ll i = 0; i < m; i++) {
            if (mask & (1LL << i)) {
                sum[0] += sub[i][0];
                sum[1] += sub[i][1];
                sum[2] += sub[i][2];
            }
        }
        if (sum[0] > 0 && sum[0] == sum[1] && sum[1] == sum[2])
            return true;
    }
    return false;
}

int main() {
    ll n; cin >> n;
    vector<array<ll,3>> vecs;
    for (ll a = 0; a <= n; a++)
        for (ll b = 0; b <= n; b++)
            for (ll c = 0; c <= n; c++) {
                if (a==0 && b==0 && c==0) continue;
                if (gcd(gcd(a,b),c) == 1)
                    vecs.push_back({a,b,c});
            }
    ll m = vecs.size();
    ll cnt = 0;
    for (ll mask = 0; mask < (1LL << m); mask++) {
        vector<array<ll,3>> sub;
        for (ll i = 0; i < m; i++)
            if (mask & (1LL << i))
                sub.push_back(vecs[i]);
        if (can_produce(sub)) cnt++;
    }
    cout << cnt << "\n";
}
