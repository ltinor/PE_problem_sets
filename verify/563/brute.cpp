#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// Brute force for PE563: enumerate smooth numbers and count pairs

int main() {
    ll N;
    cin >> N;
    
    // Small brute force for verification
    vector<ll> primes = {2,3,5,7,11,13,17,19,23};
    vector<ll> smooth;
    
    function<void(ll, int)> gen = [&](ll v, int idx) {
        smooth.push_back(v);
        for (int i = idx; i < (int)primes.size(); i++) {
            if (v <= 1000000 / primes[i])
                gen(v * primes[i], i);
        }
    };
    gen(1, 0);
    sort(smooth.begin(), smooth.end());
    
    map<ll, int> area_cnt;
    for (ll w : smooth) {
        ll max_h = min((ll)(w * 1.1), 1000000LL / w);
        auto it = lower_bound(smooth.begin(), smooth.end(), w);
        while (it != smooth.end() && *it <= max_h) {
            area_cnt[w * (*it)]++;
            ++it;
        }
    }
    
    vector<ll> M(N+1, LLONG_MAX);
    for (auto& [a, c] : area_cnt)
        if (c >= 2 && c <= N && a < M[c]) M[c] = a;
    
    ll sum = 0;
    for (ll i = 2; i <= N; i++) sum += M[i];
    cout << sum << "\n";
    return 0;
}
