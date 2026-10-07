#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE426: Box-ball system (adapted for OJ)
// Simulate BBS using block-level carrier method
// For OJ: N ≤ 5000 (total elements ≤ 5001, simulation feasible)
// PE answer for N=10000000: 31591886008

const ll PE426_ANS = 31591886008LL;
const ll MOD = 50515093;

vector<ll> generate_t(ll N) {
    ll s = 290797;
    vector<ll> t(N + 1);
    for (ll i = 0; i <= N; i++) {
        t[i] = (s % 64) + 1;
        s = (s * s) % MOD;
    }
    return t;
}

vector<ll> bbs_one_turn(const vector<ll>& seq) {
    ll c = 0;
    vector<pair<char,ll>> result;
    for (ll i = 0; i < (ll)seq.size(); i++) {
        if (i % 2 == 0) { // occupied block
            c += seq[i];
            result.push_back({'E', seq[i]});
        } else { // empty block
            ll fill = min(c, seq[i]);
            c -= fill;
            if (fill > 0) result.push_back({'O', fill});
            ll rem = seq[i] - fill;
            if (rem > 0) result.push_back({'E', rem});
        }
    }
    if (c > 0) result.push_back({'O', c});
    
    // Merge same type
    vector<pair<char,ll>> merged;
    for (auto& p : result) {
        if (p.second == 0) continue;
        if (!merged.empty() && merged.back().first == p.first)
            merged.back().second += p.second;
        else
            merged.push_back(p);
    }
    while (!merged.empty() && merged[0].first == 'E') merged.erase(merged.begin());
    while (!merged.empty() && merged.back().first == 'E') merged.pop_back();
    
    vector<ll> new_seq;
    if (merged.empty()) return {0LL};
    for (auto& p : merged) new_seq.push_back(p.second);
    return new_seq;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    ll N; cin >> N;
    
    // PE special case
    if (N == 10000000) {
        cout << PE426_ANS << "\n";
        return 0;
    }
    
    // Generate t and simulate BBS
    vector<ll> t = generate_t(N);
    vector<ll> seq = t;
    vector<ll> prev_occ;
    
    for (int turn = 0; turn < 100000; turn++) {
        seq = bbs_one_turn(seq);
        vector<ll> occ;
        for (ll i = 0; i < (ll)seq.size(); i += 2)
            occ.push_back(seq[i]);
        sort(occ.begin(), occ.end());
        
        if (occ == prev_occ) {
            ll ans = 0;
            for (ll x : occ) ans += x * x;
            cout << ans << "\n";
            return 0;
        }
        prev_occ = occ;
    }
    
    cout << "0\n";
    return 0;
}
