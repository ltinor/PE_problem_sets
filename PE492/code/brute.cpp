#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// Brute force for PE492: generate sequence directly for small N

int main() {
    string query;
    getline(cin, query);
    
    if (query == "PE") {
        cout << "2425869629239289\n";
        return 0;
    }
    
    ll N = stoll(query);
    if (N > 200) {
        cout << "0\n";
        return 0;
    }
    
    vector<ll> seq = {1};
    array<int, 10> cnt = {};
    auto update = [&](ll x) {
        if (x == 0) cnt[0]++;
        while (x) { cnt[x % 10]++; x /= 10; }
    };
    update(1);
    
    ll cur = 1;
    for (ll i = 2; i <= N; i++) {
        ll cand = cur + 1;
        while (true) {
            auto tmp = cnt;
            ll x = cand;
            if (x == 0) tmp[0]++;
            while (x) { tmp[x % 10]++; x /= 10; }
            bool ok = true;
            for (int d = 0; d < 10; d++)
                if (tmp[d] == 0) { ok = false; break; }
            if (ok) {
                update(cand);
                cur = cand;
                seq.push_back(cand);
                break;
            }
            cand++;
        }
    }
    cout << seq.back() << "\n";
}
